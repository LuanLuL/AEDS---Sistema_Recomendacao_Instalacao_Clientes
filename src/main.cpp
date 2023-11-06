#include <iostream>
#include <clocale>
#include <cstring>
#include "Sistema.hpp"

using namespace std;

int main() {
    setlocale(LC_ALL, "Portuguese");
    Sistema app;
    int op = 0;
    do{
        cout << "\n******************** Sistema de Recomendação ********************\n\n";
        cout << "1 - Consultar postes\n2 - Inserir cliente\n3 - Sair\n\nEscolha uma opção: ";
        cin >> op;
        switch (op){
            case 1: {
                app.imprimirMapa();
                break;
            }
            case 2: {
                string identificador = "";
                cout << "\nQual poste o cliente foi lançado? ";
                cin >> identificador;
                app.recomendar(identificador);
                break;
            }
            case 3: {
                cout << "\nSaindo do sistema...\n\n";
                break;
            }
            default: {
                cout << "\nERRO...OPÇÃO INVÁLIDA...ERRO\n\n";
                break;
            }
        }
        cout << "-----------------------------------------------------------------\n";
    }while(op != 3);
}