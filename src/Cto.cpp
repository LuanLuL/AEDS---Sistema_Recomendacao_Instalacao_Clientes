#include "Cto.hpp"

Cto::Cto(string id, string endereco, vector<pair<string, float>> vizinhos, float latitude, float longitude) : Poste(id, endereco, vizinhos, latitude, longitude){
    this->qtdClientes = 0;
    this->clientes = new bool[this->capacidade];
}

Cto::~Cto() {/*...*/}

int Cto::getCapacidade() {
    return this->capacidade;
}

int Cto::getQtdClientes() {
    return this->qtdClientes;
}

void Cto::setQtdClientes(int newQtdClientes) {
    this->qtdClientes = newQtdClientes;
}

bool *Cto::getClientes() {
    return this->clientes;
}

void Cto::setClientes(bool *newClientes) {
    this->clientes = newClientes;
}

bool Cto::cheio() {
    return (this->qtdClientes == this->capacidade);
}

void Cto::armazenarCliente() {
    if(this->qtdClientes < this->capacidade){
        this->clientes[this->qtdClientes] = true;
        this->qtdClientes++;
    }
}
