#ifndef ARVOREAVLFLOAT_HPP
#define ARVOREAVLFLOAT_HPP

#include <iostream>

// Definição do nó da árvore AVL para valores do tipo float
class NoFloat {
public:
    float chave;                        // Chave armazenada no nó
    int* indices;                       // Array dinâmico que armazena os índices relacionados à chave
    int capacidade;                     // Capacidade atual do array de índices
    int tamanho;                        // Quantidade de índices armazenados no array
    NoFloat* esquerda;                  // Ponteiro para o nó à esquerda (subárvore esquerda)
    NoFloat* direita;                   // Ponteiro para o nó à direita (subárvore direita)
    int altura;                         // Altura do nó, usada para balanceamento da árvore

    
    NoFloat(float chave, int indice);   // Construtor da classe NoFloat
    ~NoFloat();                         // Destruidor da classe NoFloat

    // Método para adicionar um índice ao nó
    void adicionarIndice(int indice);
};

// Classe da árvore AVL que armazena valores do tipo float
class ArvoreAVLFloat {
private:
    // Método para calcular a altura de um nó
    int altura(NoFloat* no) const;

    // Método para calcular o fator de balanceamento de um nó
    int fatorDeBalanceamento(NoFloat* no) const;

    // Método para retornar o maior valor entre dois números do tipo float
    float maximo(float a, float b) const;

    // Ponteiro para a raiz da árvore AVL
    NoFloat* raiz;

    // Método para realizar uma rotação à direita
    NoFloat* rotacaoDireita(NoFloat* y);

    // Método para realizar uma rotação à esquerda
    NoFloat* rotacaoEsquerda(NoFloat* x);

    // Método para balancear a árvore após a inserção ou remoção de um nó
    NoFloat* balancear(NoFloat* no);

    // Método recursiva para inserir um nó na árvore
    NoFloat* inserir(NoFloat* no, float chave, int indice);

public:
    // Construtor da árvore AVL
    ArvoreAVLFloat();

    // Destrudor da árvore AVL
    ~ArvoreAVLFloat();

    // Método para destruir a árvore
    void destruir(NoFloat* no);

    // Método para inserir uma chave e um índice
    void inserir(float chave, int indice);

    /*-------------------------------------- Sistema de Buscas nas árvores -------------------------------------*/
    //É maior ou igual
    void buscarInOrdemMaior (NoFloat* no, float valor, int* indicesEncontrados, int& contador);
    int* buscarInOrdemMaior (float valor, int& contador);

    // É menor ou igual
    void buscarInOrdemMenor (NoFloat* no, float valor, int* indicesEncontrados, int& contador);
    int* buscarInOrdemMenor (float valor, int& contador);

    // É igual
    void buscarInOrdemIgual (NoFloat* no, float valor, int* indicesEncontrados, int& contador);
    int* buscarInOrdemIgual (float valor, int& contador);
};

#endif // ARVOREAVLFLOAT_HPP
