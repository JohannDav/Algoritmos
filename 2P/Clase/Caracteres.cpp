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
int opcion = 0;
int repeticion = 0;
char caracterBuscar;
char aux;


// variables del metodo Quick Sort
int izq=0, der=0, pivote=0;   
int temporal =0;
int limite_izq=0; 
int limite_der=0; // limite_izq = 0, limite_der = n-1


//Banderas
int banderaEncontro = 0;

// ================= Declaracion variables para manejo de archivos =================
char arreglo[100];
int n = 0;
int cn = 0;
int guardacn = 0;


// ================= Declaracion de prototipos =================
int cantidadCaracteres();           // Cambiado de "numeroDatos" a "cantidadCaracteres"
int capturaCaracteres();		
int impresionCaracteres();		
int menu();
int impresionCaracteresArchivo();   // Cambiado de "impresionNumerosArchivo" a "impresionCaracteresArchivo"
int burbuja();                      // Agregado metodo burbuja para ordenamiento


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

    return (0);
}


// ================= Lectura del archivo =================
// Lee los caracteres contenidos en el archivo y los copia en el arreglo "arreglo"
// Se dejan los caracteres en un arreglo llamado "arreglo" para que las funciones puedan trabajar con ellos

int leeArchivo() {

    FILE *archivo1;

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

    for (int i = 0; !feof(archivo1); i++) {
        fscanf(archivo1, "%c\n", &entrada.valor);
        arreglo[i] = entrada.valor;
        cn++;
    }

    //cn--;

    cout << "\n\nSe ha generado el arreglo con los datos del archivo de entrada";
    cout << "\nLa cantidad de caracteres contenidos en el arreglo son:  " << cn << "\n\n";

    n = cn;

    fclose(archivo1);

    return (0);
}


// ================= Guarda archivo =================

int guardaArchivo() {

    FILE *archivo2;

    cout << "\nTeclea el nombre del archivo de salida (sin espacio, ni caracteres especiales):   ";
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

    cout << "\n\nGuarda los caracteres contenidos en el arreglo en el archivo";

    guardacn = 0;

    for (i = 0; i < n; i++) {
        salida.valor = arreglo[i];
        fprintf(archivo2, "%c\n", salida.valor);
        guardacn++;
    }

    cout << "\n\nTotal de caracteres guardados en el segundo archivo son: " << guardacn;
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


// ================= Captura de caracteres a procesar =================

int cantidadCaracteres() {  // Cambiado de "numeroDatos" a "cantidadCaracteres"
    cout << "\nTeclee la cantidad de caracteres a procesar : ";
    cin >> n;
    return (0);
}


int busquedaCaracteres (){
	banderaEncontro = 0;
	impresionCaracteres ();
	cout<<"\nTeclee el caracter a buscar : ";
	cin>>caracterBuscar;
	for (i=0; i<n; i++){
	    if (caracterBuscar == arreglo [i]){
	        cout<<"\nCaracter encontrado en la posicion "<<i+1;
	        banderaEncontro = 1;
	    }
	}
	if (banderaEncontro == 0){
	    cout<<"\nCaracter no encontrado en el arreglo ";
	}
	return (0);		
}


int burbuja () {
    cout << "\n--- ORDENAMIENTO BURBUJA ---" << endl;
    cout << "Arreglo original: ";
    impresionCaracteres ();
    
    // Algoritmo de ordenamiento burbuja
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-i-1; j++){
            if (arreglo[j] > arreglo[j+1]) {
                aux = arreglo[j];
                arreglo[j] = arreglo[j+1];
                arreglo[j+1] = aux;
            }
        }
    }
    
    cout << "Arreglo ordenado: ";
    impresionCaracteres ();
    return (0);
}


// ================= Impresion de caracteres desde archivo =================

int impresionCaracteresArchivo() {
    FILE *archivo;
    char caracter;
    
    cout << "\nTeclea el nombre del archivo a leer: ";
    cin >> nombreArchivoE;
    nombreArchivoE += ".txt";
    
    archivo = fopen(nombreArchivoE.c_str(), "r");
    
    if (archivo == NULL) {
        cout << "\nNo se puede abrir el archivo " << nombreArchivoE.c_str() << endl;
        return (1);
    }
    
    cout << "\nContenido del archivo " << nombreArchivoE.c_str() << ":" << endl;
    
    while (fscanf(archivo, "%c\n", &caracter) != EOF) {
        cout << caracter << "  ";
    }
    
    cout << endl;
    fclose(archivo);
    
    return (0);
}


// ================= MENU =================

int menu() {
    system("cls");
    cout << "\n Quirino Gonzalez Johann David";
    cout << "\n\tMenu";
    cout << "\n1 - Captura de caracteres";
    cout << "\n2 - Lectura de archivo caracteres";
    cout << "\n3 - Busqueda caracteres";
    cout << "\n4 - Metodo de ordenamiento Burbuja";
    cout << "\n5 - Guardar archivo";
    cout << "\n6 - Impresion de caracteres desde archivo";
    cout << "\n7 - Salir del menu";
    cout << "\nTeclee la opcion deseada : ";
    cin >> opcion;

    return (0);
}


// ================= MAIN =================

int main() {

    for (repeticion = 0; repeticion == 0;) {

        menu();

        switch (opcion) {
        case (1):
            cantidadCaracteres();       // Se solicita la cantidad de caracteres
            capturaCaracteres();
            impresionCaracteres();
            break;
            
        case (2):
            leeArchivo();
            impresionCaracteres();
            break;
            
        case (3):
            busquedaCaracteres();
            break;
            
        case (4):
            burbuja();
            break;
        
        case (5):
            guardaArchivo();
            break;
            
        case (6):
            impresionCaracteresArchivo();
            break;
            
        case (7):
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
    return (0);
}