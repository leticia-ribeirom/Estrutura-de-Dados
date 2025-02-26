#include "Fila.hpp"
#include <cmath>
#include <stdexcept> // Tratar excecoes

// Inicializa a fila com a capacidade especificada
void Fila::inicializa(int capacidade) {
    this->capacidade = capacidade;
    pacientes = new Paciente*[capacidade];
    tamanho = 0;
    inicio = 0;
    fim = 0;
}

// Finaliza a fila liberando a memoria alocada
void Fila::finaliza() {
    delete[] pacientes;
    pacientes = nullptr;
    capacidade = tamanho = inicio = fim = 0;
}

// Enfileira um paciente na fila
void Fila::enfileira(Paciente* paciente) {
    
    if (tamanho == capacidade) {
        throw std::overflow_error("Fila cheia");
    }

    // Adiciona o paciente na posição 'fim'
    pacientes[fim] = paciente;
    fim = (fim + 1) % capacidade;
    tamanho++;

}

// Desenfileira um paciente da fila
Paciente* Fila::desenfileira() {
    if (filaVazia()) {
        throw std::underflow_error("Fila vazia");
    }
    Paciente* paciente = pacientes[inicio];
    inicio = (inicio + 1) % capacidade;
    tamanho--;

    return paciente;
}

// Verifica se a fila esta vazia
bool Fila::filaVazia() const {
    return tamanho == 0;
}
