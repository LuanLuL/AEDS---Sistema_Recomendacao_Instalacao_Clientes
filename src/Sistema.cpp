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
    for(pair<string, Poste> poste : this->mapPoste){
        cout << poste.second.getId() << "; " << poste.second.getEndereco() << "; " << poste.second.getLatitude() << "; " << poste.second.getLongitude() << "; " << "\n\n"; 
    }
    for(pair<string, Cto> cto : this->mapCto){
        cout << cto.second.getId() << "; " << cto.second.getEndereco() << "; " << cto.second.getLatitude() << "; " << cto.second.getLongitude() << "; " << "\n\n"; 
    }
}