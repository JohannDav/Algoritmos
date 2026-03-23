//Descripción:  Ordenamiento por el metodo Quick Sort

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
using namespace std;

//Se generan variables globales para evitar el paso de parametros o argumentos entre las funciones
int i=0, j=0, k=0, l=0;
int n=0;
int cn=0;                   //Numero de datos leidos y a ordenar
int temp = 0;
int aux = 0;
int arreglo[1000];         //maximo se podran ordenar 1000000 de numeros


// variables del metodo Quick Sort
int izq=0, der=0, pivote=0;   
int temporal =0;
int limite_izq=0; 
int limite_der=0; // limite_izq = 0, limite_der = n-1

// Prototipado
void ordenamientoQuick(); 
void quickSort (int arreglo[], int limite_izq, int limite_der);


string nombrearchivo;      //nombre del archivo de entrada
string nombrearchivo2;     //nombre del archivo de salida


struct Entrada {           //declaracion de estructura que permiten leer y copiar los numeros en el arreglo "arreglo"
		int valor;
} entrada;

struct Salida {          //declaracion de estructura que permiten los numeros ordenados en el arreglo "arreglo" guardalos en el archivo de salida
		int valor;
} salida;


//Impresion de datos
int impresion (){
	for (k=0; k<n; k++){
		cout<<arreglo [k]<<"  ";
	} 
	cout<<endl;
	return (0);
}


// Funcion de lectura del archivo 
void leeArchivo(){
	FILE *archivo1;                                 //Crea un apuntador de archivo, utilizando en la función fopen, el apuntador se le asigná el llamado al archivo
    cout<<"\n Teclea el nombre del archivo de entrada (sin espacio, ni caracteres especiales):   ";
	cin>>nombrearchivo;
	nombrearchivo+= ".txt";						 	// Se le agrega al nombre del archivo la extension ".txt" 
	archivo1 = fopen(nombrearchivo.c_str(), "r");   // Se abre el archivo de modo lectura  
	if(archivo1== NULL ){                           //    el archivo contiene los numeros a ordenar
      	cout<<"\n No se puede abrir el archivo ";   //    si no se puede abrir el archivo termina con error el programa
		exit(1);
	}                                   
	else{
	    cout<<"\n Se abrio el archivo "<<nombrearchivo.c_str()<<"  correctamente";
    }
    	
    //Lee el archivo y copia los numeros contenidos en el archivo en el arreglo "arreglo"   	
    cn=0;
    for (int i=0; !feof(archivo1); i++) {          // Repite hasta que sea el fin del archivo
        fscanf (archivo1, "%i", &entrada.valor);   // Lee el numero contenido en el archivo y lo guarda en la estructura
        arreglo[i]=entrada.valor;                  // El numero contenido en la estructura lo pasa al arreglo "arreglo"
        cn++;                                      // suma 1 al contador de numeros leidos
	}
	cn--;	
	cout<<"\n\n Total de numeros contenidos en el archivo:  "<<cn<<"\n\n";
	n=cn;
	fclose(archivo1);                             //cierra el archivo de entrada
	impresion ();
	system ("pause");
}


//Llama a la función de quickSort
void ordenamientoQuick() {
    quickSort (arreglo, 0, n-1);             //Se requiere el prototipado de la funcion porque esta despues de la funcion que la llamó
} 

void quickSort (int arreglo[], int limite_izq, int limite_der){
	
    izq = limite_izq;
    der = limite_der;
    pivote = arreglo[(izq + der)/2];
    do{
        while (arreglo [izq] < pivote && izq < limite_der){
        	izq++;	
		}
        while (pivote < arreglo[der] && der > limite_izq){
        	der--;
		}
        if (izq <= der){
            temporal = arreglo[izq];
            arreglo[izq] = arreglo[der];
            arreglo[der] = temporal;
            izq++;
            der--;
        }
    }while(izq <= der);    
    
    if(limite_izq < der){
		quickSort(arreglo, limite_izq, der);
	}
    if(limite_der > izq){
		quickSort(arreglo, izq, limite_der);
	}
}

int main() {
    leeArchivo();  
         
    ordenamientoQuick( );                       //Llama al metodo de ordenamiento
    
    impresion ();

}