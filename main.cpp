#include <iostream>
#include <fstream>
#include <vector> 
#include <sstream>

using namespace std;

int main()
{
    string nombre;
    cout <<"nombre del archivo(" "nombre.txt" "): " << endl;
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
        for (int j = 0; j < n - 1; ++j) {
                leerArch >> matriz[i][j];
                leerArch.ignore(1, ','); 
        }
    }

    leerArch.close();

    cout << "Contenido de la matriz:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}