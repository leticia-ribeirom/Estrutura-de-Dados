#include "Procedimento.hpp"
#include <iostream>
#include <stdexcept>

// Construtor
Procedimento::Procedimento(double tempoMedioExecucao, int unidadesDisponiveis)
    : tempoMedioExecucao(tempoMedioExecucao), unidadesDisponiveis(unidadesDisponiveis), unidadesOcupadas(0) {}

// Metodos
bool Procedimento::estaDisponivel() const {
    return unidadesOcupadas < unidadesDisponiveis;
}

// Ocupa uma unidade
void Procedimento::ocuparUnidade() {
    if (estaDisponivel()) {
        unidadesOcupadas++;
    }
}

// Libera uma unidade
void Procedimento::liberarUnidade() {
    if (unidadesOcupadas > 0) {
        unidadesOcupadas--;
    }
}

//------------------------------- Metodos de Acesso ------------------------------------//
double Procedimento::getTempoMedioExecucao() const {
    return tempoMedioExecucao;
}

int Procedimento::getUnidadesDisponiveis() const {
    return unidadesDisponiveis;
}

int Procedimento::getUnidadesOcupadas() const {
    return unidadesOcupadas;
}