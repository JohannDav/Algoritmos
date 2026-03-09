// ================================================================
// Autor: Quirino Gonzalez Johann David
// Descripcion:
// Programa que permite:
//
// 1) Leer caracteres desde un archivo de texto
// 2) Guardarlos en un arreglo
// 3) Mostrar los caracteres en pantalla
// 4) Guardar los caracteres en un nuevo archivo
// 5) Capturar caracteres, numeros y nombres manualmente
//
// El programa trabaja principalmente con archivos de texto que
// contienen CARACTERES.
// ================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;


// ================================================================
// ================== VARIABLES GLOBALES ==========================
// ================================================================

// Variable auxiliar usada como contador en ciclos for
int i = 0;

// Guarda la opcion que el usuario selecciona en el menu
int opcion = 0;

// Controla la repeticion del menu principal
// 0 = seguir mostrando menu
// 1 = salir del programa
int repeticion = 0;

// Arreglo para almacenar caracteres capturados manualmente
char caracteres[100];

// Arreglo para almacenar numeros capturados manualmente
int numeros[100];

// Arreglo para almacenar nombres capturados manualmente
string nombres[100];


// ================= VARIABLES PARA MANEJO DE ARCHIVOS =============

// Arreglo principal donde se almacenan los caracteres
// leidos desde el archivo de entrada
char arreglo[100];

// Variable que indica la cantidad de datos que se trabajaran
// (numero de caracteres almacenados)
int n = 0;

// Contador de numeros/caracteres leidos del archivo
int cn = 0;

// Contador de caracteres guardados en el archivo de salida
int guardacn = 0;


// ================= ESTRUCTURAS =================

// Estructura utilizada para leer un caracter
// desde el archivo de entrada
struct Entrada {
    char valor;   // Guarda temporalmente el caracter leido
} entrada;

// Estructura utilizada para guardar un caracter
// en el archivo de salida
struct Salida {
    char valor;   // Guarda temporalmente el caracter a escribir
} salida;


// ================= NOMBRES DE ARCHIVOS =================

// Guarda el nombre del archivo de entrada
string nombreArchivoE;

// Guarda el nombre del archivo de salida
string nombreArchivoS;


// ================================================================
// ================== PROTOTIPOS ==================================
// ================================================================

int capturaCaracteres();
int impresionCaracteres();
int capturaNumeros();
int impresionNumeros();
int capturaNombres();
int impresionNombres();
int leeArchivo();
int guardaArchivo();
int impresionArchivo();
int menu();


// ================================================================
// ================== FUNCIONES ===================================
// ================================================================


// ------------------------------------------------
// Funcion: leeArchivo()
// Descripcion:
// Lee caracteres desde un archivo de texto
// y los almacena en el arreglo global "arreglo"
// ------------------------------------------------
int leeArchivo() {

    FILE *archivo1;   // Apuntador al archivo

    cout << "\nTeclea el nombre del archivo de entrada (sin espacio): ";
    cin >> nombreArchivoE;

    // Se agrega la extension .txt al nombre del archivo
    nombreArchivoE += ".txt";

    // Se abre el archivo en modo lectura
    archivo1 = fopen(nombreArchivoE.c_str(), "r");

    // Verifica si el archivo se pudo abrir
    if (archivo1 == NULL) {
        cout << "\nNo se puede abrir el archivo";
        exit(1);
    }
    else {
        cout << "\nSe abrio correctamente el archivo " << nombreArchivoE;
    }

    cn = 0;   // Inicializa contador

    // Lee caracter por caracter hasta llegar al final del archivo
    for (int i = 0; !feof(archivo1); i++) {
        fscanf(archivo1, "%c\n", &entrada.valor);
        arreglo[i] = entrada.valor;
        cn++;
    }

    cn--;      // Ajuste por lectura extra al final
    n = cn;    // Se actualiza cantidad de caracteres

    cout << "\n\nSe ha generado el arreglo con los datos del archivo";
    cout << "\nLa cantidad de caracteres contenidos en el arreglo son: " << cn << "\n\n";

    fclose(archivo1);  // Cierra el archivo

    return 0;
}


// ------------------------------------------------
// Funcion: guardaArchivo()
// Descripcion:
// Guarda los caracteres almacenados en el arreglo
// en un archivo de salida
// ------------------------------------------------
int guardaArchivo() {

    FILE *archivo2;

    cout << "\nTeclea el nombre del archivo de salida: ";
    cin >> nombreArchivoS;

    nombreArchivoS += ".txt";

    archivo2 = fopen(nombreArchivoS.c_str(), "w");

    if (archivo2 == NULL) {
        cout << "\nNo se puede abrir el archivo";
        exit(1);
    }
    else {
        cout << "\nSe abrio el archivo " << nombreArchivoS << " correctamente\n";
    }

    cout << "\n\nGuarda los caracteres contenidos en el arreglo en el archivo";

    guardacn = 0;

    // Escribe caracter por caracter en el archivo
    for (i = 0; i < n; i++) {
        salida.valor = arreglo[i];
        fprintf(archivo2, "%c\n", salida.valor);
        guardacn++;
    }

    cout << "\n\nTotal de caracteres guardados en el archivo son: " << guardacn;
    cout << "\n\n";

    fclose(archivo2);

    return 0;
}


// ------------------------------------------------
// Funcion: impresionArchivo()
// Descripcion:
// Muestra en pantalla los caracteres almacenados
// en el arreglo principal
// ------------------------------------------------
int impresionArchivo() {

    cout << "\n\nCaracteres del archivo : ";

    for (i = 0; i < n; i++) {
        cout << arreglo[i] << "  ";
    }

    return 0;
}


// ------------------------------------------------
// Funcion: capturaCaracteres()
// Descripcion:
// Permite capturar manualmente caracteres
// ------------------------------------------------
int capturaCaracteres() {

    cout << "\nTeclee " << n << " caracteres separados por un espacio : ";

    for (i = 0; i < n; i++) {
        cin >> caracteres[i];
    }

    return 0;
}


// ------------------------------------------------
// Funcion: impresionCaracteres()
// ------------------------------------------------
int impresionCaracteres() {

    cout << "\nUsted tecleo " << n << " caracteres : ";

    for (i = 0; i < n; i++) {
        cout << caracteres[i] << "  ";
    }

    return 0;
}


// ------------------------------------------------
// Funcion: capturaNumeros()
// ------------------------------------------------
int capturaNumeros() {

    cout << "\nTeclee " << n << " numeros separados por un espacio : ";

    for (i = 0; i < n; i++) {
        cin >> numeros[i];
    }

    return 0;
}


// ------------------------------------------------
// Funcion: impresionNumeros()
// ------------------------------------------------
int impresionNumeros() {

    cout << "\n\nNumeros : ";

    for (i = 0; i < n; i++) {
        cout << numeros[i] << "  ";
    }

    return 0;
}


// ------------------------------------------------
// Funcion: capturaNombres()
// ------------------------------------------------
int capturaNombres() {

    cout << "\nTeclee " << n << " nombres";

    for (i = 0; i < n; i++) {
        cout << "\nTeclee el nombre " << i + 1 << " : ";
        fflush(stdin);
        getline(cin, nombres[i]);
        fflush(stdin);
    }

    return 0;
}


// ------------------------------------------------
// Funcion: impresionNombres()
// ------------------------------------------------
int impresionNombres() {

    cout << "\n\nNombres : ";

    for (i = 0; i < n; i++) {
        cout << endl << nombres[i];
    }

    return 0;
}


// ================================================================
// ================== FUNCION PRINCIPAL ===========================
// ================================================================
int main() {

    // Ciclo que mantiene activo el menu hasta que el usuario decida salir
    for (repeticion = 0; repeticion == 0;) {

        menu();

        switch (opcion) {

            case 1:
                leeArchivo();
                impresionArchivo();
                break;

            case 2:
                capturaCaracteres();
                impresionCaracteres();
                break;

            case 3:
                capturaNumeros();
                impresionNumeros();
                break;

            case 4:
                capturaNombres();
                impresionNombres();
                break;

            case 5:
                cout << "\nHasta luego";
                repeticion++;
                break;

            default:
                cout << "\nOpcion invalida";
        }

        cout << endl;
        system("pause");
    }

    return 0;
}


// ================================================================
// ================== MENU ========================================
// ================================================================
int menu() {

    system("cls");

    cout << "\n\tMenu";
    cout << "\n1 - Lectura de archivo de caracteres";
    cout << "\n2 - Captura de caracteres";
    cout << "\n3 - Captura de numeros";
    cout << "\n4 - Captura de nombres";
    cout << "\n5 - Salir del menu";
    cout << "\nTeclee la opcion deseada : ";

    cin >> opcion;

    return 0;
}