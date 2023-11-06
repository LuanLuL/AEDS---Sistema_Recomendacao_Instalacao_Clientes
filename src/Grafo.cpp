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

void Grafo::create(unordered_map <string, Poste> *mapPoste, unordered_map <string, Cto> *mapCto) {
    calculaPesoDasArestas(mapPoste, mapCto);
    for(pair<string, Poste> poste : *mapPoste){
        adicionarAresta(poste.second);
    }
    for(pair<string, Cto> cto : *mapCto){
        adicionarAresta(cto.second);
    }
}

void Grafo::calculaPesoDasArestas(unordered_map <string, Poste> *mapPoste, unordered_map <string, Cto> *mapCto) {
    for(pair<string, Poste> poste : *mapPoste){
        vector<pair<string, float>> aux;
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
        vector<pair<string, float>> aux;
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
        vector<pair<string, float>> lista = hash.second;
        for(auto aresta : lista){
            cout << " -> " << aresta.first << " (" << aresta.second << ")";
        }
        cout << "\n\n";
    }
}

vector<pair<pair<string, string>, float>> Grafo::algoritimoDijkstra(string inicio) {
    vector<pair<pair<string, string>, float>> returnDados;
    priority_queue<pair<string, float>> fila; // vértice, distância
    unordered_map<string, float> dist;
    unordered_map<string, vector<string>> predecessores; // Alteração
    for (const auto& item : this->lista) {
        dist.insert(make_pair(item.first, FLT_MAX));
        predecessores[item.first] = vector<string>();
    }
    dist[inicio] = 0.0;
    fila.push(make_pair(inicio, 0.0));
    while (!fila.empty()) {
        string vertice = fila.top().first;
        float peso = -fila.top().second;
        fila.pop();
        if (peso != dist[vertice]) {
            continue;
        }
        for (pair<string, float> aresta : this->lista[vertice]) {
            if (dist[aresta.first] > (dist[vertice] + aresta.second)) {
                dist[aresta.first] = (dist[vertice] + aresta.second);
                predecessores[aresta.first] = predecessores[vertice]; // Copie os predecessores do vértice atual
                predecessores[aresta.first].push_back(vertice); // Adicione o vértice atual como predecessor
                fila.push(make_pair(aresta.first, -dist[aresta.first]));
            }
        }
    }
    string way;
    for (const auto& pair : dist) {
        way = "";
        if (pair.second == FLT_MAX) {
            way += "Caminho não encontrado";
        } else {
            vector<string> caminho = predecessores[pair.first];
            while (!caminho.empty()) {
                way += caminho.front() + " -> ";
                caminho.erase(caminho.begin());
            }
            way += pair.first;
            returnDados.push_back(make_pair(make_pair(pair.first, way), pair.second));
            // cout << way << "(" << pair.second << ")" << endl;
        }
    }
    return returnDados;
}

