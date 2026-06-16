// Autor: Quirino González Johann David
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <cmath>
#include <algorithm>  // Libreria necesaria para la funcion sort()
#include <chrono>      // Para medicion de tiempo en Timsort e Introsort
#include <vector>      // Para vectores auxiliares
#include <limits>      // Para numeric_limits
using namespace std;
using namespace std::chrono;

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

// Variables para Timsort e Introsort (para arreglo temporal de enteros)
int* arregloEnteros = nullptr;  // Arreglo dinamico para enteros
int tamEnteros = 0;              // Tamanio del arreglo de enteros
bool archivoLeidoEnteros = false;
bool archivoOrdenadoEnteros = false;
bool archivoGrabadoEnteros = false;
int opcionalEnteros = 0;
bool mensajeTim = false;
bool mensajeMerge = false;
bool mensajElnsertionsort = false;
bool mensajeCambioOrden = false;
bool mensajeHeapsort = false;
bool mensajelInsertionsort = false;
const int RUN = 32;  // Tamanio de RUN para Timsort

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

// ================= Funcion para preguntar orden ascendente/descendente =================
bool preguntarOrden() {
    int orden;
    cout << "\n--- SELECCIONE EL ORDEN DE ORDENAMIENTO ---" << endl;
    cout << "1. Ascendente (menor a mayor)" << endl;
    cout << "2. Descendente (mayor a menor)" << endl;
    cout << "Opcion: ";
    orden = leerEntero();
    while (orden != 1 && orden != 2) {
        cout << "Opcion invalida. Seleccione 1 (Ascendente) o 2 (Descendente): ";
        orden = leerEntero();
    }
    return (orden == 1); // true = ascendente, false = descendente
}

// ================= Funcion auxiliar para swap de filas =================
void swapFilas(float fila1[5], float fila2[5]) {
    for (int idx = 0; idx < 5; idx++) {
        swap(fila1[idx], fila2[idx]);
    }
}

// ================= Funciones para Timsort =================
void insertionSortEnteros(int arr[], int left, int right, bool ascendente) {
    if (!mensajElnsertionsort) {
        cout << "Inicio ordenamiento con insercion de tamanio " << (right - left + 1) << endl;
        mensajElnsertionsort = true;
    }
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && ((ascendente && arr[j] > temp) || (!ascendente && arr[j] < temp))) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void mergeEnteros(int arr[], int l, int m, int r, bool ascendente) {
    if (!mensajeMerge) {
        cout << "Inicio ordenamiento con Merge de tamanio " << (r - l + 1) << endl;
        mensajeMerge = true;
    }

    int len1 = m - l + 1, len2 = r - m;
    int* left = new int[len1];
    int* right = new int[len2];

    copy(arr + l, arr + m + 1, left);
    copy(arr + m + 1, arr + r + 1, right);

    int i = 0, j = 0, k = l;
    while (i < len1 && j < len2) {
        if ((ascendente && left[i] <= right[j]) || (!ascendente && left[i] >= right[j])) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < len1) arr[k++] = left[i++];
    while (j < len2) arr[k++] = right[j++];

    delete[] left;
    delete[] right;
}

void timSort(int arr[], int n, bool ascendente) {
    if (!mensajeTim) {
        cout << "Inicio ordenamiento con TimSort, tamanio de RUN: " << RUN << endl;
        mensajeTim = true;
    }

    auto inicio = high_resolution_clock::now();

    for (int i = 0; i < n; i += RUN)
        insertionSortEnteros(arr, i, min(i + RUN - 1, n - 1), ascendente);

    for (int size = RUN; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);
            if (mid < right) mergeEnteros(arr, left, mid, right, ascendente);
        }
    }

    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << "Tiempo de ejecucion de TimSort: " << duracion.count() << " segundos" << endl;
}

// ================= Funciones para Introsort =================
void insertionSortIntrosort(int* arr, int izquierda, int derecha, bool ascendente) {
    if (!mensajelInsertionsort) {
        cout << "Se activa Insertion Sort para subarreglo pequeno (" << (derecha - izquierda + 1) << " elementos)" << endl;
        mensajelInsertionsort = true;
    }
    for (int i = izquierda + 1; i <= derecha; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= izquierda && ((ascendente && arr[j] > key) || (!ascendente && arr[j] < key))) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void heapifyIntrosort(int* arr, int n, int i, bool ascendente) {
    int extremo = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;

    if (ascendente) {
        if (izquierda < n && arr[izquierda] > arr[extremo]) extremo = izquierda;
        if (derecha < n && arr[derecha] > arr[extremo]) extremo = derecha;
    } else {
        if (izquierda < n && arr[izquierda] < arr[extremo]) extremo = izquierda;
        if (derecha < n && arr[derecha] < arr[extremo]) extremo = derecha;
    }

    if (extremo != i) {
        swap(arr[i], arr[extremo]);
        heapifyIntrosort(arr, n, extremo, ascendente);
    }
}

void heapSortIntrosort(int* arr, int n, bool ascendente) {
    if (!mensajeHeapsort) {
        cout << "Se activa Heapsort debido a profundidad excesiva en QuickSort" << endl;
        mensajeHeapsort = true;
    }
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyIntrosort(arr, n, i, ascendente);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapifyIntrosort(arr, i, 0, ascendente);
    }
}

void introsortUtil(int* arr, int izquierda, int derecha, int profundidadMax, bool ascendente) {
    int n = derecha - izquierda + 1;

    // Usa Insercion para arreglos pequenos
    if (n <= 16) {
        insertionSortIntrosort(arr, izquierda, derecha, ascendente);
        return;
    }

    // Si se alcanza la profundidad maxima usa HeapSort
    if (profundidadMax == 0) {
        heapSortIntrosort(arr + izquierda, n, ascendente);
        return;
    }

    // Selecciona el pivote (valor central)
    int pivote = arr[izquierda + (derecha - izquierda) / 2];
    int i = izquierda, j = derecha;

    // Particion QuickSort
    while (i <= j) {
        if (ascendente) {
            while (arr[i] < pivote) i++;
            while (arr[j] > pivote) j--;
        } else {
            while (arr[i] > pivote) i++;
            while (arr[j] < pivote) j--;
        }
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    // Llamada recursiva
    if (izquierda < j)
        introsortUtil(arr, izquierda, j, profundidadMax - 1, ascendente);
    if (i < derecha)
        introsortUtil(arr, i, derecha, profundidadMax - 1, ascendente);
}

void introsort(int* arr, int n, bool ascendente) {
    mensajeHeapsort = false;
    mensajelInsertionsort = false;

    // Calcula la profundidad maxima permitida
    int profundidadMax = 2 * log(n);
    cout << "Comienza Introsort con profundidad maxima permitida: " << profundidadMax << endl;

    // Llama a la funcion auxiliar
    introsortUtil(arr, 0, n - 1, profundidadMax, ascendente);
}

// ================= Funciones para el menu de Timsort =================
void leerArchivoEnteros() {
    if (archivoLeidoEnteros) {
        cout << "El archivo ya ha sido leido" << endl;
        return;
    }

    string nombre;
    cout << "Ingrese el nombre del archivo sin extension: ";
    cin >> ws;
    getline(cin, nombre);
    nombre += ".txt";

    ifstream archivo(nombre);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    int valor;
    tamEnteros = 0;
    while (archivo >> valor) tamEnteros++;

    if (tamEnteros == 0) {
        cout << "El archivo esta vacio" << endl;
        archivo.close();
        return;
    }

    archivo.clear();
    archivo.seekg(0);

    delete[] arregloEnteros;
    arregloEnteros = new int[tamEnteros];
    for (int i = 0; i < tamEnteros; i++) archivo >> arregloEnteros[i];

    archivo.close();
    archivoLeidoEnteros = true;
    archivoOrdenadoEnteros = false;
    archivoGrabadoEnteros = false;

    cout << "Archivo leido correctamente. Total de valores: " << tamEnteros << endl;
}

void mostrarArregloEnteros() {
    if (!archivoLeidoEnteros) {
        cout << "Primero debe leer un archivo" << endl;
        return;
    }
    if (archivoGrabadoEnteros) {
        cout << "El archivo ya fue guardado" << endl;
        return;
    }
    cout << "Cuantos elementos desea mostrar? ";
    int elementos = leerEntero();
    cout << "Contenido del arreglo: ";
    for (int i = 0; i < elementos && i < tamEnteros; i++) cout << arregloEnteros[i] << " ";
    cout << endl;
}

void ordenarTimsort() {
    if (!archivoLeidoEnteros) {
        cout << "Primero debe leer un archivo" << endl;
        return;
    }
    if (archivoGrabadoEnteros) {
        cout << "El archivo ya fue guardado" << endl;
        return;
    }

    cout << "Seleccione el orden:" << endl;
    cout << "1. Ascendente" << endl;
    cout << "2. Descendente" << endl;
    cout << "Opcion: ";
    int opcionTim = leerEntero();
    if (opcionTim <= 0 || opcionTim > 2) {
        cout << "Opcion invalida" << endl;
        return;
    }

    bool asc = (opcionTim == 1);

    if (opcionalEnteros != opcionTim && !mensajeCambioOrden) {
        cout << (asc ? "Cambiando a orden ascendente..." : "Cambiando a orden descendente...") << endl;
        mensajeCambioOrden = true;
    }

    if (opcionalEnteros == opcionTim && archivoOrdenadoEnteros) {
        cout << "El arreglo ya ha sido ordenado en ese orden" << endl;
        return;
    }

    opcionalEnteros = opcionTim;
    cout << "Iniciando ordenamiento con Timsort de un arreglo de " << tamEnteros << " elementos" << endl;
    
    // Resetear mensajes
    mensajeTim = false;
    mensajeMerge = false;
    mensajElnsertionsort = false;
    
    timSort(arregloEnteros, tamEnteros, asc);
    archivoOrdenadoEnteros = true;
    cout << "Ordenamiento completado exitosamente" << endl;
}

void guardarArchivoEnteros() {
    if (!archivoLeidoEnteros) {
        cout << "Primero debe leer un archivo" << endl;
        return;
    }
    if (archivoGrabadoEnteros) {
        cout << "El archivo ya fue grabado" << endl;
        return;
    }
    if (!archivoOrdenadoEnteros) {
        cout << "El arreglo no esta ordenado" << endl;
        return;
    }

    string nombre;
    cout << "Ingrese el nombre del archivo para guardar (sin extension): ";
    cin >> ws;
    getline(cin, nombre);
    nombre += ".txt";

    ofstream archivo(nombre);
    if (!archivo.is_open()) {
        cout << "No se pudo crear el archivo" << endl;
        return;
    }

    for (int i = 0; i < tamEnteros; i++) archivo << arregloEnteros[i] << " ";
    archivo.close();
    archivoGrabadoEnteros = true;

    cout << "Archivo guardado exitosamente como: " << nombre << endl;
}

void mostrarPositivosNegativos() {
    if (!archivoLeidoEnteros) {
        cout << "Primero debe leer un archivo" << endl;
        return;
    }
    if (archivoGrabadoEnteros) {
        cout << "El archivo ya fue guardado" << endl;
        return;
    }
    
    cout << "\n--- ANALISIS DE NUMEROS POSITIVOS Y NEGATIVOS ---" << endl;
    int positivos = 0, negativos = 0;
    for (int i = 0; i < tamEnteros; i++) {
        if (arregloEnteros[i] < 0) {
            cout << "Numero negativo: " << arregloEnteros[i] << endl;
            negativos++;
        } else {
            cout << "Numero positivo: " << arregloEnteros[i] << endl;
            positivos++;
        }
    }
    cout << "\n--- RESUMEN ---" << endl;
    cout << "Total de numeros positivos: " << positivos << endl;
    cout << "Total de numeros negativos: " << negativos << endl;
}

bool salirEnteros() {
    if (!archivoLeidoEnteros) {
        cout << "Debe leer un archivo antes de salir" << endl;
        return false;
    }
    if (!archivoGrabadoEnteros) {
        cout << "Debe guardar el archivo antes de salir" << endl;
        return false;
    }
    delete[] arregloEnteros;
    return true;
}

// ================= Funciones para Introsort =================
void leerArchivoIntrosort() {
    if (archivoLeidoEnteros) {
        cout << "El archivo ya ha sido leido" << endl;
        return;
    }

    string nombre;
    cout << "Ingrese el nombre del archivo sin extension: ";
    cin >> ws;
    getline(cin, nombre);
    nombre += ".txt";

    ifstream archivo(nombre);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    int valor;
    tamEnteros = 0;
    while (archivo >> valor) tamEnteros++;

    if (tamEnteros == 0) {
        cout << "El archivo esta vacio" << endl;
        archivo.close();
        return;
    }

    archivo.clear();
    archivo.seekg(0);

    delete[] arregloEnteros;
    arregloEnteros = new int[tamEnteros];
    for (int i = 0; i < tamEnteros; i++) archivo >> arregloEnteros[i];

    archivo.close();
    archivoLeidoEnteros = true;
    archivoOrdenadoEnteros = false;
    archivoGrabadoEnteros = false;

    cout << "Archivo leido correctamente. Total de valores: " << tamEnteros << endl;
}

void mostrarArregloIntrosort() {
    if (!archivoLeidoEnteros) {
        cout << "Primero debe leer un archivo" << endl;
        return;
    }
    if (archivoGrabadoEnteros) {
        cout << "El archivo ya fue guardado" << endl;
        return;
    }
    cout << "Cuantos elementos desea mostrar? ";
    int elementos = leerEntero();
    cout << "Contenido del arreglo: ";
    for (int i = 0; i < elementos && i < tamEnteros; i++) cout << arregloEnteros[i] << " ";
    cout << endl;
}

void ordenarIntrosort() {
    if (!archivoLeidoEnteros) {
        cout << "Primero debe leer un archivo" << endl;
        return;
    }
    if (archivoGrabadoEnteros) {
        cout << "El archivo ya fue guardado" << endl;
        return;
    }

    cout << "Seleccione el orden:" << endl;
    cout << "1. Ascendente" << endl;
    cout << "2. Descendente" << endl;
    cout << "Opcion: ";
    int opcionIntro = leerEntero();
    if (opcionIntro <= 0 || opcionIntro > 2) {
        cout << "Opcion invalida" << endl;
        return;
    }

    if (opcionalEnteros == opcionIntro && archivoOrdenadoEnteros) {
        cout << "El arreglo ya ha sido ordenado en ese orden" << endl;
        return;
    }

    opcionalEnteros = opcionIntro;
    bool asc = (opcionIntro == 1);
    
    cout << "Iniciando ordenamiento con Introsort de un arreglo de " << tamEnteros << " elementos" << endl;
    
    auto inicio = high_resolution_clock::now();
    introsort(arregloEnteros, tamEnteros, asc);
    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    
    archivoOrdenadoEnteros = true;
    cout << "Ordenamiento completado exitosamente" << endl;
    cout << "Tiempo de ejecucion de Introsort: " << duracion.count() << " segundos" << endl;
}

void guardarArchivoIntrosort() {
    if (!archivoLeidoEnteros) {
        cout << "Primero debe leer un archivo" << endl;
        return;
    }
    if (archivoGrabadoEnteros) {
        cout << "El archivo ya fue grabado" << endl;
        return;
    }
    if (!archivoOrdenadoEnteros) {
        cout << "El arreglo no esta ordenado" << endl;
        return;
    }

    string nombre;
    cout << "Ingrese el nombre del archivo para guardar (sin extension): ";
    cin >> ws;
    getline(cin, nombre);
    nombre += ".txt";

    ofstream archivo(nombre);
    if (!archivo.is_open()) {
        cout << "No se pudo crear el archivo" << endl;
        return;
    }

    for (int i = 0; i < tamEnteros; i++) archivo << arregloEnteros[i] << " ";
    archivo.close();
    archivoGrabadoEnteros = true;

    cout << "Archivo guardado exitosamente como: " << nombre << endl;
}

bool salirIntrosort() {
    if (!archivoLeidoEnteros) {
        cout << "Debe leer un archivo antes de salir" << endl;
        return false;
    }
    if (!archivoGrabadoEnteros) {
        cout << "Debe guardar el archivo antes de salir" << endl;
        return false;
    }
    delete[] arregloEnteros;
    return true;
}

// ================= Funcion de comparacion para sort() =================
bool compararPorIDAsc(const float fila1[5], const float fila2[5]) {
    return fila1[0] < fila2[0];
}

bool compararPorIDDesc(const float fila1[5], const float fila2[5]) {
    return fila1[0] > fila2[0];
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
void identificar_mayor(float arreglo[][5], int i, int n, bool ascendente);
void conformar_arbol(float arreglo[][5], int n, bool ascendente);
void heapSort(bool ascendente);
int ordenamientoQuick();
int identAlfaNumerico();
int identVotante();
int identInscrito();
int calculoIMC();
int analisisIMCHombres();
int analisisIMCMujeres();
int menuTimsort();
int menuIntrosort();

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
    
    bool ascendente = preguntarOrden();
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();
    t_ini = clock();
    for (i = 0; i < n - 1; i++) {
        for (j = i; j < n; j++) {
            if (ascendente) {
                if (arreglo[i][0] > arreglo[j][0]) {
                    swapFilas(arreglo[i], arreglo[j]);
                }
            } else {
                if (arreglo[i][0] < arreglo[j][0]) {
                    swapFilas(arreglo[i], arreglo[j]);
                }
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
    
    bool ascendente = preguntarOrden();
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();
    t_ini = clock();
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1; j++) {
            if (ascendente) {
                if (arreglo[j][0] > arreglo[j + 1][0]) {
                    swapFilas(arreglo[j], arreglo[j + 1]);
                }
            } else {
                if (arreglo[j][0] < arreglo[j + 1][0]) {
                    swapFilas(arreglo[j], arreglo[j + 1]);
                }
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
    
    bool ascendente = preguntarOrden();
    
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
        if (ascendente) {
            while (j >= 0 && arreglo[j][0] > key) {
                for (k = 0; k < 5; k++) {
                    arreglo[j + 1][k] = arreglo[j][k];
                }
                j--;
            }
        } else {
            while (j >= 0 && arreglo[j][0] < key) {
                for (k = 0; k < 5; k++) {
                    arreglo[j + 1][k] = arreglo[j][k];
                }
                j--;
            }
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
    
    bool ascendente = preguntarOrden();
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();
    t_ini = clock();
    for (i = 0; i < n - 1; i++) {
        int extremo_idx = i;
        for (j = i + 1; j < n; j++) {
            if (ascendente) {
                if (arreglo[extremo_idx][0] > arreglo[j][0]) {
                    extremo_idx = j;
                }
            } else {
                if (arreglo[extremo_idx][0] < arreglo[j][0]) {
                    extremo_idx = j;
                }
            }
        }
        if (extremo_idx != i) {
            swapFilas(arreglo[i], arreglo[extremo_idx]);
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
    
    bool ascendente = preguntarOrden();
    
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
            if (ascendente) {
                while ((j >= subarreglo) && (arreglo[j - subarreglo][0] > filaTemp[0])) {
                    for (k = 0; k < 5; k++) {
                        arreglo[j][k] = arreglo[j - subarreglo][k];
                    }
                    j = j - subarreglo;
                }
            } else {
                while ((j >= subarreglo) && (arreglo[j - subarreglo][0] < filaTemp[0])) {
                    for (k = 0; k < 5; k++) {
                        arreglo[j][k] = arreglo[j - subarreglo][k];
                    }
                    j = j - subarreglo;
                }
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
void identificar_mayor(float arreglo[][5], int i, int n, bool ascendente) {
    int izquierda, derecha;
    izquierda = 2 * i + 1;
    derecha = 2 * i + 2;
    
    if (ascendente) {
        if ((izquierda <= n) && (arreglo[izquierda][0] > arreglo[i][0]))
            masgrande = izquierda;
        else
            masgrande = i;
        if ((derecha <= n) && (arreglo[derecha][0] > arreglo[masgrande][0]))
            masgrande = derecha;
    } else {
        if ((izquierda <= n) && (arreglo[izquierda][0] < arreglo[i][0]))
            masgrande = izquierda;
        else
            masgrande = i;
        if ((derecha <= n) && (arreglo[derecha][0] < arreglo[masgrande][0]))
            masgrande = derecha;
    }
    
    if (masgrande != i) {
        swapFilas(arreglo[i], arreglo[masgrande]);
        identificar_mayor(arreglo, masgrande, n, ascendente);
    }
}

void conformar_arbol(float arreglo[][5], int n, bool ascendente) {
    for (int k = n / 2; k >= 0; k--) {
        identificar_mayor(arreglo, k, n, ascendente);
    }
}

void heapSort(bool ascendente) {
    conformar_arbol(arreglo, n - 1, ascendente);
    for (i = n - 1; i >= 1; i--) {
        swapFilas(arreglo[i], arreglo[0]);
        identificar_mayor(arreglo, 0, i - 1, ascendente);
    }
}

int ordenamientoHeapSort() {
    if (hayDatos == 0) {
        cout << "\n  ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo.  \n";
        return (0);
    }
    
    bool ascendente = preguntarOrden();
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();
    t_ini = clock();
    heapSort(ascendente);
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
    
    bool ascendente = preguntarOrden();
    
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

// ================= Menu Timsort =================
int menuTimsort() {
    system("cls");
    cout << "\n Quirino Gonzalez Johann David - TIMSORT";
    cout << "\n\tMenu Timsort";
    cout << "\n1 - Leer archivo";
    cout << "\n2 - Ordenar con Timsort";
    cout << "\n3 - Guardar archivo";
    cout << "\n4 - Mostrar arreglo";
    cout << "\n5 - Mostrar numeros negativos y positivos";
    cout << "\n6 - Regresar al menu principal";
    cout << "\n7 - Salir";
    cout << "\nTeclee la opcion deseada : ";
    int op;
    cin >> op;
    return op;
}

// ================= Menu Introsort =================
int menuIntrosort() {
    system("cls");
    cout << "\n Quirino Gonzalez Johann David - INTROSORT";
    cout << "\n\tMenu Introsort";
    cout << "\n1 - Leer archivo";
    cout << "\n2 - Ordenar con Introsort";
    cout << "\n3 - Guardar archivo";
    cout << "\n4 - Mostrar arreglo";
    cout << "\n5 - Regresar al menu principal";
    cout << "\n6 - Salir";
    cout << "\nTeclee la opcion deseada : ";
    int op;
    cin >> op;
    return op;
}

// ================= MAIN =================
int main() {
    for (repeticion = 0; repeticion == 0;) {
        menu();
        switch (opcion) {
        case 1: numeroDatos(); capturaNumeros(); cout << "\n--- VERIFICACION ---"; impresionNumeros(); break;
        case 2: leeArchivo(); cout << "\n--- VERIFICACION ---"; impresionNumeros(); break;
        case 3: if (hayDatos == 0) cout << "\n ERROR: No hay datos. \n"; else impresionNumeros(); break;
        case 4: busquedaNumeros(); break;
        case 5: if (hayDatos == 0) cout << "\n ERROR: No hay datos. \n"; else if (datosOrdenados == 0) cout << "\n ERROR: Datos no ordenados. \n"; else busquedaBin(); break;
        case 6: burbuja(); break;
        case 7: flotacion(); break;
        case 8: insercion(); break;
        case 9: seleccion(); break;
        case 10: shell(); break;
        case 11: ordenamientoHeapSort(); break;
        case 12: ordenamientoQuick(); break;
        case 13: identAlfaNumerico(); break;
        case 14: identVotante(); break;
        case 15: identInscrito(); break;
        case 16: calculoIMC(); break;
        case 17: guardaArchivo(); break;
        case 18: {
            // Submenu Timsort
            bool continuarTimsort = true;
            while (continuarTimsort) {
                int opTim = menuTimsort();
                switch (opTim) {
                    case 1: leerArchivoEnteros(); break;
                    case 2: ordenarTimsort(); break;
                    case 3: guardarArchivoEnteros(); break;
                    case 4: mostrarArregloEnteros(); break;
                    case 5: mostrarPositivosNegativos(); break;
                    case 6: continuarTimsort = false; break;
                    case 7: cout << "\nHasta luego"; repeticion++; continuarTimsort = false; break;
                    default: cout << "\nOpcion invalida";
                }
                if (repeticion) break;
                cout << endl; system("pause");
            }
            break;
        }
        case 19: {
            // Submenu Introsort
            bool continuarIntrosort = true;
            while (continuarIntrosort) {
                int opIntro = menuIntrosort();
                switch (opIntro) {
                    case 1: leerArchivoIntrosort(); break;
                    case 2: ordenarIntrosort(); break;
                    case 3: guardarArchivoIntrosort(); break;
                    case 4: mostrarArregloIntrosort(); break;
                    case 5: continuarIntrosort = false; break;
                    case 6: cout << "\nHasta luego"; repeticion++; continuarIntrosort = false; break;
                    default: cout << "\nOpcion invalida";
                }
                if (repeticion) break;
                cout << endl; system("pause");
            }
            break;
        }
        case 20: cout << "\nHasta luego"; repeticion++; break;
        default: cout << "\nOpcion invalida";
        }
        if (repeticion) break;
        cout << endl; system("pause");
    }
    cout << endl; system("pause");
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
    cout << "\n12 - Metodo de ordenamiento QuickSort (sort del compilador)";
    cout << "\n13 - Identificador Alfanumerico";
    cout << "\n14 - Identificar votante";
    cout << "\n15 - Identificar si esta inscrito";
    cout << "\n16 - Calculo de IMC";
    cout << "\n17 - Guardar archivo";
    cout << "\n18 - Timsort (ordenamiento hibrido)";
    cout << "\n19 - Introsort (ordenamiento hibrido)";
    cout << "\n20 - Salir del menu";
    cout << "\nTeclee la opcion deseada : ";
    cin >> opcion;
    return (0);
}