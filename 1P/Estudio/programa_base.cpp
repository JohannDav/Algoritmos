//Autor: Quirino Gonzalez
//Modificar el programa para que:
// 1 - Declarar a las variables de forma global (todas las funciones tienen acceso a ellas)
// 2 - Declarar funciones de solicitud de datos (numeros, caracteres, string)
// 3 - Declarar funciones de impresion de datos (numeros, caracteres, string)
// 4 - Declarar funciones de manejo de datos (busqueda de numeros o caracteres)
// 5 - Separar el programa en 2 --- Uno que trabaje numeros y otro que trabaje caracteres
// 5 - En el programa que trabaja numeros - (Realizar operaciones con los numeros) 
// 6 - En el programa que trabaja con caracteres - Ejecutar una función del compilador para idetificar si es mayuscula, numero, etcetera.   
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
#include <time.h>     //Cabecera que permite contabilizar el tiempo de ejecución
using namespace std;
 

//Declaracion de variables globales
  int i=0;
  int opcion=0;
  int repeticion = 0;
  char caracteres [100];
  int numeros [100];
  string nombres [100];
 
  
//Declaracion variables y arreglos para el manejo de archivos  
  int arreglo [100];
  int n=0;
  int cn = 0;
  int guardacn=0;  
//Declaracion de prototipos
int numeroDatos ();
int capturaCaracteres ();  
int impresionCaracteres ();
int capturaNumeros ();
int impresionNumeros ();
int capturaNombres ();  
int menu ();
int impresionNumerosArchivo ();
 
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
int capturaCaracteres (){
  cout<<"\nTeclee "<<n<<" caracteres separados por un espacio : ";
  for (i=0; i<n; i++){
    cin>>caracteres [i];
  } 
  return (0);
}  
 
 
// lectura del archivo 
//  lee los numeros contenidos en el archivo y los copia en el arreglo "arreglo" 
//  Se dejan los numeros en un arreglo llamado "arreglo" para que las funciones puedan trabajar con ellos
int leeArchivo(){
	FILE *archivo1;                                     //Crea un apuntador de archivo, utilizando en la función fopen, el apuntador se le asigná el llamado al archivo
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
 
 
//Copia el contenido del arreglo en un archivo de salida
int guardaArchivo(){
	FILE *archivo2;                                         //Crea un apuntador de archivo, utilizando en la función fopen, el apuntador se le asigná el llamado al archivo
    //cout<<"\n\n Teclea el nombre del archivo de salida (sin espacios, ni caracteres especiales):   ";
	//cin>>nombreArchivoS;
	nombreArchivoS+= "miranda.txt";						 		// se agrega la extension ".txt"
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
	return (0);
}
 
 
//Impresion de caracteres
int impresionCaracteres (){
  cout<<"\nUsted tecleo "<<n<<" caracteres : ";
  for(i=0; i<n; i++){
    cout<<caracteres[i]<<"  ";
  } 
  return (0);
}  
 
 
//Captura de numeros
int capturaNumeros (){
  cout<<"\nTeclee "<<n<<" numeros separados por un espacio : ";
  for (i=0; i<n; i++){
    cin>>numeros[i];
  }
  return (0);
}
 
 
//Impresion de numeros
int impresionNumeros (){
  cout<<"\n\nNumeros : ";
  for(i=0; i<n; i++){
    cout<<numeros[i]<<"  ";
  }
  return (0);
}
 
 
//Caputa de nombre
int  capturaNombres (){
  cout<<"\nTeclee "<<n<<" nombres";
  for (i=0; i<n; i++){
    cout<<"\nTeclee el nombre "<<i+1<<" : ";
    fflush (stdin);
    getline(cin,nombres[i]);
    fflush (stdin);
  }
  return (0);
}
 
 
//Impresion de nombres 
int impresionNombres (){
  cout<<"\n\nNombres : ";
  for(i=0; i<n; i++){
    cout<<endl<<nombres[i];
  }
  return (0);
}
 

//Captura de numeros a procesar
int numeroDatos (){
  cout<<"\nTeclee la cantidad de datos a procesar : ";
  cin>>n;
  return (0);
}
 
 
//Impresion de numeros del archivo
int impresionNumerosArchivo (){
//int impresionNumeros (){
  cout<<"\n\nNumeros : ";
  for(i=0; i<n; i++){
    cout<<arreglo[i]<<"  ";
  }
  return (0);
}
 
int main (){
  //numeroDatos ();
  for (repeticion=0; repeticion==0;  ){
    menu ();
    switch (opcion){
      case (1):
        //capturaNumeros ();
        //impresionNumeros (); 
		leeArchivo();
        impresionNumerosArchivo ();
        break;
      case (2):
        capturaCaracteres ();
        impresionCaracteres ();
        break; 
      case (3):
        capturaNumeros ();
        impresionNumeros ();        
      case (4):
        capturaNombres ();
        impresionNombres ();
        break;
      case (5):
        cout<<"\nHasta luego";
        repeticion++;
        break;  
      default:
        cout<<"\nOpcion invalida";    
    }
    cout<<endl;
    system ("pause");
  }
  //Fin de programa
  cout<<endl;
  system("pause");
}  
 
 
int menu (){
  system ("cls");
  cout<<"\n\tMenu";
  cout<<"\n1 - Lectura de archivo de numeros";
  cout<<"\n2 - Captura de caracteres";
  cout<<"\n3 - Captura de numeros";
  cout<<"\n4 - Captura de nombres";
  cout<<"\n5 - Salir del menu";
  cout<<"\nTeclee la opcion deseada : ";
  cin>>opcion;
  return (0);
}