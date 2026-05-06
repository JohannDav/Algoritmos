// Autor: Quirino González Johann David
// VERSION PARA ANALISIS DE RENDIMIENTO - SIN IMPRESIONES INNECESARIAS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>    
#include <time.h>     
using namespace std;


// ================= Declaracion de variables globales =================
int i = 0;
int j = 0;
int k = 0;
int l = 0;
int opcion = 0;
int repeticion = 0;
char caracterBuscar;
char aux;
char numMayor;
char temp;


int banderaEncontro = 0;

// ================= Variables para manejo de archivos =================
char arreglo[10000000];
int n = 0;
int cn = 0;
int guardacn = 0;


// Busqueda binaria
int inferior = 0;
int superior = n;
char buscar = 0;


// QuickSort
int izq=0, der=0;
char pivote;
char temporal;


// Tiempo
clock_t t_ini, t_fin;
double secs;


// ================= Prototipos =================
int numeroDatos();
int capturaCaracteres();
int impresionCaracteres();
int menu();
int leeArchivo();
int guardaArchivo();
int busquedaCaracteres();
int burbuja();
int flotacion();
int insercion();
int seleccion();
int shell();
int heapSort();
void identificar_mayor(char arreglo[], int i, int n);
void conformar_arbol(char arreglo[], int n);
void ordenamientoQuick();
void quickSort(char arreglo[], int limite_izq, int limite_der);
void busquedaBin();
int busquedaBinaria();
int identAlfaNumerico();


// Estructuras para archivos
struct Entrada {
    char valor;
} entrada;

struct Salida {
    char valor;
} salida;

string nombreArchivoE;
string nombreArchivoS;


// ================= Captura de caracteres =================
int capturaCaracteres() {
    cout << "\nTeclee " << n << " caracteres separados por un espacio : ";
    for (i = 0; i < n; i++) {
        cin >> arreglo[i];
    }
    return (0);
}


// ================= Lectura del archivo =================
int leeArchivo() {
    FILE *archivo1;
    cout << "\nTeclea el nombre del archivo de entrada: ";
    cin >> nombreArchivoE;
    nombreArchivoE += ".txt";
    archivo1 = fopen(nombreArchivoE.c_str(), "r");

    if (archivo1 == NULL) {
        cout << "\nNo se puede abrir el archivo ";
        return (0);
    }

    cn = 0;
    for (int i = 0; !feof(archivo1); i++) {
        fscanf(archivo1, "%c\n", &entrada.valor);
        arreglo[i] = entrada.valor;
        cn++;
    }
    n = cn;
    fclose(archivo1);
    cout << "\nSe leyeron " << n << " caracteres\n";
    return (0);
}


// ================= Guarda archivo =================
int guardaArchivo() {
    FILE *archivo2;
    cout << "\nTeclea el nombre del archivo de salida: ";
    cin >> nombreArchivoS;
    nombreArchivoS += ".txt";
    archivo2 = fopen(nombreArchivoS.c_str(), "w");

    if (archivo2 == NULL) {
        cout << "\nNo se puede abrir el archivo ";
        exit(1);
    }

    for (i = 0; i < n; i++) {
        salida.valor = arreglo[i];
        fprintf(archivo2, "%c\n", salida.valor);
    }
    fclose(archivo2);
    cout << "\nArchivo guardado correctamente\n";
    return (0);
}


// ================= Impresion de caracteres (SOLO PARA DEBUG) =================
int impresionCaracteres() {
    cout << "\nContenido del arreglo: \n ";
    for (i = 0; i < n; i++) {
        cout << arreglo[i] << "  ";
    }
    cout << endl;
    return (0);
}


// ================= Captura de numeros =================
int numeroDatos() {
    cout << "\nTeclee la cantidad de datos a procesar : ";
    cin >> n;
    return (0);
}


// ================= BUSQUEDA SECUENCIAL (VERSION RAPIDA) =================
int busquedaCaracteres() {
    banderaEncontro = 0;
    cout << "\nTeclee el caracter a buscar : ";
    cin >> caracterBuscar;
    
    t_ini = clock();
    
    // SOLO EL BUCLE DE BUSQUEDA - SIN IMPRESIONES DURANTE LA BUSQUEDA
    for (i = 0; i < n; i++) {
        if (caracterBuscar == arreglo[i]) {
            banderaEncontro = 1;
        }
    }
    
    t_fin = clock();
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    
    // RESULTADO
    if (banderaEncontro == 1) {
        cout << "\nCaracter ENCONTRADO";
    } else {
        cout << "\nCaracter NO encontrado";
    }
    cout << "\nTIEMPO: " << secs * 1000.0 << " milisegundos\n";
    return (0);
}


// ================= BUSQUEDA BINARIA (VERSION RAPIDA) =================
void busquedaBin() {
    cout << "\nTeclee el caracter a buscar : ";
    cin >> buscar;
    
    t_ini = clock();
    busquedaBinaria();
    t_fin = clock();
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    
    if (arreglo[i] == buscar) {
        cout << "Caracter ENCONTRADO en posicion " << i + 1;
    } else {
        cout << "Caracter NO encontrado";
    }
    cout << "\nTIEMPO: " << secs * 1000.0 << " milisegundos\n";
}

int busquedaBinaria() {
    inferior = 0, superior = n;
    while (superior >= inferior) {
        i = (inferior + superior) / 2;
        if (arreglo[i] == buscar) {
            return i;
        } else {
            if (buscar < arreglo[i]) {
                superior = i - 1;
            } else {
                inferior = i + 1;
            }
        }
    }
    return (0);
}


// ================= BURBUJA (VERSION RAPIDA - SIN PASADAS VISUALES) =================
int burbuja() {
    // SIN IMPRIMIR EL ARREGLO ANTES
    t_ini = clock();
    
    // SOLO EL ALGORITMO PURO
    for (i = 0; i < n - 1; i++) {
        for (j = i; j < n; j++) {
            if (arreglo[i] > arreglo[j]) {
                aux = arreglo[i];
                arreglo[i] = arreglo[j];
                arreglo[j] = aux;
            }
        }
    }
    
    t_fin = clock();
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    
    cout << "TIEMPO Burbuja: " << secs * 1000.0 << " milisegundos\n";
    return (0);
}


// ================= FLOTACION (VERSION RAPIDA - SIN PASADAS VISUALES) =================
int flotacion() {
    t_ini = clock();
    
    // SOLO EL ALGORITMO PURO - SIN cout DE PASADAS
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1; j++) {
            if (arreglo[j] > arreglo[j + 1]) {
                numMayor = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = numMayor;
            }
        }
        // LINEA ELIMINADA: cout << "\nPasada " << i + 1 << "..."
    }
    
    t_fin = clock();
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    
    cout << "TIEMPO Flotacion: " << secs * 1000.0 << " milisegundos\n";
    return (0);
}


// ================= INSERCION (VERSION RAPIDA - SIN PASADAS VISUALES) =================
int insercion() {
    char clave;
    int pos;
    
    t_ini = clock();
    
    for (i = 1; i < n; i++) {
        clave = arreglo[i];
        pos = i;
        while (pos > 0 && arreglo[pos - 1] > clave) {
            arreglo[pos] = arreglo[pos - 1];
            pos--;
        }
        arreglo[pos] = clave;
        // LINEA ELIMINADA: cout << "\nPasada " << i << ": ";
    }
    
    t_fin = clock();
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    
    cout << "TIEMPO Insercion: " << secs * 1000.0 << " milisegundos\n";
    return (0);
}


// ================= SELECCION (VERSION RAPIDA - SIN PASADAS VISUALES) =================
int seleccion() {
    int minimo;
    
    t_ini = clock();
    
    for (i = 0; i < n - 1; i++) {
        minimo = i;
        for (j = i + 1; j < n; j++) {
            if (arreglo[j] < arreglo[minimo]) {
                minimo = j;
            }
        }
        if (minimo != i) {
            aux = arreglo[i];
            arreglo[i] = arreglo[minimo];
            arreglo[minimo] = aux;
        }
        // LINEA ELIMINADA: cout << "\nPasada " << i + 1 << ": ";
    }
    
    t_fin = clock();
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    
    cout << "TIEMPO Seleccion: " << secs * 1000.0 << " milisegundos\n";
    return (0);
}


// ================= SHELL (VERSION RAPIDA) =================
int shell() {
    int subarreglo = 0;
    
    t_ini = clock();
    
    subarreglo = n / 2;
    while (subarreglo > 0) {
        for (i = subarreglo; i < n; i++) {
            j = i;
            temp = arreglo[i];
            while ((j >= subarreglo) && (arreglo[j - subarreglo] > temp)) {
                arreglo[j] = arreglo[j - subarreglo];
                j = j - subarreglo;
            }
            arreglo[j] = temp;
            // LINEAS ELIMINADAS: cout << "\nInicia subarreglo..."
        }
        subarreglo /= 2;
    }
    
    t_fin = clock();
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    
    cout << "TIEMPO Shell: " << secs * 1000.0 << " milisegundos\n";
    return (0);
}


// ================= HEAPSORT (VERSION RAPIDA) =================
void identificar_mayor(char arreglo[], int i, int n) {
    int izquierda, derecha, masgrande;
    char auxiliar;
    izquierda = 2 * i + 1;
    derecha = 2 * i + 2;
    if ((izquierda <= n) && (arreglo[izquierda] > arreglo[i])) {
        masgrande = izquierda;
    } else {
        masgrande = i;
    }
    if ((derecha <= n) && (arreglo[derecha] > arreglo[masgrande])) {
        masgrande = derecha;
    }
    if (masgrande != i) {
        auxiliar = arreglo[i];
        arreglo[i] = arreglo[masgrande];
        arreglo[masgrande] = auxiliar;
        identificar_mayor(arreglo, masgrande, n);
    }
}

void conformar_arbol(char arreglo[], int n) {
    for (int k = n / 2; k >= 0; k--) {
        identificar_mayor(arreglo, k, n - 1);
    }
}

int heapSort() {
    t_ini = clock();
    
    conformar_arbol(arreglo, n);
    for (i = n - 1; i >= 1; i--) {
        temp = arreglo[i];
        arreglo[i] = arreglo[0];
        arreglo[0] = temp;
        identificar_mayor(arreglo, 0, i - 1);
        // LINEA ELIMINADA: cout << "\nPasada " << n - i << ": ";
    }
    
    t_fin = clock();
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    
    cout << "TIEMPO HeapSort: " << secs * 1000.0 << " milisegundos\n";
    return (0);
}


// ================= QUICKSORT (VERSION RAPIDA) =================
void ordenamientoQuick() {
    t_ini = clock();
    quickSort(arreglo, 0, n - 1);
    t_fin = clock();
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    cout << "TIEMPO QuickSort: " << secs * 1000.0 << " milisegundos\n";
}

void quickSort(char arreglo[], int limite_izq, int limite_der) {
    izq = limite_izq;
    der = limite_der;
    pivote = arreglo[(izq + der) / 2];
    do {
        while (arreglo[izq] < pivote && izq < limite_der) izq++;
        while (pivote < arreglo[der] && der > limite_izq) der--;
        if (izq <= der) {
            temporal = arreglo[izq];
            arreglo[izq] = arreglo[der];
            arreglo[der] = temporal;
            izq++;
            der--;
        }
    } while (izq <= der);
    if (limite_izq < der) quickSort(arreglo, limite_izq, der);
    if (limite_der > izq) quickSort(arreglo, izq, limite_der);
}


// ================= IDENTIFICAR ALFANUMERICO =================
int identAlfaNumerico() {
    t_ini = clock();
    for (i = 0; i < n; i++) {
        if ((arreglo[i] >= 'A' && arreglo[i] <= 'Z') || 
            (arreglo[i] >= 'a' && arreglo[i] <= 'z') || 
            (arreglo[i] >= '0' && arreglo[i] <= '9')) {
            // SIN cout por caracter
        }
    }
    t_fin = clock();
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    cout << "TIEMPO verificacion alfanumerica: " << secs * 1000.0 << " milisegundos\n";
    return (0);
}


// ================= MENU PRINCIPAL =================
int menu() {
    system("cls");
    cout << "\n==========================================";
    cout << "\n   ANALISIS DE RENDIMIENTO - ALGORITMOS";
    cout << "\n==========================================";
    cout << "\n1 - Captura de caracteres";
    cout << "\n2 - Lectura de archivo";
    cout << "\n3 - Impresion de caracteres";
    cout << "\n4 - Busqueda Secuencial";
    cout << "\n5 - Busqueda Binaria";
    cout << "\n6 - Burbuja";
    cout << "\n7 - Flotacion";
    cout << "\n8 - Insercion";
    cout << "\n9 - Seleccion";
    cout << "\n10 - Shell";
    cout << "\n11 - HeapSort";
    cout << "\n12 - QuickSort";
    cout << "\n13 - Verificar alfanumerico";
    cout << "\n14 - Guardar archivo";
    cout << "\n15 - Salir";
    cout << "\n==========================================";
    cout << "\nOpcion: ";
    cin >> opcion;
    return (0);
}


// ================= MAIN =================
int main() {
    for (repeticion = 0; repeticion == 0;) {
        menu();
        switch (opcion) {
        case (1): 
			numeroDatos(); 
			capturaCaracteres(); 
			break;
        case (2): 
			leeArchivo(); 
			break;
        case (3): 
			impresionCaracteres(); 
		break;
        case (4): 
			busquedaCaracteres();
			break;
        case (5): 
			//impresionCaracteres(); 
			busquedaBin(); 
			break;
        case (6): 
			burbuja(); 
			break;
        case (7): 
			flotacion(); 
			break;
        case (8): 
			insercion(); 
			break;
        case (9): 
			seleccion(); 
			break;
        case (10): 
			shell(); 
			break;
        case (11): 
			heapSort(); 
			break;
        case (12): 
			ordenamientoQuick(); 
			break;
        case (13): 
			identAlfaNumerico(); 
			break;
        case (14): 
			guardaArchivo();
			break;
        case (15): 
			cout << "\nHasta luego"; 
			repeticion++; break;
        default: 
			cout << "\nOpcion inválida";
        }
        if (opcion != 15) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    }
    return (0);
}