#ifndef ORDIND_HPP
#define ORDIND_HPP

#include <string>

#define MAX_ATRIBUTOS 100 // Limite de atributos
#define MAX_DADOS 1000 // Limite de registros

class OrdInd {
private:
    std::string atributos[MAX_ATRIBUTOS];                   // Nomes dos atributos
    std::string dados[MAX_DADOS][MAX_ATRIBUTOS];            // Dados
    int numAtributos;                                       // Quantidade de atributos
    int numDados;                                           // Quantidade de cadastros

    //---------------------------------- Ponto Extra ------------------------------------------------------//
    int frequencia[MAX_DADOS];                              // Array para armazenar a frequência de acesso
    int matrizFrequencia[MAX_DADOS][2];                     // Matriz pra organizar as frequencias
    //-----------------------------------------------------------------------------------------------------//

public:
    // Construtor e Destrutor
    OrdInd();
    ~OrdInd();
    
    void Swap(int i, int j);  
    int CarregaArquivo(const std::string& nomeEntrada);
    void Particao(int Esq, int Dir, int* i, int* j, int atribId);
    void Ordena(int Esq, int Dir, int atribId);
    void QuickSort(int atribId);
    void InsertionSort(int atribId);
    void BubbleSort(int atribId);
    void ImprimeOrdenadoIndice(int atribId) const;

    // Métodos Getters e Setters
    const std::string& GetAtributo(int i) const;
    const std::string& GetDado(int i, int j) const;
    int GetNumAtributos() const;
    int GetNumDados() const;

    /*---------------------------------- Ponto Extra -------------------------------------------------------/
    void Particao_frequencia(int Esq, int Dir, int* i, int* j, int (*matrizFrequencia)[2]);
    void Ordena_frequencia(int Esq, int Dir, int (*matrizFrequencia)[2]);
    void QuickSort_frequencia(int n);
    void OrdenarFrequencia();
    void ReorganizaDados();
    -----------------------------------------------------------------------------------------------------*/
};

#endif // ORDIND_HPP

