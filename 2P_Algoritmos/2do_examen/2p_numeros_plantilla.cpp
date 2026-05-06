// Autor: Quirino González Johann David
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
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
int arreglo[1000]; //Tamaño 1,000
int inferior = 0; 				//Busqueda binaria
int superior = n;				//Busqueda binaria
int buscar = 0; 				//Busqueda Binaria
int izq=0, der=0, pivote=0;		//Quick Sort
int temporal =0;				//Quick Sort
int limite_izq=0;				//Quick Sort
int limite_der=0;				//Quick Sort, limite_izq = 0, limite_der = n-1
clock_t t_ini, t_fin;			//Tiempo
double secs;					//Tiempo
string nombreArchivoE;
string nombreArchivoS;

// Banderas
int hayDatos = 0;        // Bandera para validar si hay datos en el arreglo
int datosOrdenados = 0;  // Bandera para validar si los datos estan ordenados

// Variables adicionales para Shell, Flotacion, Insercion, Seleccion y HeapSort
int subarreglo = 0;     // Para Shell sort
int temp = 0;           // Para Shell sort e Insercion
int numMayor = 0;       // Para Flotacion
int min_idx = 0;        // Para Seleccion
int masgrande = 0;      // Para HeapSort
int auxiliar = 0;       // Para HeapSort

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
void identificar_mayor(int arreglo[], int i, int n);
void conformar_arbol(int arreglo[], int n);
void ordenamientoQuick();
void quickSort(int arreglo[], int limite_izq, int limite_der);
int identificacionCaracteres();  // Solo como ejemplo (identifica si es digito o no)

// Declaracion de la estructura que permite leer datos del archivo de entrada y copiarlos a un arreglo
struct Entrada {
    int valor;
} entrada;


// Declaracion de la estructura que permite copiar los datos del arreglo y guardarlos en un archivo de salida
struct Salida {
    int valor;
} salida;

// ================= Captura de numeros =================

int capturaNumeros() {

    cout << "\nTeclee " << n << " numeros separados por un espacio : ";

    for (i = 0; i < n; i++) {
        cin >> arreglo[i];
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
        fscanf(archivo1, "%d\n", &entrada.valor);
        arreglo[i] = entrada.valor;
        cn++;
    }

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

    cout << "\nTeclea el nombre del archivo de salida (sin espacios, ni caracteres especiales): ";
    cin >> nombreArchivoS;

    nombreArchivoS += ".txt";

    archivo2 = fopen(nombreArchivoS.c_str(), "w");

    if (archivo2 == NULL) {
        cout << "\nNo se puede abrir el archivo ";
        return (0);
    }
    else {
        cout << "\nSe abrio el archivo  " << nombreArchivoS.c_str() << "  correctamente\n";
    }

    cout << "\n\nGuarda los numeros contenidos en el arreglo en el archivo";

    guardacn = 0;

    for (i = 0; i < n; i++) {
        salida.valor = arreglo[i];
        fprintf(archivo2, "%d\n", salida.valor);
        guardacn++;
    }

    cout << "\n\nTotal de numeros guardados en el segundo archivo son: " << guardacn;
    cout << "\n\n";

    fclose(archivo2);

    return (0);
}


// ================= Impresion de numeros =================

int impresionNumeros() {

    cout << "\nContenido del arreglo: \n ";

    for (i = 0; i < n; i++) {
        cout << arreglo[i] << "  ";
    }
    cout << endl;

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
    cout << "\nTeclee el numero a buscar : ";
    cin >> numeroBuscar;

    t_ini = clock();  // Inicia contador de tiempo (SOLO para la busqueda)

    for (i = 0; i < n; i++) {
        if (numeroBuscar == arreglo[i]) {
            cout << "\nNumero encontrado en la posicion " << i + 1;
            banderaEncontro = 1;
        }
    }

    t_fin = clock();  // Finaliza contador de tiempo

    if (banderaEncontro == 0) {
        cout << "\nNumero no encontrado en el arreglo ";
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
        cout << " Primero ordene los datos con cualquier metodo de ordenamiento. n";
        return;
    }

    cout << "\n--- ANTES DE LA BUSQUEDA ---";
    impresionNumeros();
    cout << "\nTeclee el numero a buscar en el arreglo :   ";
    cin >> buscar;

    t_ini = clock();  // Inicia contador de tiempo

    busquedaBinaria();

    t_fin = clock();  // Finaliza contador de tiempo

    if (arreglo[i] == buscar) {
        cout << "\nEl valor  " << buscar << "  se encuentra en la posicion " << i + 1;
    }
    else {
        cout << "\nNo se encuentra el valor  " << buscar << "  en el arreglo\n";
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
        if (arreglo[i] == buscar) {
            return i;
        }
        else {
            if (buscar < arreglo[i]) {
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
            if (arreglo[i] > arreglo[j]) {
                aux = arreglo[i];
                arreglo[i] = arreglo[j];
                arreglo[j] = aux;
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

// ================= Metodo Flotacion =================
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
            if (arreglo[j] > arreglo[j + 1]) {
                numMayor = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = numMayor;
            }
        }
        // Se quita la impresion de pasadas
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

// ================= Metodo Insercion =================
int insercion() {
    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }

    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();

    t_ini = clock();        //Inicia el conteo de tiempo

    // Implementación del ordenamiento por inserción
    for (i = 1; i < n; i++) {
        temp = arreglo[i];  // Elemento actual a insertar
        j = i - 1;
        // Desplazar elementos mayores a la derecha
        while (j >= 0 && arreglo[j] > temp) {
            arreglo[j + 1] = arreglo[j];
            j--;
        }
        arreglo[j + 1] = temp; // Insertar en la posición correcta
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

// ================= Metodo Seleccion =================
int seleccion() {
    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }

    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();

    t_ini = clock();        //Inicia el conteo de tiempo

    // Implementación del ordenamiento por selección
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arreglo[min_idx] > arreglo[j]) {
                min_idx = j;
            }
        }
        // Intercambiar el elemento menor con el de la posición actual
        if (min_idx != i) {
            aux = arreglo[min_idx];
            arreglo[min_idx] = arreglo[i];
            arreglo[i] = aux;
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

// ================= Metodo Shell =================
int shell() {
    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
        return (0);
    }

    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionNumeros();

    t_ini = clock();        //Inicia el conteo de tiempo

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

// ================= Metodo HeapSort =================
// Funcion que identifica el número mayor de todo el arreglo
void identificar_mayor(int arreglo[], int i, int n) {
    int izquierda, derecha;
    izquierda = 2 * i + 1;  // Ajuste para índice base 0
    derecha = 2 * i + 2;    // Ajuste para índice base 0

    if ((izquierda <= n) && (arreglo[izquierda] > arreglo[i]))
        masgrande = izquierda;
    else
        masgrande = i;

    if ((derecha <= n) && (arreglo[derecha] > arreglo[masgrande]))
        masgrande = derecha;

    if (masgrande != i) {
        auxiliar = arreglo[i];
        arreglo[i] = arreglo[masgrande];
        arreglo[masgrande] = auxiliar;
        identificar_mayor(arreglo, masgrande, n);
    }
}

// Función que va conformando el arbol
void conformar_arbol(int arreglo[], int n) {
    for (int k = n / 2; k >= 0; k--) {
        identificar_mayor(arreglo, k, n);
    }
}

// Metodo de ordenamiento HeapSort
void heapSort() {
    conformar_arbol(arreglo, n - 1);
    for (i = n - 1; i >= 1; i--) {
        temp = arreglo[i];
        arreglo[i] = arreglo[0];
        arreglo[0] = temp;
        identificar_mayor(arreglo, 0, i - 1);
    }
}

int ordenamientoHeapSort() {
    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
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

// ================= Metodo QuickSort =================
void ordenamientoQuick() {
    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
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

void quickSort(int arreglo[], int limite_izq, int limite_der) {
    izq = limite_izq;
    der = limite_der;
    pivote = arreglo[(izq + der) / 2];
    do {
        while (arreglo[izq] < pivote && izq < limite_der) {
            izq++;
        }
        while (pivote < arreglo[der] && der > limite_izq) {
            der--;
        }
        if (izq <= der) {
            temporal = arreglo[izq];
            arreglo[izq] = arreglo[der];
            arreglo[der] = temporal;
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

// ================= Funcion para el Examen (Identificacion de caracteres/numeros) =================
int identificacionCaracteres() {
    // Validacion: No se puede identificar si no hay datos
    if (hayDatos == 0) {
        cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
        return (0);
    }

    cout << "\n=== EXAMEN - IDENTIFICACION DE NUMEROS ===\n";
    cout << "El programa identifica numeros primos, pares, impares, etc.\n";
    cout << "\n--- CONTENIDO DEL ARREGLO ---";
    impresionNumeros();
    cout << "\n";

    int contadorPares = 0;
    int contadorImpares = 0;
    int contadorPrimos = 0;

    for (i = 0; i < n; i++) {
        // Verificar si es par o impar
        if (arreglo[i] % 2 == 0) {
            cout << "El numero " << arreglo[i] << " es PAR\n";
            contadorPares++;
        } else {
            cout << "El numero " << arreglo[i] << " es IMPAR\n";
            contadorImpares++;
        }

        // Verificar si es primo (solo para numeros mayores a 1)
        int esPrimo = 1;
        if (arreglo[i] <= 1) {
            esPrimo = 0;
        } else {
            for (int d = 2; d * d <= arreglo[i]; d++) {
                if (arreglo[i] % d == 0) {
                    esPrimo = 0;
                    break;
                }
            }
        }
        if (esPrimo) {
            cout << "El numero " << arreglo[i] << " es PRIMO\n";
            contadorPrimos++;
        }
        cout << "------------------------\n";
    }

    cout << "\n--- RESUMEN ---";
    cout << "\nTotal de numeros pares: " << contadorPares;
    cout << "\nTotal de numeros impares: " << contadorImpares;
    cout << "\nTotal de numeros primos: " << contadorPrimos;
    cout << "\nTotal de numeros analizados: " << n;
    cout << "\n";

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
                cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
            } else {
                impresionNumeros();
            }
            break;

        case (4):  // Busqueda Secuencial
            busquedaNumeros();
            break;

        case (5):  // Busqueda Binaria
            if (hayDatos == 0) {
                cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
            } else if (datosOrdenados == 0) {
                cout << "\n*** ERROR: No se puede realizar la busqueda binaria porque los datos no estan ordenados. ***\n";
                cout << "*** Primero ordene los datos con cualquier metodo de ordenamiento. ***\n";
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

        case (13): // Examen - Identificacion de numeros
            identificacionCaracteres();
            break;

        case (14): // Guardar archivo
            guardaArchivo();
            break;

        case (15): // Salir del menu
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
    cout << "\n13 - Examen - Identificacion de numeros";
    cout << "\n14 - Guardar archivo";
    cout << "\n15 - Salir del menu";
    cout << "\nTeclee la opcion deseada : ";
    cin >> opcion;
    return (0);
}