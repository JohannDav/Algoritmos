// Autor: Quirino Gonzalez Johann David
// Descripcion:
// 1) Leer numeros desde un archivo de texto
// 2) Guardarlos en un arreglo
// 3) Mostrar los numeros en pantalla
// 4) Guardarlos en un nuevo archivo
// 5) Capturar caracteres, numeros y nombres manualmente

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

// ================== VARIABLES GLOBALES ==========================

// Variable auxiliar utilizada como contador en ciclos repetitivos
int i = 0;

// Variable que almacena la opcion seleccionada en el menu
int opcion = 0;

// Controla la repeticion del menu principal
// 0 = continuar ejecutando
// 1 = salir del programa
int repeticion = 0;

// Arreglo que almacena caracteres capturados manualmente
char caracteres[100];

// Arreglo que almacena numeros capturados manualmente
int numeros[100];

// Arreglo que almacena nombres capturados manualmente
string nombres[100];


// ================================================================
// ========== VARIABLES PARA MANEJO DE ARCHIVOS ==================
// ================================================================

// Arreglo principal donde se almacenan los numeros leidos del archivo
int arreglo[100];

// Variable que indica la cantidad de datos a trabajar
// Representa el tamaño logico del arreglo
int n = 0;

// Contador de numeros leidos desde el archivo de entrada
int cn = 0;

// Contador de numeros guardados en el archivo de salida
int guardacn = 0;


// ================================================================
// ================== ESTRUCTURAS ================================
// ================================================================

// Estructura utilizada para leer temporalmente
// un numero desde el archivo
struct Entrada {
    int valor;   // Guarda el numero leido
} entrada;

// Estructura utilizada para escribir temporalmente
// un numero en el archivo de salida
struct Salida {
    int valor;   // Guarda el numero a escribir
} salida;


// ================================================================
// ================== VARIABLES DE ARCHIVOS =======================
// ================================================================

// Almacena el nombre del archivo de entrada
string nombreArchivoE;

// Almacena el nombre del archivo de salida
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
int impresionNumerosArchivo();
int menu();


// ================================================================
// ================== FUNCIONES ===================================
// ================================================================


// ------------------------------------------------
// Funcion: capturaCaracteres()
// Permite capturar caracteres manualmente
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
// Muestra los caracteres capturados
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
// Permite capturar numeros manualmente
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
// Muestra los numeros capturados manualmente
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
// Permite capturar nombres usando getline
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
// Muestra los nombres capturados
// ------------------------------------------------
int impresionNombres() {

    cout << "\n\nNombres : ";

    for (i = 0; i < n; i++) {
        cout << endl << nombres[i];
    }

    return 0;
}


// ------------------------------------------------
// Funcion: leeArchivo()
// Lee numeros enteros desde un archivo de texto
// y los almacena en el arreglo global "arreglo"
// ------------------------------------------------
int leeArchivo() {

    FILE *archivo1;

    cout << "\nTeclea el nombre del archivo de entrada (sin espacios): ";
    cin >> nombreArchivoE;

    // Se agrega la extension .txt
    nombreArchivoE += ".txt";

    // Se abre el archivo en modo lectura
    archivo1 = fopen(nombreArchivoE.c_str(), "r");

    if (archivo1 == NULL) {
        cout << "\nNo se puede abrir el archivo";
        exit(1);
    }
    else {
        cout << "\nSe abrio correctamente el archivo " << nombreArchivoE;
    }

    cn = 0;

    // Lee numero por numero hasta el final del archivo
    for (int i = 0; !feof(archivo1); i++) {
        fscanf(archivo1, "%i", &entrada.valor);
        arreglo[i] = entrada.valor;
        cn++;
    }

    cn--;   // Ajuste por lectura extra
    n = cn; // Actualiza cantidad de datos

    cout << "\n\nSe ha generado el arreglo con los datos del archivo de entrada";
    cout << "\nLa cantidad de numeros contenidos en el arreglo son: " << cn << "\n\n";

    fclose(archivo1);

    return 0;
}


// ------------------------------------------------
// Funcion: guardaArchivo()
// Guarda los numeros almacenados en el arreglo
// en un archivo de salida
// ------------------------------------------------
int guardaArchivo() {

    FILE *archivo2;

    // Se agrega nombre fijo al archivo de salida
    nombreArchivoS += "miranda.txt";

    archivo2 = fopen(nombreArchivoS.c_str(), "w");

    if (archivo2 == NULL) {
        cout << "\nNo se puede abrir el archivo";
        exit(1);
    }
    else {
        cout << "\nSe abrio el archivo " << nombreArchivoS << " correctamente\n";
    }

    cout << "\n\nGuarda los numeros contenidos en el arreglo en el archivo";

    guardacn = 0;

    // Escribe numero por numero en el archivo
    for (i = 0; i < n; i++) {
        salida.valor = arreglo[i];
        fprintf(archivo2, "%i\n", salida.valor);
        guardacn++;
    }

    cout << "\n\nTotal de numeros guardados en el segundo archivo son: " << guardacn;
    cout << "\n\n";

    fclose(archivo2);

    return 0;
}


// ------------------------------------------------
// Funcion: impresionNumerosArchivo()
// Muestra los numeros leidos del archivo
// ------------------------------------------------
int impresionNumerosArchivo() {

    cout << "\n\nNumeros : ";

    for (i = 0; i < n; i++) {
        cout << arreglo[i] << "  ";
    }

    return 0;
}


// ================================================================
// ================== FUNCION PRINCIPAL ===========================
// ================================================================
int main() {

    // Ciclo principal del programa
    for (repeticion = 0; repeticion == 0;) {

        menu();

        switch (opcion) {

            case 1:
                leeArchivo();
                impresionNumerosArchivo();
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

// ================== MENU ========================================
int menu() {

    system("cls");

    cout << "\n\tMenu";
    cout << "\n1 - Lectura de archivo de numeros";
    cout << "\n2 - Captura de caracteres";
    cout << "\n3 - Captura de numeros";
    cout << "\n4 - Captura de nombres";
    cout << "\n5 - Salir del menu";
    cout << "\nTeclee la opcion deseada : ";

    cin >> opcion;

    return 0;
}