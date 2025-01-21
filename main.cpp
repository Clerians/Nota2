#include <iostream>
#include <fstream>
#include <vector> 
#include <sstream>

using namespace std;

int main()
{
    string nombre;
    cout <<"nombre del archivo(nombre.txt): " << endl;
    cin >> nombre;

    ifstream leerArch;
    leerArch.open(nombre);
    if(!leerArch.is_open()){
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    int n;
    leerArch >> n;
    leerArch.ignore();

    int matriz[n][n];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j < n - 1) {
                leerArch >> matriz[i][j];
                leerArch.ignore(1, ','); 
            } else {
                leerArch >> matriz[i][j]; 
            }
        }
    }

    leerArch.close();

    string grafo;
    cout <<"Ingresa el nodo destino (letra, ej. F): " << endl;
    cin >> grafo;

    int inicio = 0;

    


    return 0;
}