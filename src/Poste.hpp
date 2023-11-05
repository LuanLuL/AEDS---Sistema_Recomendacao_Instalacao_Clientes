#ifndef __POSTE_HPP
#define __POSTE_HPP

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Poste{
    private:
        string id, endereco;
        vector<pair<string, float>> vizinhos;
        float latitude, longitude;
    public:
        Poste(string id, string endereco, vector<pair<string, float>> vizinhos, float latitude, float longitude);
        ~Poste();
        string getId();
        void setId(string newId);
        string getEndereco();
        vector<pair<string, float>> getVizinhos();
        void setVizinhos(vector<pair<string, float>> newVizinhos);
        void setEndereco(string newEndereco);
        float getLatitude();
        void setLatitude(float newLatitude);
        float getLongitude();
        void setLongitude(float newLongitude);
};
#endif