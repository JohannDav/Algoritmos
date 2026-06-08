// Autor: Quirino González Johann David
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <cmath>
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
int izq=0, der=0, pivote=0;     //Quick Sort
float temporal =0;              //Quick Sort
int limite_izq=0;               //Quick Sort
int limite_der=0;               //Quick Sort, limite_izq = 0, limite_der = n-1
clock_t t_ini, t_fin;           //Tiempo
double secs;                    //Tiempo
string nombreArchivoE;
string nombreArchivoS;

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
void ordenamientoQuick();
void quickSort(float arreglo[][5], int limite_izq, int limite_der);
int identAlfaNumerico();
int identVotante();
int identInscrito();
int calculoIMC();

// Declaracion de la estructura que permite leer datos del archivo de entrada y copiarlos a un arreglo
struct Entrada {
    int id;
    int sexo;      //1 - hombres, 2 mujeres
    float peso;
    float estatura;
    float imc;
} entrada;

// Declaracion de la estructura que permite copiar los datos del arreglo y guardarlos en un archivo de salida
struct Salida {
    int id;
    int sexo;      //1 - hombres, 2 mujeres
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

    hayDatos = 1;        // Marcar que ya hay datos		
    datosOrdenados = 0;  // Los datos nuevos no estan ordenados

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
        return (0);  // No termina el programa, solo regresa al menu
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
    hayDatos = 1;        // Marcar que ya hay datos
    datosOrdenados = 0;  // Los datos del archivo no estan ordenados

    fclose(archivo1);

    return (0);
}

// ================= Guarda archivo =================

int guardaArchivo() {

    FILE *archivo2;

    // Validacion: No se puede guardar si no hay datos
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }

    // Validacion: No se puede guardar si no se han ordenado los datos
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

// ================= Busqueda de numeros (Secuencial) =================
int busquedaNumeros() {
    // Validacion: No se puede buscar si no hay datos
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }

    banderaEncontro = 0;
    cout << "\n--- ANTES DE LA BUSQUEDA ---";
    impresionNumeros();
    cout << "\nTeclee el ID a buscar : ";
    cin >> numeroBuscar;

    t_ini = clock();  // Inicia contador de tiempo (SOLO para la busqueda)

    for (i = 0; i < n; i++) {
        if (numeroBuscar == arreglo[i][0]) {
            cout << "\nID encontrado en la posicion " << i + 1;
            banderaEncontro = 1;
        }
    }

    t_fin = clock();  // Finaliza contador de tiempo

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

//  ================= Busqueda Binaria =================
void busquedaBin() {
    // Validacion: No se puede buscar si no hay datos
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return;
    }

    // Validacion: Los datos deben estar ordenados para busqueda binaria
    if (datosOrdenados == 0) {
        cout << "\n ERROR: No se puede realizar la busqueda binaria porque los datos no estan ordenados. \n";
        cout << " Primero ordene los datos con cualquier metodo de ordenamiento. \n";
        return;
    }

    cout << "\n--- ANTES DE LA BUSQUEDA ---";
    impresionNumeros();
    cout << "\nTeclee el ID a buscar en el arreglo :   ";
    cin >> buscar;

    t_ini = clock();  // Inicia contador de tiempo

    busquedaBinaria();

    t_fin = clock();  // Finaliza contador de tiempo

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

// ================= Metodo burbuja (con swap) =================
int burbuja() {
    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }

    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();

    t_ini = clock();        //Inicia el conteo de tiempo
    cout << endl;

    for (i = 0; i < n - 1; i++) {
        for (j = i; j < n; j++) {
            if (arreglo[i][0] > arreglo[j][0]) {
                // Usando swap para intercambiar filas completas
                swapFilas(arreglo[i], arreglo[j]);
            }
        }
    }

    t_fin = clock();        //Finaliza el conteo tiempo

    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionNumeros();

    //Inicia la impresion de tiempo
    cout << "\n\n Tiempo de ordenamiento por el metodo de Burbuja :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    //Termina impresion de tiempo

    datosOrdenados = 1;  // Marcar que los datos ya estan ordenados

    return (0);
}

// ================= Metodo Flotacion (con swap) =================
int flotacion() {
    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }

    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();

    t_ini = clock();        //Inicia el conteo de tiempo

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1; j++) {
            if (arreglo[j][0] > arreglo[j + 1][0]) {
                // Usando swap para intercambiar filas completas
                swapFilas(arreglo[j], arreglo[j + 1]);
            }
        }
    }

    t_fin = clock();        //Finaliza el conteo tiempo

    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionNumeros();

    //Inicia la impresion de tiempo
    cout << "\n\n Tiempo de ordenamiento por el metodo de Flotacion :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    //Termina impresion de tiempo

    datosOrdenados = 1;  // Marcar que los datos ya estan ordenados

    return (0);
}

// ================= Metodo Insercion (con swap) =================
int insercion() {
    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }

    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();

    t_ini = clock();        //Inicia el conteo de tiempo

    for (i = 1; i < n; i++) {
        int key = arreglo[i][0];
        float filaKey[5];
        
        // Guardar la fila completa que se va a insertar
        for (k = 0; k < 5; k++) {
            filaKey[k] = arreglo[i][k];
        }
        
        j = i - 1;
        while (j >= 0 && arreglo[j][0] > key) {
            // Mover fila j a posicion j+1
            for (k = 0; k < 5; k++) {
                arreglo[j + 1][k] = arreglo[j][k];
            }
            j--;
        }
        
        // Insertar la fila guardada en su posicion correcta
        for (k = 0; k < 5; k++) {
            arreglo[j + 1][k] = filaKey[k];
        }
    }

    t_fin = clock();        //Finaliza el conteo tiempo

    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionNumeros();

    //Inicia la impresion de tiempo
    cout << "\n\n Tiempo de ordenamiento por el metodo de Insercion :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    //Termina impresion de tiempo

    datosOrdenados = 1;  // Marcar que los datos ya estan ordenados

    return (0);
}

// ================= Metodo Seleccion (con swap) =================
int seleccion() {
    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }

    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();

    t_ini = clock();        //Inicia el conteo de tiempo

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arreglo[min_idx][0] > arreglo[j][0]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            // Usando swap para intercambiar filas completas
            swapFilas(arreglo[i], arreglo[min_idx]);
        }
    }

    t_fin = clock();        //Finaliza el conteo tiempo

    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionNumeros();

    //Inicia la impresion de tiempo
    cout << "\n\n Tiempo de ordenamiento por el metodo de Seleccion :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    //Termina impresion de tiempo

    datosOrdenados = 1;  // Marcar que los datos ya estan ordenados

    return (0);
}

// ================= Metodo Shell (con swap) =================
int shell() {
    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n  ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo.  \n";
        return (0);
    }

    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();

    t_ini = clock();        //Inicia el conteo de tiempo

    subarreglo = n / 2;
    while (subarreglo > 0) {
        for (i = subarreglo; i < n; i++) {
            j = i;
            float filaTemp[5];
            
            // Guardar la fila completa
            for (k = 0; k < 5; k++) {
                filaTemp[k] = arreglo[i][k];
            }
            
            while ((j >= subarreglo) && (arreglo[j - subarreglo][0] > filaTemp[0])) {
                // Mover fila j-subarreglo a posicion j
                for (k = 0; k < 5; k++) {
                    arreglo[j][k] = arreglo[j - subarreglo][k];
                }
                j = j - subarreglo;
            }
            
            // Insertar la fila en su posicion correcta
            for (k = 0; k < 5; k++) {
                arreglo[j][k] = filaTemp[k];
            }
        }
        subarreglo /= 2;
    }

    t_fin = clock();        //Finaliza el conteo tiempo
    cout << endl;

    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionNumeros();

    //Inicia la impresion de tiempo
    cout << "\n\n Tiempo de ordenamiento por el metodo de Shell :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    //Termina impresion de tiempo

    datosOrdenados = 1;  // Marcar que los datos ya estan ordenados

    return (0);
}

// ================= Metodo HeapSort (con swap) =================
// Funcion que identifica el numero mayor de todo el arreglo
void identificar_mayor(float arreglo[][5], int i, int n) {
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
        // Usando swap para intercambiar filas completas
        swapFilas(arreglo[i], arreglo[masgrande]);
        identificar_mayor(arreglo, masgrande, n);
    }
}

// Funcion que va conformando el arbol
void conformar_arbol(float arreglo[][5], int n) {
    for (int k = n / 2; k >= 0; k--) {
        identificar_mayor(arreglo, k, n);
    }
}

// Metodo de ordenamiento HeapSort
void heapSort() {
    conformar_arbol(arreglo, n - 1);
    for (i = n - 1; i >= 1; i--) {
        // Usando swap para intercambiar filas completas
        swapFilas(arreglo[i], arreglo[0]);
        identificar_mayor(arreglo, 0, i - 1);
    }
}

int ordenamientoHeapSort() {
    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n  ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo.  \n";
        return (0);
    }

    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();

    t_ini = clock();        //Inicia el conteo de tiempo

    heapSort();

    t_fin = clock();        //Finaliza el conteo tiempo

    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionNumeros();

    //Inicia la impresion de tiempo
    cout << "\n\n Tiempo de ordenamiento por el metodo de HeapSort :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    //Termina impresion de tiempo

    datosOrdenados = 1;  // Marcar que los datos ya estan ordenados

    return (0);
}

// ================= Metodo QuickSort (con swap) =================
void ordenamientoQuick() {
    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n  ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo.  \n";
        return;
    }

    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();

    t_ini = clock();        //Inicia el conteo de tiempo

    quickSort(arreglo, 0, n - 1);

    t_fin = clock();        //Finaliza el conteo tiempo

    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionNumeros();

    //Inicia la impresion de tiempo
    cout << "\n\n Tiempo de ordenamiento por el metodo de QuickSort :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    //Termina impresion de tiempo

    datosOrdenados = 1;  // Marcar que los datos ya estan ordenados
}

void quickSort(float arreglo[][5], int limite_izq, int limite_der) {
    izq = limite_izq;
    der = limite_der;
    pivote = arreglo[(izq + der) / 2][0];
    do {
        while (arreglo[izq][0] < pivote && izq < limite_der) {
            izq++;
        }
        while (pivote < arreglo[der][0] && der > limite_izq) {
            der--;
        }
        if (izq <= der) {
            // Usando swap para intercambiar filas completas
            swapFilas(arreglo[izq], arreglo[der]);
            izq++;
            der--;
        }
    } while (izq <= der);

    if (limite_izq < der) {
        quickSort(arreglo, limite_izq, der);
    }
    if (limite_der > izq) {
        quickSort(arreglo, izq, limite_der);
    }
}

// ================= identAlfaNumerico =================
int identAlfaNumerico() {
    // No aplica para numeros, pero se mantiene la estructura
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

// ================= calculoIMC =================
int calculoIMC() {
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }
    
    cout << "\n--- CALCULO DEL INDICE DE MASA CORPORAL (IMC) ---\n";
    for(i = 0; i < n; i++){
        float divisor = arreglo[i][3] * arreglo[i][3];
        float imc = arreglo[i][2] / divisor;
        cout << "Persona " << i+1 << " (ID: " << arreglo[i][0] << "): ";
        cout << "Peso = " << arreglo[i][2] << " kg, Estatura = " << arreglo[i][3] << " m, ";
        cout << "IMC = " << imc << endl;
    }
    return (0);
}

// ================= MAIN =================
int main() {

    for (repeticion = 0; repeticion == 0;) {

        menu();

        switch (opcion) {
        case (1):  // Captura de numeros
            numeroDatos();
            capturaNumeros();
            cout << "\n--- VERIFICACION ---";
            impresionNumeros();
            break;

        case (2):  // Lectura de archivo numeros
            leeArchivo();
            cout << "\n--- VERIFICACION ---";
            impresionNumeros();
            break;

        case (3):  // Impresion numeros
            if (hayDatos == 0) {
                cout << "\n  ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo.  \n";
            } else {
                impresionNumeros();
            }
            break;

        case (4):  // Busqueda Secuencial
            busquedaNumeros();
            break;

        case (5):  // Busqueda Binaria
            if (hayDatos == 0) {
                cout << "\n  ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo.  \n";
            } else if (datosOrdenados == 0) {
                cout << "\n  ERROR: No se puede realizar la busqueda binaria porque los datos no estan ordenados.  \n";
                cout << "  Primero ordene los datos con cualquier metodo de ordenamiento.  \n";
            } else {
                busquedaBin();
            }
            break;

        case (6):  // Metodo de ordenamiento Burbuja
            burbuja();
            break;

        case (7):  // Metodo de ordenamiento Flotacion
            flotacion();
            break;

        case (8):  // Metodo de ordenamiento Insercion
            insercion();
            break;

        case (9):  // Metodo de ordenamiento Seleccion
            seleccion();
            break;

        case (10): // Metodo de ordenamiento Shell
            shell();
            break;

        case (11): // Metodo de ordenamiento HeapSort
            ordenamientoHeapSort();
            break;

        case (12): // Metodo de ordenamiento QuickSort
            ordenamientoQuick();
            break;

        case (13): // Identificador Alfanumerico
            identAlfaNumerico();
            break;
            
        case (14): // Identificar votante
            identVotante();
            break;
            
        case (15): // Identificar inscrito
            identInscrito();
            break;
            
        case (16): // Calculo de IMC
            calculoIMC();
            break;

        case (17): // Guardar archivo
            guardaArchivo();
            break;

        case (18): // Salir del menu
            cout << "\nHasta luego";
            repeticion++;
            break;

        default:
            cout << "\nOpcion invalida";
        }
        
        cout << endl;
        system("pause");
    }

    cout << endl;
    system("pause");
}

// ================= MENU =================

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