#include "OrdInd.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Construtor
OrdInd::OrdInd() : numAtributos(0), numDados(0), frequencia {0} {}

// Destrutor
OrdInd::~OrdInd() {}

// Método para trocar as linhas de dados 
void OrdInd::Swap(int i, int j) {
    for (int k = 0; k < GetNumAtributos(); k++) {
        // Troca os dados das colunas entre as linhas i e j
        std::string temp = dados[i][k];
        dados[i][k] = dados[j][k];
        dados[j][k] = temp;
    }
    frequencia[i]++;  // Incrementa a frequencia do índice i
    frequencia[j]++;  // Incrementa a frequencia do índice j
}

// Metodo para carregar o arquivo
int OrdInd::CarregaArquivo(const std::string& nomeEntrada) {
    // Abrir o arquivo
    std::ifstream arquivo(nomeEntrada); 
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << nomeEntrada << std::endl;
        return -1;
    }
    
    // Lê a primeira linha para obter o número de atributos
    std::string linha; 
    if (!std::getline(arquivo, linha)) { 
        std::cerr << "Erro ao ler o numero de atributos." << std::endl;
        return -1;
    }
    
    // Armazena a quantidade de atributos
    std::istringstream quantidadeAtributos(linha); 
    if (!(quantidadeAtributos >> numAtributos) || numAtributos > MAX_ATRIBUTOS) {
        std::cerr << "Erro ao ler o numero de atributos ou excedeu o limite." << std::endl;
        return -1;
    }

    // Lê os dados de cabeçalho e armazena os nomes dos atributos
    for (int i = 0; i < GetNumAtributos(); i++) {
        if (!std::getline(arquivo, linha)) {
            std::cerr << "Erro ao ler os cabeçalhos." << std::endl;
            return -1;
        }
        
        // Lê os atributos com virgula
        std::istringstream variaveisAtributos(linha); 
        std::string nomeAtributo;
        if (!std::getline(variaveisAtributos, nomeAtributo, ',')) {
            std::cerr << "Erro ao dividir o nome do atributo." << std::endl;
            return -1;
        }
        // Armazenar o nome do atributo sem virgula
        atributos[i] = nomeAtributo; 
    }

    // Obtem a quantidade de pessoas registradas
    if (!std::getline(arquivo, linha)) {
        std::cerr << "Erro ao ler a quantidade de dados" << std::endl;
        return -1;
    }
    
    // Lê e armazena a quantidade de pessoas registradas
    std::istringstream quantidadeDados(linha); 
    if (!(quantidadeDados >> numDados) || numDados > MAX_DADOS) {
        std::cerr << "Erro ao ler o número de pessoas ou excedeu o limite" << std::endl;
        return -1;
    }

    // Leitura e armazenamento dos registros
    for (int i = 0; i < GetNumDados() && std::getline(arquivo, linha); i++) {
        std::istringstream conteudoDados(linha);
        std::string campo;
        for (int j = 0; j < GetNumAtributos() && std::getline(conteudoDados, campo, ','); j++) {
            // Armazena o valor do campo
            dados[i][j] = campo; 
        }
    }
    return 0;
}

// Metodo QuickSort particao
void OrdInd::Particao(int Esq, int Dir, int* i, int* j, int atribId) {
    std::string pivo;

    *i = Esq;                                               // Inicializa índices i e j, que vão percorrer o vetor
    *j = Dir;

    pivo = dados[(*i + *j) / 2][atribId];                   // Inicializa pivô com elemento central

    do {
        while (dados[*i][atribId] < pivo)  {       
            (*i)++;                                         // i procura elemento maior que pivô
            frequencia[*i]++;                               // Incrementa a frequencia do índice                                            
        }   
        while (dados[*j][atribId] > pivo){ 
            (*j)--;                                         // j procura elemento menor que pivô
            frequencia[*j]++;                               // Incrementa a frequencia do índice
        }
        if (*i <= *j) {                                     //Se i e j ainda não se cruzaram, então

            frequencia[*i]++;                               // i procura elemento maior que pivô
            frequencia[*j]++;                               // Incrementa a frequencia do índice
            Swap(*i, *j);                                   // Troca os elementos de índice i e j de lugar

            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
    
}

//Metodo Quicksort ordena
void OrdInd::Ordena(int Esq, int Dir, int atribId) {
    int i, j;                               // indices i e j, que vão percorrer o vetor
    Particao(Esq, Dir, &i, &j, atribId);    // Chama partição, com índices i  e j passados por referencia
    if (Esq < j) Ordena(Esq, j, atribId);   // Recursão para a parte esquerda
    if (i < Dir) Ordena(i, Dir, atribId);   // Recursão para a parte direita
}

// Metodo Quicksort
void OrdInd::QuickSort(int atribId) {
    Ordena(0, GetNumDados() - 1, atribId);
}

// Método Insertion Sort
void OrdInd::InsertionSort(int atribId) {
    int i, j;
    std::string aux;
    
    for (i = 1; i < GetNumDados(); i++) {                       // Começa do segundo elemento (i = 1)
        std::string auxDados[GetNumAtributos()];                // Armazena o registro inteiro da linha i
        for (int k = 0; k < GetNumAtributos(); k++) {
            auxDados[k] = dados[i][k];                          // Armazena toda a linha
        }

        aux = dados[i][atribId];                                // Pega o valor do atributo na linha i
        j = i - 1;                                              // Inicializa j para a comparação com o elemento anterior

        // Enquanto j não é negativo e o valor do atributo da linha j é maior que o valor de aux
        while (j >= 0 && aux < dados[j][atribId]) {
            frequencia[j]++;                                    // Incrementa a frequencia de acesso para o índice j
            
            for (int k = 0; k < GetNumAtributos(); k++) {       // Move toda a linha para a direita
                dados[j + 1][k] = dados[j][k];
            }
            j--;                                                // Move para o elemento anterior
        }
        
        // Coloca a linha de volta na posição correta
        for (int k = 0; k < GetNumAtributos(); k++) {
            dados[j + 1][k] = auxDados[k]; 
        }

        frequencia[i]++;                                        // Incrementa a frequencia de acesso para o índice i após o deslocamento
    }

}

// Método Bolha
void OrdInd::BubbleSort(int atribId) {
    for (int i = 0; i < GetNumDados() - 1; i++) {
        for (int j = 1; j < GetNumDados() - i; j++) {
            frequencia[j]++;                                    // Incrementa a frequencia de acesso para o índice j
            frequencia[j - 1]++;                                // Incrementa a frequencia de acesso para o índice j-1

            if (dados[j][atribId] < dados[j - 1][atribId]) {
                    Swap (j, j - 1);                            // Troca todas as colunas entre as linhas j e j-1
            }
        }
    }
}


// Método para imprimir os dados ordenados
void OrdInd::ImprimeOrdenadoIndice(int atribId) const {
    for (int i = 0; i < GetNumDados(); i++) {
        for (int j = 0; j < GetNumAtributos(); j++) {
            if (j != GetNumAtributos() - 1){
                std::cout << dados[i][j] << ",";
            }
            else {
                std::cout << dados[i][j];
            }
        }
        std::cout << std::endl;
    }
}

// Métodos de acesso
// Retorna o atributo i
const std::string& OrdInd::GetAtributo(int i) const {
    return atributos[i];  // Retorna o valor do atributo na posição i
}

// Retorna o dado de uma pessoa i na posição j
const std::string& OrdInd::GetDado(int i, int j) const {
    return dados[i][j];  // Retorna o dado da pessoa i e atributo j
}

// Retorna o número de atributos
int OrdInd::GetNumAtributos() const {
    return numAtributos; // Retorna o numero de atributos
}

// Retorna a quantidade de pessoas registrados
int OrdInd::GetNumDados() const {
    return numDados; // Retorna o numero de pessoas
}

/* -------------------------------------- Ponto Extra ------------------------------------------------------
// Metodo QuickSort particao
void OrdInd::Particao_frequencia(int Esq, int Dir, int* i, int* j, int (*matrizFrequencia)[2]) {
    int pivo = matrizFrequencia[(Esq + Dir) / 2][1]; // Pivô é a frequencia no meio

    *i = Esq;
    *j = Dir;

    do {
        // Procurar valores maiores que o pivô (decrescente)
        while (matrizFrequencia[*i][1] > pivo) (*i)++;
        // Procurar valores menores que o pivô (decrescente)
        while (matrizFrequencia[*j][1] < pivo) (*j)--;

        if (*i <= *j) {
            // Trocar os elementos das posições *i e *j
            std::swap(matrizFrequencia[*i][0], matrizFrequencia[*j][0]);
            std::swap(matrizFrequencia[*i][1], matrizFrequencia[*j][1]);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void OrdInd::Ordena_frequencia(int Esq, int Dir, int (*matrizFrequencia)[2]) {
    int i, j;
    Particao_frequencia(Esq, Dir, &i, &j, matrizFrequencia);

    if (Esq < j) Ordena_frequencia(Esq, j, matrizFrequencia); // Ordenar lado esquerdo
    if (i < Dir) Ordena_frequencia(i, Dir, matrizFrequencia); // Ordenar lado direito
}

// Metodo Quicksort
void OrdInd::QuickSort_frequencia(int n) {
    Ordena_frequencia(0, n - 1, matrizFrequencia);
}

void OrdInd::OrdenarFrequencia() {
    // Preencher a matriz com índices e frequencias
    for (int i = 0; i < GetNumDados(); i++) {
        matrizFrequencia[i][0] = i + 1;         // Índice
        matrizFrequencia[i][1] = frequencia[i]; // Frequencia
    }

    // Imprimir antes da ordenação
    
    std::cout << "Matriz de Frequencias (antes de ordenar):" << std::endl;
    for (int i = 0; i < GetNumDados(); i++) {
        std::cout << matrizFrequencia[i][0] << ": " << matrizFrequencia[i][1] << std::endl;
    }

    // Chamar QuickSort para ordenar
    QuickSort_frequencia(GetNumDados());

    // Imprimir após a ordenação
    
    std::cout << "Matriz de Frequencias (ordem decrescente):" << std::endl;
    for (int i = 0; i < GetNumDados(); i++) {
        std::cout << matrizFrequencia[i][0] << ": "
                  << matrizFrequencia[i][1] << std::endl;
    }
}

void OrdInd::ReorganizaDados() {
    // Criar uma estrutura temporária para armazenar os dados reorganizados
    std::string dadosReorganizados[MAX_DADOS][MAX_ATRIBUTOS];

    // Reorganizar os dados com base na matriz de frequencia (ordem decrescente)
    for (int i = 0; i < GetNumDados(); i++) {
        int indiceOriginal = matrizFrequencia[i][0] - 1; // Obter o índice original a partir da matriz de frequencia
        for (int j = 0; j < GetNumAtributos(); j++) {
            dadosReorganizados[i][j] = dados[indiceOriginal][j]; // Copiar os dados correspondentes
        }
    }

    // Copiar os dados reorganizados de volta para o array original
    for (int i = 0; i < GetNumDados(); i++) {
        for (int j = 0; j < GetNumAtributos(); j++) {
            dados[i][j] = dadosReorganizados[i][j];
        }
    }

    // Imprimir os dados reorganizados
    
    std::cout << std::endl << "Dados reorganizados com base na frequencia:" << std::endl;
    for (int i = 0; i < GetNumDados(); i++) {
        for (int j = 0; j < GetNumAtributos(); j++) {
            if (j != GetNumAtributos() - 1) {
                std::cout << dados[i][j] << ",";
            } else {
                std::cout << dados[i][j];
            }
        }
        std::cout << std::endl;
    }
}---------------------------------------------------------------------------------------------------*/
