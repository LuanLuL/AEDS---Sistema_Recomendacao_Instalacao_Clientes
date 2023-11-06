#include "Cto.hpp"

Cto::Cto(string id, string endereco, vector<pair<string, float>> vizinhos, float latitude, float longitude) : Poste(id, endereco, vizinhos, latitude, longitude){
    this->clientesAlocados = 0;
    this->clientes = new string[this->capacidade];
}

Cto::~Cto() {/*...*/}

int Cto::getCapacidade() {
    return this->capacidade;
}

bool Cto::cheio() {
    return (this->clientesAlocados == this->capacidade);
}

void Cto::armazenarCliente(string contrato) {
    if(this->clientesAlocados < this->capacidade){
        this->clientes[this->clientesAlocados] = contrato;
        this->clientesAlocados++;
        cout << "Armazenou" << endl;
    }
    else{
        cout << "Nao armazenou" << endl;
    }
}
