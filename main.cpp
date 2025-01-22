#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Nodo {
public:
    pair<char, int> nombres;
    vector<pair<Nodo*, int>> vecinos;

    Nodo(char nombre, int peso) {
        nombres = {nombre, peso};
    }
};

Nodo* armarArbol(int n, vector<vector<int>>& matriz, vector<Nodo*>& lista, vector<bool>& visitado) {
    Nodo* raiz = lista[0];
    visitado[0] = true;

    for (int i = 0; i < n; ++i) {
        if (matriz[0][i] > 0 && !visitado[i]) {
            Nodo* hijo = lista[i];
            raiz->vecinos.push_back({hijo, matriz[0][i]});
            visitado[i] = true;
            armarArbol(n, matriz, lista, visitado);
        }
    }
    return raiz;
}

void imprimir(Nodo* nodo, string letra) {
    if (nodo == nullptr) return;

    cout << letra << nodo->nombres.first << " Peso: " << nodo->nombres.second << endl;
    for (size_t i = 0; i < nodo->vecinos.size(); ++i) {
        imprimir(nodo->vecinos[i].first, letra + " ");
    }
}

int main() {
    string nombre;
    ifstream leerArch;

    while (true) {
        cout << "Nombre del archivo (nombre.txt): " << endl;
        cin >> nombre;
        leerArch.open(nombre);

        if (leerArch.is_open()) {
            break;
        } else {
            cerr << "No se encontró el archivo. Intente otra vez." << endl;
            leerArch.clear();
        }
    }

    int n;
    leerArch >> n;
    leerArch.ignore();

    vector<vector<int>> matriz(n, vector<int>(n));

    // Leer la matriz desde el archivo
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
    for (int i = 0; i < n; ++i) {
        char nodo = 'A' + i;
        lista.push_back(new Nodo(nodo, 0));
    }

    vector<bool> visitado(n, false);
    Nodo* arbol = armarArbol(n, matriz, lista, visitado);

    cout << "Árbol a partir del nodo A:" << endl;
    imprimir(arbol, "");

    return 0;
}
