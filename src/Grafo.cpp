#include "Grafo.hpp"

Grafo::Grafo(){/*...*/}

Grafo::~Grafo(){/*...*/}

void Grafo::adicionarAresta(Poste poste){
    for(pair<string, float> vizinho : poste.getVizinhos()){
        this->lista[poste.getId()].push_back(make_pair(vizinho.first, vizinho.second));
    }
}

void Grafo::adicionarAresta(Cto cto) {
    for(pair<string, float> vizinho : cto.getVizinhos()){
        this->lista[cto.getId()].push_back(make_pair(vizinho.first, vizinho.second));
    }
}

void Grafo::create(unordered_map <string, Poste> mapPoste, unordered_map <string, Cto> mapCto) {
    calculaPesoDasArestas(&mapPoste, &mapCto);
    for(pair<string, Poste> poste : mapPoste){
        adicionarAresta(poste.second);
    }
    for(pair<string, Cto> cto : mapCto){
        adicionarAresta(cto.second);
    }
}

void Grafo::calculaPesoDasArestas(unordered_map <string, Poste> *mapPoste, unordered_map <string, Cto> *mapCto) {
    for(pair<string, Poste> poste : *mapPoste){
        list<pair<string, float>> aux;
        for(pair<string, float> vizinho : poste.second.getVizinhos()){
            auto it = (*mapPoste).find(vizinho.first);
            if (it != (*mapPoste).end()) {
                aux.push_back(make_pair(vizinho.first, calculaDistanciaEntreArestas(it->second.getLatitude(), it->second.getLongitude(), poste.second.getLatitude(), poste.second.getLongitude())));
            } else{
                auto iterator = (*mapCto).find(vizinho.first);
                if(iterator != (*mapCto).end()){
                    aux.push_back(make_pair(vizinho.first, calculaDistanciaEntreArestas(iterator->second.getLatitude(), iterator->second.getLongitude(), poste.second.getLatitude(), poste.second.getLongitude())));
                }
            }
        }
        auto it = (*mapPoste).find(poste.first);
        if (it != (*mapPoste).end()) {
            it->second.setVizinhos(aux);
        }
    }
     for(pair<string, Cto> cto : *mapCto){
        list<pair<string, float>> aux;
        for(pair<string, float> vizinho : cto.second.getVizinhos()){
            auto it = (*mapCto).find(vizinho.first);
            if (it != (*mapCto).end()) {
                aux.push_back(make_pair(vizinho.first, calculaDistanciaEntreArestas(it->second.getLatitude(), it->second.getLongitude(), cto.second.getLatitude(), cto.second.getLongitude())));
            } else{
                auto iterator = (*mapPoste).find(vizinho.first);
                if(iterator != (*mapPoste).end()){
                    aux.push_back(make_pair(vizinho.first, calculaDistanciaEntreArestas(iterator->second.getLatitude(), iterator->second.getLongitude(), cto.second.getLatitude(), cto.second.getLongitude())));
                }
            }
        }
        auto it = (*mapCto).find(cto.first);
        if (it != (*mapCto).end()) {
            it->second.setVizinhos(aux);
        }
    }
}

float Grafo::calculaDistanciaEntreArestas(float x1, float y1, float x2, float y2) {
    return sqrt(((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
}

void Grafo::imprimir() {
    cout << "\n";
    for(auto hash : this->lista){
        cout << hash.first << ": ";
        list<pair<string, float>> lista = hash.second;
        for(auto aresta : lista){
            cout << aresta.first << " - ";
        }
        cout << endl;
    }
    cout << endl;
}