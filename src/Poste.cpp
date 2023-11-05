#include "Poste.hpp"

Poste::Poste(string id, string endereco, list<pair<string, float>> vizinhos, float latitude, float longitude) {
    this->id = id;
    this->endereco = endereco;
    this->vizinhos = vizinhos;
    this->latitude = latitude;
    this->longitude = longitude;
}

Poste::~Poste() {/*...*/}

string Poste::getId() {
    return this->id;
}

void Poste::setId(string newId) {
    this->id = newId;
}

string Poste::getEndereco() {
    return this->endereco;
}

void Poste::setEndereco(string newEndereco) {
    this->endereco = newEndereco;
}

list<pair<string, float>> Poste::getVizinhos() {
    return this->vizinhos;
}

void Poste::setVizinhos(list<pair<string, float>> newVizinhos) {
    this->vizinhos = newVizinhos;
}

float Poste::getLatitude() {
    return this->latitude;
}

void Poste::setLatitude(float newLatitude) {
    this->latitude = newLatitude;
}

float Poste::getLongitude() {
    return this->longitude;
}

void Poste::setLongitude(float newLongitude) {
    this->longitude = newLongitude;
}