#ifndef DADOSVIAGEM_HPP
#define DADOSVIAGEM_HPP

#include <string>
#include <chrono>

class DadosViagem {
private:
    // Atributos privados que armazenam as informações da viagem
    std::string partida;             // Local de partida da viagem
    std::string destino;             // Local de destino da viagem
    float preco;                     // Preço da viagem
    int assentos;                    // Quantidade de assentos disponíveis
    std::string dataPartida;         // Data da partida (formato string)
    std::string horaPartida;         // Hora da partida (formato string)
    std::string dataChegada;         // Data da chegada (formato string)
    std::string horaChegada;         // Hora da chegada (formato string)
    int conexoes;                    // Número de conexões durante a viagem
    std::chrono::system_clock::time_point horarioPartida;  // Horário de partida (tipo time_point para manipulação com data/hora)
    std::chrono::system_clock::time_point horarioChegada;  // Horário de chegada (tipo time_point)
    long duracao;                    // Duração total da viagem em segundos

public:
    // Construtor padrão
    DadosViagem();

    // Construtor com parâmetros para inicializar os dados da viagem
    DadosViagem(const std::string& partida, const std::string& destino, float preco, int assentos,
                const std::string& dataPartida, const std::string& horaPartida,
                const std::string& dataChegada, const std::string& horaChegada, int conexoes);

    // Método para calcular a duração da viagem em segundos
    long calcularDuracaoSegundos() const;

    // Método para converter uma string de data e hora no formato adequado para time_point
    std::chrono::system_clock::time_point parseDateTime(const std::string& dataHora);

    // Métodos de acesso (getters) para acessar os dados privados

    std::string getPartida() const;      // Retorna o local de partida
    std::string getDestino() const;      // Retorna o local de destino
    float getPreco() const;              // Retorna o preço da viagem
    int getAssentos() const;             // Retorna o número de assentos disponíveis
    std::string getDataPartida() const;  // Retorna a data da partida
    std::string getHoraPartida() const;  // Retorna a hora da partida
    std::string getDataChegada() const;  // Retorna a data de chegada
    std::string getHoraChegada() const;  // Retorna a hora de chegada
    int getConexoes() const;             // Retorna o número de conexões
    long int getDuracao() const;         // Retorna a duração da viagem em segundos

};

#endif  // DADOSVIAGEM_HPP
