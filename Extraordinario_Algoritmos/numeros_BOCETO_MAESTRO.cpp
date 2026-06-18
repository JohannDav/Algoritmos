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
// NOTA: Estas variables se utilizan en múltiples funciones del programa
// Se mantienen como globales para facilitar el copiado de métodos

int i = 0;          // Variable de control para ciclos (usada en casi todas las funciones)
int j = 0;          // Variable de control para ciclos anidados (usada en burbuja, flotacion, insercion, seleccion, shell)
int k = 0;          // Variable de control para ciclos adicionales (usada en insercion, shell, heapSort)
int l = 0;          // Variable de control auxiliar (no se usa actualmente)
int n = 0;          // Cantidad de datos (usada en numeroDatos, capturaNumeros, impresionNumeros, y todos los ordenamientos)
int cn = 0;         // Contador de datos leidos del archivo (usada en leeArchivo)
int guardacn = 0;   // Contador de datos guardados (usada en guardaArchivo)
int banderaEncontro = 0; // Bandera para busqueda secuencial (usada en busquedaNumeros)
int aux = 0;        // Variable auxiliar (no se usa actualmente)
int aux_num = 0;    // Variable auxiliar (no se usa actualmente)
int opcion = 0;     // Opcion del menu (usada en main y menu)
int repeticion = 0; // Control del bucle principal (usada en main)
int numeroBuscar;   // Numero a buscar en busqueda secuencial (usada en busquedaNumeros)
float arreglo[100][5];  // Matriz principal: [ID][Sexo][Peso][Estatura][IMC] (usada en todas las funciones)
float arreglo2[100];    // Arreglo auxiliar (no se usa actualmente)
int inferior = 0;   // Limite inferior para busqueda binaria (usada en busquedaBin y busquedaBinaria)
int superior = 0;   // Limite superior para busqueda binaria (usada en busquedaBin y busquedaBinaria)
int buscar = 0;     // Valor a buscar en busqueda binaria (usada en busquedaBin, busquedaBinaria, identInscrito)
int izq=0, der=0, pivote=0;  // Variables para QuickSort (ya no se usan, se mantienen por compatibilidad)
float temporal =0;  // Variable temporal para QuickSort (ya no se usa)
int limite_izq=0;   // Limite izquierdo para QuickSort (ya no se usa)
int limite_der=0;   // Limite derecho para QuickSort (ya no se usa)
clock_t t_ini, t_fin;   // Variables para medir tiempo (usadas en todos los metodos de ordenamiento y busqueda)
double secs;        // Tiempo en segundos (usada en todos los metodos de ordenamiento y busqueda)
string nombreArchivoE;  // Nombre del archivo de entrada (usada en leeArchivo)
string nombreArchivoS;  // Nombre del archivo de salida (usada en guardaArchivo)

// Variables globales para IMC
float divisor = 0;  // Variable para calcular el divisor (estatura^2) - usada en calculoIMC
float imc = 0;      // Variable para almacenar el IMC calculado - usada en calculoIMC, analisisIMCHombres, analisisIMCMujeres

// Banderas
int hayDatos = 0;        // Bandera para validar si hay datos en el arreglo (usada en casi todas las funciones)
int datosOrdenados = 0;  // Bandera para validar si los datos estan ordenados (usada en busquedaBin, guardaArchivo, identInscrito)

// Variables adicionales para Shell, Flotacion, Insercion, Seleccion y HeapSort
int subarreglo = 0;  // Tamaño del subarreglo para Shell sort (usada en shell)
float temp = 0;      // Variable temporal para Shell sort e Insercion (usada en shell e insercion)
float numMayor = 0;  // Variable para Flotacion (no se usa actualmente)
int min_idx = 0;     // Indice del elemento minimo para Seleccion (usada en seleccion)
int masgrande = 0;   // Indice del elemento mas grande para HeapSort (usada en identificar_mayor y conformar_arbol)
float auxiliar = 0;  // Variable auxiliar (no se usa actualmente)
float auxMatriz[1][5];  // Auxiliar para intercambiar filas completas (no se usa actualmente)

// ================= Funcion auxiliar para swap de filas =================
// Variables usadas: arreglo (global), idx (local)
void swapFilas(float fila1[5], float fila2[5]) {
    // Intercambia todos los elementos de dos filas completas
    // Usada en: burbuja, flotacion, seleccion, heapSort
    for (int idx = 0; idx < 5; idx++) {
        swap(fila1[idx], fila2[idx]);
    }
}

// ================= Funciones para leer entero con validacion =================
// Variables usadas: valor (local)
int leerEntero() {
    // Lee un entero con validacion de entrada
    // Usada para lectura segura de datos
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

// ================= Funcion de comparacion para sort() =================
// Variables usadas: fila1, fila2 (parametros)
bool compararPorID(const float fila1[5], const float fila2[5]) {
    // Compara dos filas por su ID (primer elemento)
    // Usada en: ordenamientoQuick (aunque se usa lambda en su lugar)
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
// Variables usadas en: leeArchivo, guardaArchivo
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
// Variables usadas: n (global), arreglo (global), hayDatos, datosOrdenados
int capturaNumeros() {
    // Captura n numeros desde el teclado y los almacena en arreglo[][0]
    // Uso: main -> opcion 1
    cout << "\nTeclee " << n << " numeros separados por un espacio : ";
    for (i = 0; i < n; i++) {
        cin >> arreglo[i][0];
    }
    hayDatos = 1;
    datosOrdenados = 0;
    return (0);
}

// ================= Lectura del archivo =================
// Variables usadas: nombreArchivoE (global), cn (global), arreglo (global), entrada (struct), hayDatos, datosOrdenados, n
int leeArchivo() {
    // Lee datos desde un archivo de texto y los carga en el arreglo
    // Formato del archivo: ID Sexo Peso Estatura
    // Uso: main -> opcion 2
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
// Variables usadas: hayDatos, datosOrdenados, nombreArchivoS, arreglo, salida (struct), guardacn, n
int guardaArchivo() {
    // Guarda los datos ordenados en un archivo de texto
    // Uso: main -> opcion 17
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
// Variables usadas: n (global), arreglo (global)
int impresionNumeros() {
    // Muestra el contenido del arreglo en pantalla
    // Uso: main -> opcion 3 y en varios metodos para mostrar antes/despues
    cout << "\nContenido del arreglo \n";
    cout << "ID   Sexo   Peso   Estatura\n";
    for(i = 0; i < n; i++){
        cout << arreglo[i][0] << "     " << arreglo[i][1] << "     " << arreglo[i][2] << "     " << arreglo[i][3] << endl;
    }
    return (0);
}

// ================= Captura de cantidad =================
// Variables usadas: n (global)
int numeroDatos() {
    // Captura la cantidad de datos a procesar
    // Uso: main -> opcion 1
    cout << "\nTeclee la cantidad de datos a procesar : ";
    cin >> n;
    return (0);
}

// ================= Busqueda Secuencial =================
// Variables usadas: hayDatos, arreglo, n, numeroBuscar, banderaEncontro, t_ini, t_fin, secs, i
int busquedaNumeros() {
    // Busca un ID de forma secuencial en el arreglo
    // Uso: main -> opcion 4
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
// Variables usadas: hayDatos, datosOrdenados, buscar, t_ini, t_fin, secs, arreglo, i
void busquedaBin() {
    // Funcion envoltorio para la busqueda binaria
    // Uso: main -> opcion 5
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

// ================= Funcion de busqueda binaria =================
// Variables usadas: inferior, superior, arreglo, buscar, i, n
int busquedaBinaria() {
    // Implementa el algoritmo de busqueda binaria
    // Usada por: busquedaBin, identInscrito
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
// Variables usadas: hayDatos, n, arreglo, t_ini, t_fin, secs, i, j, datosOrdenados
int burbuja() {
    // Ordena el arreglo usando el metodo de la burbuja
    // Uso: main -> opcion 6
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();
    t_ini = clock();
    for (i = 0; i < n - 1; i++) {
        for (j = i; j < n; j++) {
            if (arreglo[i][0] > arreglo[j][0]) {
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
// Variables usadas: hayDatos, n, arreglo, t_ini, t_fin, secs, i, j, datosOrdenados
int flotacion() {
    // Ordena el arreglo usando el metodo de flotacion (burbuja optimizada)
    // Uso: main -> opcion 7
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();
    t_ini = clock();
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1; j++) {
            if (arreglo[j][0] > arreglo[j + 1][0]) {
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
// Variables usadas: hayDatos, n, arreglo, t_ini, t_fin, secs, i, j, k, datosOrdenados
int insercion() {
    // Ordena el arreglo usando el metodo de insercion
    // Uso: main -> opcion 8
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }
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
        while (j >= 0 && arreglo[j][0] > key) {
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
// Variables usadas: hayDatos, n, arreglo, t_ini, t_fin, secs, i, j, min_idx, datosOrdenados
int seleccion() {
    // Ordena el arreglo usando el metodo de seleccion
    // Uso: main -> opcion 9
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();
    t_ini = clock();
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arreglo[min_idx][0] > arreglo[j][0]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swapFilas(arreglo[i], arreglo[min_idx]);
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
// Variables usadas: hayDatos, n, arreglo, t_ini, t_fin, secs, subarreglo, i, j, k, datosOrdenados
int shell() {
    // Ordena el arreglo usando el metodo Shell sort
    // Uso: main -> opcion 10
    if (hayDatos == 0) {
        cout << "\n  ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo.  \n";
        return (0);
    }
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
            while ((j >= subarreglo) && (arreglo[j - subarreglo][0] > filaTemp[0])) {
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
// Variables usadas: arreglo, masgrande, n, i
void identificar_mayor(float arreglo[][5], int i, int n) {
    // Identifica el mayor elemento en el arbol heap
    // Usada por: conformar_arbol, heapSort
    int izquierda, derecha;
    izquierda = 2 * i + 1;
    derecha = 2 * i + 2;
    if ((izquierda <= n) && (arreglo[izquierda][0] > arreglo[i][0]))
        masgrande = izquierda;
    else
        masgrande = i;
    if ((derecha <= n) && (arreglo[derecha][0] > arreglo[masgrande][0]))
        masgrande = derecha;
    if (masgrande != i) {
        swapFilas(arreglo[i], arreglo[masgrande]);
        identificar_mayor(arreglo, masgrande, n);
    }
}

// Variables usadas: arreglo, n
void conformar_arbol(float arreglo[][5], int n) {
    // Conforma el arbol heap a partir del arreglo
    // Usada por: heapSort
    for (int k = n / 2; k >= 0; k--) {
        identificar_mayor(arreglo, k, n);
    }
}

// Variables usadas: arreglo, n, i
void heapSort() {
    // Implementa el algoritmo HeapSort
    // Usada por: ordenamientoHeapSort
    conformar_arbol(arreglo, n - 1);
    for (i = n - 1; i >= 1; i--) {
        swapFilas(arreglo[i], arreglo[0]);
        identificar_mayor(arreglo, 0, i - 1);
    }
}

// Variables usadas: hayDatos, n, arreglo, t_ini, t_fin, secs, datosOrdenados
int ordenamientoHeapSort() {
    // Funcion envoltorio para HeapSort con medicion de tiempo
    // Uso: main -> opcion 11
    if (hayDatos == 0) {
        cout << "\n  ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo.  \n";
        return (0);
    }
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
// Variables usadas: hayDatos, n, arreglo, t_ini, t_fin, secs, datosOrdenados
int ordenamientoQuick() {
    // Ordena el arreglo usando la funcion sort() de la libreria algorithm
    // Uso: main -> opcion 12
    if (hayDatos == 0) {
        cout << "\n  ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo.  \n";
        return (0);
    }
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();
    t_ini = clock();
    float* ptrArreglo[100];
    for (int idx = 0; idx < n; idx++) {
        ptrArreglo[idx] = arreglo[idx];
    }
    sort(ptrArreglo, ptrArreglo + n, [](const float* a, const float* b) {
        return a[0] < b[0];
    });
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
// Variables usadas: ninguna
int identAlfaNumerico() {
    // Funcion placeholder para identificador alfanumerico
    // Uso: main -> opcion 13
    cout << "\nIdentificador alfanumerico - No aplica para arreglo de numeros\n";
    return (0);
}

// ================= IdentVotante =================
// Variables usadas: hayDatos, n, arreglo, i
int identVotante() {
    // Identifica si los votantes son mayores de edad (ID >= 18)
    // Uso: main -> opcion 14
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
// Variables usadas: hayDatos, datosOrdenados, buscar, arreglo, i
int identInscrito() {
    // Verifica si un ID esta inscrito usando busqueda binaria
    // Uso: main -> opcion 15
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
// Variables usadas: imc (global)
int analisisIMCHombres() {
    // Analiza el IMC segun la tabla para hombres
    // Usada por: calculoIMC
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
// Variables usadas: imc (global)
int analisisIMCMujeres() {
    // Analiza el IMC segun la tabla para mujeres
    // Usada por: calculoIMC
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
// Variables usadas: hayDatos, n, arreglo, divisor, imc, i
int calculoIMC() {
    // Calcula el Indice de Masa Corporal para cada persona
    // Uso: main -> opcion 16
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
// Variables usadas: repeticion, opcion, hayDatos, datosOrdenados
int main() {
    // Funcion principal que maneja el menu y las opciones
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
// Variables usadas: opcion (global)
int menu() {
    // Muestra el menu principal y captura la opcion seleccionada
    // Uso: main
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