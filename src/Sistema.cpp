#include "Sistema.hpp"

Sistema::Sistema() {
    getCSV();
    this->grafo.create(&(this->mapPoste), &(this->mapCto));
    this->quantidadeDeElementos = this->mapPoste.size() + this->mapCto.size();
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

int Sistema::getQuantidadeDeElementos() {
    return this->quantidadeDeElementos;
}

void Sistema::setQuantidadeDeElementos(int newQuantidadeDeElementos) {
    this->quantidadeDeElementos = newQuantidadeDeElementos;
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

void Sistema::selectionSort(vector<pair<pair<string, string>, float>> &vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (vec[j].second < vec[min_index].second) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(vec[i], vec[min_index]);
        }
    }
}

void Sistema::recomendar(string identificador) {
    if(stoi(identificador) > this->quantidadeDeElementos || stoi(identificador) < 1){
        cout << "\nERRO...POSTE NÃO ENCONTRADO...ERRO\n";
    }
    else{
        vector<pair<pair<string, string>, float>>  resultadosGerais = this->grafo.algoritimoDijkstra(identificador);
        vector<pair<pair<string, string>, float>> resultadosParciais;
        for(pair<pair<string, string>, float> item : resultadosGerais){
            auto it = this->mapCto.find(item.first.first);
            if(it != this->mapCto.end()){
                resultadosParciais.push_back(item);
            }
        }
        resultadosGerais.clear();
        selectionSort(resultadosParciais);
        bool continuar = true;
        while(!resultadosParciais.empty() && continuar){
            auto it = this->mapCto.find(resultadosParciais[0].first.first);
            if(it != this->mapCto.end()){        
                if(it->second.cheio()){
                    resultadosParciais.erase(resultadosParciais.begin());
                } else{
                    cout << "\n-----------------------------------------------------------------\n\nCliente deve ser instalado na CTO: '" << it->second.getId()  << "'";
                    cout << "\n\nDeseja instalar o cliente? [S/N] ";
                    char instalar = 'S';
                    cin >> instalar;
                    switch (instalar) {
                        case 'S':
                        case 's': {
                            it->second.armazenarCliente();
                            continuar = false;
                            cout << "\nSiga o menor caminho:\n\n\t" << resultadosParciais[0].first.second << "\n";
                            break;
                        }
                        case 'N': 
                        case 'n': {
                            continuar = false;
                            cout << endl;
                            break;
                        }
                        default:{
                            cout << "\nERRO...OPÇÃO INVÁLIDA...ERRO\n";
                            break;
                        }  
                    }
                }
            }else{
                cout << "\n../Sistema::recomendar(string identificador) -> ERRO: CTO não encontrada \n";
                break;
            }
        }
    }
}
