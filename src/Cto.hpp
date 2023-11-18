#ifndef __CTO_HPP
#define __CTO_HPP

#include <iostream>
#include <cstring>
#include <vector>

#include "Poste.hpp"

using namespace std;

class Cto: public Poste{
    private:
        const static int capacidade = 2;
        int qtdClientes;
        bool *clientes;
    public:
        Cto(string id, string endereco, vector<pair<string, float>> vizinhos, float latitude, float longitude);
        ~Cto();
        int getCapacidade();
        void setCapacidade(int newCapacidade);
        int getQtdClientes();
        void setQtdClientes(int newQtdClientes);
        bool *getClientes();
        void setClientes(bool *newClientes);
        bool cheio();
        void armazenarCliente();
};

#endif