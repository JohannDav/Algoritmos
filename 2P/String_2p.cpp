// Autor: Quirino González Johann David
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <time.h>
#include <ctype.h>
#include <cstring>
using namespace std;


// ================= Declaracion de variables globales =================
int i = 0;
int j = 0;
int opcion = 0;
int repeticion = 0;
string caracterBuscar;
char aux;


//Banderas
int banderaEncontro = 0;

// ================= Declaracion variables para manejo de archivos =================
string arreglo[1000];  // ARREGLO DE STRINGS (palabras completas)
int n = 0;
int cn = 0;
int guardacn = 0;


//Busqueda binaria
int inferior = 0;
int superior = 0;
string buscar;


//QuickSort
int izq=0, der=0;
string pivote;
string temporal;


//Tiempo
clock_t t_ini, t_fin;
double secs;


// ================= Declaracion de prototipos =================
int numeroDatos();
int capturaStrings();
int impresionStrings();
int menu();
int leeArchivo();
int guardaArchivo();
int busquedaStrings();
int burbuja();
void ordenamientoQuick();
void quickSort(string arreglo[], int limite_izq, int limite_der);
void busquedaBin();
int busquedaBinaria();
int identAlfaNumerico();
int identLetra();
int identDigito();
int identMinuscula();
int identMayuscula();
int identEspacio();
int identPuntuacion();
int convertirMinuscula();
int convertirMayuscula();


string nombreArchivoE;
string nombreArchivoS;


// ================= Captura de strings =================

int capturaStrings() {
    cout << "\nTeclee " << n << " palabras separadas por un espacio : ";
    for (i = 0; i < n; i++) {
        cin >> arreglo[i];
    }
    return (0);
}


// ================= Lectura del archivo (lee palabras completas usando fgets) =================

int leeArchivo() {
    FILE *archivo1;
    char linea[1000];
    
    cout << "\nTeclea el nombre del archivo de entrada (sin espacio, ni caracteres especiales):   ";
    cin >> nombreArchivoE;
    
    nombreArchivoE += ".txt";
    
    archivo1 = fopen(nombreArchivoE.c_str(), "r");
    
    if (archivo1 == NULL) {
        cout << "\nNo se puede abrir el archivo ";
        exit(1);
    }
    else {
        cout << "\nSe abrio correctamente el archivo " << nombreArchivoE.c_str();
    }
    
    cn = 0;
    
    // Leer el archivo y separar en palabras (strings)
    while (fgets(linea, sizeof(linea), archivo1) != NULL) {
        // Usar strtok para separar la linea en palabras
        char *token = strtok(linea, " \t\n\r");
        
        while (token != NULL) {
            arreglo[cn] = string(token);
            cn++;
            token = strtok(NULL, " \t\n\r");
        }
    }
    
    cout << "\n\nSe ha generado el arreglo con los datos del archivo de entrada";
    cout << "\nLa cantidad de palabras contenidas en el arreglo son:  " << cn << "\n\n";
    
    n = cn;
    superior = n;
    
    fclose(archivo1);
    
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
    else {
        cout << "\nSe abrio el archivo  " << nombreArchivoS.c_str() << "  correctamente\n";
    }
    
    cout << "\n\nGuardando las palabras contenidas en el arreglo en el archivo";
    
    guardacn = 0;
    
    for (i = 0; i < n; i++) {
        fprintf(archivo2, "%s\n", arreglo[i].c_str());
        guardacn++;
    }
    
    cout << "\n\nTotal de palabras guardadas en el archivo son: " << guardacn;
    cout << "\n\n";
    
    fclose(archivo2);
    
    return (0);
}


// ================= Impresion de strings =================

int impresionStrings() {
    cout << "\nContenido del arreglo: \n ";
    for (i = 0; i < n; i++) {
        cout << arreglo[i] << "  ";
    }
    cout << "\n";
    return (0);
}


// ================= Captura de numeros a procesar =================

int numeroDatos() {
    cout << "\nTeclee la cantidad de palabras a procesar : ";
    cin >> n;
    superior = n;
    return (0);
}


// ================= Busqueda de strings =================

int busquedaStrings() {
    banderaEncontro = 0;
    impresionStrings();
    cout << "\nTeclee la palabra a buscar : ";
    cin >> caracterBuscar;
    
    for (i = 0; i < n; i++) {
        if (caracterBuscar == arreglo[i]) {
            cout << "\nPalabra encontrada en la posicion " << i + 1;
            banderaEncontro = 1;
        }
    }
    
    if (banderaEncontro == 0) {
        cout << "\nPalabra no encontrada en el arreglo ";
    }
    return (0);
}


// ================= Busqueda Binaria =================

void busquedaBin() {
    if (n == 0) {
        cout << "\nPrimero debes capturar o leer datos";
        return;
    }
    cout << "\nTeclee la palabra a buscar en el arreglo :   ";
    cin >> buscar;
    busquedaBinaria();
    if (arreglo[i] == buscar) {
        cout << "La palabra \"" << buscar << "\" se encuentra en la posicion " << i + 1;
    }
    else {
        cout << "No se encontro la palabra \"" << buscar << "\" en el arreglo\n";
    }
}

int busquedaBinaria() {
    inferior = 0;
    superior = n - 1;
    
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
    if (n == 0) {
        cout << "\nPrimero debes capturar o leer datos";
        return 0;
    }
    
    cout << "\nOrdenando por metodo Burbuja...";
    impresionStrings();
    t_ini = clock();
    
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (arreglo[i] > arreglo[j]) {
                temporal = arreglo[i];
                arreglo[i] = arreglo[j];
                arreglo[j] = temporal;
            }
        }
    }
    
    t_fin = clock();
    cout << "\nArreglo ordenado: ";
    impresionStrings();
    
    cout << "\n\n Tiempo de ordenamiento por el metodo de Burbuja :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
    
    return (0);
}


// ================= Metodo QuickSort =================

void ordenamientoQuick() {
    if (n == 0) {
        cout << "\nPrimero debes capturar o leer datos";
        return;
    }
    
    cout << "\nOrdenando por metodo QuickSort...";
    impresionStrings();
    t_ini = clock();
    quickSort(arreglo, 0, n - 1);
    t_fin = clock();
    cout << "\nArreglo ordenado: ";
    impresionStrings();
    
    cout << "\n\n Tiempo de ordenamiento por el metodo de QuickSort :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout << "\n\n";
}

void quickSort(string arreglo[], int limite_izq, int limite_der) {
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


// ================= Funciones de verificacion de strings =================

int identAlfaNumerico() {
    if (n == 0) {
        cout << "\nPrimero debes capturar o leer datos";
        return 0;
    }
    cout << "\nVerificando cada palabra si es alfanumerica:\n";
    for (i = 0; i < n; i++) {
        bool esAlfanumerico = true;
        for (char c : arreglo[i]) {
            if (!isalnum(c)) {
                esAlfanumerico = false;
                break;
            }
        }
        if (esAlfanumerico) {
            cout << "La palabra \"" << arreglo[i] << "\" es alfanumerica\n";
        } else {
            cout << "La palabra \"" << arreglo[i] << "\" contiene simbolos\n";
        }
    }
    return (0);
}

int identLetra() {
    if (n == 0) {
        cout << "\nPrimero debes capturar o leer datos";
        return 0;
    }
    cout << "\nVerificando cada palabra si contiene solo letras:\n";
    for (i = 0; i < n; i++) {
        bool sonLetras = true;
        for (char c : arreglo[i]) {
            if (!isalpha(c)) {
                sonLetras = false;
                break;
            }
        }
        if (sonLetras) {
            cout << "La palabra \"" << arreglo[i] << "\" solo tiene letras\n";
        } else {
            cout << "La palabra \"" << arreglo[i] << "\" no solo tiene letras\n";
        }
    }
    return (0);
}

int identDigito() {
    if (n == 0) {
        cout << "\nPrimero debes capturar o leer datos";
        return 0;
    }
    cout << "\nVerificando cada palabra si es un numero:\n";
    for (i = 0; i < n; i++) {
        bool sonDigitos = true;
        for (char c : arreglo[i]) {
            if (!isdigit(c)) {
                sonDigitos = false;
                break;
            }
        }
        if (sonDigitos) {
            cout << "La palabra \"" << arreglo[i] << "\" es un numero\n";
        } else {
            cout << "La palabra \"" << arreglo[i] << "\" no es un numero\n";
        }
    }
    return (0);
}

int identMinuscula() {
    if (n == 0) {
        cout << "\nPrimero debes capturar o leer datos";
        return 0;
    }
    cout << "\nVerificando cada palabra si esta en minusculas:\n";
    for (i = 0; i < n; i++) {
        bool sonMinusculas = true;
        for (char c : arreglo[i]) {
            if (isalpha(c) && !islower(c)) {
                sonMinusculas = false;
                break;
            }
        }
        if (sonMinusculas) {
            cout << "La palabra \"" << arreglo[i] << "\" esta en minusculas\n";
        } else {
            cout << "La palabra \"" << arreglo[i] << "\" NO esta en minusculas\n";
        }
    }
    return (0);
}

int identMayuscula() {
    if (n == 0) {
        cout << "\nPrimero debes capturar o leer datos";
        return 0;
    }
    cout << "\nVerificando cada palabra si esta en mayusculas:\n";
    for (i = 0; i < n; i++) {
        bool sonMayusculas = true;
        for (char c : arreglo[i]) {
            if (isalpha(c) && !isupper(c)) {
                sonMayusculas = false;
                break;
            }
        }
        if (sonMayusculas) {
            cout << "La palabra \"" << arreglo[i] << "\" esta en mayusculas\n";
        } else {
            cout << "La palabra \"" << arreglo[i] << "\" NO esta en mayusculas\n";
        }
    }
    return (0);
}

int identEspacio() {
    if (n == 0) {
        cout << "\nPrimero debes capturar o leer datos";
        return 0;
    }
    cout << "\nVerificando cada palabra si contiene espacios:\n";
    for (i = 0; i < n; i++) {
        bool tieneEspacio = false;
        for (char c : arreglo[i]) {
            if (isspace(c)) {
                tieneEspacio = true;
                break;
            }
        }
        if (tieneEspacio) {
            cout << "La palabra \"" << arreglo[i] << "\" contiene espacios\n";
        } else {
            cout << "La palabra \"" << arreglo[i] << "\" NO contiene espacios\n";
        }
    }
    return (0);
}

int identPuntuacion() {
    if (n == 0) {
        cout << "\nPrimero debes capturar o leer datos";
        return 0;
    }
    cout << "\nVerificando cada palabra si contiene signos de puntuacion:\n";
    for (i = 0; i < n; i++) {
        bool tienePuntuacion = false;
        for (char c : arreglo[i]) {
            if (ispunct(c)) {
                tienePuntuacion = true;
                break;
            }
        }
        if (tienePuntuacion) {
            cout << "La palabra \"" << arreglo[i] << "\" contiene signos de puntuacion\n";
        } else {
            cout << "La palabra \"" << arreglo[i] << "\" NO contiene signos de puntuacion\n";
        }
    }
    return (0);
}

int convertirMinuscula() {
    if (n == 0) {
        cout << "\nPrimero debes capturar o leer datos";
        return 0;
    }
    cout << "\nConvirtiendo cada palabra a minuscula:\n";
    cout << "Arreglo original: ";
    for (i = 0; i < n; i++) {
        cout << arreglo[i] << "  ";
    }
    cout << "\nArreglo convertido: ";
    for (i = 0; i < n; i++) {
        for (char &c : arreglo[i]) {
            c = tolower(c);
        }
        cout << arreglo[i] << "  ";
    }
    cout << "\n";
    return (0);
}

int convertirMayuscula() {
    if (n == 0) {
        cout << "\nPrimero debes capturar o leer datos";
        return 0;
    }
    cout << "\nConvirtiendo cada palabra a mayuscula:\n";
    cout << "Arreglo original: ";
    for (i = 0; i < n; i++) {
        cout << arreglo[i] << "  ";
    }
    cout << "\nArreglo convertido: ";
    for (i = 0; i < n; i++) {
        for (char &c : arreglo[i]) {
            c = toupper(c);
        }
        cout << arreglo[i] << "  ";
    }
    cout << "\n";
    return (0);
}


// ================= MAIN =================

int main() {
    for (repeticion = 0; repeticion == 0;) {
        menu();
        
        switch (opcion) {
        case (1):
            numeroDatos();
            capturaStrings();
            impresionStrings();
            break;
            
        case (2):
            leeArchivo();
            impresionStrings();
            break;
            
        case (3):
            impresionStrings();
            break;
            
        case (4):
            busquedaStrings();
            break;
            
        case (5):
            busquedaBin();
            break;
            
        case (6):
            burbuja();
            break;
            
        case (7):
            ordenamientoQuick();
            break;
            
        case (8):
            identAlfaNumerico();
            break;
            
        case (9):
            identLetra();
            break;
            
        case (10):
            identDigito();
            break;
            
        case (11):
            identMinuscula();
            break;
            
        case (12):
            identMayuscula();
            break;
            
        case (13):
            identEspacio();
            break;
            
        case (14):
            identPuntuacion();
            break;
            
        case (15):
            convertirMinuscula();
            break;
            
        case (16):
            convertirMayuscula();
            break;
            
        case (17):
            guardaArchivo();
            break;
            
        case (18):
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
    return (0);
}


// ================= MENU =================

int menu() {
    system("cls");
    cout << "\n Quirino Gonzalez Johann David";
    cout << "\n\tMenu - MANEJO DE STRINGS";
    cout << "\n1 - Captura de strings";
    cout << "\n2 - Lectura de archivo de strings";
    cout << "\n3 - Impresion de strings";
    cout << "\n4 - Busqueda de strings";
    cout << "\n5 - Busqueda binaria";
    cout << "\n6 - Metodo de ordenamiento Burbuja";
    cout << "\n7 - Metodo de ordenamiento QuickSort";
    cout << "\n8 - Identificar si el string es alfanumerico (isalnum)";
    cout << "\n9 - Identificar si el string es una letra (isalpha)";
    cout << "\n10 - Identificar si el string es un digito (isdigit)";
    cout << "\n11 - Identificar si el string es minuscula (islower)";
    cout << "\n12 - Identificar si el string es mayuscula (isupper)";
    cout << "\n13 - Identificar si el string tiene espacios (isspace)";
    cout << "\n14 - Identificar si el string tiene puntuacion (ispunct)";
    cout << "\n15 - Convertir todo a minuscula (tolower)";
    cout << "\n16 - Convertir todo a mayuscula (toupper)";
    cout << "\n17 - Guardar archivo";
    cout << "\n18 - Salir del menu";
    cout << "\nTeclee la opcion deseada : ";
    cin >> opcion;
    
    return (0);
}