#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include <iostream>
#include "Paciente.hpp"

// Estrutura de evento que armazena informacoes sobre um evento especifico
struct Evento {
    int ano;                // Ano do evento
    int mes;                // Mes do evento
    int dia;                // Dia do evento
    double hora;            // Hora do evento
    Paciente* paciente;     // Ponteiro para o objeto Paciente associado a este evento
    
    // Construtor padrao
    Evento() : ano (0), mes (0), dia (0), hora(0), paciente(nullptr) {}
    // Construtor que inicializa os membros com valores fornecidos
    Evento(int ano, int mes, int dia, double h, Paciente* p) : ano (ano), mes (mes), dia (dia), hora(h), paciente(p) {}
};

class Escalonador {
private:
    Evento heap[1000];      // Array de eventos
    int tamanho;            // Numero de eventos presentes

public:
    // Construtor padrao
    Escalonador();
    
    // Inicializa o escalonador
    void inicializa();
    
    // Metodos para garantir a propriedade do minheap
    void heapifyUp(int i);
    void heapifyDown(int i);

    // Insere um evento
    void insereEvento(int ano, int mes, int dia, double hora, Paciente* paciente);
    
    // Retira o proximo evento
    Evento retiraProximoEvento();

    // Verifica se o escalonador esta vazio
    bool vazio() const;

    // Metodos de acesso
    double getProximoTempo() const; // Retorna o tempo do proximo evento
    int getProximoAno() const;      // Retorna o ano do proximo evento
    int getProximoMes() const;      // Retorna o mês do proximo evento
    int getProximoDia() const;      // Retorna o dia do proximo evento
    
    int getAncestral(int i);        // Retorna o ancestral
    int getSucessorEsq(int i);      // Retorna o sucessor a esquerda
    int getSucessorDir(int i);      // Retorna o sucessor a direita
};

#endif
