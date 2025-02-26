#ifndef ARVOREAVLSTRING_HPP
#define ARVOREAVLSTRING_HPP

#include <iostream>
#include <string>

// Definição do nó da árvore AVL para valores do tipo String
class NoString {
public:
    std::string chave;                          // Chave armazenada no nó (do tipo string)
    int* indices;                               // Array dinâmico que armazena os índices relacionados à chave
    int capacidade;                             // Capacidade atual do array de índices
    int tamanho;                                // Quantidade de índices armazenados no array
    NoString* esquerda;                         // Ponteiro para o nó à esquerda (subárvore esquerda)
    NoString* direita;                          // Ponteiro para o nó à direita (subárvore direita)
    int altura;                                 // Altura do nó, usada para balanceamento

    NoString(std::string chave, int indice);    // Construtor da classe NoString
    ~NoString();                                // Destrutor da classe NoString

    // Método para adicionar um índice ao nó
    void adicionarIndice(int indice);
};

// Classe da árvore AVL que armazena valores do tipo String
class ArvoreAVLString {
private:
    // Método para calcular a altura de um nó
    int altura(NoString* no) const;

    // Método para calcular o fator de balanceamento de um nó
    int fatorDeBalanceamento(NoString* no) const;

    // Método para retornar o maior valor entre dois números do tipo inteiro 
    int maximo(int a, int b) const;

    // Ponteiro para a raiz da árvore
    NoString* raiz;  

    // Método para realizar uma rotação à direita
    NoString* rotacaoDireita(NoString* y); 

    // Método para realizar uma rotação à esquerda 
    NoString* rotacaoEsquerda(NoString* x);

    // Método para balancear a árvore após a inserção ou remoção de um nó
    NoString* balancear(NoString* no);

    // Método recursivo para inserir um nó na árvore
    NoString* inserir(NoString* no, std::string chave, int indice);

public:
    // Construtor da árvore AVL
    ArvoreAVLString();

    // Destrutor da árvore AVL  
    ~ArvoreAVLString(); 

    // Método para destruir a árvore
    void destruir(NoString* no);

    // Método para inserir uma chave e um índice 
    void inserir(std::string chave, int indice);

    /*-------------------------------------- Sistema de Buscas nas árvores -------------------------------------*/
    //É igual
    void buscarInOrdem (NoString* no, const std::string& valor, int* indicesEncontrados, int& contador);
    int* buscarInOrdem (const std::string& valor, int& contador); 
};

#endif // ARVOREAVLSTRING_HPP
