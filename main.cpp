#include <iostream>
#include <fstream>
#include <vector> 
#include <sstream>

using namespace std;

class Nodo{
    public:
    pair<char,int> nombres;
    vector<pair<Nodo*, int>> vecinos;
    Nodo(char nombre, int peso){
        nombres = {nombre,peso};
    }
};

void dijkstra(){

}

int main()
{
    string nombre;
    ifstream leerArch;

    while(true){
        cout <<"nombre del archivo(nombre.txt): " << endl;
        cin >> nombre;
        leerArch.open(nombre);

        if(leerArch.is_open()){
            break;
        }else{
            cerr << "No se encontro el txt. Intente otra vez." << endl;
            leerArch.clear();
        }
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