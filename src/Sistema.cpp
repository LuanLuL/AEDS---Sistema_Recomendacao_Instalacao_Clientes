#include "Sistema.hpp"

Sistema::Sistema() {
    getCSV();
    this->grafo.create(&(this->mapPoste), &(this->mapCto));
}

Sistema::~Sistema() {/*...*/}

unordered_map<string, Poste> Sistema::getMapPoste() {
    return this->mapPoste;
}

void Sistema::setMapPoste(unordered_map<string, Poste> newMapPoste) {
    this->mapPoste = newMapPoste;
}

unordered_map<string, Cto> Sistema::getMapCto() {
    return this->mapCto;
}

void Sistema::setMapCto(unordered_map<string, Cto> newMapCto) {
    this->mapCto = newMapCto;
}

Grafo Sistema::getGrafo() {
    return this->grafo;
}

void Sistema::setGrafo(Grafo newGrafo) {
    this->grafo = newGrafo;
}

vector<pair<string, float>> Sistema::separaVizinhos(string lista) {
    vector<pair<string, float>> numeros;
    istringstream stream(lista);
    string token;
    while (getline(stream, token, ',')) {
        token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
        numeros.push_back(make_pair(token, 0));
    }
    return numeros;
}

void Sistema::getCSV(){
    ifstream file("dataset/Postes.csv");
    if(!file.is_open()){
        cerr << "Error: File din't find\n\n";
    } else{
        string id = "", endereco = "", latitude = "", longitude = "", vizinhos = "", cto ="";
        vector<pair<string, float>> lstVizinhos;
        bool primeiraLinha = true;
        while(file.good()){
             if (primeiraLinha) {
                primeiraLinha = false;
                getline(file, id);
                continue; // Pule a primeira linha
            }
            getline(file, id, ';');
            if(id == ""){ // verifica se é a ultima linha do CSV
                break;
            }
            getline(file, endereco, ';');
            getline(file, latitude, ';');
            replace(latitude.begin(), latitude.end(), ',', '.');
            getline(file, longitude, ';');
            replace(longitude.begin(), longitude.end(), ',', '.');
            getline(file, vizinhos, ';');
            lstVizinhos = separaVizinhos(vizinhos);
            getline(file, cto, '\n');
            cto.pop_back();
            if(cto == "1"){
                this->mapCto.insert(make_pair(id, Cto(id, endereco, lstVizinhos, stof(latitude), stof(longitude))));
            } else{
                this->mapPoste.insert(make_pair(id, Poste(id, endereco, lstVizinhos, stof(latitude), stof(longitude))));
            }
        }
    }
    file.close();
}

void Sistema::imprimirMapa(){
    cout << "\nPostes alocados no sitema: \n\n";
    for(int i = 1; i <= (this->mapPoste.size() + this->mapCto.size()); i++){
        cout << i << " - "; 
        auto it = this->mapPoste.find(to_string(i));
        if(it != mapPoste.end()){
            cout << it->second.getEndereco() << "\n\n";
        } else{
            auto iterator = this->mapCto.find(to_string(i));
            if(iterator != this->mapCto.end()){
                cout << iterator->second.getEndereco() << "\n\n";
            }
        }
    }
}

// void Sistema::recomendar(string identificador) {
//     pair<unordered_map<string, float>, unordered_map<string, vector<string>>> resultados = this->grafo.algoritimoDijkstra(identificador);
//     string way;
//     set<pair<string, float>> fila;
//     for (const auto& pair : resultados.first) {
//         auto it = this->mapCto.find(pair.first);
//         if(it != this->mapCto.end()){
//             way = "";
//             if (pair.second == FLT_MAX) {
//                 way += "Caminho não encontrado";
//             } else {
//                 vector<string> caminho = resultados.second[pair.first];
//                 while (!caminho.empty()) {
//                     way += caminho.front() + " -> ";
//                     caminho.erase(caminho.begin());
//                 }
//                 way += pair.first;
//                 fila.insert(make_pair(way, pair.second));
//                 cout << way << "(" << pair.second << ")" << endl;
//             }
//         }
//     }
//     // char instalar;
//     // while(!fila.empty()){
//     //     way = fila.top().first;
//     //     float peso = fila.top().second;
//     //     fila.pop();
//     //     cout << "CTO mais próxima a '" << peso << "'";
//     //     cout << "\n\n Deseja instalar o cliente? [S/N] ";
//     //     cin >> instalar;
//     //     switch (instalar) {
//     //         case 'S':
//     //         case 's': {
//     //             cout << "\n\ninstalou\n\n";
//     //             break;
//     //         }
//     //         case 'N': 
//     //         case 'n': {
//     //             cout << "\n\nnao instalou\n\n";
//     //             break;
//     //         }
//     //         default:{
//     //             break;
//     //         }  
//     //     }
//     // }

// }
