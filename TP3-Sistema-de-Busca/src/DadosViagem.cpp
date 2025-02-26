#include "DadosViagem.hpp"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>

// Construtor padrão
DadosViagem::DadosViagem()
    : partida(""), destino(""), preco(0), assentos(0), 
      dataPartida(""), horaPartida(""), dataChegada(""), horaChegada(""), 
      conexoes(0), duracao(0) {}

// Construtor com parâmetros para inicializar os dados da viagem
DadosViagem::DadosViagem(const std::string& partida, const std::string& destino, float preco, int assentos,
                         const std::string& dataPartida, const std::string& horaPartida,
                         const std::string& dataChegada, const std::string& horaChegada, int conexoes)
    : partida(partida), destino(destino), preco(preco), assentos(assentos),
      dataPartida(dataPartida), horaPartida(horaPartida),
      dataChegada(dataChegada), horaChegada(horaChegada),
      conexoes(conexoes),
      horarioPartida(parseDateTime(dataPartida + " " + horaPartida)),   // Converte data e hora de partida para time_point
      horarioChegada(parseDateTime(dataChegada + " " + horaChegada)) {  // Converte data e hora de chegada para time_point
    duracao = calcularDuracaoSegundos();  // Calcula a duração da viagem
}

// Método para calcular a duração da viagem em segundos
long DadosViagem::calcularDuracaoSegundos() const {
    // Calcula a diferença entre o horário de chegada e o de partida e converte para segundos
    return std::chrono::duration_cast<std::chrono::seconds>(horarioChegada - horarioPartida).count();
}


// Método auxiliar para converter uma string de data e hora no formato "YYYY-MM-DD HH:MM" em um time_point
std::chrono::system_clock::time_point DadosViagem::parseDateTime(const std::string& dataHora) {
    std::tm tm = {};  
    std::string data = dataHora.substr(0, 10);  
    std::string hora = dataHora.substr(11, 5); 
    
    // Cria um stringstream com a data e hora no formato adequado
    std::istringstream ss(data + " " + hora);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M"); 

    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

/*-------------------------------------------- Métodos de Acesso ----------------------------------------------*/

// Métodos getters para acessar os atributos privados da classe:

std::string DadosViagem::getPartida() const{
    return partida;  // Retorna o local de partida
}

std::string DadosViagem::getDestino() const{
    return destino;  // Retorna o local de destino
}

float DadosViagem::getPreco() const {
    return preco;  // Retorna o preço da viagem
}

int DadosViagem::getAssentos() const {
    return assentos;  // Retorna o número de assentos disponíveis
}

std::string DadosViagem::getDataPartida() const{
    return dataPartida;  // Retorna a data de partida
}

std::string DadosViagem::getHoraPartida() const{
    return horaPartida;  // Retorna a hora de partida
}

std::string DadosViagem::getDataChegada() const{
    return dataChegada;  // Retorna a data de chegada
}

std::string DadosViagem::getHoraChegada() const{
    return horaChegada;  // Retorna a hora de chegada
}

int DadosViagem::getConexoes() const{
    return conexoes;  // Retorna o número de conexões da viagem
}

long int DadosViagem::getDuracao() const{
    return duracao;  // Retorna a duração da viagem em segundos
}
