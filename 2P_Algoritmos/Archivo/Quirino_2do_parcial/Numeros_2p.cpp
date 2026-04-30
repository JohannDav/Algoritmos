// Autor: Quirino González Johann David
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
using namespace std;

// ================= Declaracion de variables globales =================
int i = 0;
int j = 0;
int k = 0;
int l = 0;
int n = 0;
int cn = 0;
int guardacn = 0;
int banderaEncontro = 0;
int aux = 0;
int aux_num = 0;
int opcion = 0;
int repeticion = 0;
int numeroBuscar;
int arreglo[1000]; //Tamaño 1,000
int inferior = 0; 				//Busqueda binaria
int superior = n;				//Busqueda binaria
int buscar = 0; 				//Busqueda Binaria
int izq=0, der=0, pivote=0;		//Quick Sort
int temporal =0;				//Quick Sort
int limite_izq=0;				//Quick Sort
int limite_der=0;				//Quick Sort, limite_izq = 0, limite_der = n-1
clock_t t_ini, t_fin;			//Tiempo
double secs;					//Tiempo
string nombreArchivoE;
string nombreArchivoS;

// Variables adicionales para Shell y Flotacion
int subarreglo = 0;     // Para Shell sort
int temp = 0;           // Para Shell sort
int numMayor = 0;       // Para Flotacion

// ================= Declaracion de prototipos =================
int numeroDatos();
int capturaNumeros();
int impresionNumeros();
int menu();
int impresionNumerosArchivo();
void ordenamientoQuick(); 
void quickSort (int arreglo[], int limite_izq, int limite_der);
void busquedaBin();
int busquedaBinaria();
int shell();            // Prototipo de Shell sort
int flotacion();        // Prototipo de Flotacion

// Declaracion de la estructura que permite leer datos del archivo de entrada y copiarlos a un arreglo
struct Entrada {
    int valor;
} entrada;


// Declaracion de la estructura que permite copiar los datos del arreglo y guardarlos en un archivo de salida
struct Salida {
    int valor;
} salida;

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
    cout << endl;

    return (0);
}


// ================= Captura de cantidad =================

int numeroDatos() {
    cout << "\nTeclee la cantidad de datos a procesar : ";
    cin >> n;
    return (0);
}

// ================= Busqueda de numeros =================
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

//  ================= Busqueda Binaria =================
void busquedaBin(){
	cout<<"\nTeclee el numero a buscar en el arreglo :   ";
	cin>>buscar;
	busquedaBinaria();             //Se requiere el prototipado de la funcion porque esta despues de la funcion que la llamó
    if (arreglo[i] == buscar){
        cout<<"El valor  "<<buscar<<"  se encuentra en la posicion "<<i + 1 << "\n";
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
    impresionNumeros ();
    t_ini = clock();		//Inicia el conteo de tiempo
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
    t_fin = clock();		//Finaliza el conteo tiempo
    impresionNumeros ();	//Imprime los numeros
    
    //Inicia la impresion de tiempo
	cout<<"\n\n Tiempo de ordenamiento por el metodo de Burbuja :  ";	// Imprime el tiempo que se tardo el metodo en ordenar los datos
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;    // determina los milisegundo utilizados
    printf("%.16g milisegundos", secs * 1000.0);                // imprime el tiempo utilizado
    cout<<"\n\n";
    //Termina impresion de tiempo
    
    return (0);
}

// ================= Metodo Flotacion =================
int flotacion() {
    impresionNumeros();
    t_ini = clock();        //Inicia el conteo de tiempo
    
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
        impresionNumeros();   
    }
    
    t_fin = clock();        //Finaliza el conteo tiempo
    impresionNumeros();     //Imprime los numeros
    
    //Inicia la impresion de tiempo
    cout<<"\n\n Tiempo de ordenamiento por el metodo de Flotacion :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout<<"\n\n";
    //Termina impresion de tiempo
    
    return (0);
}

// ================= Metodo Shell =================
int shell() {
    impresionNumeros();
    t_ini = clock();        //Inicia el conteo de tiempo
    
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
    
    t_fin = clock();        //Finaliza el conteo tiempo
    cout<<endl;
    impresionNumeros();     //Imprime los numeros
    
    //Inicia la impresion de tiempo
    cout<<"\n\n Tiempo de ordenamiento por el metodo de Shell :  ";
    secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;
    printf("%.16g milisegundos", secs * 1000.0);
    cout<<"\n\n";
    //Termina impresion de tiempo
    
    return (0);
}

// ================= Metodo QuickSort =================
void ordenamientoQuick() {
	impresionNumeros ();
    quickSort (arreglo, 0, n-1);             //Se requiere el prototipado de la funcion porque esta despues de la funcion que la llamó
	cout << endl;
	cout << endl;
	cout << "\n" << endl;
	impresionNumeros ();	//Imprime los numeros
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
            
        case (3)://Secuencial
            busquedaNumeros();
            break;
            
		case (4): //Binaria
            impresionNumeros();
            busquedaBin();
			break;
		    
        case (5): //Burbuja
            burbuja();
            break;
        
        case (6): //Flotacion
            flotacion();
            break;
            
        case (7): //Shell
            shell();
            break;
            
        case (8): //Quick
        	t_ini = clock();		//Inicia el conteo de tiempo
            ordenamientoQuick();
            t_fin = clock();		//Finaliza el conteo tiempo    		
		    //Inicia la impresion de tiempo
			cout<<"\n\n Tiempo de ordenamiento por el metodo de QuickSort :  ";	// Imprime el tiempo que se tardo el metodo en ordenar los datos
    		secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;    // determina los milisegundo utilizados
    		printf("%.16g milisegundos", secs * 1000.0);                // imprime el tiempo utilizado
    		cout<<"\n\n";
    		//Termina impresion de tiempo
            break;
            
        case (9):
            guardaArchivo();
            break;
            
        case (10):
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
    cout << "\n3 - Busqueda Secuencial";
    cout << "\n4 - Busqueda Binaria";
    cout << "\n5 - Metodo de ordenamiento Burbuja";
    cout << "\n6 - Metodo de ordenamiento Flotacion"; 	
    cout << "\n7 - Metodo de ordenamiento Shell";		
    cout << "\n8 - Metodo de ordenamiento QuickSort";
    cout << "\n9 - Guardar archivo";
    cout << "\n10 - Salir del menu";
    cout << "\nTeclee la opcion deseada : ";
    cin >> opcion;

    return (0);
}