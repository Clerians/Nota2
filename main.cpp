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

pair<vector<char>, int> dijkstra(Nodo* inicio, Nodo* fin, int n) {
    vector<int> distancia(n, 1000000);
    vector<Nodo*> visitados(n, nullptr);
    distancia[inicio->nombres.first - 'A'] = 0;
    
    queue<Nodo*> cola;
    cola.push(inicio);

    while (!cola.empty()) {
        Nodo* aux = cola.front();
        cola.pop();

        for (int i = 0; i < aux->vecinos.size(); i++) {
            Nodo* siguiente = aux->vecinos[i].first;
            int peso = aux->vecinos[i].second;
            int indiceSiguiente = siguiente->nombres.first - 'A';

            if (distancia[aux->nombres.first - 'A'] + peso < distancia[indiceSiguiente]) {
                distancia[indiceSiguiente] = distancia[aux->nombres.first - 'A'] + peso;
                visitados[indiceSiguiente] = aux;
                cola.push(siguiente);
            }
        }
    }

    vector<char> recorrido;
    for (Nodo* a = fin; a != nullptr; a = visitados[a->nombres.first - 'A']) {
        recorrido.push_back(a->nombres.first);
    }

    vector<char> recorridoSeverla;
    for (int i = recorrido.size() - 1; i >= 0; i--) {
        recorridoSeverla.push_back(recorrido[i]);
    }

    int pesoTotal = distancia[fin->nombres.first - 'A'];
    return {recorridoSeverla, pesoTotal};
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
    cout << "Nodos que se pueden visitar: " << endl;
    for (int i = 0; i < n; i++) {
        char nodo = 'A' + i;
        lista.push_back(new Nodo(nodo, 0));
        cout<< nodo << " ";
    }cout << endl;

    Nodo* arbol = armarArbol(n, matriz, lista);

    char final;
    int indice;

    while(true){
        cout << "Donde vamos? (El camino empieza en A): " << endl;
        cin >> final;
        final = toupper(final);
        indice = final - 'A';

        if (indice < n && indice >= 0) {
            break;
        } else {
            cout << "Destino no válido" << endl;
        }
    }

    
    pair<vector<char>, int> resultado = dijkstra(lista[0], lista[indice], n);
    vector<char> camino = resultado.first;
    int pesoTotal = resultado.second;

    cout << "Tiempo de viaje: " << pesoTotal << endl;

    cout << "Camino más corto de A a " << final << ": ";
    for (char nodo : camino) {
        cout << nodo << " ";
    }
    cout << endl;
        
    return 0;
}
