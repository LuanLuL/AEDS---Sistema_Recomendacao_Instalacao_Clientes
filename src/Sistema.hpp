#ifndef __SISTEMA_HPP
#define __SISTEMA_HPP

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cstring>
#include <list>

#include "Poste.hpp"
#include "Cto.hpp"
#include "Grafo.hpp"

using namespace std;

class Sistema{
    private:
        unordered_map<string, Poste> mapPoste; 
        unordered_map<string, Cto> mapCto;
        Grafo grafo;
    public:
        Sistema();
        ~Sistema();
        unordered_map<string, Poste> getMapPoste();
        void setMapPoste(unordered_map<string, Poste> newMapPoste);
        unordered_map<string, Cto> getMapCto();
        void setMapCto(unordered_map<string, Cto> newMapCto);
        Grafo getGrafo();
        void setGrafo(Grafo newGrafo);
        list<pair<string, float>> separaVizinhos(string lista);
        void getCSV();
        void imprimirMapa();
};

#endif