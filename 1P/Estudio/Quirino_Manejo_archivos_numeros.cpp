// Autor: Quirino Gonzalez Johann David
// Funcion: abre un archivo, guarda los datos en un arreglo,
//           imprime el arreglo, realiza pequeña modificacion a
//           los datos y guarda en un segundo archivo

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <ctime>

using namespace std;

// ================= VARIABLES GLOBALES =================

int i = 0;
int n = 0;
int cn = 0;
int guardacn = 0;
int arreglo[1000];

clock_t t_ini, t_fin;
double secs;

string nombreArchivoE;
string nombreArchivoS;

// ================= ESTRUCTURAS =================

struct Entrada {
    int valor;
} entrada;

struct Salida {
    int valor;
} salida;

// ================= PROGRAMA PRINCIPAL =================

int main() {

    t_ini = clock(); // Inicia medicion de tiempo

    cout << "\nIngrese el nombre del archivo de entrada: ";
    cin >> nombreArchivoE;

    ifstream archivoEntrada(nombreArchivoE.c_str());

    if (!archivoEntrada) {
        cout << "\nError al abrir el archivo de entrada.\n";
        system("pause");
        return 1;
    }

    // Leer archivo y guardar en arreglo
    while (archivoEntrada >> entrada.valor) {
        arreglo[cn] = entrada.valor;
        cn++;
    }

    archivoEntrada.close();

    cout << "\nDatos leidos del archivo:\n";
    for (i = 0; i < cn; i++) {
        cout << arreglo[i] << "  ";
    }

    // Pequeña modificacion (ejemplo: sumar 1 a cada numero)
    for (i = 0; i < cn; i++) {
        arreglo[i] = arreglo[i] + 1;
    }

    cout << "\n\nIngrese el nombre del archivo de salida: ";
    cin >> nombreArchivoS;

    ofstream archivoSalida(nombreArchivoS.c_str());

    if (!archivoSalida) {
        cout << "\nError al crear el archivo de salida.\n";
        system("pause");
        return 1;
    }

    // Guardar datos modificados
    for (i = 0; i < cn; i++) {
        salida.valor = arreglo[i];
        archivoSalida << salida.valor << endl;
        guardacn++;
    }

    archivoSalida.close();

    cout << "\nDatos modificados guardados correctamente.\n";
    cout << "Total de numeros guardados: " << guardacn << endl;

    t_fin = clock(); // Fin medicion
    secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;

    cout << "\nTiempo de ejecucion: " << secs << " segundos\n";

    cout << endl;
    system("pause");
    return 0;
}