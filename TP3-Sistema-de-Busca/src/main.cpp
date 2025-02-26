#include "DadosViagem.hpp"
#include "HeapSort.hpp"
#include "SistemaBusca.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>" << std::endl;
        return 1;
    }

    std::ifstream arquivo(argv[1]);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << argv[1] << std::endl;
        return 1;
    }

    int quantidadeVoos;
    arquivo >> quantidadeVoos;
    arquivo.ignore();

    SistemaBusca sistema(quantidadeVoos);

    // Lê dados dos voos
    for (int i = 0; i < quantidadeVoos; ++i) {
        std::string partida, destino, dataHoraPartida, dataHoraChegada;
        float preco;
        int assentos, conexoes;

        arquivo >> partida >> destino >> preco >> assentos >> dataHoraPartida >> dataHoraChegada >> conexoes;

        // Encontrar o índice do 'T' em dataHoraPartida
        int posT1 = 0;
        while (dataHoraPartida[posT1] != 'T' && dataHoraPartida[posT1] != '\0') {
            ++posT1;
        }

        // Separar data e hora da partida
        std::string dataPartida, horaPartida;
        for (int j = 0; j < posT1; ++j) {
            dataPartida += dataHoraPartida[j];
        }
        for (int j = posT1 + 1; j < (int)dataHoraPartida.size(); ++j) {
            horaPartida += dataHoraPartida[j];
        }

        // Encontrar o índice do 'T' em dataHoraChegada
        int posT2 = 0;
        while (dataHoraChegada[posT2] != 'T' && dataHoraChegada[posT2] != '\0') {
            ++posT2;
        }

        // Separar data e hora da chegada
        std::string dataChegada, horaChegada;
        for (int j = 0; j < posT2; ++j) {
            dataChegada += dataHoraChegada[j];
        }
        for (int j = posT2 + 1; j < (int)dataHoraChegada.size(); ++j) {
            horaChegada += dataHoraChegada[j];
        }

        DadosViagem voo(partida, destino, preco, assentos, dataPartida, horaPartida, dataChegada, horaChegada, conexoes);
        sistema.adicionarVoo(voo, i);
    }
    
    int quantidadeBuscas;
    arquivo >> quantidadeBuscas;
    arquivo.ignore();

    // Lê e processa as buscas
    for (int i = 0; i < quantidadeBuscas; i++) {
        int maxResultados;
        char ordem[3];
        std::string consulta;
        
        arquivo >> maxResultados >> ordem;
        std::getline(arquivo, consulta);
        
        std::cout << maxResultados << " " << ordem  << consulta << std::endl;
        sistema.satisfazConsulta(consulta, ordem, maxResultados, quantidadeVoos);
    }
    
    return 0;
}
