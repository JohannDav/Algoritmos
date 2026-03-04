//Autor: Quirino González Johann David 
//Búsqueda Lineal

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

main (){
		//int arreglo [5], i = 0, contador = 0, numBuscar = 0, bandera = 0;
	int i = 0, contador = 0, bandera = 0;
	char carBuscar;
	
		//Captura de los datos en el arreglo
		cout << "\nTeclee 5 numeros, los cuales se guardaran en un arreglo"<<endl;
		for(int i = 0; i < 5; i ++){
			contador ++;
			cout << "\nTeclee el numero " << contador << " : ";
			cin >> arreglo[i];
		}
	
		//Imprimir los datos capturados
		cout << "\nLos datos almacenados en el arreglo son: "<<endl;
		for(int i = 0; i < 5; i ++){
			cout<<arreglo[i]<<" ";
		}
		cout << endl;
	
		//Captura el numero a buscar
		cout << "\nTeclee el numero a buscar ";
		cin >> numBuscar ;
	
		//Busqueda si el numero se encuentra dentro del arreglo
		for(i = 0; i <5; i ++){
			if(numBuscar == arreglo[i]){
				cout << "\nEl numero "<<numBuscar<<" se encontro en el arreglo en la localidad "<< i << "\n";
				i = 5;
				bandera = 1;
			}
		}
		if(bandera == 0){
			cout<<"\nEl numero " <<numBuscar << " no se encontro en el arreglo" <<endl;
		
		}
	
	system("PAUSE");
}
