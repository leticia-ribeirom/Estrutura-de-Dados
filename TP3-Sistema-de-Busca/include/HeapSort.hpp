#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include "DadosViagem.hpp"

class HeapSort {
private:
    DadosViagem* heap;      // Ponteiro para o array que armazenará os elementos do heap
    int tamanho;            // Número de elementos presentes no heap
    int capacidade;         // Capacidade máxima do heap
    char prioridade[3];     // Vetor que define os critérios de ordenação

    // Método para manter a propriedade do heap ao inserir um elemento (subir)
    void heapifyUp(int index);

    // Método para manter a propriedade do heap ao remover um elemento (descer)
    void heapifyDown(int index);

    // Método de comparação para ordenar de acordo com a prioridade definida
    int comparar(const DadosViagem& a, const DadosViagem& b);

public:
    // Construtor que inicializa a capacidade e o critério de prioridade
    HeapSort(int capacidade, const char ordem[3]);

    // Destruidor que desaloca a memória usada pelo heap
    ~HeapSort();

    // Método para inserir um novo elemento no heap
    void inserir(DadosViagem voo);

    // Método para remover o elemento de maior ou menor prioridade (dependendo da ordenação)
    DadosViagem remover();

    // Método para verificar se o heap está vazio
    bool vazio() const;
};

#endif  // HEAPSORT_HPP
