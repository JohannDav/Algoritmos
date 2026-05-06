//Autor: Quirino González Johann David
//Creacion de archivos de texto con números aleatorios
#include <stdlib.h>
#include <stdio.h>
#include <string>       // Se puede añadir la biblioteca "string.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

// Variables globales
int i = 0, f = 0, v = 0, inicio = 0, n = 0;
string nombrearchivo;

// Estructura que permite generar el archivo
FILE *archivo1;    // Estructura que permite generar la fila del archivo

struct Registro {
    int valor;
} entrada;


int main() {

    // Creación de archivo
    srand(time(NULL));   // Inicializa la semilla aleatoria

    printf("\nTeclea el nombre que va a tener el archivo: ");
    cin >> nombrearchivo;

    nombrearchivo += ".txt";   // Se agrega la extensión ".txt"

    archivo1 = fopen(nombrearchivo.c_str(), "w");   // Se abre el archivo en modo escritura

    if (archivo1 == NULL) {
        printf("\nNo se puede generar el archivo");
        exit(1);
    }
    else {
        printf("\nSe genero el espacio para los datos del archivo %s\n", nombrearchivo.c_str());
    }

    // Establecer el numero de registros en el archivo
    cout << "\nTeclee la cantidad de numeros que desea que contenga el archivo: ";
    cin >> n;

    // Establecer el rango de numeros dentro del archivo
    cout << "\nLos numeros van a ser generados con un rango";
    cout << "\n - Maximo de 4 digitos";
    cout << "\n - Debe teclear el numero inicial del rango de los datos a generar (ejemplo: 0)";
    cout << "\n - Debe teclear el numero final que va a tener el rango (ejemplo: 100)";
    cout << "\n   No debe exceder el rango final del numero 10000";

    do {
        cout << "\n\nTeclee el numero inicial que va a tener el rango: ";
        cin >> i;
        inicio = i;

        cout << "\nTeclee el numero final que va a tener el rango: ";
        cin >> f;

    } while (f - i > 10001);   // Observar que se analiza el numero final

    // Se generan numeros aleatorios dentro del archivo
    // Los numeros se van a encontrar en un rango
    for (i = 0; i < n; i++) {
        v = inicio + rand() % (f + 1 - inicio);
        entrada.valor = v;
        fprintf(archivo1, "%i\n", entrada.valor);
    }

    cout << "\n\nSe genero correctamente el archivo con " << i << " numeros";

    // Cerrar el archivo
    fclose(archivo1);

    return 0;
}