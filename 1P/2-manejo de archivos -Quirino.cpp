// Autor: Quirino González Johann David
//
//Descripción:  Abre un archivo con datos 
//              guarda los datos en un arreglo 
//              imprime contenido del arreglo
//              realiza una peque?a modificaci?n a los datos
//              guarda los datos en un segundo archivo


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>    //Cabecera o Biblioteca que permite el trabajar con archivos
#include <time.h>     //Cabecera que permite contabilizar el tiempo de ejecuci?n
#include <string>
using namespace std;


//Se generan variables globales para evitar el paso de parametros 
//   o argumentos entre los metodos o funciones
int i=0, j=0, k=0;
int n=0;
int cn=0;                   //Contabiliza el numero de datos leidos en el archivo 
int guardacn=0;
int temp;
int arreglo[1000]; 
clock_t t_ini, t_fin;
double secs;
string nombreArchivoE;     //nombre del archivo de entrada
string nombreArchivoS;     //nombre del archivo de salida
int continuar = 0;
int bandera = 0;

//Declaracion de la estructura que permite leer datos del archivo de entrada y copiarlos a un arreglo
struct Entrada {           
	int valor;
} entrada;

//Declaracion de la estructura que permite copiar los datos del arreglo y guardarlos en un archivo de salida
struct Salida {          
	int valor;
} salida;

// Prototipo o definici?n de los metodos o funciones
int leeArchivo();
int imprimieArreglo();
int modificaArreglo();
int guardaArchivo();


// lectura del archivo 
//  lee los numeros contenidos en el archivo y los copia en el arreglo "arreglo" 
//  Se dejan los numeros en un arreglo llamado "arreglo" para que las funciones puedan trabajar con ellos
int leeArchivo(){
	FILE *archivo1;                                     //Crea un apuntador de archivo, utilizando en la funci?n fopen, el apuntador se le asign? el llamado al archivo
    cout<<"\nTeclea el nombre del archivo de entrada (sin espacio, ni caracteres especiales):   ";
	cin>>nombreArchivoE;
	nombreArchivoE+= ".txt";						 	// Se le agrega al nombre del archivo la extension ".txt" 
	archivo1 = fopen(nombreArchivoE.c_str(), "r");      // Se abre el archivo de modo lectura  
	if(archivo1== NULL ){                       
	    cout<<"\nNo se puede abrir el archivo "; 
	    exit (1);
	}                                   
	else{
	  	cout<<"\nSe abrio correctamente el archivo "<<nombreArchivoE.c_str();
    }
    	
    //Lee los datos del archivo y copia los numeros contenidos en el archivo en el arreglo "arreglo"   	
    cn=0;
    for (int i=0; !feof(archivo1); i++) {            // Repite hasta que sea el fin del archivo
        fscanf (archivo1, "%i", &entrada.valor);     // Lee el numero contenido en el archivo y lo guarda en la estructura
        arreglo[i]=entrada.valor;                    // El numero contenido en la estructura lo pasa al arreglo "arreglo"
        cn++;                                        // suma 1 al contador de numeros leidos
	}
	cn--;
	cout<<"\n\nSe ha generado el arreglo con los datos del archivo de entrada";	
	cout<<"\nLa cantidad de numeros contenidos en el arreglo son:  "<<cn<<"\n\n";
	n=cn;
	fclose(archivo1);                             //cierra el archivo de entrada
	return(0);
}

//Imprimir los datos del arreglo
//  Los datos son los que se copiaron del archivo 
int imprimeArreglo(){
	cout<<"\n\nDatos en el arreglo\n";
	for (i=0; i<n; i++){
		cout<<arreglo[i]<<"  ";
	}
	cout<<"\n";
	return(0);
}


//Modifica los datos contenidos en el arreglo
int modificaArreglo(){
	for (i=0; i<n; i++){
		arreglo[i] = arreglo [i] * 2;
	}
	cout<<"\nSe multiplican los dato por 2";
}


//Copia el contenido del arreglo en un archivo de salida
int guardaArchivo(){
	FILE *archivo2;                                         //Crea un apuntador de archivo, utilizando en la funci?n fopen, el apuntador se le asign? el llamado al archivo
    cout<<"\n\n Teclea el nombre del archivo de salida (sin espacios, ni caracteres especiales):   ";
	cin>>nombreArchivoS;
	nombreArchivoS+= ".txt";						 		// se agrega la extension ".txt"
	archivo2 = fopen(nombreArchivoS.c_str(), "w");		    // se abre el archivo de modo escritura 
	if(archivo2== NULL ){
		cout<<"\nNo se puede abrir el archivo ";
		exit(1);
    }
	else{
		cout<<"\nSe abrio el archivo  "<<nombreArchivoS.c_str()<<"  correctamente\n";
    }

    cout<<"\n\nGuarda los numeros contenidos en el arreglo en el archivo";
    guardacn=0;
    for (i=0; i<n; i++) {
        salida.valor=arreglo[i];
        fprintf(archivo2, "%i\n", salida.valor);
        guardacn++;
    }
    
    cout<<"\n\nTotal de numeros guardados en el segundo archivo son: "<<guardacn;
    cout<<"\n\n";
	fclose(archivo2);
}


//Funcion main ()
int main() {
    leeArchivo ();         // lee y copia en una arreglo los numeros contenidos en el archivo de entrada
    imprimeArreglo();  
    modificaArreglo();     //realiza una operacion sencilla con los datos del arreglo
    imprimeArreglo();
    guardaArchivo();
    system ("pause");
}