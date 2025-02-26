#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip> // Para std::fixed e std::setprecision
#include <cmath>   // Para std::round e std::abs
#include "AjustarSaidaPaciente.hpp"
#include "Escalonador.hpp"
#include "Fila.hpp"
#include "Paciente.hpp"
#include "Procedimento.hpp"
#include "ProcedimentoComFilas.hpp"
#include "TempoOcioso.hpp"

//--------------------------------- Ajustar tempo para que fique entre 0 e 24hr -----------------------------//
float ajustarTempoParaNovoDia(Paciente* paciente, float& tempoConclusao) {
    // Ajusta a hora para dentro de um único dia

    while (paciente->getControleHoras() >= 24.0 || tempoConclusao >= 24.0) {
    // Reduz 24 horas de tempoConclusao, se necessário
        if (tempoConclusao >= 24.0) {
            tempoConclusao -= 24.0;
        }

        // Reduz 24 horas de controleHoras, para começar um novo dia no hospital
        if (paciente->getControleHoras() >= 24.0) {
            paciente->setControleHoras(paciente->getControleHoras() - 24.0);
        }
        
        // Atualiza o dia, mes e ano do paciente
        int novoDia = paciente->getDia_H() + 1;
        int novoMes = paciente->getMes_H();
        int novoAno = paciente->getAno_H();

        // Arrays para o número de dias de cada mes (considerando anos nao bissextos)
        int diasPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // Verificar se o ano e bissexto e ajustar fevereiro
        if ((paciente->getAno_H() % 4 == 0 && paciente->getAno_H() % 100 != 0) || (paciente->getAno_H() % 400 == 0)) {
            diasPorMes[1] = 29;
        }

        // Verificar se o dia ultrapassa os dias do mes
        if (novoDia > diasPorMes[novoMes - 1]) {
            novoDia = 1;
            novoMes++;

            // Se passar de dezembro, ajusta para o proximo ano
            if (novoMes > 12) {
                novoMes = 1;
                novoAno++;
            }
        }

        // Atualiza os dados do paciente com o novo dia, mes e ano
        paciente->setDia_H(novoDia);
        paciente->setMes_H(novoMes);
        paciente->setAno_H(novoAno);
    }

    // Arredonda o tempo restante para 2 casas decimais
    tempoConclusao = std::round(tempoConclusao * 100) / 100.0;
    // Retorna o tempoConclusao ajustado
    return tempoConclusao;
}

//--------------------------------- Funções para serem executadas durante o While ----------------------------------------------------//
// Função que atualiza o estado de um paciente em um procedimento
void atualizarEstadoPaciente(Paciente* paciente, Procedimento& procedimento, float tempoAtual, float duracao, 
                            Escalonador& escalonador) {
    // Marca o procedimento como ocupado
    procedimento.ocuparUnidade();
    
    // Define a permanência do paciente com base na duracao do procedimento
    paciente->setPermanencia(duracao);
    
    // Calcula o tempo de conclusao do procedimento
    float tempoConclusao = tempoAtual + duracao;
    
    // Ajusta o tempo de conclusao para refletir um novo dia, se necessario
    ajustarTempoParaNovoDia(paciente, tempoConclusao);
    
    // Insere um evento no escalonador indicando a conclusao do procedimento
    escalonador.insereEvento(paciente->getAno_H(), paciente->getMes_H(), paciente->getDia_H(), tempoConclusao, paciente);
    
    // Atualiza o estado atual do paciente para o proximo estagio
    paciente->setEstado(paciente->getEstadoAtual() + 1);
}

// / Funcao que escolhe o tempo necessario para um procedimento especifico com base no tipo
float procedimentoEscolhido (Paciente* proximo, float n){
    if (n == 2){
        return proximo->getMedidasHospitalares();
    } else if (n == 3){
        return proximo->getTestesLaboratorio();
    } else if (n == 4) {
        return proximo->getExamesImagem();
    } else if (n == 5){
        return proximo->getInstrumentos();
    } else {
        return n;
    }
}

// Funcao que libera um procedimento ocupado e processa o proximo paciente na fila
void liberarProcedimentoEProcessarProximo(ProcedimentoComFilas& procedimento, float duracao, int anoAtual, int mesAtual, 
                                        int diaAtual, float tempoAtual, Escalonador& escalonador) {
    // Libera a unidade do procedimento
    procedimento.liberarUnidade();

    // Verifica se ha pacientes aguardando na fila
    if (!procedimento.filaVazia()) {
        // Obtém o proximo paciente da fila
        Paciente* proximo = procedimento.obterProximoPaciente();

        // Calcula o tempo ocioso do paciente
        TempoOcioso tempoOcioso;
        tempoOcioso.setEntrada(proximo->getAno_H(), proximo->getMes_H(), proximo->getDia_H(), proximo->getHora_H());
        tempoOcioso.setSaida(anoAtual, mesAtual, diaAtual, tempoAtual);
        float tempoEspera = tempoOcioso.calcularTempoOcioso();

        // Marca o procedimento como ocupado
        procedimento.ocuparUnidade();

        // Define a permanencia do paciente, somando o tempo de espera e o tempo necessario para o procedimento
        proximo->setPermanencia(tempoEspera + procedimentoEscolhido(proximo, duracao));

        // Calcula o tempo de conclusao do procedimento
        float tempoConclusao = tempoAtual + procedimentoEscolhido(proximo, duracao);

        // Ajusta o tempo de conclusao para refletir um novo dia, se necessario
        ajustarTempoParaNovoDia(proximo, tempoConclusao);

        // Atualiza o estado atual do paciente para o proximo estagio
        proximo->setEstado(proximo->getEstadoAtual() + 1);

        // Insere um evento no escalonador
        escalonador.insereEvento(proximo->getAno_H(), proximo->getMes_H(), proximo->getDia_H(), tempoConclusao, proximo);
    }
}

// Funcao que processa a entrada de um paciente na fila de um procedimento
void processarEntradaNaFila(Paciente* paciente, float tempoAtual, int anoAtual, int mesAtual, 
                            int diaAtual, ProcedimentoComFilas& procedimento) {
    // Atualiza os dados do paciente com a data e hora atuais
    paciente->setHora_H(tempoAtual);
    paciente->setAno_H(anoAtual);
    paciente->setMes_H(mesAtual);
    paciente->setDia_H(diaAtual);
    
    // Insere o paciente na fila
    procedimento.adicionarPacienteNaFila(paciente);
}

int main(int argc, char* argv[]) {
    // Verifica se o numero de argumentos esta correto
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>" << std::endl;
        return 1;
    }

    // Abre o arquivo de entrada
    std::ifstream arquivo(argv[1]);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << argv[1] << std::endl;
        return 1;
    }

    // Ler os parametros iniciais do arquivo
    float tempoTriagem, tempoAtendimento, tempomh, tempotl, tempoei, tempoim;
    int numeroTriagem, numeroAtendimento, numeromh, numerotl, numeroei, numeroim, numeroPacientes;

    // Ler parametros do arquivo
    arquivo >> tempoTriagem >> numeroTriagem;
    arquivo >> tempoAtendimento >> numeroAtendimento;
    arquivo >> tempomh >> numeromh;
    arquivo >> tempotl >> numerotl;
    arquivo >> tempoei >> numeroei;
    arquivo >> tempoim >> numeroim;
    arquivo >> numeroPacientes;

    // Inicializa estruturas
    Escalonador escalonador;
    escalonador.inicializa();

    // Procedimentos
    Procedimento triagem(tempoTriagem, numeroTriagem);
    ProcedimentoComFilas atendimento (tempoAtendimento, numeroAtendimento, numeroPacientes);
    ProcedimentoComFilas medidas(tempomh, numeromh, numeroPacientes);
    ProcedimentoComFilas testes(tempotl, numerotl, numeroPacientes);
    ProcedimentoComFilas exames(tempoei, numeroei, numeroPacientes);
    ProcedimentoComFilas instrumentos (tempoim, numeroim, numeroPacientes);

    // Fila unica para triagem
    Fila filaTriagem;
    filaTriagem.inicializa (numeroPacientes);

    // Criando um array de ponteiros de Paciente
    Paciente* pacientes[numeroPacientes];

    // Criar paciente
    for (int i = 0; i < numeroPacientes; i++) {
        int id;
        int alta, ano, mes, dia, grauUrgencia;
        float hora, medidasHospitalares, testesLaboratorio, examesImagem, instrumentos;
        arquivo >> id >> alta >> ano >> mes >> dia >> hora >> grauUrgencia >> medidasHospitalares 
            >> testesLaboratorio >> examesImagem >> instrumentos;

        if (alta == 1) {
            medidasHospitalares = 0;
            testesLaboratorio = 0;
            examesImagem = 0;
            instrumentos = 0;

            pacientes[i] = new Paciente(id, alta, ano, mes, dia, hora, grauUrgencia, (tempomh * medidasHospitalares), 
                (tempotl * testesLaboratorio), (tempoei * examesImagem), (tempoim * instrumentos));
            
            // Calculando o tempo minimo de permanencia 
            pacientes[i]->calcularTempoMinimoHospital(tempoTriagem, tempoAtendimento, tempomh, tempotl, 
                tempoei, tempoim, medidasHospitalares, testesLaboratorio, examesImagem, instrumentos);
        }
        else {
            // Criando o paciente e armazenando no array
            pacientes[i] = new Paciente(id, alta, ano, mes, dia, hora, grauUrgencia, (tempomh * medidasHospitalares), 
                (tempotl * testesLaboratorio), (tempoei * examesImagem), (tempoim * instrumentos));
            
            // Calculando o tempo minimo de permanencia
            pacientes[i]->calcularTempoMinimoHospital(tempoTriagem, tempoAtendimento, tempomh, tempotl, 
                tempoei, tempoim, medidasHospitalares, testesLaboratorio, examesImagem, instrumentos);
        }
        
        // Insere evento no escalonador
        escalonador.insereEvento(ano, mes, dia, hora, pacientes[i]);
    }

    arquivo.close();

    // Simulação principal
    
    // Variaveis de controle (principalmente para os calculos de tempo em espera nas filas)
    float tempoAtual = 0.0;
    int anoAtual = 0;
    int diaAtual = 0;
    int mesAtual = 0;

    TempoOcioso tempoOcioso;  // Instanciando um objeto da classe TempoOcioso

    while (!escalonador.vazio() || (!filaTriagem.filaVazia() && !atendimento.filaVazia() 
        && !medidas.filaVazia() && !testes.filaVazia() && !exames.filaVazia() && !instrumentos.filaVazia())) {

        tempoAtual = escalonador.getProximoTempo();
        anoAtual = escalonador.getProximoAno();
        mesAtual = escalonador.getProximoMes();
        diaAtual = escalonador.getProximoDia();

        // Processar eventos no tempo atual
        while (!escalonador.vazio() && escalonador.getProximoTempo() == tempoAtual){

            Evento eventoAtual = escalonador.retiraProximoEvento();
            Paciente* paciente = eventoAtual.paciente;

            switch (paciente->getEstadoAtual()) {
                
                case 0: {  // Paciente em triagem
                
                    if (triagem.estaDisponivel()) {
                        atualizarEstadoPaciente(paciente, triagem, tempoAtual, tempoTriagem, escalonador);
                    } else {
                        paciente->setHora_H (tempoAtual);
                        paciente->setAno_H (anoAtual);
                        paciente->setMes_H (mesAtual);
                        paciente->setDia_H (diaAtual);
                        filaTriagem.enfileira(paciente);
                    }
                    break;
                }
                case 1: {  // Paciente em atendimento
                    
                    triagem.liberarUnidade();
                    
                    if (!filaTriagem.filaVazia()) {
                        Paciente* proximo = filaTriagem.desenfileira();
                        tempoOcioso.setEntrada(proximo->getAno_H(), proximo->getMes_H(), proximo->getDia_H(), proximo->getHora_H());
                        tempoOcioso.setSaida(anoAtual, mesAtual, diaAtual, tempoAtual);
                        float tempoEspera = tempoOcioso.calcularTempoOcioso();
                        triagem.ocuparUnidade();
                        proximo->setPermanencia(tempoEspera + tempoTriagem);
                        float tempoConclusao = tempoAtual + tempoTriagem;
                        ajustarTempoParaNovoDia(proximo, tempoConclusao);
                       
                        escalonador.insereEvento(proximo->getAno_H(), proximo->getMes_H(), proximo->getDia_H(), tempoConclusao, proximo);
                        proximo->setEstado(1); // Atualiza para o próximo estado

                    }

                    if (atendimento.estaDisponivel()) {
                        atualizarEstadoPaciente(paciente, atendimento, tempoAtual, tempoAtendimento, escalonador);
                    } else {                        
                        processarEntradaNaFila(paciente, tempoAtual, anoAtual, mesAtual, diaAtual, atendimento);
                    }
                    break;

                }
                case 2: { // Paciente em medidas
                
                    liberarProcedimentoEProcessarProximo(atendimento, tempoAtendimento, anoAtual, mesAtual, diaAtual, tempoAtual, escalonador);    
                    
                    /*------------------------------- PONTO EXTRA ---------------------------------------------------------/
                    // Paciente que recebem alta logo após o atendimento, vai direto para estado de finalizado
                    if (paciente->getAlta() == 1){
                        paciente->setEstado(7);
                        break;
                    }------------------------------------------------------------------------------------------------------*/
                    
                    if (medidas.estaDisponivel()) {
                        atualizarEstadoPaciente(paciente, medidas, tempoAtual, paciente->getMedidasHospitalares(), escalonador);
                    } else {
                        processarEntradaNaFila(paciente, tempoAtual, anoAtual, mesAtual, diaAtual, medidas);
                    }
                    break;
                }
                case 3: { // Paciente em testes
                    
                    liberarProcedimentoEProcessarProximo(medidas, 2, anoAtual, mesAtual, diaAtual, tempoAtual, escalonador);    

                    if (testes.estaDisponivel()) {
                        atualizarEstadoPaciente(paciente, testes, tempoAtual, paciente->getTestesLaboratorio(), escalonador);
                    } else {
                        processarEntradaNaFila(paciente, tempoAtual, anoAtual, mesAtual, diaAtual, testes);
                    }
                    break;
                }
                case 4: { // Paciente em exames
                
                    liberarProcedimentoEProcessarProximo(testes, 3, anoAtual, mesAtual, diaAtual, tempoAtual, escalonador);
                    
                    if (exames.estaDisponivel()) {
                        atualizarEstadoPaciente(paciente, exames, tempoAtual, paciente->getExamesImagem(), escalonador);
                    } else {
                        processarEntradaNaFila(paciente, tempoAtual, anoAtual, mesAtual, diaAtual, exames);
                    }
                    break;
                }
                case 5: { // Paciente em Instrumentos
                    
                    liberarProcedimentoEProcessarProximo(exames, 4, anoAtual, mesAtual, diaAtual, tempoAtual, escalonador);

                    if (instrumentos.estaDisponivel()) {
                        atualizarEstadoPaciente(paciente, instrumentos, tempoAtual, paciente->getInstrumentos(), escalonador);
                    } else {
                        processarEntradaNaFila(paciente, tempoAtual, anoAtual, mesAtual, diaAtual, instrumentos);
                    }
                    break;

                }

                case 6: {
                    liberarProcedimentoEProcessarProximo(instrumentos, 5, anoAtual, mesAtual, diaAtual, tempoAtual, escalonador);
                }
                case 7: {
                    break;
                }

            }

        }
    
    }
    
    // Finalizar filas
    filaTriagem.finaliza();
    atendimento.finaliza();
    medidas.finaliza();
    testes.finaliza();
    exames.finaliza();
    instrumentos.finaliza();

    for (int i = 0; i < numeroPacientes; i++) {
    Paciente* paciente = pacientes[i];

    // Dados entrada
    std::ostringstream entradaFormatada;
    std::string dataEntrada = AjustarSaidaPaciente::getDiaSemanaEntrada(paciente);
    int diaEntrada = paciente->getDia();
    int horaEntrada = paciente->getHora();
    int anoEntrada = paciente->getAno();

    entradaFormatada << dataEntrada << " "  
                    << diaEntrada << " "
                    << std::setw(2) << std::setfill('0') << horaEntrada << ":00:00 " 
                    << anoEntrada;

    // Dados saída
    float tempoTotal = paciente->getTempoTotalPermanencia();
    AjustarSaidaPaciente::ajustarSaidaPaciente(paciente, tempoTotal);
    float tempoMinimo = paciente->getTempoMinimoHospital();
    float tempoOcioso = tempoTotal - tempoMinimo;

    int anoSaida = paciente->getAno_H(); 
    int diaSaida = paciente->getDia_H(); 
    int minutosSaida = paciente->getMinutos_H();

    // Corrigir formato de saída
    std::ostringstream saidaFormatada;
    std::string dataSaida = AjustarSaidaPaciente::getDiaSemanaSaida(paciente);
    saidaFormatada << dataSaida << " " 
                   << diaSaida << " "
                   << std::setw(2) << std::setfill('0') << paciente->getHora_H() << ":"
                   << std::setw(2) << std::setfill('0') << minutosSaida << ":00 "
                   << anoSaida;

    // Exibir saída formatada
    std::cout << std::fixed << std::setprecision(2);
    std::cout << paciente->getId() << " "
              << entradaFormatada.str() << " "
              << saidaFormatada.str() << " "
              << tempoTotal << " "
              << tempoMinimo << " "
              << tempoOcioso
              << std::endl;
    }

    // Liberar a memória alocada
    for (int i = 0; i < numeroPacientes; i++) {
        delete pacientes[i];
    }

    return 0;
}
/*--------------------------------------------------------- PONTO EXTRA -----------------------------------------------------------------
// Substitua as funções das linhas 70 e 107 por estas abaixo:

void atualizarEstadoPaciente(Paciente* paciente, Procedimento& procedimento, float tempoAtual, float duracao, Escalonador& escalonador) {
    if (duracao > 0){
        procedimento.ocuparUnidade();
        paciente->setPermanencia(duracao);
        float tempoConclusao = tempoAtual + duracao;
        ajustarTempoParaNovoDia(paciente, tempoConclusao);
        escalonador.insereEvento(paciente->getAno_H(), paciente->getMes_H(), paciente->getDia_H(), tempoConclusao, paciente);
    }
    paciente->setEstado(paciente->getEstadoAtual() + 1);
}

void liberarProcedimentoEProcessarProximo(ProcedimentoComFilas& procedimento, float duracao, int anoAtual, int mesAtual, int diaAtual, float tempoAtual, Escalonador& escalonador) {
    procedimento.liberarUnidade();
    if (!procedimento.filaVazia()) {
        Paciente* proximo = procedimento.obterProximoPaciente();
        TempoOcioso tempoOcioso;
        tempoOcioso.setEntrada(proximo->getAno_H(), proximo->getMes_H(), proximo->getDia_H(), proximo->getHora_H());
        tempoOcioso.setSaida(anoAtual, mesAtual, diaAtual, tempoAtual);
        float tempoEspera = tempoOcioso.calcularTempoOcioso();
        if (duracao > 0) {
            procedimento.ocuparUnidade();
            proximo->setPermanencia(tempoEspera + procedimentoEscolhido (proximo, duracao));
            float tempoConclusao = tempoAtual + procedimentoEscolhido (proximo, duracao);
            ajustarTempoParaNovoDia(proximo, tempoConclusao);            
            escalonador.insereEvento(proximo->getAno_H(), proximo->getMes_H(), proximo->getDia_H(), tempoConclusao, proximo);
        }
        proximo->setEstado(proximo->getEstadoAtual() + 1);
    }
} -----------------------------------------------------------------------------------------------------------------------------------------*/