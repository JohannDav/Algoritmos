//Autor: Quirino Gonzalez Johann David

//Modificar el programa para que:
// 1 - Declarar a las variables de forma global (todas las funciones tienen acceso a ellas)
// 2 - Declarar funciones de solicitud de datos (numeros, caracteres, string)
// 3 - Declarar funciones de impresion de datos (numeros, caracteres, string)
// 4 - Declarar funciones de manejo de datos (busqueda de numeros o caracteres)
// 5 - Separar el programa en 2 --- Uno que trabaje numeros y otro que trabaje caracteres
// 5 - En el programa que trabaja numeros - (Realizar operaciones con los numeros) 
// 6 - En el programa que trabaja con caracteres - Ejecutar una funcion del compilador para idetificar si es mayuscula, numero, etcetera.   
// 7 - En el programa que trabaja con caracteres ejecutar funciones para identificar si es simbolo, numero, letra 
// 8 - Declaracion de funciones 
// 9 - Trabajar con un menu (switch y funciones)
// 10 - Trabajar con archivos 
// 11 - Agregar el metodo de busqueda
// 12 - Agregar el metodo de ordenamiento de burbuja

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>    //Cabecera o Biblioteca que permite el trabajar con archivos
#include <time.h>     //Cabecera que permite contabilizar el tiempo de ejecucion

using namespace std;

//Declaracion de variables globales
	int i = 0;
	int opcion = 0;
	int repeticion = 0;
	char caracteres[100];
	char caracterBuscar;
	int numeros[100];
	string nombres[100];

//Banderas
	int banderaEncontro = 0;


//Declaracion variables y arreglos para el manejo de archivos  
	int arreglo[100];
	int n = 0;
	int cn = 0;
	int guardacn = 0;

//Declaracion de prototipos
	int numeroDatos();
	int capturaCaracteres();
	int impresionCaracteres();
	int capturaNumeros();
	int impresionNumeros();
	int capturaNombres();
	int impresionNombres();
	int menu();
	int leeArchivo();
	int guardaArchivo();
	int impresionCaracteres();

//Declaracion de la estructura que permite leer datos del archivo de entrada y copiarlos a un arreglo
struct Entrada {
    int valor;
} entrada;

//Declaracion de la estructura que permite copiar los datos del arreglo y guardarlos en un archivo de salida
struct Salida {
    int valor;
} salida;

string nombreArchivoE;     //nombre del archivo de entrada
string nombreArchivoS;     //nombre del archivo de salida

//Captura de caracteres
int capturaCaracteres() {
    cout << "\nTeclee " << n << " caracteres separados por un espacio : ";
    for (i = 0; i < n; i++) {
        cin >> caracteres[i];
    }
    return (0);
}

// lectura del archivo 
// lee los numeros contenidos en el archivo y los copia en el arreglo "arreglo" 
// Se dejan los numeros en un arreglo llamado "arreglo" para que las funciones puedan trabajar con ellos
int leeArchivo() {
    FILE *archivo1; 
    cout << "\nTeclea el nombre del archivo de entrada (sin extension): ";
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
    while (fscanf(archivo1, "%i", &entrada.valor) != EOF) { 
        arreglo[cn] = entrada.valor; 
        cn++; 
    }

    cout << "\n\nSe ha generado el arreglo con los datos del archivo de entrada";
    cout << "\nLa cantidad de numeros contenidos en el arreglo son:  " << cn << "\n\n";
    n = cn;
    fclose(archivo1); 
    return (0);
}

//Copia el contenido del arreglo en un archivo de salida
int guardaArchivo() {
    FILE *archivo2; 
    nombreArchivoS = "miranda.txt"; 
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
        fprintf(archivo2, "%i\n", salida.valor);
        guardacn++;
    }

    cout << "\n\nTotal de numeros guardados en el segundo archivo son: " << guardacn;
    cout << "\n\n";
    fclose(archivo2);
    return (0);
}

//Impresion de caracteres
int impresionCaracteres() {
    cout << "\nUsted tecleo " << n << " caracteres : ";
    for (i = 0; i < n; i++) {
        cout << caracteres[i] << "  ";
    }
    return (0);
}


int busquedaCaracteres (){
	cout<<"\nteclee el caracter a buscar : ";
	cin>>caracterBuscar;
	
	//Busqueda del caracter
	for (i = 0; i < n; i++){
		if (caracterBuscar == caracteres [i]){
			cout<<"\nCaracter encontrado en la posicion: " <<i + 1;
			banderaEncontro = 1;
			}
		}
		
	if (banderaEncontro == 0){
		cout << "\Caracter no encontrado en el arreglo ";
		
	}
	
	return (0);
}


int main() {
    // Primera linea que sale en pantalla
    cout << "Quirino Gonzalez Johann David" << endl;
    system("pause");

    for (repeticion = 0; repeticion == 0; ) {
        menu();
        switch (opcion) {
        	
        	case (1):
                numeroDatos();
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
    return 0;
}

int menu() {
    system("cls");
    cout <<"\nQuirino Gonzalez Johann David";
    cout << "\n\tMenu Principal";
    cout << "\n1 - Captura de caracteres";
    cout << "\n2 - Lectura de archivo de numeros";
    cout << "\n3 - Busqueda caracteres";
    cout << "\n4 - Salir del menu";
    cout << "\nTeclee la opcion deseada : ";
    cin >> opcion;
    return (0);
}