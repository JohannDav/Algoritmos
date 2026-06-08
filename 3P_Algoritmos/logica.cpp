// Autor: Quirino González Johann David
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <cmath>
using namespace std;

//Variables globales
int i = 0, j = 0, k = 0, aux1 = 0, aux2 = 0, opcion = 0;
int op = 0;
int repeticion;
float cambio = 0;
float convertido = 0;

float cateto1, cateto2, hipotenusa;
float base, altura; 			//Rectangulo asteriscos
// ================= Declaracion de prototipos =================
int menu();
int divisas ();

int pitagoras();
int rectanguloasteriscos();
int tablasmultiplicar();

// ================= Declaracion de Funciones =================

int divisas (){
	
	for (i = 0; i == 0;){
		int op = 0;
		float cambio = 0;
		float convertido = 0;
		int salir = 0;
		
		cout << "\n=== CONVERSOR DE DIVISAS ===" << endl;
		cout << "Seleccione el tipo de cambio que desea calcular" << endl;
		cout << "1 - Peso a dolar" << endl;
		cout << "2 - Dolar a peso" << endl;
		cout << "3 - Peso a Euro" << endl;
		cout << "4 - Euro a peso" << endl;
		cout << "5 - Salir del conversor" << endl;
		cout << "Opcion: ";
		cin >> op;
		
		switch(op){
			case (1):
				cout << "Ingrese la cantidad de pesos que tiene: " << endl;
				cin >> cambio;
				convertido = cambio * 0.058;  // Tipo de cambio: 1 peso = 0.058 dolares (aproximado)
				cout << "La cantidad de " << cambio << " pesos equivale a: " << convertido << " dolares" << endl;
			break;
			
			case (2):
				cout << "Ingrese la cantidad de dolares que tiene: " << endl;
				cin >> cambio;
				convertido = cambio * 17.29;  
				cout << "La cantidad de " << cambio << " dolares equivale a: " << convertido << " pesos" << endl;
			break;	
			
			case (3):
				cout << "Ingrese la cantidad de pesos que tiene: " << endl;
				cin >> cambio;
				convertido = cambio * 0.054;  
				cout << "La cantidad de " << cambio << " pesos equivale a: " << convertido << " euros" << endl;
			break;
			
			case (4):
				cout << "Ingrese la cantidad de euros que tiene: " << endl;
				cin >> cambio;
				convertido = cambio * 18.52; 
				cout << "La cantidad de " << cambio << " euros equivale a: " << convertido << " pesos" << endl;
			break;
			
			case (5):
				cout << "Saliendo del conversor de divisas..." << endl;
				salir = 1;
			break;
			
			default:
				cout << "Opcion no valida. Intente de nuevo." << endl;
			break;
		}
		
		if (salir == 1){
			break;
		}
		
		cout << "\n¿Desea realizar otra conversion? (1 = Si / 0 = No): ";
		cin >> salir;
		if (salir == 0){
			break;
		}
	}
	
	return (0);
}


int pitagoras(){
	int op = 0;
	float hipotenusa = 0;
	float cateto1 = 0;
	float cateto2 = 0;
	
	for(i = 0; i == 0;){
	cout << "\nIngrese la opcion a calcular";
	cout << "\n1 - Calcular hipotenusa";
    cout << "\n2 - Calcular un cateto";
    cout << "\n33 - Salir" << endl;
    cin >> op;
    switch(op){
    	case(1):
    		cout << "\nHa escogido calcular la hipotenusa";
    		cout << "\nIngrese el valor del primer cateto" << endl;
    		cin >> cateto1;
    		cout << "\nIngrese el valor del segundo cateto" << endl;
    		cin >> cateto2;
    		hipotenusa = sqrt((cateto1 * cateto1) + (cateto2 * cateto2));
    		cout << "\nLa hipotenusa tiene un valor de: " << hipotenusa;
    		cout << endl;
    		break;
    		
    	case(2):
    		
    		cout << "\nHa escogido calcular un cateto";
    		cout << "\nIngrese el valor del cateto conocido" << endl;
    		cin >> cateto1;
    		cout << "\nIngrese el valor de la hipotenusa" << endl;
    		cin >> hipotenusa;
    		cateto2 = sqrt((cateto1 * cateto1) + (hipotenusa * hipotenusa));
    		cout << "\nEl otro cateto tiene un valor de: " << cateto2;
    		cout << endl;
    		break;
    		
    	case(3):
    		cout << "Ha escogido la opcion de SALIR";
    		i = 1;
    		break;
    	default:
    		cout << "\nOpcion inválida";
    	}
		
	}
	
	return(0);
}

int rectanguloasteriscos() {
	int base = 0;
	int altura = 0;
	
	cout << "\nIngrese la base del rectangulo" << endl;
	cin >> base;
	
	cout << "\nIngrese la altura del rectangulo" << endl;
	cin >> altura;
	
	for(i = 0; i < altura; i ++){ //Numero de filas
		for(j = 0; j < base; j ++){
			cout << " *" ;
		}
		cout << endl;
	}
	
	return (0);
}

int tablasmultiplicar(){
	
	for(i = 1; i < 11; i ++){ //Esto es el numero de filas
		cout << " " << i << "";
		for(j = 2; j < 11; j ++){
			cout << " " << j * i << "";
		}
		cout << endl;
	}
	
	return(0);
}

// ============================== MAIN ==========================================
int main (){
    for (repeticion = 0; repeticion == 0;) {
        menu();
        
        switch (opcion) {
            case (1):  // Divisas
            	divisas ();             
                break;
            
            case (2):  // Conversion temperatura
                
                break;
            
            case (3):  // Teorema de pitagoras
                pitagoras();
                break;
            
            case (4):  // Rectangulo con asteriscos
                rectanguloasteriscos();
                break;
                
            case (5):  // Tablas de multiplicar
                tablasmultiplicar();
                break;
                
            case (6):  // 
                
                break;
            
            case (7):  // 
                
                break;
                
            case (8):  // 
            
                break;
                
            case (9):  // 
                
                break;
                
            case (10):  // Salir
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
    cout << "\n1 - Divisas ";
    cout << "\n2 - no Temperatura ";
    cout << "\n3 - Pitagoras ";
    cout << "\n4 - Rectangulo con asteriscos";
    cout << "\n5 - tablasmultiplicar";
    cout << "\n6 - F ";
    cout << "\n7 - F ";
    cout << "\n8 - F ";
    cout << "\n9 - F ";
    cout << "\n10 - Salir del menu";
    cout << "\nTeclee la opcion deseada : ";
    cin >> opcion;
    return (0);
}                                           