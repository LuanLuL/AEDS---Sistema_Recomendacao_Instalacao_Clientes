#ifndef __SISTEMA_HPP
#define __SISTEMA_HPP

#include <iostream>
#include <set>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <vector>

#include "Poste.hpp"
#include "Cto.hpp"
#include "Grafo.hpp"

using namespace std;

class Sistema{
    private:
        unordered_map<string, Poste> mapPoste; 
        unordered_map<string, Cto> mapCto;
        Grafo grafo;
        int quantidadeDeElementos;
    public:
        Sistema();
        ~Sistema();
        unordered_map<string, Poste> getMapPoste();
        void setMapPoste(unordered_map<string, Poste> newMapPoste);
        unordered_map<string, Cto> getMapCto();
        void setMapCto(unordered_map<string, Cto> newMapCto);
        Grafo getGrafo();
        void setGrafo(Grafo newGrafo);
        int getQuantidadeDeElementos();
        void setQuantidadeDeElementos(int newQuantidadeElementos);
        vector<pair<string, float>> separaVizinhos(string lista);
        void getCSV();
        void imprimirMapa();
        void selectionSort(vector<pair<pair<string, string>, float>> &vec);
        void recomendar(string identificador);
};

#endif