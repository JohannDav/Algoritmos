 #include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <limits>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>      // Para vectores auxiliares
#include <limits>      // Para numeric_limits

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
int yaOrdenados = 0;
int numeroBuscar;
float arreglo2[100];    // Arreglo auxiliar
clock_t t_ini, t_fin;           //Tiempo
double secs;                    //Tiempo
// Banderas
int hayDatos = 0;        // Bandera para validar si hay datos en el arreglo
int datosOrdenados = 0;  // Bandera para validar si los datos estan ordenados
using namespace std;
using namespace chrono;

const int RUN = 32;
int* arreglo = nullptr;
int tam = 0;
int opcional = 0;
int opcion = 0;
int repeticion = 0;
int menu();
bool archivoLeido = false;
bool archivoOrdenado = false;
bool archivoGrabado = false;
bool mensajeCambioOrden = false;
bool mensajeMerge = false;
bool mensajElnsertionsort = false;
bool mensajeTim = false;

int leerEntero() {
    int valor;
    while (true) {
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Ingrese un número entero: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

void insertionSort(int arr[], int left, int right, bool ascendente) {
    if (!mensajElnsertionsort) {
        cout << "Inicio ordenamiento con inserción " << right - left << " de tamaño del subarreglo\n";
        mensajElnsertionsort = true;
    }
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && ((ascendente && arr[j] > temp) || (!ascendente && arr[j] < temp))) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void merge(int arr[], int l, int m, int r, bool ascendente) {
    if (!mensajeMerge) {
        cout << "Inicio ordenamiento con Merge " << r - l << " tamaño de la división\n";
        mensajeMerge = true;
    }

    int len1 = m - l + 1, len2 = r - m;
    int* left = new int[len1];
    int* right = new int[len2];

    copy(arr + l, arr + m + 1, left);
    copy(arr + m + 1, arr + r + 1, right);

    int i = 0, j = 0, k = l;
    while (i < len1 && j < len2) {
        if ((ascendente && left[i] <= right[j]) || (!ascendente && left[i] >= right[j])) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < len1) arr[k++] = left[i++];
    while (j < len2) arr[k++] = right[j++];

    delete[] left;
    delete[] right;
}

void timSort(int arr[], int n, bool ascendente) {
    if (!mensajeTim) {
        cout << "Inicio ordenamiento con TimSort " << RUN << " de tamaño de run \n";
        mensajeTim = true;
    }

    auto inicio = high_resolution_clock::now();

    for (int i = 0; i < n; i += RUN)
        insertionSort(arr, i, min(i + RUN - 1, n - 1), ascendente);

    for (int size = RUN; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);
            if (mid < right) merge(arr, left, mid, right, ascendente);
        }
    }

    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << "Tiempo de ejecucion de TimSort: " << duracion.count() << " segundos\n";
}

void ordenarTimsort() {
    if (!archivoLeido) {
        cout << "Primero debe leer un archivo\n";
        return;
    }
    if (archivoGrabado) {
        cout << "Archivo ya fue grabado\n";
        return;
    }

    cout << "Seleccione el orden:\n1. Ascendente\n2. Descendente\nOpción: ";
    int opcionOrden = leerEntero();
    if (opcionOrden <= 0 || opcionOrden > 2) {
        cout << "Opción inválida\n";
        return;
    }

    bool asc = (opcionOrden == 1);

    if (opcional != opcionOrden && !mensajeCambioOrden) {
        cout << (asc ? "Cambiando a orden ascendente..." : "Cambiando a orden descendente...") << endl;
        mensajeCambioOrden = true;
    }

    if (opcional == opcionOrden && archivoOrdenado) {
        cout << "El arreglo ya ha sido ordenado en ese orden\n";
        return;
    }

    opcional = opcionOrden;
    cout << "Iniciando ordenamiento con Timsort de un arreglo de " << tam << " tamaño\n";
    timSort(arreglo, tam, asc);
    archivoOrdenado = true;
    cout << "Ordenamiento completado exitosamente\n";
    yaOrdenados = 1;
}

void leerArchivo() {
    if (archivoLeido) {
        cout << "El archivo ya ha sido leído\n";
        return;
    }

    string nombre;
    cout << "Ingrese el nombre del archivo sin extensión: ";
    cin >> ws;
    getline(cin, nombre);
    nombre += ".txt";

    ifstream archivo(nombre);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo\n";
        return;
    }

    int valor;
    tam = 0;
    while (archivo >> valor) tam++;

    if (tam == 0) {
        cout << "El archivo está vacío\n";
        archivo.close();
        return;
    }

    archivo.clear();
    archivo.seekg(0);

    delete[] arreglo;
    arreglo = new int[tam];
    for (int i = 0; i < tam; i++) archivo >> arreglo[i];

    archivo.close();
    archivoLeido = true;
    archivoOrdenado = false;
    archivoGrabado = false;

    cout << "Archivo leído correctamente. Total de valores: " << tam << endl;
    hayDatos = 1;
}

void mostrarArreglo() {
    if (!archivoLeido) {
        cout << "Primero debe leer un archivo\n";
        return;
    }
    if (archivoGrabado) {
        cout << "El archivo ya fue guardado";
        return;
    }
    cout << "¿Cuántos elementos desea mostrar? ";
    int elementos = leerEntero();
    cout << "Contenido del arreglo: ";
    for (int i = 0; i < elementos && i < tam; i++) cout << arreglo[i] << " ";
    cout << endl;
}

int mostrarTodo() {
    cout << "Contenido del arreglo: ";
    for (int i = 0; i < tam; i++) cout << arreglo[i] << " ";
    cout << endl;
    return (0);
}

void guardarArchivo() {
    if (!archivoLeido) {
        cout << "Primero debe leer un archivo\n";
        return;
    }
    if (archivoGrabado) {
        cout << "archivo ya grabado \n";
        return;
    }
    if (!archivoOrdenado) {
        cout << "El arreglo no esta ordenado";
        return;
    }

    string nombre;
    nombre = "CAMBIAR.txt";

    ofstream archivo(nombre);
    if (!archivo.is_open()) {
        cout << "No se pudo crear el archivo\n";
        return;
    }

    for (int i = 0; i < tam; i++) archivo << arreglo[i] << " ";
    archivo.close();
    archivoGrabado = true;

    cout << "Archivo guardado exitosamente como: " << nombre << endl;
}

bool salir() {
    if (!archivoLeido) {
        cout << "Debe leer un archivo antes de salir\n";
        return false;
    }
    if (!archivoGrabado) {
        cout << "Debe guardar el archivo antes de salir\n";
        return false;
    }
    delete[] arreglo;
    return true;
}

int mostrarPositivosNegativos() {
    for (int i = 0; i < tam; i++) {
        if (arreglo[i] < 0) {
            cout << "nEs un numero negativo: " << arreglo[i];
        } else {
            cout << "nEs un numero positivo: " << arreglo[i];
        }
    }
    return 0;
}

// ================= Busqueda Secuencial =================
int busquedaNumeros() {
    if (hayDatos == 0) {
        cout << "\n ERROR: No hay datos en el arreglo. Primero capture datos o lea un archivo. \n";
        return (0);
    }
    if(yaOrdenados == 0){
    	cout << "\n ERROR: Primero ordena \n";
        return (0);
	}
    banderaEncontro = 0;
    cout<<"\nTeclee el numero a buscar : ";
    cin>>numeroBuscar;
    for (i=0; i<tam; i++){
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

int impuestos(){
	for (i=0; i<tam; i++){
        if(arreglo [i] < 9451){
        	cout << "\nEl sueldo neto es de: " << arreglo [i];
        	cout << "\nNO PAGA IMPUESTOS" << endl;
        	cout << "\nSu sueldo neto es de: " << arreglo [i];
		}
		if((arreglo [i] >= 9452) && (arreglo [i] <= 9451)){
        	cout << "\nEl sueldo neto es de: " << arreglo [i];
        	cout << "\nPAGA UN 10%" << endl;
        	cout << "\nSu sueldo neto es de: " << (arreglo [i] * 0.10);
		}
    }
	
	
	return(0);
}

// ================= MAIN =================
int main() {
    system("chcp 65001 > nul");
    setlocale(LC_ALL, "es_MX.UTF-8");

    for (repeticion = 0; repeticion == 0;) {
        menu();
        switch (opcion) {
            case 1: 
				leerArchivo(); 
				break;
            case 2:
            	//Esto debe de mostrar todo
				mostrarTodo();
				break;
            case 3:
            	mostrarArreglo();                       	
				break;
            case 4: 
				busquedaNumeros();
				break;
            case 5: 
				ordenarTimsort();
				break;
            case 6: 
            	impuestos();
				break;
			case 7: 
				guardarArchivo();
				break;
			case 8: 
				cout << "\nHasta luego"; 
				repeticion++; 
				break;
				break;
            default: cout << "\nOpcion invalida";
        }
        if (repeticion) break;
        cout << endl;
        system("pause");
    }
    cout << endl;
    system("pause");
    return 0;
}

// ================= MENU PRINCIPAL =================
int menu() {
    system("cls");
    cout << "\n CAMBIAR";
    cout << "\n\tMenu";
    cout << "\n1 - Leer archivo";
    cout << "\n2 - Imprimir archivo";
    cout << "\n3 - Mostrar arreglo";
    cout << "\n4 - Busqueda Secuencial";
    cout << "\n5 - Ordenamiento TimSort";
    cout << "\n6 - Calculo de pago de impuestos";
    cout << "\n7 - Guardar archivo";	        
    cout << "\n8 - Salir";
    cout << "\nTeclee la opcion deseada : ";
    cin >> opcion;
    return 0;
}