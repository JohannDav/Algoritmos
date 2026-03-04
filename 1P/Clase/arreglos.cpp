//Manejo de arreglos
// Autor: Quirino David
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;
 
int main (){
	//Declaracion de variables
	int i=0;
	char caracteres [5] = {' '};
	int numeros [5] = {0};
	string nombres [3] = {" "}; 
	
	//Captura de caracteres
	cout<<"\nTeclee cinco caracteres separados por un espacio : ";
	for (i=0; i<5; i++){
		cin>>caracteres [i];
	}
	
	//Captura de numeros
	cout<<"\nTeclee cinco numeros separados por un espacio : ";
	for (i=0; i<5; i++){
		cin>>numeros[i];
	}
	
	//Captura de nombres
	cout<<"\nTeclee tres nombres";
	for (i=0; i<3; i++){
		cout<<"\nTeclee el nombre "<<i+1<<" : ";
		fflush (stdin);
		getline(cin,nombres[i]);
		fflush (stdin);
	}
	
	//Impresion de caracteres
	cout<<"\nUsted tecleo";
	cout<<"\n\nCaracteres : ";
	for(i=0; i<5; i++){
		cout<<caracteres[i]<<"  ";
	}
	
	//Impresion de numeros
	cout<<"\n\nNumeros : ";
	for(i=0; i<5; i++){
		cout<<numeros[i]<<"  ";
	}
	
	//Impresion de nombres
	cout<<"\n\nNombres : ";
	for(i=0; i<3; i++){
		cout<<endl<<nombres[i];
	}
	
	
	cout<<endl;
	system("pause");
}