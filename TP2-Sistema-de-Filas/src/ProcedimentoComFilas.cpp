#include "ProcedimentoComFilas.hpp"

// Construtor
ProcedimentoComFilas::ProcedimentoComFilas(double tempoMedioExecucao, int unidadesDisponiveis, int capacidadeFila)
    : Procedimento(tempoMedioExecucao, unidadesDisponiveis) {
    filaVermelha.inicializa(capacidadeFila);
    filaAmarela.inicializa(capacidadeFila);
    filaVerde.inicializa(capacidadeFila);
}

// Adicionar paciente em uma fila especifica
void ProcedimentoComFilas::adicionarPacienteNaFila(Paciente* paciente) {
    int grauUrgencia = paciente->getGrauUrgencia();
    if (grauUrgencia == 2) {
        filaVermelha.enfileira(paciente);
    } else if (grauUrgencia == 1) {
        filaAmarela.enfileira(paciente);
    } else {
        filaVerde.enfileira(paciente);
    }
}

// Obter o proximo paciente da fila
Paciente* ProcedimentoComFilas::obterProximoPaciente() {
    if (!filaVermelha.filaVazia()) {
        return filaVermelha.desenfileira();
    } else if (!filaAmarela.filaVazia()) {
        return filaAmarela.desenfileira();
    } else if (!filaVerde.filaVazia()) {
        return filaVerde.desenfileira();
    }
    return nullptr;
}

// Verificar se todas as filas estao vazias
bool ProcedimentoComFilas::filaVazia() const {
    return filaVermelha.filaVazia() && filaAmarela.filaVazia() && filaVerde.filaVazia();
}

// Finalizar todas as filas
void ProcedimentoComFilas::finaliza() {
    filaVermelha.finaliza();
    filaAmarela.finaliza();
    filaVerde.finaliza();
}
