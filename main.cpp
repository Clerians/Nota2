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

Nodo* armarArbol(int n, int matriz[][],vector<Nodo*>& lista){
    Nodo* raiz = lista[0];

    for(int i = 0; i < n ; ++i){
        if(matriz[0][i] > 0){
            Nodo* hijo = armarArbol(n,matriz,lista);
            raiz->vecinos.puch_back({hijo,matriz[0][i]});
        }
    }
    return raiz;
}

void imprimir(Nodo* nodo, string letra){
    if(nodo == nullptr) return;

    cout <<nodo->nombres.first << " Peso: " << nodo->nombres.second << endl;
    imprimir(vecinos.first, " ");
}

//void dijkstra(){}

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


    vector<Nodo*> lista;

    for(int i = 0; i < n; ++i){
        char nodo = 'A' + i;
        lista.puch_back(new Nodo(nodo,0));
    } 

    Nodo* arbol = armarArbol(n,matriz,lista);

     cout << "Árbol a partir del nodo A:" << endl;
     imprimir(arbol);

    //string letra;
    //cout <<"Ingresa el nodo destino (letra, ej. A-" << char('A' + n - 1) << "): ";
    //cin >> letra;

    //int final = letras - 'A';



    return 0;
}