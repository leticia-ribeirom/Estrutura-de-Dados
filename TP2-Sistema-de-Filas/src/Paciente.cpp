#include "Paciente.hpp"
#include <cmath> 

// Construtor Padrao
Paciente::Paciente()
    : id(0), alta(0), ano(0), mes(0), dia(0), hora(0), ano_h (0), mes_h(0), dia_h(0), hora_h(0.0), minutos_h(0.0),
    tempoControleHoras (0.0), estadoAtual(0), grauUrgencia(0), medidasHospitalares(0), testesLaboratorio(0), examesImagem(0), 
    instrumentos(0), tempoMinimoPermanencia (0.0),tempoTotalPermanencia (0.0) {}

// Construtor
Paciente::Paciente(int id, int alta, int ano, int mes, int dia, float hora, int grauUrgencia,
                   float medidasHospitalares, float testesLaboratorio, float examesImagem, float instrumentos)
    : id(id), alta(alta), ano(ano), mes(mes), dia(dia), hora(hora), ano_h (ano), mes_h(mes), dia_h(dia), 
    hora_h(hora), minutos_h(0), tempoControleHoras (hora), estadoAtual(0), grauUrgencia(grauUrgencia), 
    medidasHospitalares(medidasHospitalares), testesLaboratorio(testesLaboratorio), 
    examesImagem(examesImagem), instrumentos(instrumentos), tempoMinimoPermanencia (0.0), 
    tempoTotalPermanencia (0.0) {}

// Metodo para atualizar os estados
void Paciente::setEstado(int novoEstado) {
    estadoAtual = novoEstado;
}

// Atualizar tempo total de Permanencia desde a entrada
void Paciente::setPermanencia(float novoTempoPermanencia) {
    if (getAlta() == 1 && getEstadoAtual() < 2){
        this->tempoTotalPermanencia += novoTempoPermanencia;
    } else if (getAlta() == 0) {
        this->tempoTotalPermanencia += novoTempoPermanencia;
    }

    this->tempoControleHoras += novoTempoPermanencia;
    tempoTotalPermanencia = std::round(tempoTotalPermanencia * 100) / 100.0;
    tempoControleHoras = std::round(tempoControleHoras * 100) / 100.0;
}

// Resetar o relogio caso o paciente ultrapasse as 24hrs
void Paciente::setControleHoras (float novoControleHoras){
    this->tempoControleHoras = novoControleHoras;
}

//------------- Atualizar horas conforme se passam os dias do paciente no hospital ----------------------//
void Paciente::setAno_H(int novoAno) {
    this->ano_h = novoAno;
}

void Paciente::setMes_H(int novoMes) {
    this->mes_h = novoMes;
}
void Paciente::setDia_H(int novoDia) {
    this->dia_h = novoDia;
}
void Paciente::setHora_H(float novaHora) {
    this->hora_h = novaHora;
}
void Paciente::setMinutos_H(float novoMinuto) {
    this->minutos_h = novoMinuto;
}

//---------------------- Metodo para calcular o tempo mínimo de atendimento -----------------------------------//
float Paciente::calcularTempoMinimoHospital(float tempoTriagem, float tempoAtendimento, float tempomh, float tempotl, 
    float tempoei, float tempoim, int medidasHospitalares, int testesLaboratorio, int examesImagem, int instrumentos) {
    
    // Calculando o tempo total de atendimento
    tempoMinimoPermanencia += tempoTriagem;                         // Tempo de triagem
    tempoMinimoPermanencia += tempoAtendimento;                     // Tempo de atendimento
    tempoMinimoPermanencia += tempomh * medidasHospitalares;        // Tempo de medidas hospitalares
    tempoMinimoPermanencia += tempotl * testesLaboratorio;          // Tempo de testes laboratoriais
    tempoMinimoPermanencia += tempoei * examesImagem;               // Tempo de exames de imagem
    tempoMinimoPermanencia += tempoim * instrumentos;               // Tempo de instrumentos/medicamentos
    
    return tempoMinimoPermanencia;
}

//------------------------- Metodos de acesso para dados de admissão do paciente ----------------------------//
int Paciente::getId() const {
    return id;
}

int Paciente::getAlta() const{
    return alta;
}

int Paciente::getMes() const {
    return mes;
}

int Paciente::getDia() const {
    return dia;
}

float Paciente::getHora() const {
    return hora;
}

int Paciente::getAno() const {
    return ano;
}

//-------------------Metodos de acesso para os dados do paciente durante o periodo no hospital------------------//

int Paciente::getAno_H() const {
    return ano_h;
}

int Paciente::getMes_H() const {
    return mes_h;
}
int Paciente::getDia_H() const {
    return dia_h;
}
float Paciente::getHora_H() const {
    return hora_h;
}
float Paciente::getMinutos_H() const {
    return minutos_h;
}
int Paciente::getEstadoAtual() const {
    return estadoAtual;
}
float Paciente::getControleHoras() const {
    return tempoControleHoras;
}

//-------------------Metodos de acesso para os dados de procedimentos dos pacientes------------------//
int Paciente::getGrauUrgencia() const {
    return grauUrgencia;
}

float Paciente::getMedidasHospitalares() const {
    return medidasHospitalares;
}

float Paciente::getTestesLaboratorio() const {
    return testesLaboratorio;
}

float Paciente::getExamesImagem() const {
    return examesImagem;
}

float Paciente::getInstrumentos() const {
    return instrumentos;
}

//------------------ Metodos de acesso dos dados do paciente para calculo da saida final ------------------//
float Paciente::getTempoMinimoHospital() const {
    return tempoMinimoPermanencia;
}

float Paciente::getTempoTotalPermanencia() const {
    return tempoTotalPermanencia;
}

