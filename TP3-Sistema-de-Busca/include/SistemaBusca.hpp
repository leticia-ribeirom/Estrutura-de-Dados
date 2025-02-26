#ifndef SISTEMABUSCA_HPP
#define SISTEMABUSCA_HPP

#include "DadosViagem.hpp"
#include "HeapSort.hpp"
#include "ArvoreAVLInt.hpp"
#include "ArvoreAVLFloat.hpp"
#include "ArvoreAVLString.hpp"
#include <string>
#include <iostream>
#define MAX_RESULTADOS 1000

class SistemaBusca {
private:
    // Índices para a busca dos voos com base nos diferentes atributos
    ArvoreAVLString indiceOrigem;       // Índice que organiza os voos por origem (cidade de partida).
    ArvoreAVLString indiceDestino;      // Índice que organiza os voos por destino (cidade de chegada).
    ArvoreAVLFloat indicePreco;         // Índice que organiza os voos por preço.
    ArvoreAVLInt indiceDuracao;         // Índice que organiza os voos por duração.
    ArvoreAVLInt indiceConexoes;        // Índice que organiza os voos por número de conexões.
    ArvoreAVLInt indiceAssentos;        // Índice que organiza os voos por número de assentos.
    ArvoreAVLString indiceDataPartida;  // Índice que organiza os voos por data de partida.
    ArvoreAVLString indiceDataChegada;  // Índice que organiza os voos por data de chegada.

    DadosViagem *voos;  // Vetor de voos armazenados no sistema.
    int tamanho;        // Variável que guarda o tamanho atual do vetor de voos (quantidade de voos).

public:
    // Construtor
    SistemaBusca(int capacidade);
    // Destrutor
    ~SistemaBusca();

    // Adiciona um voo ao sistema
    void adicionarVoo(const DadosViagem& voo, int indice);   
    
    // Método que verifica se as buscas satisfazem os filtros
    void satisfazConsulta(const std::string& consulta, const char ordem[3], int maxResultados, int quantidadeVoos);

    // Método que realiza todas as buscas
    void realizarBusca(const std::string& consulta, int buscas[MAX_RESULTADOS], int& contadorBuscas, int& quantidadeIntersecao);

    // Método que vê as interseções, insere no heap e chama a impressão dos resultados
    void inserirNoHeap(int buscas[MAX_RESULTADOS], int contadorBuscas, const char ordem[3], int quantidadeIntersecao, int maxResultados);

    // Imprime os detalhes de um voo de maneira formatada.    
    void imprimirVooFormatado(const DadosViagem& voo);  
    
    // Extrai e processa os dados numéricos da consulta
    bool extrairDaConsulta(const std::string& consulta, const std::string& operador, std::string& operadorEncontrado, int& valor);  
    
    // Extrai e processa os dados tipo string da consulta
    bool extrairDaConsultaString(const std::string& consulta, const std::string& operador, std::string& operadorEncontrado, std::string& valor);

    // Método para adicionar os voos que correspondem a cada filtro
    void adicionarIndicesIntersecao(int* indices, int contador, int& quantidadeIntersecao, int* buscas, int& contadorBuscas);

    /*-------------------------------------------- Ponto Extra ----------------------------------------------------
    void inserirNoHeapUniao(int buscas[MAX_RESULTADOS], int contadorBuscas, const char ordem[3], int quantidadeIntersecao, int maxResultados);
    --------------------------------------------------------------------------------------------------------------*/
};

#endif // SISTEMABUSCA_HPP
