#ifndef AJUSTARSAIDAPACIENTE_HPP
#define AJUSTARSAIDAPACIENTE_HPP

#include "Paciente.hpp" 
#include <string>
#include <cmath>        // Para funcoes matematicas como fabs e round
#include <ctime>        // Para manipulacao de datas e horarios

class AjustarSaidaPaciente {
public:
    // Funcao para ajustar a saida do paciente
    static void ajustarSaidaPaciente(Paciente* paciente, float tempoTotalHoras);

    // Obter o dia da semana da entrada do paciente
    static std::string getDiaSemanaEntrada(const Paciente* paciente);

    // Obter o dia da semana da saida do paciente
    static std::string getDiaSemanaSaida(const Paciente* paciente);
};

#endif // AJUSTARSAIDAPACIENTE_HPP
