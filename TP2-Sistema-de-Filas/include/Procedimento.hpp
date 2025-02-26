#ifndef PROCEDIMENTO_HPP
#define PROCEDIMENTO_HPP

#include <string>

// Classe para representar um procedimento
class Procedimento {
private:
    double tempoMedioExecucao;  // Tempo medio de execução do procedimento
    int unidadesDisponiveis;    // Numero de unidades disponiveis para o procedimento
    int unidadesOcupadas;       // Numero de unidades ocupadas no momento

public:
    // Construtor
    Procedimento(double tempoMedioExecucao, int unidadesDisponiveis);

    // Verifica se ha unidade disponivel
    bool estaDisponivel() const;
    // Ocupa uma unidade
    void ocuparUnidade();
    // Libera uma unidade
    void liberarUnidade();       
    
    // Metodos de acesso
    double getTempoMedioExecucao() const;
    int getUnidadesDisponiveis() const;
    int getUnidadesOcupadas() const;
};

#endif // PROCEDIMENTO_HPP
