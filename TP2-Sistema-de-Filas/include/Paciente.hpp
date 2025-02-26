#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include <string>
#include <ctime>
#include <iomanip>

class Paciente {
private:
    int id;                                 // Identificador unico do paciente
    int alta;                               // Indicador se o paciente teve alta (0 ou 1)
    int ano, mes, dia;                      // Data e hora de admissão
    float hora;

    int ano_h, mes_h, dia_h;                // Variavel de controle: Data no hospital ate alta
    float hora_h, minutos_h;                // Variavel de controle: Tempo no no hospital ate alta
    float tempoControleHoras;               // Variavel de controle para pacientes que passaram mais de um dia no hospital
    
    int estadoAtual;                        // Estado atual do paciente
    int grauUrgencia;                       // Grau de urgencia: 0 (verde), 1 (amarelo), 2 (vermelho)

    float medidasHospitalares;              // Tempo gasto em medidas hospitalares
    float testesLaboratorio;                // Tempo gasto de testes laboratoriais
    float examesImagem;                     // Tempo gasto em exames de imagem
    float instrumentos;                     // Tempo gasto em instrumentos/medicamentos

    float tempoMinimoPermanencia;           // Tempo minimo de permanencia no hospital
    float tempoTotalPermanencia;            // Tempo total de permanencia

public:

    // Construtor Padrao
    Paciente ();

    // Construtor
    Paciente(int id, int alta, int ano, int mes, int dia, float hora, int grauUrgencia,
             float medidasHospitalares, float testesLaboratorio, float examesImagem, float instrumentos);
    
    // Metodos para atualizar o estado do paciente no hospital
    void setEstado(int novoEstado);

    // Atualizar tempo total de Permanencia desde a entrada
    void setPermanencia(float novoTempoPermanencia);

    // Resetar o relogio caso o paciente ultrapasse as 24hrs
    void setControleHoras (float novoControleHoras);

    // Atualizar horas conforme se passam os dias do paciente no hospital
    void setAno_H(int novoAno);
    void setMes_H(int novoMes);
    void setDia_H(int novoDia);
    void setHora_H(float novaHora);
    void setMinutos_H(float novoMinuto);
    float getControleHoras() const;


    // Metodo para calcular o tempo minimo de permanencia no hospital
    float calcularTempoMinimoHospital(float tempoTriagem, float tempoAtendimento, float tempomh, float tempotl, 
    float tempoei, float tempoim, int medidasHospitalares, int testesLaboratorio, int examesImagem, int instrumentos);

    // Metodos de acesso para dados de entrada do paciente
    int getId() const;
    int getAlta() const;
    int getMes() const;
    int getDia() const;
    float getHora() const;
    int getAno() const;

    // Metodos de acesso para dados de saida do paciente
    int getAno_H() const;
    int getMes_H() const;
    int getDia_H() const;
    float getHora_H() const;
    float getMinutos_H() const;

    // Metodos de acesso para dados do paciente durante o periodo no hospital
    int getEstadoAtual() const;
    int getGrauUrgencia() const;
    float getMedidasHospitalares() const;
    float getTestesLaboratorio() const;
    float getExamesImagem() const;
    float getInstrumentos() const;
    
    // Metodos para a saida final
    float getTempoMinimoHospital() const;
    float getTempoTotalPermanencia() const;
};

#endif // PACIENTE_HPP
