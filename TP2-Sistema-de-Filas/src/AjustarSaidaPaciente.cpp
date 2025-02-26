#include "AjustarSaidaPaciente.hpp"

void AjustarSaidaPaciente::ajustarSaidaPaciente(Paciente* paciente, float tempoTotalHoras) {
    // Extrair os componentes do horario inicial
    float horasEntrada = paciente->getHora();
    int dia = paciente->getDia();
    int mes = paciente->getMes();
    int ano = paciente->getAno();

    // Adicionar o tempo total ao horario inicial
    int horasTotais = horasEntrada + static_cast<int>(tempoTotalHoras); 

    // Calculando minutosTotais usando o valor absoluto da parte decimal
    float minutosTotais = std::fabs(tempoTotalHoras - static_cast<int>(tempoTotalHoras)) * 60;

    // Arredondar minutosTotais para evitar problemas de precisao
    int minutosInteiros = std::round(minutosTotais); 

    // Ajustar minutos que ultrapassam 60
    if (minutosInteiros >= 60) {
        horasTotais += minutosInteiros / 60;
        minutosInteiros = minutosInteiros % 60; 
    }

    // Ajustar horas que ultrapassam 24
    while (horasTotais >= 24) {
        horasTotais -= 24;
        dia += 1; 
    }

    // Ajustar o dia caso ultrapasse o numero de dias do mes
    while (true) {
        bool bissexto = (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
        int diasNoMes = 31;

        if (mes == 2) {
            diasNoMes = bissexto ? 29 : 28;
        } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
            diasNoMes = 30;
        }

        if (dia <= diasNoMes) {
            break; 
        }

        dia -= diasNoMes; 
        mes += 1;

        if (mes > 12) {
            mes = 1;
            ano += 1; 
        }
    }

    // Atualizar os dados do paciente
    paciente->setHora_H(horasTotais);           // Atualiza a hora do paciente
    paciente->setMinutos_H(minutosInteiros);    // Atualiza os minutos do paciente
    paciente->setDia_H(dia);                    // Atualiza o dia
    paciente->setMes_H(mes);                    // Atualiza o mes
    paciente->setAno_H(ano);                    // Atualiza o ano
}

// Obter o dia da semana da entrada do paciente
std::string AjustarSaidaPaciente::getDiaSemanaEntrada(const Paciente* paciente) {
    std::tm time = {};
    time.tm_year = paciente->getAno() - 1900;
    time.tm_mon = paciente->getMes() - 1;
    time.tm_mday = paciente->getDia();

    std::mktime(&time);

    char buffer[10];
    std::strftime(buffer, sizeof(buffer), "%a %b", &time);

    return std::string(buffer);
}

// Obter o dia da semana da saida do paciente
std::string AjustarSaidaPaciente::getDiaSemanaSaida(const Paciente* paciente) {
    std::tm time = {};
    time.tm_year = paciente->getAno_H() - 1900;
    time.tm_mon = paciente->getMes_H() - 1;
    time.tm_mday = paciente->getDia_H();

    std::mktime(&time);

    char buffer[10];
    std::strftime(buffer, sizeof(buffer), "%a %b", &time);

    return std::string(buffer);
}
