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
int l = 0;  // Variable para impresion de pasadas
int opcion = 0;
int repeticion = 0;
char caracterBuscar;
char aux;
char numMayor;  // Variable para flotacion


//Banderas
int banderaEncontro = 0;

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
int impresionNumerosArchivo();
int leeArchivo();
int guardaArchivo();
int busquedaCaracteres();
int burbuja();
int flotacion();
int shell();
void ordenamientoQuick();
void quickSort (char arreglo[], int limite_izq, int limite_der);
void busquedaBin();
int busquedaBinaria();
int identAlfaNumerico();  // Este se mantiene


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


// ================= Busqueda de caracteres =================

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


// ================= Busqueda Binaria =================

void busquedaBin(){
	cout<<"\nTeclee el caracter a buscar en el arreglo :   ";
	cin>>buscar;
	busquedaBinaria();
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


// ================= Metodo burbuja =================

int burbuja () {
	impresionCaracteres ();
	t_ini = clock();
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
	t_fin = clock();
	impresionCaracteres ();

	cout<<"\n\n Tiempo de ordenamiento por el metodo de Burbuja :  ";
	secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
	printf("%.16g milisegundos", secs * 1000.0);
	cout<<"\n\n";

	return (0);
}


// ================= Metodo Flotacion =================

int flotacion (){
	impresionCaracteres ();
	t_ini = clock();
	
	for (i=0; i < n-1; i++){ 
    	//Intercambio
    	for (j=0; j < n-1; j++){
        	if (arreglo[j] > arreglo[j+1]) {
            	numMayor = arreglo[j];
            	arreglo[j] = arreglo[j + 1];
            	arreglo[j + 1] = numMayor;
        	}      
    	}	
    	cout<<"\nPasada "<<i+1<<" observe los intercambios ";
		impresionCaracteres ();   
	}
	
	t_fin = clock();
	impresionCaracteres ();
	
	cout<<"\n\n Tiempo de ordenamiento por el metodo de Flotacion :  ";
	secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
	printf("%.16g milisegundos", secs * 1000.0);
	cout<<"\n\n";
	
	return (0);
}


// ================= Metodo Shell =================

int shell(){
	int subarreglo=0;
	char temp;
	
	impresionCaracteres ();
	t_ini = clock();
	
    subarreglo = n/2;
    while (subarreglo > 0) {
        for (i=subarreglo; i < n; i++) {
            j = i;
            temp = arreglo[i];
            while ((j >= subarreglo) && (arreglo[j - subarreglo] > temp)) {
                arreglo[j] = arreglo[j - subarreglo];
                j = j - subarreglo;
            }
            arreglo[j] = temp;
			//Impresion de pasadas            
            cout<<endl<<endl;
            cout<<"\nInicia subarreglo en la posicion :  "<<subarreglo<< "   y contiene  "<<arreglo[subarreglo];
 	        cout<<"\nQue contiene el numero \n";
           for (l=0; l<n; l++){
       	        cout<<arreglo [l]<< "   ";
	        }
        }
        
	    //Impresion de pasada por pasada
		cout<<"\nInicia subarreglo en la posicion :  "<<subarreglo<< "   y contiene  "<<arreglo[subarreglo];
		cout<<"\nQue contiene el numero \n";
    	for (l=0; l<n; l++){
    		cout<<arreglo [l]<< "   ";
		}		
        subarreglo /= 2;
    }
    cout<<endl;
	
	t_fin = clock();
	impresionCaracteres ();
	
	cout<<"\n\n Tiempo de ordenamiento por el metodo de Shell :  ";
	secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
	printf("%.16g milisegundos", secs * 1000.0);
	cout<<"\n\n";
	
    return (0);
}


// ================= Metodo QuickSort =================

void ordenamientoQuick() {
	impresionCaracteres ();
	quickSort (arreglo, 0, n-1);
	cout << endl;
	cout << endl;
	cout << "\n" << endl;
	impresionCaracteres ();
}

void quickSort (char arreglo[], int limite_izq, int limite_der){
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


// ================= Funcion de verificacion de caracteres (solo alfanumerico) =================

int identAlfaNumerico() {
	cout << "\nVerificando caracter por caracter si es alfanumerico:\n";
	for (i = 0; i < n; i++) {
		if ((arreglo[i] >= 'A' && arreglo[i] <= 'Z') || (arreglo[i] >= 'a' && arreglo[i] <= 'z') || (arreglo[i] >= '0' && arreglo[i] <= '9')) {
			cout << "El caracter " << arreglo[i] << " es alfanumerico\n";
		} else {
			cout << "El caracter " << arreglo[i] << " es un simbolo\n";
		}
	}
	return (0);
}


// ================= MAIN =================

int main() {

	for (repeticion = 0; repeticion == 0;) {

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
			impresionCaracteres();
			break;

		case (4): //Secuencial
			busquedaCaracteres();
			break;

		case (5):		//Busqueda binaria
			impresionCaracteres();
			busquedaBin();
			break;

		case (6):		//Burbuja
			burbuja();
			break;
			
		case (7):		//Flotacion
			flotacion();
			break;
		
		case (8):		//Shell
			shell();
			break;

		case (9):		//QuickSort
			t_ini = clock();
			ordenamientoQuick();
			t_fin = clock();

			cout<<"\n\n Tiempo de ordenamiento por el metodo de QuickSort :  ";
			secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
			printf("%.16g milisegundos", secs * 1000.0);
			cout<<"\n\n";
			break;

		case (10):      // Identificador alfanumerico (se mantiene)
			identAlfaNumerico();
			break;

		case (11):
			guardaArchivo();
			break;

		case (12):
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
	cout << "\n2 - Lectura de archivo caracteres";
	cout << "\n3 - Impresion de caracteres";
	cout << "\n4 - Busqueda Secuencial";
	cout << "\n5 - Busqueda Binaria";
	cout << "\n6 - Metodo de ordenamiento Burbuja";
	cout << "\n7 - Metodo de ordenamiento Flotacion";
	cout << "\n8 - Metodo de ordenamiento Shell";
	cout << "\n9 - Metodo de ordenamiento QuickSort";
	cout << "\n10 - Identificar si el caracter es alfanumerico";
	cout << "\n11 - Guardar archivo";
	cout << "\n12 - Salir del menu";
	cout << "\nTeclee la opcion deseada : ";
	cin >> opcion;

	return (0);
}