#ifndef FILA_HPP
#define FILA_HPP

#include "Paciente.hpp"

class Fila {
private:
    Paciente** pacientes; // Array de ponteiros para pacientes
    int capacidade;       // Capacidade maxima da fila
    int tamanho;          // Tamanho atual da fila
    int inicio;           // Indice do inicio da fila
    int fim;              // Indice do final da fila

public:
    // Construtor e destrutor
    void inicializa(int capacidade);
    void finaliza();

    // Metodos
    void enfileira(Paciente* paciente);
    Paciente* desenfileira();
    bool filaVazia() const;
};
#endif // FILA_HPP