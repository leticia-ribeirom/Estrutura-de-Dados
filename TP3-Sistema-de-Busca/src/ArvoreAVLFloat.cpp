#include "ArvoreAVLFloat.hpp"

// Construtor de NoFloat: inicializa a chave, os índices, e configura os ponteiros de filhos e altura
NoFloat::NoFloat(float chave, int indice) : chave(chave), esquerda(nullptr), direita(nullptr), altura(1) {
    capacidade = 10;
    tamanho = 1;
    indices = new int[capacidade]; 
    indices[0] = indice; // Armazena o primeiro índice
}

// Destruidor de NoFloat: libera a memória do array de índices
NoFloat::~NoFloat() {
    delete[] indices;
}

// Adiciona um índice ao nó
void NoFloat::adicionarIndice(int indice) {
    if (tamanho == capacidade) {
        capacidade *= 2; // Dobra a capacidade
        int* novoArray = new int[capacidade];
        for (int i = 0; i < tamanho; i++) {
            novoArray[i] = indices[i]; // Copia os índices existentes
        }
        delete[] indices;
        indices = novoArray;
    }
    indices[tamanho++] = indice; // Adiciona o novo índice
}

// Construtor da árvore AVL
ArvoreAVLFloat::ArvoreAVLFloat() : raiz(nullptr) {}

// Destruidor da árvore AVL
ArvoreAVLFloat::~ArvoreAVLFloat() {
    destruir(raiz);
}

// Método recursivo para destruir a árvore
void ArvoreAVLFloat::destruir(NoFloat* no) {
    if (no) {
        destruir(no->esquerda);
        destruir(no->direita);
        delete no; // Libera a memória do nó
    }
}

// Retorna a altura de um nó (0 se for nullptr)
int ArvoreAVLFloat::altura(NoFloat* no) const {
    if (no) {
        return no->altura; // Retorna a altura do nó
    } else {
        return 0; // Se o nó for nullptr, retorna 0
    }
}

// Calcula o fator de balanceamento de um nó
int ArvoreAVLFloat::fatorDeBalanceamento(NoFloat* no) const {
    return altura(no->esquerda) - altura(no->direita);
}

// Retorna o maior valor entre dois números float
float ArvoreAVLFloat::maximo(float a, float b) const {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

// Realiza uma rotação à direita para balanceamento
NoFloat* ArvoreAVLFloat::rotacaoDireita(NoFloat* y) {
    NoFloat* x = y->esquerda;
    NoFloat* T2 = x->direita;
    x->direita = y;
    y->esquerda = T2;
    y->altura = maximo(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = maximo(altura(x->esquerda), altura(x->direita)) + 1;
    return x; // Retorna o novo nó raiz
}

// Realiza uma rotação à esquerda para balanceamento
NoFloat* ArvoreAVLFloat::rotacaoEsquerda(NoFloat* x) {
    NoFloat* y = x->direita;
    NoFloat* T2 = y->esquerda;
    y->esquerda = x;
    x->direita = T2;
    x->altura = maximo(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = maximo(altura(y->esquerda), altura(y->direita)) + 1;
    return y; // Retorna o novo nó raiz
}

// Balanceia um nó da árvore, realizando rotações conforme necessário
NoFloat* ArvoreAVLFloat::balancear(NoFloat* no) {
    int balanceamento = fatorDeBalanceamento(no);
    // Realiza as rotações dependendo do fator de balanceamento
    if (balanceamento > 1 && fatorDeBalanceamento(no->esquerda) >= 0)
        return rotacaoDireita(no);
    if (balanceamento < -1 && fatorDeBalanceamento(no->direita) <= 0)
        return rotacaoEsquerda(no);
    if (balanceamento > 1 && fatorDeBalanceamento(no->esquerda) < 0) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }
    if (balanceamento < -1 && fatorDeBalanceamento(no->direita) > 0) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }
    return no; // Se o nó já está balanceado, retorna ele sem alterações
}

// Método recursivo para inserir um novo nó na árvore AVL
NoFloat* ArvoreAVLFloat::inserir(NoFloat* no, float chave, int indice) {
    if (!no) {
        return new NoFloat(chave, indice);                              // Cria um novo nó se o nó atual for nullptr
    }
    if (chave < no->chave) {
        no->esquerda = inserir(no->esquerda, chave, indice);            // Inserção na subárvore esquerda
    } else if (chave > no->chave) {
        no->direita = inserir(no->direita, chave, indice);              // Inserção na subárvore direita
    } else {
        no->adicionarIndice(indice);                                    // Se a chave já existir, apenas adiciona o índice
        return no;
    }
    no->altura = maximo(altura(no->esquerda), altura(no->direita)) + 1; // Atualiza a altura
    return balancear(no);                                               // Balanceia a árvore após a inserção
}

// Método público para inserir um novo nó na árvore
void ArvoreAVLFloat::inserir(float chave, int indice) {
    raiz = inserir(raiz, chave, indice);                                // Chama o método recursivo de inserção
}

/*----------------------------------------- Sistema de Buscas nas árvores ----------------------------------------*/
#define MAX_RESULTADOS 100  // Define o tamanho máximo para o array de resultados

// Maior ou igual
void ArvoreAVLFloat::buscarInOrdemMaior(NoFloat* no, float valor, int* indicesEncontrados, int& contador) {
    if (no) {
        // Verifica na subárvore esquerda
        buscarInOrdemMaior(no->esquerda, valor, indicesEncontrados, contador);

        // Verifica os índices do nó
        if (no->chave >= valor) {
            for (int j = 0; j < no->tamanho; j++) {
                // Adiciona o índice encontrado ao array, se ainda houver espaço
                if (contador < MAX_RESULTADOS) {
                    indicesEncontrados[contador++] = no->indices[j];
                }
            }
        }

        // Verifica na subárvore direita
        buscarInOrdemMaior(no->direita, valor, indicesEncontrados, contador);
    }
}

// Método público para buscar os índices associados a um valor
int* ArvoreAVLFloat::buscarInOrdemMaior(float valor, int& contador) {
    static int indicesEncontrados[MAX_RESULTADOS];  // Array estático para armazenar os índices

    // Chama a função recursiva para buscar os índices
    buscarInOrdemMaior(raiz, valor, indicesEncontrados, contador);

    // Se algum índice foi encontrado, retorna o array de índices encontrados
    if (contador > 0) {
        return indicesEncontrados;  // Retorna o array de índices encontrados
    } else {
        std::cout << "Índice não encontrado!" << std::endl;
        return nullptr;  // Caso nenhum índice tenha sido encontrado
    }
}

// Menor ou igual
void ArvoreAVLFloat::buscarInOrdemMenor(NoFloat* no, float valor, int* indicesEncontrados, int& contador) {
    if (no) {
        // Verifica na subárvore esquerda
        buscarInOrdemMenor(no->esquerda, valor, indicesEncontrados, contador);

        // Verifica os índices do nó
        if (no->chave <= valor) {
            for (int j = 0; j < no->tamanho; j++) {
                // Adiciona o índice encontrado ao array, se ainda houver espaço
                if (contador < MAX_RESULTADOS) {
                    indicesEncontrados[contador++] = no->indices[j];
                }
            }
        }

        // Verifica na subárvore direita
        buscarInOrdemMenor(no->direita, valor, indicesEncontrados, contador);
    }
}

// Método público para buscar os índices associados a um valor
int* ArvoreAVLFloat::buscarInOrdemMenor(float valor, int& contador) {
    static int indicesEncontrados[MAX_RESULTADOS];  // Array estático para armazenar os índices

    // Chama a função recursiva para buscar os índices
    buscarInOrdemMenor(raiz, valor, indicesEncontrados, contador);

    // Se algum índice foi encontrado, retorna o array de índices encontrados
    if (contador > 0) {
        return indicesEncontrados;  // Retorna o array de índices encontrados
    } else {
        std::cout << "Índice não encontrado!" << std::endl;
        return nullptr;  // Caso nenhum índice tenha sido encontrado
    }
}


// É igual
void ArvoreAVLFloat::buscarInOrdemIgual(NoFloat* no, float valor, int* indicesEncontrados, int& contador) {
    if (no) {
        // Verifica na subárvore esquerda
        buscarInOrdemIgual(no->esquerda, valor, indicesEncontrados, contador);

        // Verifica os índices do nó
        if (no->chave == valor) {
            for (int j = 0; j < no->tamanho; j++) {
                // Adiciona o índice encontrado ao array, se ainda houver espaço
                if (contador < MAX_RESULTADOS) {
                    indicesEncontrados[contador++] = no->indices[j];
                }
            }
        }

        // Verifica na subárvore direita
        buscarInOrdemIgual(no->direita, valor, indicesEncontrados, contador);
    }
}

// Método público para buscar os índices associados a um valor
int* ArvoreAVLFloat::buscarInOrdemIgual(float valor, int& contador) {
    static int indicesEncontrados[MAX_RESULTADOS];  // Array estático para armazenar os índices

    // Chama a função recursiva para buscar os índices
    buscarInOrdemIgual(raiz, valor, indicesEncontrados, contador);

    // Se algum índice foi encontrado, retorna o array de índices encontrados
    if (contador > 0) {
        return indicesEncontrados;  // Retorna o array de índices encontrados
    } else {
        std::cout << "Índice não encontrado!" << std::endl;
        return nullptr;  // Caso nenhum índice tenha sido encontrado
    }
}
