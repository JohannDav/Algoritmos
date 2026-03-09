// Autor: Quirino Gonzalez Johann David
// Programa exclusivo para manejo de CARACTERES
// Incluye: captura, impresion, analisis, busqueda,
// ordenamiento burbuja y manejo de archivo

#include <iostream>
#include <fstream>
#include <cctype>
#include <stdlib.h>

using namespace std;

// ================= VARIABLES GLOBALES =================

char caracteres[100];
int n = 0;
int i = 0;
int opcion = 0;
int repeticion = 0;

// ================= PROTOTIPOS =================

int menu();
int numeroDatos();
int capturaCaracteres();
int impresionCaracteres();
int analizarCaracteres();
int busquedaCaracter();
int burbujaCaracteres();
int guardarArchivo();
int leerArchivo();

// ================= FUNCIONES =================

int numeroDatos() {
    cout << "\nCantidad de caracteres: ";
    cin >> n;
    return 0;
}

int capturaCaracteres() {
    cout << "\nTeclee los caracteres: ";
    for (i = 0; i < n; i++)
        cin >> caracteres[i];
    return 0;
}

int impresionCaracteres() {
    cout << "\nCaracteres:\n";
    for (i = 0; i < n; i++)
        cout << caracteres[i] << "  ";
    return 0;
}

// -------- ANALISIS DE TIPO --------

int analizarCaracteres() {

    for (i = 0; i < n; i++) {

        cout << "\nCaracter: " << caracteres[i] << " -> ";

        if (isupper(caracteres[i]))
            cout << "Es mayuscula";
        else if (islower(caracteres[i]))
            cout << "Es minuscula";
        else if (isdigit(caracteres[i]))
            cout << "Es numero";
        else if (ispunct(caracteres[i]))
            cout << "Es simbolo";
        else
            cout << "Otro tipo";
    }

    return 0;
}

// -------- BUSQUEDA --------

int busquedaCaracter() {

    char buscado;
    int bandera = 0;

    cout << "\nCaracter a buscar: ";
    cin >> buscado;

    for (i = 0; i < n; i++) {
        if (caracteres[i] == buscado) {
            cout << "\nEncontrado en posicion: " << i;
            bandera = 1;
        }
    }

    if (bandera == 0)
        cout << "\nNo encontrado";

    return 0;
}

// -------- ORDENAMIENTO BURBUJA --------

int burbujaCaracteres() {

    char aux;

    for (int j = 0; j < n - 1; j++) {
        for (i = 0; i < n - 1; i++) {
            if (caracteres[i] > caracteres[i + 1]) {
                aux = caracteres[i];
                caracteres[i] = caracteres[i + 1];
                caracteres[i + 1] = aux;
            }
        }
    }

    cout << "\nOrdenamiento completado correctamente";
    return 0;
}

// -------- GUARDAR EN ARCHIVO --------

int guardarArchivo() {

    ofstream archivo("caracteres.txt");

    for (i = 0; i < n; i++)
        archivo << caracteres[i] << endl;

    archivo.close();

    cout << "\nArchivo guardado correctamente";
    return 0;
}

// -------- LEER DESDE ARCHIVO --------

int leerArchivo() {

    ifstream archivo("caracteres.txt");

    n = 0;

    while (archivo >> caracteres[n])
        n++;

    archivo.close();

    cout << "\nArchivo leido correctamente";
    return 0;
}

// ================= MENU =================

int menu() {

    system("cls");

    cout << "\n\tMENU CARACTERES";
    cout << "\n1 - Capturar caracteres";
    cout << "\n2 - Imprimir caracteres";
    cout << "\n3 - Analizar tipo";
    cout << "\n4 - Buscar caracter";
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

        case 1: numeroDatos(); capturaCaracteres(); break;
        case 2: impresionCaracteres(); break;
        case 3: analizarCaracteres(); break;
        case 4: busquedaCaracter(); break;
        case 5: burbujaCaracteres(); break;
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