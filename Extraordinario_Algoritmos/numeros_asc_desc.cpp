// Autor: Quirino González Johann David
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <cmath>
#include <algorithm>  // Libreria necesaria para la funcion sort()
#include <limits>      // Para numeric_limits
using namespace std;

// ================= Declaracion de variables globales =================
int i = 0;
int j = 0;
int k = 0;
int l = 0;
int n = 0;
int cn = 0;
int guardacn = 0;
int banderaEncontro = 0;
int aux = 0;
int aux_num = 0;
int opcion = 0;
int repeticion = 0;
int numeroBuscar;
float arreglo[100][5];  // Cambiado a matriz 100x5 como en codigo de la profesora
float arreglo2[100];    // Arreglo auxiliar
int inferior = 0;               //Busqueda binaria
int superior = n;               //Busqueda binaria
int buscar = 0;                 //Busqueda Binaria
int izq=0, der=0, pivote=0;     //Quick Sort (ya no se usa, se mantiene por compatibilidad)
float temporal =0;              //Quick Sort (ya no se usa, se mantiene por compatibilidad)
int limite_izq=0;               //Quick Sort (ya no se usa, se mantiene por compatibilidad)
int limite_der=0;               //Quick Sort (ya no se usa, se mantiene por compatibilidad)
clock_t t_ini, t_fin;           //Tiempo
double secs;                    //Tiempo
string nombreArchivoE;
string nombreArchivoS;

// Variables globales para IMC
float divisor = 0;  // Variable para calcular el divisor (estatura^2)
float imc = 0;      // Variable para almacenar el IMC calculado

// Variables para orden ascendente/descendente
int ordenOpcion = 1;  // 1 = Ascendente, 2 = Descendente
bool mensajeCambioOrden = false;

// Banderas
int hayDatos = 0;        // Bandera para validar si hay datos en el arreglo
int datosOrdenados = 0;  // Bandera para validar si los datos estan ordenados

// Variables adicionales para Shell, Flotacion, Insercion, Seleccion y HeapSort
int subarreglo = 0;     // Para Shell sort
float temp = 0;         // Para Shell sort e Insercion
float numMayor = 0;     // Para Flotacion
int min_idx = 0;        // Para Seleccion
int masgrande = 0;      // Para HeapSort
float auxiliar = 0;     // Para HeapSort
float auxMatriz[1][5];  // Auxiliar para intercambiar filas completas

// ================= Funcion auxiliar para swap de filas =================
void swapFilas(float fila1[5], float fila2[5]) {
    for (int idx = 0; idx < 5; idx++) {
        swap(fila1[idx], fila2[idx]);
    }
}

// ================= Funciones para leer entero con validacion =================
int leerEntero() {
    int valor;
    while (true) {
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Ingrese un numero entero: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

// ================= Funcion para seleccionar orden =================
int seleccionarOrden() {
    cout << "\nSeleccione el orden:" << endl;
    cout << "1. Ascendente (menor a mayor)" << endl;
    cout << "2. Descendente (mayor a menor)" << endl;
    cout << "Opcion: ";
    int opcionOrden = leerEntero();
    
    if (opcionOrden <= 0 || opcionOrden > 2) {
        cout << "Opcion invalida, se usara orden ascendente por defecto" << endl;
        return 1;
    }
    
    if (ordenOpcion != opcionOrden && !mensajeCambioOrden) {
        cout << (opcionOrden == 1 ? "Cambiando a orden ascendente..." : "Cambiando a orden descendente...") << endl;
        mensajeCambioOrden = true;
    }
    
    return opcionOrden;
}

// ================= Funcion de comparacion para sort() =================
bool compararPorID(const float fila1[5], const float fila2[5]) {
    return fila1[0] < fila2[0];
}

// ================= Declaracion de prototipos =================
int numeroDatos();
int capturaNumeros();
int impresionNumeros();
int menu();
int leeArchivo();
int guardaArchivo();
int busquedaNumeros();
void busquedaBin();
int busquedaBinaria();
int burbuja();
int flotacion();
int insercion();
int seleccion();
int shell();
int ordenamientoHeapSort();
void identificar_mayor(float arreglo[][5], int i, int n);
void conformar_arbol(float arreglo[][5], int n);
int ordenamientoQuick();
int identAlfaNumerico();
int identVotante();
int identInscrito();
int calculoIMC();
int analisisIMCHombres();
int analisisIMCMujeres();

// Declaracion de la estructura que permite leer datos del archivo de entrada
struct Entrada {
    int id;
    int sexo;
    float peso;
    float estatura;
    float imc;
} entrada;

struct Salida {
    int id;
    int sexo;
    float peso;
    float estatura;
    float imc;
} salida;

// ================= Captura de numeros =================
int capturaNumeros() {
    cout << "\nTeclee " << n << " numeros separados por un espacio : ";
    for (i = 0; i < n; i++) {
        cin >> arreglo[i][0];
    }
    hayDatos = 1;
    datosOrdenados = 0;
    return (0);
}

// ================= Lectura del archivo =================
int leeArchivo() {
    FILE *archivo1;
    cout << "\nTeclea el nombre del archivo de entrada (sin espacio, ni caracteres especiales):   ";
    cin >> nombreArchivoE;
    nombreArchivoE += ".txt";
    archivo1 = fopen(nombreArchivoE.c_str(), "r");

    if (archivo1 == NULL) {
        cout << "\nNo se puede abrir el archivo ";
        return (0);
    }
    else {
        cout << "\nSe abrio correctamente el archivo " << nombreArchivoE.c_str();
    }

    cn = 0;
    for (int i = 0; !feof(archivo1); i++) {
        fscanf(archivo1, "%i %i %f %f", &entrada.id, &entrada.sexo, &entrada.peso, &entrada.estatura);
        arreglo[i][0] = entrada.id;
        arreglo[i][1] = entrada.sexo;
        arreglo[i][2] = entrada.peso;
        arreglo[i][3] = entrada.estatura;
        cn++;
    }
    cn--;
    cout << "\n\nSe ha generado el arreglo con los datos del archivo de entrada";
    cout << "\nLa cantidad de numeros contenidos en el arreglo son:  " << cn << "\n\n";
    n = cn;
    hayDatos = 1;
    datosOrdenados = 0;
    fclose(archivo1);
    return (0);
}

// ================= Guarda archivo =================
int guardaArchivo() {
    FILE *archivo2;
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }
    if (datosOrdenados == 0) {
        cout << "\n ERROR: No se puede guardar el archivo porque los datos no estan ordenados. \n";
        cout << " Primero ordene los datos con cualquier metodo de ordenamiento. \n";
        return (0);
    }
    nombreArchivoS = "Quirino.txt";
    archivo2 = fopen(nombreArchivoS.c_str(), "w");
    if (archivo2 == NULL) {
        cout << "\nNo se puede abrir el archivo ";
        return (0);
    }
    else {
        cout << "\nSe abrio el archivo  " << nombreArchivoS.c_str() << "  correctamente\n";
    }
    cout << "\n\nGuardando los numeros ordenados en el archivo: " << nombreArchivoS;
    guardacn = 0;
    for (i = 0; i < n; i++) {
        salida.id = arreglo[i][0];
        salida.sexo = arreglo[i][1];
        salida.peso = arreglo[i][2];
        salida.estatura = arreglo[i][3];
        fprintf(archivo2, "%i %i %f %f\n", salida.id, salida.sexo, salida.peso, salida.estatura);
        guardacn++;
    }
    cout << "\n\nTotal de numeros guardados en el archivo son: " << guardacn;
    cout << "\n\n";
    fclose(archivo2);
    return (0);
}

// ================= Impresion de numeros =================
int impresionNumeros() {
    cout << "\nContenido del arreglo \n";
    cout << "ID   Sexo   Peso   Estatura\n";
    for(i = 0; i < n; i++){
        cout << arreglo[i][0] << "     " << arreglo[i][1] << "     " << arreglo[i][2] << "     " << arreglo[i][3] << endl;
    }
    return (0);
}

// ================= Captura de cantidad =================
int numeroDatos() {
    cout << "\nTeclee la cantidad de datos a procesar : ";
    cin >> n;
    return (0);
}

// ================= Busqueda Secuencial =================
int busquedaNumeros() {
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }
    banderaEncontro = 0;
    cout << "\n--- ANTES DE LA BUSQUEDA ---";
    impresionNumeros();
    cout << "\nTeclee el ID a buscar : ";
    cin >> numeroBuscar;
    t_ini = clock();
    for (i = 0; i < n; i++) {
        if (numeroBuscar == arreglo[i][0]) {
            cout << "\nID encontrado en la posicion " << i + 1;
            banderaEncontro = 1;
        }
    }
    t_fin = clock();
    if (banderaEncontro == 0) {
        cout << "\nID no encontrado en el arreglo ";
    }
    cout << "\n\n--- DESPUES DE LA BUSQUEDA ---";
    impresionNumeros();
    cout << "\n\n Tiempo de busqueda secuencial:  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n";
    return (0);
}

// ================= Busqueda Binaria =================
void busquedaBin() {
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return;
    }
    if (datosOrdenados == 0) {
        cout << "\n ERROR: No se puede realizar la busqueda binaria porque los datos no estan ordenados. \n";
        return;
    }
    cout << "\n--- ANTES DE LA BUSQUEDA ---";
    impresionNumeros();
    cout << "\nTeclee el ID a buscar en el arreglo :   ";
    cin >> buscar;
    t_ini = clock();
    busquedaBinaria();
    t_fin = clock();
    if (arreglo[i][0] == buscar) {
        cout << "\nEl ID " << buscar << " se encuentra en la posicion " << i + 1;
    }
    else {
        cout << "\nNo se encuentra el ID " << buscar << " en el arreglo\n";
    }
    cout << "\n--- DESPUES DE LA BUSQUEDA ---";
    impresionNumeros();
    cout << "\n\n Tiempo de busqueda binaria:  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n";
}

int busquedaBinaria() {
    inferior = 0;
    superior = n;
    while (superior >= inferior) {
        i = (inferior + superior) / 2;
        if (arreglo[i][0] == buscar) {
            return i;
        }
        else {
            if (buscar < arreglo[i][0]) {
                superior = i - 1;
            }
            else {
                inferior = i + 1;
            }
        }
    }
    return (0);
}

// ================= Metodo burbuja =================
int burbuja() {
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }
    
    ordenOpcion = seleccionarOrden();
    bool ascendente = (ordenOpcion == 1);
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();
    t_ini = clock();
    
    for (i = 0; i < n - 1; i++) {
        for (j = i; j < n; j++) {
            if ((ascendente && arreglo[i][0] > arreglo[j][0]) || 
                (!ascendente && arreglo[i][0] < arreglo[j][0])) {
                swapFilas(arreglo[i], arreglo[j]);
            }
        }
    }
    
    t_fin = clock();
    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionNumeros();
    cout << "\n\n Tiempo de ordenamiento por el metodo de Burbuja :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    datosOrdenados = 1;
    return (0);
}

// ================= Metodo Flotacion =================
int flotacion() {
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }
    
    ordenOpcion = seleccionarOrden();
    bool ascendente = (ordenOpcion == 1);
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();
    t_ini = clock();
    
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1; j++) {
            if ((ascendente && arreglo[j][0] > arreglo[j + 1][0]) || 
                (!ascendente && arreglo[j][0] < arreglo[j + 1][0])) {
                swapFilas(arreglo[j], arreglo[j + 1]);
            }
        }
    }
    
    t_fin = clock();
    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionNumeros();
    cout << "\n\n Tiempo de ordenamiento por el metodo de Flotacion :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    datosOrdenados = 1;
    return (0);
}

// ================= Metodo Insercion =================
int insercion() {
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }
    
    ordenOpcion = seleccionarOrden();
    bool ascendente = (ordenOpcion == 1);
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();
    t_ini = clock();
    
    for (i = 1; i < n; i++) {
        int key = arreglo[i][0];
        float filaKey[5];
        for (k = 0; k < 5; k++) {
            filaKey[k] = arreglo[i][k];
        }
        j = i - 1;
        while (j >= 0 && ((ascendente && arreglo[j][0] > key) || 
                          (!ascendente && arreglo[j][0] < key))) {
            for (k = 0; k < 5; k++) {
                arreglo[j + 1][k] = arreglo[j][k];
            }
            j--;
        }
        for (k = 0; k < 5; k++) {
            arreglo[j + 1][k] = filaKey[k];
        }
    }
    
    t_fin = clock();
    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionNumeros();
    cout << "\n\n Tiempo de ordenamiento por el metodo de Insercion :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    datosOrdenados = 1;
    return (0);
}

// ================= Metodo Seleccion =================
int seleccion() {
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }
    
    ordenOpcion = seleccionarOrden();
    bool ascendente = (ordenOpcion == 1);
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();
    t_ini = clock();
    
    for (i = 0; i < n - 1; i++) {
        int idx_extremo = i;
        for (j = i + 1; j < n; j++) {
            if ((ascendente && arreglo[idx_extremo][0] > arreglo[j][0]) || 
                (!ascendente && arreglo[idx_extremo][0] < arreglo[j][0])) {
                idx_extremo = j;
            }
        }
        if (idx_extremo != i) {
            swapFilas(arreglo[i], arreglo[idx_extremo]);
        }
    }
    
    t_fin = clock();
    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionNumeros();
    cout << "\n\n Tiempo de ordenamiento por el metodo de Seleccion :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    datosOrdenados = 1;
    return (0);
}

// ================= Metodo Shell =================
int shell() {
    if (hayDatos == 0) {
        cout << "\n  ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo.  \n";
        return (0);
    }
    
    ordenOpcion = seleccionarOrden();
    bool ascendente = (ordenOpcion == 1);
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();
    t_ini = clock();
    
    subarreglo = n / 2;
    while (subarreglo > 0) {
        for (i = subarreglo; i < n; i++) {
            j = i;
            float filaTemp[5];
            for (k = 0; k < 5; k++) {
                filaTemp[k] = arreglo[i][k];
            }
            while ((j >= subarreglo) && ((ascendente && arreglo[j - subarreglo][0] > filaTemp[0]) || 
                                         (!ascendente && arreglo[j - subarreglo][0] < filaTemp[0]))) {
                for (k = 0; k < 5; k++) {
                    arreglo[j][k] = arreglo[j - subarreglo][k];
                }
                j = j - subarreglo;
            }
            for (k = 0; k < 5; k++) {
                arreglo[j][k] = filaTemp[k];
            }
        }
        subarreglo /= 2;
    }
    
    t_fin = clock();
    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionNumeros();
    cout << "\n\n Tiempo de ordenamiento por el metodo de Shell :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    datosOrdenados = 1;
    return (0);
}

// ================= Metodo HeapSort =================
void identificar_mayor(float arreglo[][5], int i, int n) {
    int izquierda, derecha;
    izquierda = 2 * i + 1;
    derecha = 2 * i + 2;
    
    bool ascendente = (ordenOpcion == 1);
    
    int extremo = i;
    if (izquierda <= n) {
        if ((ascendente && arreglo[izquierda][0] > arreglo[extremo][0]) || 
            (!ascendente && arreglo[izquierda][0] < arreglo[extremo][0])) {
            extremo = izquierda;
        }
    }
    if (derecha <= n) {
        if ((ascendente && arreglo[derecha][0] > arreglo[extremo][0]) || 
            (!ascendente && arreglo[derecha][0] < arreglo[extremo][0])) {
            extremo = derecha;
        }
    }
    if (extremo != i) {
        swapFilas(arreglo[i], arreglo[extremo]);
        identificar_mayor(arreglo, extremo, n);
    }
}

void conformar_arbol(float arreglo[][5], int n) {
    for (int k = n / 2; k >= 0; k--) {
        identificar_mayor(arreglo, k, n);
    }
}

void heapSort() {
    conformar_arbol(arreglo, n - 1);
    for (i = n - 1; i >= 1; i--) {
        swapFilas(arreglo[i], arreglo[0]);
        identificar_mayor(arreglo, 0, i - 1);
    }
}

int ordenamientoHeapSort() {
    if (hayDatos == 0) {
        cout << "\n  ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo.  \n";
        return (0);
    }
    
    ordenOpcion = seleccionarOrden();
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();
    t_ini = clock();
    heapSort();
    t_fin = clock();
    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionNumeros();
    cout << "\n\n Tiempo de ordenamiento por el metodo de HeapSort :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    datosOrdenados = 1;
    return (0);
}

// ================= Metodo QuickSort con sort() =================
int ordenamientoQuick() {
    if (hayDatos == 0) {
        cout << "\n  ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo.  \n";
        return (0);
    }
    
    ordenOpcion = seleccionarOrden();
    bool ascendente = (ordenOpcion == 1);
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();
    t_ini = clock();
    
    float* ptrArreglo[100];
    for (int idx = 0; idx < n; idx++) {
        ptrArreglo[idx] = arreglo[idx];
    }
    
    if (ascendente) {
        sort(ptrArreglo, ptrArreglo + n, [](const float* a, const float* b) {
            return a[0] < b[0];
        });
    } else {
        sort(ptrArreglo, ptrArreglo + n, [](const float* a, const float* b) {
            return a[0] > b[0];
        });
    }
    
    float arregloTemp[100][5];
    for (int idx = 0; idx < n; idx++) {
        for (int col = 0; col < 5; col++) {
            arregloTemp[idx][col] = ptrArreglo[idx][col];
        }
    }
    for (int idx = 0; idx < n; idx++) {
        for (int col = 0; col < 5; col++) {
            arreglo[idx][col] = arregloTemp[idx][col];
        }
    }
    
    t_fin = clock();
    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionNumeros();
    cout << "\n\n Tiempo de ordenamiento por el metodo de QuickSort (funcion sort() del compilador) :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    datosOrdenados = 1;
    return (0);
}

// ================= identAlfaNumerico =================
int identAlfaNumerico() {
    cout << "\nIdentificador alfanumerico - No aplica para arreglo de numeros\n";
    return (0);
}

// ================= IdentVotante =================
int identVotante() {
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }
    cout << "\n--- IDENTIFICACION DE VOTANTES ---\n";
    for(i = 0; i < n; i++){
        if(arreglo[i][0] >= 18){
            cout << "El votante con ID " << arreglo[i][0] << " es mayor de edad y puede votar" << endl;
        }
        else{
            cout << "El votante con ID " << arreglo[i][0] << " es menor de edad y NO puede votar" << endl;
        }
    }
    return (0);
}

// ================= identInscrito =================
int identInscrito() {
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }
    if (datosOrdenados == 0) {
        cout << "\n ERROR: Los datos no estan ordenados. Primero ordene los datos.\n";
        return (0);
    }
    cout << "\n--- IDENTIFICACION DE INSCRITOS ---\n";
    cout << "Teclee el ID a buscar: ";
    cin >> buscar;
    busquedaBinaria();
    if (arreglo[i][0] == buscar) {
        cout << "El ID " << buscar << " SI se encuentra inscrito en la posicion " << i + 1 << endl;
    }
    else {
        cout << "El ID " << buscar << " NO se encuentra inscrito" << endl;
    }
    return (0);
}

// ================= analisisIMCHombres =================
int analisisIMCHombres() {
    if (imc < 20) {
        cout << " - Tiene bajo peso (Hombres: menos de 20)" << endl;
    }
    else if (imc >= 20 && imc < 26) {
        cout << " - Tiene peso normal (Hombres: 20 - 25.9)" << endl;
    }
    else if (imc >= 26 && imc <= 30) {
        cout << " - Tiene sobrepeso (Hombres: 26 - 30)" << endl;
    }
    else if (imc > 30) {
        cout << " - Tiene Obesidad (Hombres: mas de 30)" << endl;
    }
    return 0;
}

// ================= analisisIMCMujeres =================
int analisisIMCMujeres() {
    if (imc < 20) {
        cout << " - Tiene bajo peso (Mujeres: menos de 20)" << endl;
    }
    else if (imc >= 20 && imc < 28) {
        cout << " - Tiene peso normal (Mujeres: 20 - 27.9)" << endl;
    }
    else if (imc >= 28 && imc <= 30) {
        cout << " - Tiene sobrepeso (Mujeres: 28 - 30)" << endl;
    }
    else if (imc > 30) {
        cout << " - Tiene Obesidad (Mujeres: mas de 30)" << endl;
    }
    return 0;
}

// ================= calculoIMC =================
int calculoIMC() {
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }
    cout << "\n--- CALCULO DEL INDICE DE MASA CORPORAL (IMC) ---\n";
    cout << "================================================================================\n";
    for (i = 0; i < n; i++) {
        divisor = arreglo[i][3] * arreglo[i][3];
        imc = arreglo[i][2] / divisor;
        cout << "\nPersona " << i+1 << " (ID: " << arreglo[i][0] << "): ";
        cout << "Peso = " << arreglo[i][2] << " kg, Estatura = " << arreglo[i][3] << " m";
        cout << "\n   Estatura^2 = " << divisor;
        cout << "\n   IMC = " << arreglo[i][2] << " / " << divisor << " = " << imc;
        if (arreglo[i][1] == 1) {
            cout << " (Hombre)";
            analisisIMCHombres();
        } else {
            cout << " (Mujer)";
            analisisIMCMujeres();
        }
        cout << "--------------------------------------------------------------------------------";
    }
    cout << "\n================================================================================\n";
    return (0);
}

// ================= MAIN =================
int main() {
    for (repeticion = 0; repeticion == 0;) {
        menu();
        switch (opcion) {
            case 1:
                numeroDatos();
                capturaNumeros();
                cout << "\n--- VERIFICACION ---";
                impresionNumeros();
                break;
                
            case 2:
                leeArchivo();
                cout << "\n--- VERIFICACION ---";
                impresionNumeros();
                break;
                
            case 3:
                if (hayDatos == 0) {
                    cout << "\n ERROR: No hay datos. \n";
                } else {
                    impresionNumeros();
                }
                break;
                
            case 4:
                busquedaNumeros();
                break;
                
            case 5:
                if (hayDatos == 0) {
                    cout << "\n ERROR: No hay datos. \n";
                } else if (datosOrdenados == 0) {
                    cout << "\n ERROR: Datos no ordenados. \n";
                } else {
                    busquedaBin();
                }
                break;
                
            case 6:
                burbuja();
                break;
                
            case 7:
                flotacion();
                break;
                
            case 8:
                insercion();
                break;
                
            case 9:
                seleccion();
                break;
                
            case 10:
                shell();
                break;
                
            case 11:
                ordenamientoHeapSort();
                break;
                
            case 12:
                ordenamientoQuick();
                break;
                
            case 13:
                identAlfaNumerico();
                break;
                
            case 14:
                identVotante();
                break;
                
            case 15:
                identInscrito();
                break;
                
            case 16:
                calculoIMC();
                break;
                
            case 17:
                guardaArchivo();
                break;
                
            case 18:
                cout << "\nHasta luego";
                repeticion++;
                break;
                
            default:
                cout << "\nOpcion invalida";
        }
        if (repeticion) {
            break;
        }
        cout << endl;
        system("pause");
    }
    cout << endl;
    system("pause");
}

// ================= MENU PRINCIPAL =================
int menu() {
    system("cls");
    cout << "\n Quirino Gonzalez Johann David";
    cout << "\n\tMenu";
    cout << "\n1 - Captura de numeros";
    cout << "\n2 - Lectura de archivo numeros";
    cout << "\n3 - Impresion numeros";
    cout << "\n4 - Busqueda Secuencial";
    cout << "\n5 - Busqueda Binaria";
    cout << "\n6 - Metodo de ordenamiento Burbuja";
    cout << "\n7 - Metodo de ordenamiento Flotacion";
    cout << "\n8 - Metodo de ordenamiento Insercion";
    cout << "\n9 - Metodo de ordenamiento Seleccion";
    cout << "\n10 - Metodo de ordenamiento Shell";
    cout << "\n11 - Metodo de ordenamiento HeapSort";
    cout << "\n12 - Metodo de ordenamiento QuickSort";
    cout << "\n13 - Identificador Alfanumerico";
    cout << "\n14 - Identificar votante";
    cout << "\n15 - Identificar si esta inscrito";
    cout << "\n16 - Calculo de IMC";
    cout << "\n17 - Guardar archivo";
    cout << "\n18 - Salir del menu";
    cout << "\nTeclee la opcion deseada : ";
    cin >> opcion;
    return (0);
}