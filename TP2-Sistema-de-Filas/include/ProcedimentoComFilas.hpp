#ifndef PROCEDIMENTOCOMFILAS_HPP
#define PROCEDIMENTOCOMFILAS_HPP

#include "Procedimento.hpp" // Classe base
#include "Fila.hpp"         // Dependencia para as filas

class ProcedimentoComFilas : public Procedimento {
private:
    Fila filaVermelha;      // Grau de Urgencia 2
    Fila filaAmarela;       // Grau de Urgencia 1
    Fila filaVerde;         // Grau de Urgencia 0

public:
    // Construtor
    ProcedimentoComFilas(double tempoMedioExecucao, int unidadesDisponiveis, int capacidadeFila);

    // Adicionar paciente em uma fila especifica
    void adicionarPacienteNaFila(Paciente* paciente);

    // Obter o proximo paciente da fila
    Paciente* obterProximoPaciente();

    // Verificar se todas as filas estao vazias
    bool filaVazia() const;

    // Finalizar todas as filas
    void finaliza();
};

#endif // PROCEDIMENTOCOMFILAS_HPP
