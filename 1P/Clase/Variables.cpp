#include <string>
#include <fstream>
#include <time.h>
#include <locale.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int main(){
	double precio = 0.0;
	char inicial=' ';
	string nombre="";
	cout<<"Teclee el precio: ";
	cin>>precio;
	//cout<<"El precio es de: "<<precio;
	printf("El precio es de: %2.10f",precio);
	cout<<endl;
	cout<<"Teclee la inicial: ";
	fflush(stdin);
	cin>>inicial;
	fflush(stdin);
	cout<<"La inicial es "<<inicial;
	cout<<endl;
	cout<<"Teclee su nombre: ";
	fflush(stdin);
	cin>>nombre;
	fflush(stdin);
	cout<<"El nombre es "<<nombre;
	cout<<endl;
}