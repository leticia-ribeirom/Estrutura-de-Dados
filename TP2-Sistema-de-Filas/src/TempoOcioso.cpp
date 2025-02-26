#include "TempoOcioso.hpp"
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cmath> 

// Converte ano, mes, dia, hora para time_point
std::chrono::system_clock::time_point TempoOcioso::construirTimePoint(int ano, int mes, int dia, double hora) {
    std::tm tm = {};
    tm.tm_year = ano - 1900;  // std::tm usa anos desde 1900
    tm.tm_mon = mes - 1;      // std::tm usa meses de 0 a 11
    tm.tm_mday = dia;

    // Parte inteira da hora
    int horas = static_cast<int>(hora);  
    
    // Fracao da hora convertida para minutos com arredondamento
    double minutosFracao = (hora - horas) * 60.0;
    int minutos = static_cast<int>(std::round(minutosFracao));  

    tm.tm_hour = horas;
    tm.tm_min = minutos;
    tm.tm_sec = 0;

    // Converter std::tm para time_t e depois para time_point
    std::time_t time = std::mktime(&tm);
    if (time == -1) {
        throw std::runtime_error("Falha ao converter a data e hora.");
    }

    return std::chrono::system_clock::from_time_t(time);
}

// Configura a data e hora de entrada
void TempoOcioso::setEntrada(int ano, int mes, int dia, double hora) {
    entrada = construirTimePoint(ano, mes, dia, hora);
}

// Configura a data e hora de saída
void TempoOcioso::setSaida(int ano, int mes, int dia, double hora) {
    saida = construirTimePoint(ano, mes, dia, hora);
}

// Calcula o tempo ocioso em horas
float TempoOcioso::calcularTempoOcioso() const {
    if (entrada == std::chrono::system_clock::time_point() || 
        saida == std::chrono::system_clock::time_point()) {
        throw std::runtime_error("Entrada ou saída não definida.");
    }

    // Calcular a diferença em segundos, e depois converter para horas
    auto duracao = std::chrono::duration_cast<std::chrono::seconds>(saida - entrada);   // Diferença em segundos
    double tempoEmHoras = static_cast<double>(duracao.count()) / 3600.0;                // Converter para horas

    tempoEmHoras = std::round(tempoEmHoras * 100.0) / 100.0;                            // Arredondar para 2 casas decimais
    return static_cast<float>(tempoEmHoras);
}


// Formata o tempo ocioso em horas 
std::string TempoOcioso::formatarTempoOcioso() const {
    double totalHoras = calcularTempoOcioso();

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << totalHoras; 
    return oss.str();
}
