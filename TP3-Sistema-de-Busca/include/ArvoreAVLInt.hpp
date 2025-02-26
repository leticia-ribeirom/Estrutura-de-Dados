#ifndef ARVOREAVLINT_HPP
#define ARVOREAVLINT_HPP

#include <iostream>

// Definição do nó da árvore AVL para valores do tipo Inteiro
class NoInt {
public:
    int chave;                              // Chave armazenada no nó
    int* indices;                           // Array dinâmico que armazena os índices relacionados à chave
    int capacidade;                         // Capacidade atual do array de índices
    int tamanho;                            // Quantidade de índices armazenados no array
    NoInt* esquerda;                        // Ponteiro para o nó à esquerda (subárvore esquerda)
    NoInt* direita;                         // Ponteiro para o nó à direita (subárvore direita)
    int altura;                             // Altura do nó, usada para balanceamento

    NoInt(int chave, int indice);           // Construtor da classe NoInt
    ~NoInt();                               // Destrutor da classe NoInt
    
    // Método para adicionar um índice ao nó
    void adicionarIndice(int indice); 
};

// Classe da árvore AVL que armazena valores do tipo inteiro
class ArvoreAVLInt {
private:
    // Método para calcular a altura de um nó
    int altura(NoInt* no) const;

    // Método para calcular o fator de balanceamento de um nó
    int fatorDeBalanceamento(NoInt* no) const;

    // Método para retornar o maior valor entre dois números do tipo inteiro 
    int maximo(int a, int b) const;

    // Ponteiro para a raiz da árvore
    NoInt* raiz;  

    // Método para realizar uma rotação à direita
    NoInt* rotacaoDireita(NoInt* y); 

    // Método para realizar uma rotação à esquerda 
    NoInt* rotacaoEsquerda(NoInt* x);

    // Método para balancear a árvore após a inserção ou remoção de um nó
    NoInt* balancear(NoInt* no);

    // Método recursiva para inserir um nó na árvore
    NoInt* inserir(NoInt* no, int chave, int indice);
public:
    // Construtor da árvore AVL
    ArvoreAVLInt();

    // Destrutor da árvore AVL  
    ~ArvoreAVLInt(); 

    // Método para destruir a árvore
    void destruir(NoInt* no);

    // Método para inserir uma chave e um índice 
    void inserir(int chave, int indice); 

    /*-------------------------------------- Sistema de Buscas nas árvores -------------------------------------*/
    //É maior ou igual
    void buscarInOrdemMaior (NoInt* no, int valor, int* indicesEncontrados, int& contador);
    int* buscarInOrdemMaior (int valor, int& contador);

    // É menor ou igual
    void buscarInOrdemMenor (NoInt* no, int valor, int* indicesEncontrados, int& contador);
    int* buscarInOrdemMenor (int valor, int& contador);

    // É igual
    void buscarInOrdemIgual (NoInt* no, int valor, int* indicesEncontrados, int& contador);
    int* buscarInOrdemIgual (int valor, int& contador);
};

#endif // ARVOREAVLINT_HPP
