#include "Escalonador.hpp"

// Construtor: inicializa o escalonador com tamanho zero
Escalonador::Escalonador() : tamanho(0) {}

// Inicializa o escalonador, redefinindo o tamanho para zero
void Escalonador::inicializa() {
    tamanho = 0;
}

// Ajusta a posicao do ultimo elemento inserido para manter a propriedade do heap (menor elemento no topo)
void Escalonador::heapifyUp(int i) {
    while (i > 0) {
        int p = getAncestral(i);
        // Verifica a hierarquia: ano > mes > dia > hora > ID
        if (heap[i].ano < heap[p].ano || 
            (heap[i].ano == heap[p].ano && heap[i].mes < heap[p].mes) ||
            (heap[i].ano == heap[p].ano && heap[i].mes == heap[p].mes && heap[i].dia < heap[p].dia) ||
            (heap[i].ano == heap[p].ano && heap[i].mes == heap[p].mes && heap[i].dia == heap[p].dia && heap[i].hora < heap[p].hora) ||
            (heap[i].ano == heap[p].ano && heap[i].mes == heap[p].mes && heap[i].dia == heap[p].dia && heap[i].hora == heap[p].hora && 
             heap[i].paciente->getId() < heap[p].paciente->getId())) {
            
            Evento temp = heap[i];
            heap[i] = heap[p];
            heap[p] = temp;
            i = p; // Continue verificando o proximo ancestral
        } else {
            break; // Propriedade do heap satisfeita
        }
    }
}

// Ajusta a posição do elemento no topo para manter a propriedade do heap apos uma remoção
void Escalonador::heapifyDown(int i) {
    while (true) {
        int esq = getSucessorEsq(i);
        int dir = getSucessorDir(i);
        int menor = i;

        // Verifica a hierarquia: ano > mes > dia > hora > ID (menor ID tem prioridade)
        if (esq < tamanho && 
            (heap[esq].ano < heap[menor].ano || 
            (heap[esq].ano == heap[menor].ano && heap[esq].mes < heap[menor].mes) ||
            (heap[esq].ano == heap[menor].ano && heap[esq].mes == heap[menor].mes && heap[esq].dia < heap[menor].dia) ||
            (heap[esq].ano == heap[menor].ano && heap[esq].mes == heap[menor].mes && heap[esq].dia == heap[menor].dia && heap[esq].hora < heap[menor].hora) ||
            (heap[esq].ano == heap[menor].ano && heap[esq].mes == heap[menor].mes && heap[esq].dia == heap[menor].dia && heap[esq].hora == heap[menor].hora &&
             heap[esq].paciente->getId() < heap[menor].paciente->getId()))) { // Menor ID tem prioridade
            menor = esq;
        }

        if (dir < tamanho && 
            (heap[dir].ano < heap[menor].ano || 
            (heap[dir].ano == heap[menor].ano && heap[dir].mes < heap[menor].mes) ||
            (heap[dir].ano == heap[menor].ano && heap[dir].mes == heap[menor].mes && heap[dir].dia < heap[menor].dia) ||
            (heap[dir].ano == heap[menor].ano && heap[dir].mes == heap[menor].mes && heap[dir].dia == heap[menor].dia && heap[dir].hora < heap[menor].hora) ||
            (heap[dir].ano == heap[menor].ano && heap[dir].mes == heap[menor].mes && heap[dir].dia == heap[menor].dia && heap[dir].hora == heap[menor].hora &&
             heap[dir].paciente->getId() < heap[menor].paciente->getId()))) { // Menor ID tem prioridade
            menor = dir;
        }

        // Se o menor elemento nao for o atual, troca e continua ajustando
        if (menor != i) {
            Evento temp = heap[i];
            heap[i] = heap[menor];
            heap[menor] = temp;
            i = menor; // Continue ajustando para baixo
        } else {
            break; // Propriedade do heap satisfeita
        }
    }
}


// Insere um novo evento no escalonador e ajusta o heap
void Escalonador::insereEvento(int ano, int mes, int dia, double hora, Paciente* paciente) {
    if (tamanho >= 1000) {
        throw std::runtime_error("Escalonador cheio: não é possível inserir mais eventos.");
    }
    heap[tamanho] = Evento(ano, mes, dia, hora, paciente); // Adiciona o novo evento
    heapifyUp(tamanho); // Ajusta o heap para manter a propriedade
    tamanho++;

}

// Remove e retorna o proximo evento (o menor, no topo do heap)
Evento Escalonador::retiraProximoEvento() {
    if (tamanho == 0) {
        throw std::runtime_error("Escalonador vazio: nenhum evento a retirar.");
    }
    Evento proximo = heap[0]; // Salva o menor evento
    heap[0] = heap[tamanho - 1]; // Substitui o topo pelo ultimo elemento
    tamanho--;
    heapifyDown(0); // Ajusta o heap para manter a propriedade
    return proximo;
}

// Verifica se o escalonador esta vazio
bool Escalonador::vazio() const {
    return tamanho == 0;
}

// Retorna o tempo do proximo evento no topo do heap sem remove-lo
double Escalonador::getProximoTempo() const {
    if (tamanho == 0) {
        throw std::runtime_error("Escalonador vazio: nenhum tempo disponível.");
    }
    return heap[0].hora;
}

// Retorna o ano do proximo evento no topo do heap
int Escalonador::getProximoAno() const {
    if (tamanho == 0) {
        throw std::runtime_error("Escalonador vazio: nenhum ano disponível.");
    }
    return heap[0].ano;
}

// Retorna o mes do proximo evento no topo do heap
int Escalonador::getProximoMes() const {
    if (tamanho == 0) {
        throw std::runtime_error("Escalonador vazio: nenhum mês disponível.");
    }
    return heap[0].mes;
}

// Retorna o dia do proximo evento no topo do heap
int Escalonador::getProximoDia() const {
    if (tamanho == 0) {
        throw std::runtime_error("Escalonador vazio: nenhum dia disponível.");
    }
    return heap[0].dia;
}

// Retorna o ancestral
int Escalonador::getAncestral(int i){
    return (i - 1) / 2;
}

// Retorna o sucessor a esquerda
int Escalonador::getSucessorEsq(int i){
    return 2 * i + 1;
}

// Retorna o sucessor a direita
int Escalonador::getSucessorDir(int i){
    return 2 * i + 2;
}