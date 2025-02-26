#include "OrdInd.hpp"
#include <iostream>
#include <string>

int main(int argc, char **argv) {

    // Verificar se o número correto de argumentos foi fornecido
    if (argc != 2) {
        std::cerr << "Não foi possível encontrar o arquivo. " << std::endl;
        return 1;
    }

    // Criar uma instância de OrdInd
    OrdInd tabela;

    // Carregar o arquivo CSV
    std::string nomeArquivo = argv[1]; // Pega o nome do arquivo da linha de comando
    if (tabela.CarregaArquivo(nomeArquivo) != 0) {
        return 1;
    }

    int quantidadeAtributo = tabela.GetNumAtributos();

    for (int i = 0; i < quantidadeAtributo - 1; i++) {

        std::cout << tabela.GetNumAtributos() << std::endl;             // Exibir o número de atributos
        for (int j = 0; j < tabela.GetNumAtributos(); j++) {            // Imprimir os cabeçalhos dos atributos
            std::cout << tabela.GetAtributo(j) << ",s" << std::endl;
        }
        std::cout << tabela.GetNumDados();                              // Exibir quantidade de cadastros
        std::cout << std::endl;

        tabela.QuickSort(i);                                            // Ordenar os dados por nome, cpf e endereco
        tabela.ImprimeOrdenadoIndice(i);                                // Chama a função para imprimir os dados ordenados

        //tabela.OrdenarFrequencia();
        //tabela.ReorganizaDados();
    }

    for (int i = 0; i < quantidadeAtributo - 1; i++) {

        std::cout << tabela.GetNumAtributos() << std::endl;             // Exibir o número de atributos
        for (int j = 0; j < tabela.GetNumAtributos(); j++) {            // Imprimir os cabeçalhos dos atributos
            std::cout << tabela.GetAtributo(j) << ",s" << std::endl;
        }
        std::cout << tabela.GetNumDados();                              // Exibir quantidade de cadastros
        std::cout << std::endl;

        tabela.InsertionSort(i);                                        // Ordenar os dados por nome, cpf e endereco
        tabela.ImprimeOrdenadoIndice(i);                                // Chama a função para imprimir os dados ordenados

        //tabela.OrdenarFrequencia();
        //tabela.ReorganizaDados();
    }
    for (int i = 0; i < quantidadeAtributo - 1; i++) {

        std::cout << tabela.GetNumAtributos() << std::endl;             // Exibir o número de atributos
        for (int j = 0; j < tabela.GetNumAtributos(); j++) {            // Imprimir os cabeçalhos dos atributos
            std::cout << tabela.GetAtributo(j) << ",s" << std::endl;
        }
        std::cout << tabela.GetNumDados();                              // Exibir quantidade de cadastros
        std::cout << std::endl;
        
        tabela.BubbleSort(i);                                                // Ordenar os dados por nome, cpf e endereco
        tabela.ImprimeOrdenadoIndice(i);                                // Chama a função para imprimir os dados ordenados

        //tabela.OrdenarFrequencia();
        //tabela.ReorganizaDados();
    }
    return 0;
}
