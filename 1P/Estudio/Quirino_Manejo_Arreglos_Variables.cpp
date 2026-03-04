//Manejo de arreglos VARIABLES
//Autor: Quirino Gonzalez Johann David

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

/*
	1 - Agregue la variable "n" ---- Cantidad
	2 - Solicite el valor de "n" --- Cantidad de datos a procesar
	3 - Declare los arreglos con tamaño "n" ---- Ejemplo char caracteres [n] = '  ';
	4 - Cambiar todos los for a que la comparación sea con "n" ---- Ejemplo  for (i=0;  i<n;  i++){ .....
*/
using namespace std;

int main() {

    int i = 0;
    int n = 0;
    
    cout<<"\nIngrese el numero de datos a procesar"<<endl;
    cin >> n;

    char caracteres[n] = { ' ' };
    int numeros[n] = { 0 };
    string nombres[n] = { " " };

    cout << "\nTeclee "<<n<<" caracteres separados por un espacio : ";

    for (i = 0; i < n; i++) {
        cin >> caracteres[i];
    }

    cout << "\nTeclee "<<n<<" numeros separados por un espacio : ";

    for (i = 0; i < n; i++) {
        cin >> numeros[i];
    }

    cout << "\nTeclee "<<n<<" nombres";

    for (i = 0; i < n; i++) {
        cout << "\nTeclee el nombre " << i + 1 << " : ";
        fflush(stdin);
        getline(cin, nombres[i]);
        fflush(stdin);
    }

    cout << "\nUsted tecleo";

    cout << "\n\nCaracteres : ";
    for (i = 0; i < n; i++) {
        cout << caracteres[i] << "  ";
    }

    cout << "\n\nNumeros : ";
    for (i = 0; i < n; i++) {
        cout << numeros[i] << "  ";
    }

    cout << "\n\nNombres : ";
    for (i = 0; i < n; i++) {
        cout << endl << nombres[i];
    }

    cout << endl;

    system("pause");
}