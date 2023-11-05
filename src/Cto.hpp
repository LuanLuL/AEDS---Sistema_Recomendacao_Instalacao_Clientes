#ifndef __CTO_HPP
#define __CTO_HPP

#include <iostream>
#include <cstring>
#include <list>

#include "Poste.hpp"

using namespace std;

class Cto: public Poste{
    private:
        const static int capacidade = 3;
        int clientesAlocados;
        string *clientes;
    public:
        Cto(string id, string endereco, list<pair<string, float>> vizinhos, float latitude, float longitude);
        ~Cto();
        int getCapacidade();
        bool cheio();
        void armazenarCliente(string contrato);
};

#endif