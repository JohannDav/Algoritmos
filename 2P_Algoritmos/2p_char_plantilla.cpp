// Autor: Quirino González Johann David
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>    // Cabecera o biblioteca que permite trabajar con archivos
#include <time.h>     // Cabecera que permite contabilizar el tiempo de ejecucion
using namespace std;


// ================= Declaracion de variables globales =================
int i = 0;
int j = 0;
int k = 0;  // Variable adicional para bucles
int l = 0;  // Variable para impresion de pasadas
int opcion = 0;
int repeticion = 0;
char caracterBuscar;
char aux;
char numMayor;  // Variable para flotacion
char temp;      // Variable para shell y otros metodos


//Banderas
int banderaEncontro = 0;
int hayDatos = 0;        // Bandera para validar si hay datos en el arreglo
int datosOrdenados = 0;  // Bandera para validar si los datos estan ordenados

// ================= Declaracion variables para manejo de archivos =================
char arreglo[100];
int n = 0;
int cn = 0;
int guardacn = 0;


//Busqueda binaria
int inferior = 0;
int superior = n;
char buscar = 0;


//QuickSort
int izq=0, der=0;
char pivote;
char temporal;


//Tiempo
clock_t t_ini, t_fin;
double secs;


// ================= Declaracion de prototipos =================
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
int identificacionNumeros();  // Funcion para el examen (ejemplo)


// Declaracion de la estructura que permite leer datos del archivo de entrada y copiarlos a un arreglo
struct Entrada {
    char valor;
} entrada;


// Declaracion de la estructura que permite copiar los datos del arreglo y guardarlos en un archivo de salida
struct Salida {
    char valor;
} salida;


string nombreArchivoE;   // Nombre del archivo de entrada
string nombreArchivoS;   // Nombre del archivo de salida


// ================= Captura de caracteres =================

int capturaCaracteres() {

    cout << "\nTeclee " << n << " caracteres separados por un espacio : ";

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
        fscanf(archivo1, "%c\n", &entrada.valor);
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
        cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
        return (0);
    }
    
    // Validacion: No se puede guardar si no se han ordenado los datos
    if (datosOrdenados == 0) {
        cout << "\n*** ERROR: No se puede guardar el archivo porque los datos no estan ordenados. ***\n";
        cout << "*** Primero ordene los datos con cualquier metodo de ordenamiento. ***\n";
        return (0);
    }

    nombreArchivoS = "Quirino";

    cout << "\nTeclea el nombre del archivo de salida: ";
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
        fprintf(archivo2, "%c\n", salida.valor);
        guardacn++;
    }

    cout << "\n\nTotal de numeros guardados en el segundo archivo son: " << guardacn;
    cout << "\n\n";

    fclose(archivo2);

    return (0);
}


// ================= Impresion de caracteres =================

int impresionCaracteres() {

    cout << "\nContenido del arreglo: \n ";

    for (i = 0; i < n; i++) {
        cout << arreglo[i] << "  ";
    }
    cout << endl;

    return (0);
}


// ================= Captura de numeros a procesar =================

int numeroDatos() {
    cout << "\nTeclee la cantidad de datos a procesar : ";
    cin >> n;
    return (0);
}


// ================= Busqueda de caracteres (Secuencial) =================

int busquedaCaracteres() {
    // Validacion: No se puede buscar si no hay datos
    if (hayDatos == 0) {
        cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
        return (0);
    }
    
    banderaEncontro = 0;
    cout << "\n--- ANTES DE LA BUSQUEDA ---";
    impresionCaracteres();
    cout << "\nTeclee el caracter a buscar : ";
    cin >> caracterBuscar;
    
    t_ini = clock();  // Inicia contador de tiempo (SOLO para la busqueda)
    
    for (i = 0; i < n; i++) {
        if (caracterBuscar == arreglo[i]) {
            cout << "\nCaracter encontrado en la posicion " << i + 1;
            banderaEncontro = 1;
        }
    }
    
    t_fin = clock();  // Finaliza contador de tiempo
    
    if (banderaEncontro == 0) {
        cout << "\nCaracter no encontrado en el arreglo ";
    }
    
    cout << "\n\n--- DESPUES DE LA BUSQUEDA ---";
    impresionCaracteres();
    
    cout << "\n\n Tiempo de busqueda secuencial:  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n";
    
    return (0);
}


// ================= Busqueda Binaria =================

void busquedaBin() {
    // Validacion: No se puede buscar si no hay datos
    if (hayDatos == 0) {
        cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
        return;
    }
    
    // Validacion: No se puede ejecutar busqueda binaria si no se han ordenado los datos
    if (datosOrdenados == 0) {
        cout << "\n*** ERROR: No se puede realizar la busqueda binaria porque los datos no estan ordenados. ***\n";
        cout << "*** Primero ordene los datos con cualquier metodo de ordenamiento. ***\n";
        return;
    }
    
    cout << "\n--- ANTES DE LA BUSQUEDA ---";
    impresionCaracteres();
    cout << "\nTeclee el caracter a buscar en el arreglo :   ";
    cin >> buscar;
    
    t_ini = clock();  // Inicia contador de tiempo
    
    busquedaBinaria();
    
    t_fin = clock();  // Finaliza contador de tiempo
    
    if (arreglo[i] == buscar) {
        cout << "\nEl valor  " << buscar << "  se encuentra en la posicion " << i + 1;
    }
    else {
        cout << "\nNo se encontra el  valor  " << buscar << "  en el arreglo\n";
    }
    
    cout << "\n--- DESPUES DE LA BUSQUEDA ---";
    impresionCaracteres();
    
    cout << "\n\n Tiempo de busqueda binaria:  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n";
}

int busquedaBinaria() {
    inferior = 0, superior = n;
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


// ================= Metodo Burbuja =================

int burbuja() {
    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
        return (0);
    }
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionCaracteres();
    
    t_ini = clock();  // Inicia contador de tiempo (SOLO para el ordenamiento)
    
    for (i = 0; i < n - 1; i++) {
        for (j = i; j < n; j++) {
            if (arreglo[i] > arreglo[j]) {
                aux = arreglo[i];
                arreglo[i] = arreglo[j];
                arreglo[j] = aux;
            }
        }
    }
    
    t_fin = clock();  // Finaliza contador de tiempo
    
    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionCaracteres();

    cout << "\n\n Tiempo de ordenamiento por el metodo de Burbuja :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    
    datosOrdenados = 1;  // Marcar que los datos ya estan ordenados

    return (0);
}


// ================= Metodo Flotacion =================

int flotacion() {
    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
        return (0);
    }
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionCaracteres();
    
    t_ini = clock();  // Inicia contador de tiempo (SOLO para el ordenamiento)

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

    t_fin = clock();  // Finaliza contador de tiempo
    
    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionCaracteres();

    cout << "\n\n Tiempo de ordenamiento por el metodo de Flotacion :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    
    datosOrdenados = 1;  // Marcar que los datos ya estan ordenados

    return (0);
}


// ================= Metodo Insercion =================

int insercion() {
    char clave;
    int pos;

    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
        return (0);
    }
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionCaracteres();
    
    t_ini = clock();  // Inicia contador de tiempo (SOLO para el ordenamiento)

    for (i = 1; i < n; i++) {
        clave = arreglo[i];
        pos = i;

        while (pos > 0 && arreglo[pos - 1] > clave) {
            arreglo[pos] = arreglo[pos - 1];
            pos--;
        }
        arreglo[pos] = clave;
        // Se quita la impresion de pasadas
    }

    t_fin = clock();  // Finaliza contador de tiempo
    
    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionCaracteres();

    cout << "\n\n Tiempo de ordenamiento por el metodo de Insercion :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    
    datosOrdenados = 1;  // Marcar que los datos ya estan ordenados

    return (0);
}


// ================= Metodo Seleccion =================

int seleccion() {
    int minimo;

    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
        return (0);
    }
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionCaracteres();
    
    t_ini = clock();  // Inicia contador de tiempo (SOLO para el ordenamiento)

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
        // Se quita la impresion de pasadas
    }

    t_fin = clock();  // Finaliza contador de tiempo
    
    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionCaracteres();

    cout << "\n\n Tiempo de ordenamiento por el metodo de Seleccion :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    
    datosOrdenados = 1;  // Marcar que los datos ya estan ordenados

    return (0);
}


// ================= Metodo Shell =================

int shell() {
    int subarreglo = 0;

    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
        return (0);
    }
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionCaracteres();
    
    t_ini = clock();  // Inicia contador de tiempo (SOLO para el ordenamiento)

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
            // Se quita la impresion de pasadas
        }
        subarreglo /= 2;
    }
    cout << endl;

    t_fin = clock();  // Finaliza contador de tiempo
    
    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionCaracteres();

    cout << "\n\n Tiempo de ordenamiento por el metodo de Shell :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    
    datosOrdenados = 1;  // Marcar que los datos ya estan ordenados

    return (0);
}


// ================= Metodo HeapSort =================

void identificar_mayor(char arreglo[], int i, int n) {
    int izquierda, derecha, masgrande;
    char auxiliar;

    izquierda = 2 * i + 1;
    derecha = 2 * i + 2;

    if ((izquierda <= n) && (arreglo[izquierda] > arreglo[i])) {
        masgrande = izquierda;
    }
    else {
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
    // Validacion: No se puede ordenar si no hay datos
    if (hayDatos == 0) {
        cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
        return (0);
    }
    
    cout << "\n--- ANTES DEL ORDENAMIENTO ---";
    impresionCaracteres();
    
    t_ini = clock();  // Inicia contador de tiempo (SOLO para el ordenamiento)

    conformar_arbol(arreglo, n);

    for (i = n - 1; i >= 1; i--) {
        temp = arreglo[i];
        arreglo[i] = arreglo[0];
        arreglo[0] = temp;
        identificar_mayor(arreglo, 0, i - 1);
        // Se quita la impresion de pasadas
    }

    t_fin = clock();  // Finaliza contador de tiempo
    
    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionCaracteres();

    cout << "\n\n Tiempo de ordenamiento por el metodo de HeapSort :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    
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
    impresionCaracteres();
    
    t_ini = clock();  // Inicia contador de tiempo (SOLO para el ordenamiento)
    
    quickSort(arreglo, 0, n - 1);
    
    t_fin = clock();  // Finaliza contador de tiempo
    
    cout << "\n--- DESPUES DEL ORDENAMIENTO ---";
    impresionCaracteres();
    
    cout << "\n\n Tiempo de ordenamiento por el metodo de QuickSort :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    
    datosOrdenados = 1;  // Marcar que los datos ya estan ordenados
}

void quickSort(char arreglo[], int limite_izq, int limite_der) {
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


// ================= Funcion de verificacion de caracteres =================

int identAlfaNumerico() {
    // Validacion: No se puede verificar si no hay datos
    if (hayDatos == 0) {
        cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
        return (0);
    }
    
    cout << "\nVerificando caracter por caracter si es alfanumerico:\n";
    cout << "\n--- CONTENIDO DEL ARREGLO ---";
    impresionCaracteres();
    cout << "\n";
    
    for (i = 0; i < n; i++) {
        if ((arreglo[i] >= 'A' && arreglo[i] <= 'Z') || (arreglo[i] >= 'a' && arreglo[i] <= 'z') || (arreglo[i] >= '0' && arreglo[i] <= '9')) {
            cout << "El caracter '" << arreglo[i] << "' es alfanumerico\n";
        }
        else {
            cout << "El caracter '" << arreglo[i] << "' es un simbolo\n";
        }
    }
    return (0);
}


// ================= Funcion para el Examen (Ejemplo: Identificacion de numeros) =================

int identificacionNumeros() {
    // Validacion: No se puede identificar si no hay datos
    if (hayDatos == 0) {
        cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
        return (0);
    }
    
    cout << "\n=== EXAMEN - IDENTIFICACION DE CARACTERES ===\n";
    cout << "Identificando si los caracteres son numeros (digitos) o no:\n";
    cout << "\n--- CONTENIDO DEL ARREGLO ---";
    impresionCaracteres();
    cout << "\n";
    
    int contadorNumeros = 0;
    int contadorNoNumeros = 0;
    
    for (i = 0; i < n; i++) {
        if (arreglo[i] >= '0' && arreglo[i] <= '9') {
            cout << "El caracter '" << arreglo[i] << "' ES un numero (digito)\n";
            contadorNumeros++;
        } else {
            cout << "El caracter '" << arreglo[i] << "' NO es un numero\n";
            contadorNoNumeros++;
        }
    }
    
    cout << "\n--- RESUMEN ---";
    cout << "\nTotal de numeros (digitos): " << contadorNumeros;
    cout << "\nTotal de caracteres que no son numeros: " << contadorNoNumeros;
    cout << "\nTotal de caracteres analizados: " << n;
    cout << "\n";
    
    return (0);
}


// ================= MAIN =================

int main() {

    for (repeticion = 0; repeticion == 0;) {

        menu();

        switch (opcion) {
        case (1):  // Captura de caracteres
            numeroDatos();
            capturaCaracteres();
            cout << "\n--- VERIFICACION ---";
            impresionCaracteres();
            break;

        case (2):  // Lee archivo de caracteres
            leeArchivo();
            cout << "\n--- VERIFICACION ---";
            impresionCaracteres();
            break;

        case (3):  // Impresion caracteres
            if (hayDatos == 0) {
                cout << "\n*** ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. ***\n";
            } else {
                impresionCaracteres();
            }
            break;

        case (4):  // Busqueda secuencial
            busquedaCaracteres();
            break;

        case (5):  // Ordenamiento metodo burbuja
            burbuja();
            break;

        case (6):  // Ordenamiento metodo flotacion
            flotacion();
            break;

        case (7):  // Ordenamiento metodo seleccion
            seleccion();
            break;

        case (8):  // Ordenamiento metodo insercion
            insercion();
            break;

        case (9):  // Ordenamiento metodo quick sort
            ordenamientoQuick();
            break;

        case (10): // Ordenamiento metodo Shell
            shell();
            break;

        case (11): // Ordenamiento metodo heapsort
            heapSort();
            break;

        case (12): // Examen - Ejemplo: Identificacion de numeros
            identificacionNumeros();
            break;

        case (13): // Guarda archivo de caracteres
            guardaArchivo();
            break;

        case (14): // Salir del menu
            cout << "\nHasta luego";
            repeticion++;
            break;

        default:
            cout << "\nOpcion inválida";
            
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
    cout << "\n1 - Captura de caracteres";
    cout << "\n2 - Lee archivo de caracteres";
    cout << "\n3 - Impresion caracteres";
    cout << "\n4 - Busqueda secuencial";
    cout << "\n5 - Ordenamiento metodo burbuja";
    cout << "\n6 - Ordenamiento metodo flotacion";
    cout << "\n7 - Ordenamiento metodo seleccion";
    cout << "\n8 - Ordenamiento metodo insercion";
    cout << "\n9 - Ordenamiento metodo quick sort";
    cout << "\n10 - Ordenamiento metodo Shell";
    cout << "\n11 - Ordenamiento metodo heapsort";
    cout << "\n12 - Examen - Ejemplo: Identificacion de numeros";
    cout << "\n13 - Guarda archivo de caracteres";
    cout << "\n14 - Salir del menu";
    cout << "\nTeclee la opcion deseada : ";
    cin >> opcion;

    return (0);
}