#include "SistemaBusca.hpp"
#include <sstream>
#define MAX_RESULTADOS 1000

// Construtor que inicializa o sistema de busca, alocando memória para o vetor de voos
SistemaBusca::SistemaBusca(int capacidade) : tamanho(0) {
    voos = new DadosViagem[capacidade]; 
}

// Destruidor que libera a memória alocada para os voos
SistemaBusca::~SistemaBusca() {
    delete[] voos;
}

// Adiciona um voo ao vetor e atualiza todos os índices de busca
void SistemaBusca::adicionarVoo(const DadosViagem& voo, int indice) {
    voos[indice] = voo;                                 // Armazena o voo no vetor
    indiceOrigem.inserir(voo.getPartida(), indice);     // Insere no índice de origem
    indiceDestino.inserir(voo.getDestino(), indice);    // Insere no índice de destino
    indicePreco.inserir(voo.getPreco(), indice);        // Insere no índice de preço
    indiceAssentos.inserir(voo.getAssentos(), indice);  // Insere no índice de assentos
    indiceDuracao.inserir(voo.getDuracao(), indice);    // Insere no índice de duração
    indiceConexoes.inserir(voo.getConexoes(), indice);  // Insere no índice de conexões
    std::string dataHoraPartida = voo.getDataPartida() + voo.getHoraPartida();  
    indiceDataPartida.inserir(dataHoraPartida, indice); // Insere no índice de data e hora de partida
    std::string dataHoraChegada = voo.getDataChegada() + voo.getHoraChegada(); 
    indiceDataChegada.inserir(dataHoraChegada, indice); // Insere no índice de data e hora de chegada
    tamanho++;                                          // Incrementa o tamanho do vetor
}

// Método que verifica se as buscas satisfazem os filtros
void SistemaBusca::satisfazConsulta(const std::string& consulta, const char ordem[3], int maxResultados, int quantidadeVoos) {

    int buscas[MAX_RESULTADOS];
    int contadorBuscas = 0;
    int quantidadeIntersecao = 0;

    // Realiza a busca nos índices
    realizarBusca(consulta, buscas, contadorBuscas, quantidadeIntersecao);

    // Verifica as interseções do vetor buscas, insere no heap e imprime
    inserirNoHeap(buscas, contadorBuscas, ordem, quantidadeIntersecao, maxResultados);

    /*----------------------------------------------- Ponto Extra -----------------------------------------------
    // Verifica a união do vetor buscas, insere no heap e imprime
    std::cout << "União" << std::endl;
    inserirNoHeapUniao(buscas, contadorBuscas, ordem, quantidadeIntersecao, maxResultados);
    ------------------------------------------------------------------------------------------------------------*/
}

// Método que realiza todas as buscas
void SistemaBusca::realizarBusca(const std::string& consulta, int buscas[MAX_RESULTADOS], int& contadorBuscas, int& quantidadeIntersecao) {
    int escolha = 0;
    std::string operadorEncontrado;
    std::string valor;

    /*---------------------------------------- Verifica a duração ------------------------------------------------*/
    if (extrairDaConsulta(consulta, "dur>=", operadorEncontrado, escolha)) {
        int contador = 0;
        int* indices = indiceDuracao.buscarInOrdemMaior(escolha, contador);
        adicionarIndicesIntersecao(indices, contador, quantidadeIntersecao, buscas, contadorBuscas);
    }
    if (extrairDaConsulta(consulta, "dur<=", operadorEncontrado, escolha)) {
        int contador = 0;
        int* indices = indiceDuracao.buscarInOrdemMenor(escolha, contador);
        adicionarIndicesIntersecao(indices, contador, quantidadeIntersecao, buscas, contadorBuscas);
    }
    if (extrairDaConsulta(consulta, "dur==", operadorEncontrado, escolha)) {
        int contador = 0;
        int* indices = indiceDuracao.buscarInOrdemIgual(escolha, contador);
        adicionarIndicesIntersecao(indices, contador, quantidadeIntersecao, buscas, contadorBuscas);
    }

    /*---------------------------------------- Verifica Número de assentos ------------------------------------------*/
    if (extrairDaConsulta(consulta, "sea>=", operadorEncontrado, escolha)) {
        int contador = 0;
        int* indices = indiceAssentos.buscarInOrdemMaior(escolha, contador);
        adicionarIndicesIntersecao(indices, contador, quantidadeIntersecao, buscas, contadorBuscas);
    }
    if (extrairDaConsulta(consulta, "sea<=", operadorEncontrado, escolha)) {
        int contador = 0;
        int* indices = indiceAssentos.buscarInOrdemMenor(escolha, contador);
        adicionarIndicesIntersecao(indices, contador, quantidadeIntersecao, buscas, contadorBuscas);
    }
    if (extrairDaConsulta(consulta, "sea==", operadorEncontrado, escolha)) {
        int contador = 0;
        int* indices = indiceAssentos.buscarInOrdemIgual(escolha, contador);
        adicionarIndicesIntersecao(indices, contador, quantidadeIntersecao, buscas, contadorBuscas);
    }

    /*---------------------------------------- Verifica o destino ------------------------------------------------*/
    if (extrairDaConsultaString(consulta, "dst==", operadorEncontrado, valor)) {
        int contador = 0;
        int* indices = indiceDestino.buscarInOrdem(valor, contador);
        adicionarIndicesIntersecao(indices, contador, quantidadeIntersecao, buscas, contadorBuscas);
    }

    /*---------------------------------------- Verifica a origem ------------------------------------------------*/
    if (extrairDaConsultaString(consulta, "org==", operadorEncontrado, valor)) {
        int contador = 0;
        int* indices = indiceOrigem.buscarInOrdem(valor, contador);
        adicionarIndicesIntersecao(indices, contador, quantidadeIntersecao, buscas, contadorBuscas);
    }

    /*---------------------------------------- Verifica o preço ------------------------------------------------*/
    if (extrairDaConsulta(consulta, "prc>=", operadorEncontrado, escolha)) {
        int contador = 0;
        int* indices = indicePreco.buscarInOrdemMaior(escolha, contador);
        adicionarIndicesIntersecao(indices, contador, quantidadeIntersecao, buscas, contadorBuscas);
    }
    if (extrairDaConsulta(consulta, "prc<=", operadorEncontrado, escolha)) {
        int contador = 0;
        int* indices = indicePreco.buscarInOrdemMenor(escolha, contador);
        adicionarIndicesIntersecao(indices, contador, quantidadeIntersecao, buscas, contadorBuscas);
    }
    if (extrairDaConsulta(consulta, "prc==", operadorEncontrado, escolha)) {
        int contador = 0;
        int* indices = indicePreco.buscarInOrdemIgual(escolha, contador);
        adicionarIndicesIntersecao(indices, contador, quantidadeIntersecao, buscas, contadorBuscas);
    }

    /*---------------------------------------- Verifica a data e hora de partida ---------------------------------*/
    if (extrairDaConsultaString(consulta, "dep==", operadorEncontrado, valor)) {
        int contador = 0;
        int* indices = indiceDataPartida.buscarInOrdem(valor, contador);
        adicionarIndicesIntersecao(indices, contador, quantidadeIntersecao, buscas, contadorBuscas);
    }

    /*---------------------------------------- Verifica a data e hora de chegada ---------------------------------*/
    if (extrairDaConsultaString(consulta, "arr==", operadorEncontrado, valor)) {
        int contador = 0;
        int* indices = indiceDataChegada.buscarInOrdem(valor, contador);
        adicionarIndicesIntersecao(indices, contador, quantidadeIntersecao, buscas, contadorBuscas);
    }

    /*---------------------------------------- Verifica a quantidade de conexões ----------------------------------*/
    if (extrairDaConsulta(consulta, "sto>=", operadorEncontrado, escolha)) {
        int contador = 0;
        int* indices = indiceConexoes.buscarInOrdemMaior(escolha, contador);
        if (indices != nullptr) {
            quantidadeIntersecao++;
            for (int i = 0; i < contador; i++) {
                buscas[contadorBuscas++] = indices[i];
            }
        }
    }
    if (extrairDaConsulta(consulta, "sto<=", operadorEncontrado, escolha)) {
        int contador = 0;
        int* indices = indiceConexoes.buscarInOrdemMenor(escolha, contador);
        adicionarIndicesIntersecao(indices, contador, quantidadeIntersecao, buscas, contadorBuscas);
    }
    if (extrairDaConsulta(consulta, "sto==", operadorEncontrado, escolha)) {
        int contador = 0;
        int* indices = indiceConexoes.buscarInOrdemIgual(escolha, contador);
        adicionarIndicesIntersecao(indices, contador, quantidadeIntersecao, buscas, contadorBuscas);
    }
}

// Método que insere no heap e chama a impressão dos resultados
void SistemaBusca::inserirNoHeap(int buscas[MAX_RESULTADOS], int contadorBuscas, const char ordem[3], int quantidadeIntersecao, int maxResultados) {
    HeapSort heap(contadorBuscas, ordem);
    int contagem[MAX_RESULTADOS] = {0};  // Vetor auxiliar para contar as repetições

    // Contar a quantidade de repetições de cada voo
    for (int i = 0; i < contadorBuscas; i++) {
        contagem[buscas[i]]++;
    }

    // Inserir no heap apenas os voos que aparecem exatamente 'quantidadeIntersecao' vezes
    for (int i = 0; i < contadorBuscas; i++) {
        if (buscas[i] < MAX_RESULTADOS && contagem[buscas[i]] == quantidadeIntersecao) {
            heap.inserir(voos[buscas[i]]);
            contagem[buscas[i]] = 0; // Evita inserção duplicada
        }
    }

    // Imprimir os dados dos voos
    for (int i = 0; i < maxResultados && !heap.vazio(); i++) {
        DadosViagem voo = heap.remover();
        imprimirVooFormatado(voo);
    }
}

// Imprime as informações do voo de forma formatada
void SistemaBusca::imprimirVooFormatado(const DadosViagem& voo) {
    std::cout << voo.getPartida() << " " << voo.getDestino() << " "
              << voo.getPreco() << " " << voo.getAssentos() << " "
              << voo.getDataPartida() << "T" << voo.getHoraPartida() << " "
              << voo.getDataChegada() << "T" << voo.getHoraChegada() << " "
              << voo.getConexoes() << std::endl;
}

// Extrai um valor numérico após um operador na consulta
bool SistemaBusca::extrairDaConsulta(const std::string& consulta, const std::string& operador, std::string& operadorEncontrado, int& valor) {
    size_t pos = 0;
    
    // Percorre a string manualmente para procurar o operador
    while (pos < consulta.length()) {
        bool operadorEncontradoLocal = true;
        
        // Verifica se a substring a partir da posição 'pos' corresponde ao operador
        for (size_t i = 0; i < operador.length(); i++) {
            if (consulta[pos + i] != operador[i]) {
                operadorEncontradoLocal = false;
                break;
            }
        }

        // Se o operador foi encontrado, extrai o valor e retorna o operador e o valor
        if (operadorEncontradoLocal) {
            operadorEncontrado = operador;  // Armazena o operador encontrado
            pos += operador.length();       // Avança para o próximo caractere (após o operador)

            // Extrai o número que está após o operador
            std::string numero;
            while (pos < consulta.length() && std::isdigit(consulta[pos])) {
                numero += consulta[pos];
                pos++;
            }

            if (!numero.empty()) {
                valor = std::stoi(numero);  // Converte o número para inteiro
                return true;
            }
        } else {
            pos++;                          // Avança para o próximo caractere se o operador não foi encontrado
        }
    }

    return false;                           // Retorna falso se o operador não foi encontrado
}

// Extrai uma string após um operador (como 'dst==') na consulta
bool SistemaBusca::extrairDaConsultaString(const std::string& consulta, const std::string& operador, std::string& operadorEncontrado, std::string& valor) {
    size_t pos = 0;

    // Percorre a string manualmente para procurar o operador
    while (pos < consulta.length()) {
        bool operadorEncontradoLocal = true;

        // Verifica se a substring a partir da posição 'pos' corresponde ao operador
        for (size_t i = 0; i < operador.length(); i++) {
            if (consulta[pos + i] != operador[i]) {
                operadorEncontradoLocal = false;
                break;
            }
        }

        // Se o operador foi encontrado, extrai a string e retorna o operador e o valor
        if (operadorEncontradoLocal) {
            operadorEncontrado = operador;  // Armazena o operador encontrado
            pos += operador.length();       // Avança para o próximo caractere (após o operador)

            // Extrai a string que está após o operador
            std::string texto;
            while (pos < consulta.length() && (isalnum(consulta[pos]) || consulta[pos] == '_')) { // Permite letras, números e underline
                texto += consulta[pos];
                pos++;
            }

            if (!texto.empty()) {
                valor = texto;              // Armazena a string extraída
                return true;
            }
        } else {
            pos++;                          // Avança para o próximo caractere se o operador não foi encontrado
        }
    }
    return false;                           // Retorna falso se o operador não foi encontrado
}

// Método para adicionar os índices que correspondem aos filtros buscados em um vetor de interseção
void SistemaBusca::adicionarIndicesIntersecao(int* indices, int contador, int& quantidadeIntersecao, int* buscas, int& contadorBuscas) {
    if (indices != nullptr) {
        quantidadeIntersecao++;
        for (int i = 0; i < contador; i++) {
            buscas[contadorBuscas++] = indices[i];
        }
    }
}
/*----------------------------------------------- Ponto Extra -----------------------------------------------------
void SistemaBusca::inserirNoHeapUniao(int buscas[MAX_RESULTADOS], int contadorBuscas, const char ordem[3], int quantidadeIntersecao, int maxResultados) {
    HeapSort heap(contadorBuscas, ordem);
    bool jaInserido[MAX_RESULTADOS] = {false};  // Vetor auxiliar para verificar se o voo já foi inserido no heap

    // Inserir no heap os voos da interseção, garantindo que cada voo seja inserido no máximo uma vez
    for (int i = 0; i < contadorBuscas; i++) {
        if (buscas[i] < MAX_RESULTADOS && !jaInserido[buscas[i]]) {
            heap.inserir(voos[buscas[i]]);
            jaInserido[buscas[i]] = true;  // Marca que o voo já foi inserido
        }
    }

    // Imprimir os dados dos voos
    for (int i = 0; i < maxResultados && !heap.vazio(); i++) {
        DadosViagem voo = heap.remover();
        imprimirVooFormatado(voo);
    }
}
-----------------------------------------------------------------------------------------------------------------*/