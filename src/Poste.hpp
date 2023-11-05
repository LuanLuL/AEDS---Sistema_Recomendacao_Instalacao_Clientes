#ifndef __POSTE_HPP
#define __POSTE_HPP

#include <iostream>
#include <list>
#include <cstring>

using namespace std;

class Poste{
    private:
        string id, endereco;
        list<pair<string, float>> vizinhos;
        float latitude, longitude;
    public:
        Poste(string id, string endereco, list<pair<string, float>> vizinhos, float latitude, float longitude);
        ~Poste();
        string getId();
        void setId(string newId);
        string getEndereco();
        list<pair<string, float>> getVizinhos();
        void setVizinhos(list<pair<string, float>> newVizinhos);
        void setEndereco(string newEndereco);
        float getLatitude();
        void setLatitude(float newLatitude);
        float getLongitude();
        void setLongitude(float newLongitude);
};
#endif