#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>    //Cabecera o Biblioteca que permite el trabajar con archivos
#include <time.h>     //Cabecera que permite contabilizar el tiempo de ejecución
#include <string>
using namespace std;

//variables abrir archivos
int i=0, j=0, k=0, l=0;
int n=0;
int cn=0;                   //Contabiliza el numero de datos leidos en el archivo 
int guardacn;
int buscar;
int arreglo[1000]; 
string nombreArchivoE;      //nombre del archivo de entrada
string nombreArchivoS;     //nombre del archivo de salida
//Declaracion de la estructura que permite leer el archivo de entrada y copiar los datos en el arreglo 
struct Entrada {           
	int valor;
} entrada;

//variables busqueda binaria
//  controlan localidades en el arreglo
int inferior=0; 
int superior=n;

// Prototipo o definición de los metodos o funciones
int leeArchivo();
int imprimirArreglo();

// Prototipado busqueda binaria
void busquedaBin();
int busquedaBinaria();


// -- Metodo de Busqueda Binaria -- //
void busquedaBin(){
	cout<<"\nTeclee el número a buscar en el arreglo :   ";
	cin>>buscar;
	busquedaBinaria();             //Se requiere el prototipado de la funcion porque esta despues de la funcion que la llamó
    if (arreglo[i] == buscar){
        cout<<"El valor  "<<buscar<<"  se encuentra en la posicion "<<i + 1;
    }
    else {
        cout<<"No se encontra el  valor  "<<buscar<<"  en el arreglo\n";
    }
} 


int busquedaBinaria(){
	inferior=0, superior=n;
    while (superior >= inferior){
        i = (inferior + superior) / 2;
        if (arreglo[i] == buscar){
             return i;
        }
        else {
            if (buscar < arreglo [i]){
                superior = i-1;
            }
            else{
                inferior = i+1;
            }
    	}
    }
    return (0);
}


// lectura del archivo 
//  lee los numeros contenidos en el archivo y los copia en el arreglo "arreglo" 
//  Se dejan los numeros en un arreglo llamado "arreglo" para que las funciones puedan trabajar con ellos
int leeArchivo(){
	FILE *archivo1;                                  //Crea un apuntador de archivo, utilizando en la función fopen, el apuntador se le asigná el llamado al archivo
    cout<<"\n Teclea el nombre del archivo de entrada (sin espacio, ni caracteres especiales):   ";
	cin>>nombreArchivoE;
	nombreArchivoE+= ".txt";						 	// Se le agrega al nombre del archivo la extension ".txt" 
	archivo1 = fopen(nombreArchivoE.c_str(), "r");   // Se abre el archivo de modo lectura  
	if(archivo1== NULL ){                       
	    cout<<"\n No se puede abrir el archivo "; 
	    exit (1);
	}                                   
	else{
	  	cout<<"\n Se abrio el archivo "<<nombreArchivoE.c_str()<<"  correctamente";
    }
    	
    //Lee el archivo y copia los numeros contenidos en el archivo en el arreglo "arreglo"   	
    cn=0;
    for (int i=0; !feof(archivo1); i++) {          // Repite hasta que sea el fin del archivo
        fscanf (archivo1, "%i", &entrada.valor);   // Lee el numero contenido en el archivo y lo guarda en la estructura
        arreglo[i]=entrada.valor;                    // El numero contenido en la estructura lo pasa al arreglo "arreglo"
        cn++;                                      // suma 1 al contador de numeros leidos
	}
	cn--;
	cout<<"\n\nSe ha generado el arreglo con los datos del archivo de entrada";	
	cout<<"\n\nLa cantidad de numeros contenidos en el arreglo son:  "<<cn<<"\n\n";
	n=cn;
	fclose(archivo1);                             //cierra el archivo de entrada
	return(0);
}


//Imprimir los datos del arreglo
//  Los datos son los que se copiaron del archivo 
int imprimirArreglo(){
	cout<<"\n\nDatos en el arreglo\n";
	for (l=0; l<n; l++){
		cout<<arreglo[l]<<"  ";
	}
	cout<<"\n\n";
	return(0);
}

int main (){
 	leeArchivo ();  
 	imprimirArreglo();
	cout<<"\nBusqueda Binaria\n";  
	busquedaBin();
	system ("pause");
		
}