// Autor: Quirino Gonzalez Johann David
// Programa exclusivo para manejo de NUMEROS

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

// ================= VARIABLES GLOBALES =================

int numeros[100];
int n = 0;
int i = 0;
int opcion = 0;
int repeticion = 0;

// ================= PROTOTIPOS =================

int menu();
int numeroDatos();
int capturaNumeros();
int impresionNumeros();
int sumaNumeros();
int busquedaNumero();
int burbuja();
int guardarArchivo();
int leerArchivo();

// ================= FUNCIONES =================

int numeroDatos() {
    cout << "\nCantidad de numeros: ";
    cin >> n;
    return 0;
}

int capturaNumeros() {
    cout << "\nTeclee los numeros: ";
    for (i = 0; i < n; i++)
        cin >> numeros[i];
    return 0;
}

int impresionNumeros() {
    cout << "\nNumeros:\n";
    for (i = 0; i < n; i++)
        cout << numeros[i] << "  ";
    return 0;
}

int sumaNumeros() {
    int suma = 0;
    for (i = 0; i < n; i++)
        suma += numeros[i];

    cout << "\nSuma total: " << suma;
    return 0;
}

int busquedaNumero() {
    int buscado, bandera = 0;
    cout << "\nNumero a buscar: ";
    cin >> buscado;

    for (i = 0; i < n; i++) {
        if (numeros[i] == buscado) {
            cout << "\nEncontrado en posicion: " << i;
            bandera = 1;
        }
    }

    if (bandera == 0)
        cout << "\nNo encontrado";

    return 0;
}

int burbuja() {
    int aux;
    for (int j = 0; j < n - 1; j++) {
        for (i = 0; i < n - 1; i++) {
            if (numeros[i] > numeros[i + 1]) {
                aux = numeros[i];
                numeros[i] = numeros[i + 1];
                numeros[i + 1] = aux;
            }
        }
    }
    cout << "\nOrdenamiento completado";
    return 0;
}

int guardarArchivo() {
    ofstream archivo("numeros.txt");
    for (i = 0; i < n; i++)
        archivo << numeros[i] << endl;
    archivo.close();
    cout << "\nArchivo guardado correctamente";
    return 0;
}

int leerArchivo() {
    ifstream archivo("numeros.txt");
    n = 0;
    while (archivo >> numeros[n])
        n++;
    archivo.close();
    cout << "\nArchivo leido correctamente";
    return 0;
}

int menu() {
    system("cls");
    cout << "\n\tMENU NUMEROS";
    cout << "\n1 - Capturar numeros";
    cout << "\n2 - Imprimir numeros";
    cout << "\n3 - Sumar numeros";
    cout << "\n4 - Buscar numero";
    cout << "\n5 - Ordenar (Burbuja)";
    cout << "\n6 - Guardar en archivo";
    cout << "\n7 - Leer archivo";
    cout << "\n8 - Salir";
    cout << "\nOpcion: ";
    cin >> opcion;
    return 0;
}

// ================= MAIN =================

int main() {

    while (repeticion == 0) {

        menu();

        switch (opcion) {

        case 1: numeroDatos(); capturaNumeros(); break;
        case 2: impresionNumeros(); break;
        case 3: sumaNumeros(); break;
        case 4: busquedaNumero(); break;
        case 5: burbuja(); break;
        case 6: guardarArchivo(); break;
        case 7: leerArchivo(); break;
        case 8: repeticion = 1; break;
        default: cout << "\nOpcion invalida";
        }

        cout << endl;
        system("pause");
    }

    return 0;
}