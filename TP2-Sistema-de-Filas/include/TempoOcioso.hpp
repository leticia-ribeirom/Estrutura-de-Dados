#ifndef TEMPOOCIOSO_HPP
#define TEMPOOCIOSO_HPP

#include <string>
#include <chrono>

class TempoOcioso {
private:
    std::chrono::system_clock::time_point entrada;  // Tempo de entrada na fila
    std::chrono::system_clock::time_point saida;    // Tempo de saida da fila

    // Funcao para converter ano, mes, dia, e hora para time_point
    std::chrono::system_clock::time_point construirTimePoint(int ano, int mes, int dia, double hora);

public:
    // Construtor padrao
    TempoOcioso() = default;

    // Configura a data e hora de entrada 
    void setEntrada(int ano, int mes, int dia, double hora);

    // Configura a data e hora de saida 
    void setSaida(int ano, int mes, int dia, double hora);

    // Calcula o tempo ocioso em horas
    float calcularTempoOcioso() const;

    // Formata o tempo ocioso em horas (considerando as frações de hora)
    std::string formatarTempoOcioso() const;
};

#endif // TEMPOOCIOSO_HPP
