// Autor: Quirino González Johann David
// Creacion de archivos de texto con caracteres aleatorios

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

// Variables globales
int i = 0, n = 0;
char v;
string nombrearchivo;

// Estructura que permite generar el archivo
FILE *archivo1;

struct Registro {
    char valor;
} entrada;

int main() {

    // Inicializa la semilla aleatoria
    srand(time(NULL));

    printf("\nTeclea el nombre que va a tener el archivo: ");
    cin >> nombrearchivo;

    nombrearchivo += ".txt";

    archivo1 = fopen(nombrearchivo.c_str(), "w");

    if (archivo1 == NULL) {
        printf("\nNo se puede generar el archivo");
        exit(1);
    }
    else {
        printf("\nSe genero el espacio para los datos del archivo %s\n", nombrearchivo.c_str());
    }

    // Cantidad de caracteres
    cout << "\nTeclee la cantidad de caracteres que desea que contenga el archivo: ";
    cin >> n;

    cout << "\nLos caracteres se generaran de forma aleatoria.";
    cout << "\nIncluyen letras mayusculas, minusculas y numeros.\n";

    // Generacion de caracteres aleatorios
    for (i = 0; i < n; i++) {

        int tipo = rand() % 3;

        if (tipo == 0)
            v = 'A' + rand() % 26;      // Mayusculas
        else if (tipo == 1)
            v = 'a' + rand() % 26;      // Minusculas
        else
            v = '0' + rand() % 10;      // Numeros

        entrada.valor = v;
        fprintf(archivo1, "%c\n", entrada.valor);
    }

    cout << "\n\nSe genero correctamente el archivo con " << i << " caracteres";

    fclose(archivo1);

    return 0;
}