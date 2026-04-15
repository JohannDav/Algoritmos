// Autor: Quirino González Johann David

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
int opcion = 0;
int repeticion = 0;
int numeroBuscar;
int aux;
int sumPar;
int sumImpar;

//Banderas
int banderaEncontro = 0;

// ================= Declaracion variables para manejo de archivos =================
int arreglo[100];
int n = 0; //Es la cantidad de datos que hay en el arreglo 
int cn = 0;
int guardacn = 0;


// ================= Declaracion de prototipos =================
int numeroDatos();
int capturaNumeros();
int impresionNumeros();
int menu();
int impresionNumerosArchivo();


// Declaracion de la estructura que permite leer datos del archivo de entrada y copiarlos a un arreglo
struct Entrada {
    int valor;
} entrada;


// Declaracion de la estructura que permite copiar los datos del arreglo y guardarlos en un archivo de salida
struct Salida {
    int valor;
} salida;


string nombreArchivoE;
string nombreArchivoS;


// ================= Captura de numeros =================

int capturaNumeros() {

    cout << "\nTeclee " << n << " numeros separados por un espacio : ";

    for (i = 0; i < n; i++) {
        cin >> arreglo[i];
    }

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
        exit(1);
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
    //cn--;

    cout << "\n\nSe ha generado el arreglo con los datos del archivo de entrada";
    cout << "\nLa cantidad de numeros contenidos en el arreglo son:  " << cn << "\n\n";

    n = cn;

    fclose(archivo1);

    return (0);
}


// ================= Guarda archivo =================

int guardaArchivo() {

    FILE *archivo2;

    nombreArchivoS += "Quirino.txt";

    archivo2 = fopen(nombreArchivoS.c_str(), "w");

    if (archivo2 == NULL) {
        cout << "\nNo se puede abrir el archivo ";
        exit(1);
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

    return (0);
}


// ================= Impresion de numeros PARES =================

int impresionNumerosPares() {

    cout << "\nPares del arreglo: \n ";

    for (i = 0; i < n; i++) { //Recorrer arreglo
    	if (arreglo[i]%2 == 0){
    		cout << arreglo[i] << "  ";
    		sumPar = sumPar + arreglo[i];
		}
    }
    cout << "\nLa sumatoria de los numeros pares es: " << sumPar;
    return (0);
}

// ================= Impresion de numeros IMPARES =================

int impresionNumerosImpares() {
	
    cout << "\nImpares del arreglo: \n ";
    for (i = 0; i < n; i++) {
    	if (arreglo[i]%2 != 0){
    		cout << arreglo[i] << "  ";
    		sumImpar = sumImpar + arreglo[i];
		}
    }
    cout << "\nLa sumatoria de los numeros Impares es: " << sumImpar;

    return (0);
}

// ================= Captura de cantidad =================

int numeroDatos() {
    cout << "\nTeclee la cantidad de datos a procesar : ";
    cin >> n;
    return (0);
}


int busquedaNumeros (){
    banderaEncontro = 0;
    impresionNumeros ();
    cout<<"\nTeclee el numero a buscar : ";
    cin>>numeroBuscar;
    for (i=0; i<n; i++){
        if (numeroBuscar == arreglo [i]){
            cout<<"\nNumero encontrado en la posicion "<<i+1;
            banderaEncontro = 1;
        }
    }
    if (banderaEncontro == 0){
        cout<<"\nNumero no encontrado en el arreglo ";
    }
    return (0);        
}


int burbuja () {
    impresionNumeros ();
    cout << endl;
    for (i=0; i<n-1; i++){
        for (j=i; j<n; j++){
            if (arreglo [i] > arreglo [j]) {
                aux = arreglo [i];
                arreglo[i] = arreglo [j];
                arreglo[j] = aux;
            }
        }
    }
    impresionNumeros ();
    return (0);
}


int identificacionNumero(){
	impresionNumeros ();
	impresionNumerosPares ();
	impresionNumerosImpares();
	
	return(0);
}
/*int identificacionSuma(){
	impresionNumeros ();
	cout << endl;
	for ()
	
} */


// ================= MAIN =================

int main() {

    for (repeticion = 0; repeticion == 0;) {

        menu();

        switch (opcion) {
        case (1):
            numeroDatos();
            capturaNumeros();
            impresionNumeros();
            break;
            
        case (2):
            leeArchivo();
            impresionNumeros();
            break;
            
        case (3):
            busquedaNumeros();
            break;
            
        case (4):
            burbuja();
            break;
        
        case (5):
            identificacionNumero();
            break;
        
        case (6):
            guardaArchivo();
            break;
            
        case (7):
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
    cout << "\n3 - Busqueda secuencial de numeros";
    cout << "\n4 - Metodo de ordenamiento Burbuja";
    cout << "\n5 - Identificacion y suma de numeros pares e impares contenidos en el arreglo";
    cout << "\n6 - Guardar archivo";
    cout << "\n7 - Salir del menu";
    cout << "\nTeclee la opcion deseada : ";
    cin >> opcion;

    return (0);
}