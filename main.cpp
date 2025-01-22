#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <climits>

using namespace std;

class Nodo {
public:
    pair<char, int> nombres;
    vector<pair<Nodo*, int>> vecinos;

    Nodo(char nombre, int peso) {
        nombres = {nombre, peso};
    }
};

Nodo* armarArbol(int n, vector<vector<int>>& matriz, vector<Nodo*>& lista) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matriz[i][j] > 0) {
                Nodo* hijo = lista[j];
                int peso = matriz[i][j];
                lista[i]->vecinos.push_back({hijo, peso});
            }
        }
    }
    return lista[0];
}

vector<char> dijkstra(Nodo* inicio, Nodo* fin, int n) {
    vector<int> distancias(n, INT_MAX);
    vector<Nodo*> previos(n, nullptr);
    distancias[inicio->nombres.first - 'A'] = 0;
    
    queue<Nodo*> q;
    q.push(inicio);

    while (!q.empty()) {
        Nodo* nodoActual = q.front();
        q.pop();

        for (int i = 0; i < nodoActual->vecinos.size(); i++) {
            Nodo* nodoVecino = nodoActual->vecinos[i].first;
            int peso = nodoActual->vecinos[i].second;
            int indiceVecino = nodoVecino->nombres.first - 'A';

            if (distancias[nodoActual->nombres.first - 'A'] + peso < distancias[indiceVecino]) {
                distancias[indiceVecino] = distancias[nodoActual->nombres.first - 'A'] + peso;
                previos[indiceVecino] = nodoActual;
                q.push(nodoVecino);
            }
        }
    }

    vector<char> camino;
    for (Nodo* at = fin; at != nullptr; at = previos[at->nombres.first - 'A']) {
        camino.push_back(at->nombres.first);
    }

    // Invertir el camino sin usar reverse()
    vector<char> caminoInvertido;
    for (int i = camino.size() - 1; i >= 0; i--) {
        caminoInvertido.push_back(camino[i]);
    }

    return caminoInvertido;
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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
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
    for (int i = 0; i < n; i++) {
        char nodo = 'A' + i;
        lista.push_back(new Nodo(nodo, 0));
    }

    Nodo* arbol = armarArbol(n, matriz, lista);

    char final;
    cout << "¿A dónde vamos? (camino de 'A' a " << char('A' + n - 1) << "): " << endl;
    cin >> final;

    int indice = final - 'A';

    if (indice >= n) {
        cout << "Destino no válido" << endl;
    } else {
        vector<char> camino = dijkstra(lista[0], lista[indice], n);
        cout << "Camino más corto de A a " << final << ": ";
        for (char nodo : camino) {
            cout << nodo << " ";
        }
        cout << endl;
    }
    
    return 0;
}
