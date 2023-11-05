#ifndef __GRAFO_HPP
#define __GRAFO_HPP

#include <iostream>
#include <cstring>
#include <list>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <unordered_map>

#include "Poste.hpp"
#include "Cto.hpp"

using namespace std;

class Grafo{
    private:
        unordered_map<string, list<pair<string, float>>> lista;
    public:
        Grafo();
        ~Grafo();
        void adicionarAresta(Poste poste);
        void adicionarAresta(Cto cto);
        void create(unordered_map <string, Poste> mapPoste, unordered_map <string, Cto> mapCto);
        void calculaPesoDasArestas(unordered_map <string, Poste> *mapPoste, unordered_map <string, Cto> *mapCto);
        float calculaDistanciaEntreArestas(float x1, float y1, float x2, float y2);
        void imprimir();
};

#endif