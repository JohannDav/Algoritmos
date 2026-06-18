#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <limits>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <limits>

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
int yaOrdenados = 0;
int numeroBuscar;
float arreglo2[100];
clock_t t_ini, t_fin;
double secs;
int hayDatos = 0;
int datosOrdenados = 0;
using namespace std;
using namespace chrono;

int* arreglo = nullptr;
int tam = 0;
int opcional = 0;
int opcion = 0;
int repeticion = 0;
int menu();
bool archivoLeido = false;
bool archivoOrdenado = false;
bool archivoGrabado = false;
bool mensajeCambioOrden = false;
bool mensajeHeapsort = false;
bool mensajelInsertionsort = false;

int leerEntero() {
    int valor;
    while (true) {
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Ingrese un número entero: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

void insertionSort(int arr[], int left, int right, bool ascendente) {
    if (!mensajelInsertionsort) {
        cout << "Se activa Insertion Sort para subarreglo pequeño (" << right - left + 1 << " elementos)\n";
        mensajelInsertionsort = true;
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

void heapify(int arr[], int n, int i, bool ascendente) {
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
        heapify(arr, n, extremo, ascendente);
    }
}

void heapSort(int arr[], int n, bool ascendente) {
    if (!mensajeHeapsort) {
        cout << "Se activa Heapsort debido a profundidad excesiva en QuickSort\n";
        mensajeHeapsort = true;
    }
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, ascendente);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, ascendente);
    }
}

void introsortUtil(int arr[], int izquierda, int derecha, int profundidadMax, bool ascendente) {
    int n = derecha - izquierda + 1;
    if (n <= 16) {
        insertionSort(arr, izquierda, derecha, ascendente);
        return;
    }
    if (profundidadMax == 0) {
        heapSort(arr + izquierda, n, ascendente);
        return;
    }
    int pivote = arr[izquierda + (derecha - izquierda) / 2];
    int i = izquierda, j = derecha;
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
    if (izquierda < j)
        introsortUtil(arr, izquierda, j, profundidadMax - 1, ascendente);
    if (i < derecha)
        introsortUtil(arr, i, derecha, profundidadMax - 1, ascendente);
}

void introsort(int arr[], int n, bool ascendente) {
    mensajeHeapsort = false;
    mensajelInsertionsort = false;
    int profundidadMax = 2 * log(n);
    cout << "Comienza Introsort con profundidad máxima permitida: " << profundidadMax << "\n";
    introsortUtil(arr, 0, n - 1, profundidadMax, ascendente);
}

void ordenarIntrosort() {
    if (!archivoLeido) {
        cout << "Primero debe leer un archivo\n";
        return;
    }
    if (archivoGrabado) {
        cout << "Archivo ya fue grabado\n";
        return;
    }

    cout << "Seleccione el orden:\n1. Ascendente\n2. Descendente\nOpción: ";
    int opcionOrden = leerEntero();
    if (opcionOrden <= 0 || opcionOrden > 2) {
        cout << "Opción inválida\n";
        return;
    }

    bool asc = (opcionOrden == 1);

    if (opcional != opcionOrden && !mensajeCambioOrden) {
        cout << (asc ? "Cambiando a orden ascendente..." : "Cambiando a orden descendente...") << endl;
        mensajeCambioOrden = true;
    }

    if (opcional == opcionOrden && archivoOrdenado) {
        cout << "El arreglo ya ha sido ordenado en ese orden\n";
        return;
    }

    opcional = opcionOrden;
    cout << "Iniciando ordenamiento con Introsort de un arreglo de " << tam << " tamaño\n";
    introsort(arreglo, tam, asc);
    archivoOrdenado = true;
    cout << "Ordenamiento completado exitosamente\n";
    yaOrdenados = 1;
}

void leerArchivo() {
    if (archivoLeido) {
        cout << "El archivo ya ha sido leído\n";
        return;
    }

    string nombre;
    cout << "Ingrese el nombre del archivo sin extensión: ";
    cin >> ws;
    getline(cin, nombre);
    nombre += ".txt";

    ifstream archivo(nombre);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo\n";
        return;
    }

    int valor;
    tam = 0;
    while (archivo >> valor) tam++;

    if (tam == 0) {
        cout << "El archivo está vacío\n";
        archivo.close();
        return;
    }

    archivo.clear();
    archivo.seekg(0);

    delete[] arreglo;
    arreglo = new int[tam];
    for (int i = 0; i < tam; i++) archivo >> arreglo[i];

    archivo.close();
    archivoLeido = true;
    archivoOrdenado = false;
    archivoGrabado = false;

    cout << "Archivo leído correctamente. Total de valores: " << tam << endl;
    hayDatos = 1;
}

void mostrarArreglo() {
    if (!archivoLeido) {
        cout << "Primero debe leer un archivo\n";
        return;
    }
    if (archivoGrabado) {
        cout << "El archivo ya fue guardado";
        return;
    }
    cout << "¿Cuántos elementos desea mostrar? ";
    int elementos = leerEntero();
    cout << "Contenido del arreglo: ";
    for (int i = 0; i < elementos && i < tam; i++) cout << arreglo[i] << " ";
    cout << endl;
}

int mostrarTodo() {
    cout << "Contenido del arreglo: ";
    for (int i = 0; i < tam; i++) cout << arreglo[i] << " ";
    cout << endl;
    return (0);
}

void guardarArchivo() {
    if (!archivoLeido) {
        cout << "Primero debe leer un archivo\n";
        return;
    }
    if (archivoGrabado) {
        cout << "archivo ya grabado \n";
        return;
    }
    if (!archivoOrdenado) {
        cout << "El arreglo no esta ordenado";
        return;
    }

    string nombre;
    nombre = "Quirino.txt";

    ofstream archivo(nombre);
    if (!archivo.is_open()) {
        cout << "No se pudo crear el archivo\n";
        return;
    }

    for (int i = 0; i < tam; i++) archivo << arreglo[i] << " ";
    archivo.close();
    archivoGrabado = true;

    cout << "Archivo guardado exitosamente como: " << nombre << endl;
}

bool salir() {
    if (!archivoLeido) {
        cout << "Debe leer un archivo antes de salir\n";
        return false;
    }
    if (!archivoGrabado) {
        cout << "Debe guardar el archivo antes de salir\n";
        return false;
    }
    delete[] arreglo;
    return true;
}

int mostrarPositivosNegativos() {
    for (int i = 0; i < tam; i++) {
        if (arreglo[i] < 0) {
            cout << "nEs un numero negativo: " << arreglo[i];
        } else {
            cout << "nEs un numero positivo: " << arreglo[i];
        }
    }
    return 0;
}

int busquedaNumeros() {
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }
    if(yaOrdenados == 0){
        cout << "\n ERROR: Primero ordena \n";
        return (0);
    }
    banderaEncontro = 0;
    cout << "\nTeclee el numero a buscar : ";
    cin >> numeroBuscar;
    for (i = 0; i < tam; i++){
        if (numeroBuscar == arreglo[i]){
            cout << "\nNumero encontrado en la posicion " << i + 1;
            banderaEncontro = 1;
        }
    }
    if (banderaEncontro == 0){
        cout << "\nNumero no encontrado en el arreglo ";
    }
    return (0);
}

int examen(){
    return (0);
}

// ================= MAIN =================
int main() {
    system("chcp 65001 > nul");
    setlocale(LC_ALL, "es_MX.UTF-8");

    for (repeticion = 0; repeticion == 0;) {
        menu();
        switch (opcion) {
            case 1:
                leerArchivo();
                break;
            case 2:
                mostrarTodo();
                break;
            case 3:
                mostrarArreglo();
                break;
            case 4:
                busquedaNumeros();
                break;
            case 5:
                ordenarIntrosort();
                break;
            case 6:
                examen();
                break;
            case 7:
                guardarArchivo();
                break;
            case 8:
                cout << "\nHasta luego";
                repeticion++;
                break;
            default:
                cout << "\nOpcion invalida";
        }
        if (repeticion) break;
        cout << endl;
        system("pause");
    }
    cout << endl;
    system("pause");
    return 0;
}

// ================= MENU PRINCIPAL =================
int menu() {
    system("cls");
    cout << "\n Quirino Gonzalez Johann David";
    cout << "\n\tMenu";
    cout << "\n1 - Leer archivo";
    cout << "\n2 - Imprimir archivo";
    cout << "\n3 - Mostrar arreglo";
    cout << "\n4 - Busqueda Secuencial";
    cout << "\n5 - Ordenamiento Introsort";
    cout << "\n6 - Opcion examen";
    cout << "\n7 - Guardar archivo";
    cout << "\n8 - Salir";
    cout << "\nTeclee la opcion deseada : ";
    cin >> opcion;
    return 0;
}