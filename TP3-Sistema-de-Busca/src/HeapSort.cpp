#include "HeapSort.hpp"
#include <iostream>

// Inicializa o heap com a capacidade fornecida e os critérios de ordenação
HeapSort::HeapSort(int cap, const char ordem[3]) : tamanho(0), capacidade(cap) {
    heap = new DadosViagem[capacidade]; 
    for (int i = 0; i < 3; i++) prioridade[i] = ordem[i];
}

// Libera a memória alocada para o heap quando o objeto é destruído
HeapSort::~HeapSort() {
    delete[] heap;  
}

// Insere novo elemento
void HeapSort::inserir(DadosViagem voo) {
    if (tamanho >= capacidade) return;  
    heap[tamanho] = voo; 
    heapifyUp(tamanho);
    tamanho++;
}

// Remove o elemento de menor prioridade do heap
DadosViagem HeapSort::remover() {
    if (tamanho == 0) return DadosViagem();  
    DadosViagem raiz = heap[0];  
    heap[0] = heap[--tamanho];
    heapifyDown(0); 
    return raiz;
}

/*------------------------------ Métodos para ajustar a posição de um elemento -----------------------------*/
void HeapSort::heapifyUp(int index) {

    while (index > 0) {
        int pai = (index - 1) / 2;  
        if (comparar(heap[index], heap[pai]) < 0) {  
            std::swap(heap[index], heap[pai]); 
            index = pai;  
        } else break;  
    }
}

void HeapSort::heapifyDown(int index) {
    int esq, dir, menor;
    while (true) {
        esq = 2 * index + 1;
        dir = 2 * index + 2;
        menor = index;
        
        if (esq < tamanho && comparar(heap[esq], heap[menor]) < 0) menor = esq;
        if (dir < tamanho && comparar(heap[dir], heap[menor]) < 0) menor = dir;
        if (menor == index) break;
        
        std::swap(heap[index], heap[menor]);
        index = menor;
    }
}

// Compara dois elementos de acordo com a prioridade definida no array 'prioridade'
int HeapSort::comparar(const DadosViagem& a, const DadosViagem& b) {
    
    for (int i = 0; i < 3; i++) {
        switch (prioridade[i]) {
            case 'p':  // Prioriza o preço
                if (std::abs(a.getPreco() - b.getPreco()) > 1e-6)  // Evita erro de precisão
                    return (a.getPreco() < b.getPreco()) ? -1 : 1; 
                break;
            case 'd':  // Prioriza a duração
                if (a.getDuracao() != b.getDuracao()) 
                    return (a.getDuracao() < b.getDuracao()) ? -1 : 1;
                break;
            case 's':  // Prioriza o número de conexões
                if (a.getConexoes() != b.getConexoes()) 
                    return (a.getConexoes() < b.getConexoes()) ? -1 : 1;
                break;
        }
    }
    return 0;  // Retorna 0 se os dois elementos forem iguais conforme os critérios
}

// Verifica se o heap está vazio
bool HeapSort::vazio() const {
    return tamanho == 0;
}
