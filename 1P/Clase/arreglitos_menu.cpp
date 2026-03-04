//Autor: Miranda Chavez
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

//Declaracion de variables globales
    int i=0;
    int n=0;
    int opcion=0;
    int repeticion = 0;
    char caracteres [100];
    int numeros [100];
    string nombres [100];

//Declaracion de prototipos
int numeroDatos ();
int capturaCaracteres ();    
int impresionCaracteres ();
int capturaNumeros ();
int    impresionNumeros ();
int    capturaNombres ();    
int menu ();


//Captura de caracteres
int capturaCaracteres (){
    cout<<"\nTeclee "<<n<<" caracteres separados por un espacio : ";
    for (i=0; i<n; i++){
        cin>>caracteres [i];
    }
    return (0);
}    

//Impresion de caracteres
int impresionCaracteres (){
    cout<<"\nUsted tecleo "<<n<< " caracteres : ";
    for(i=0; i<n; i++){
        cout<<caracteres[i]<<" ";
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
        cout<<numeros[i]<<" ";
    }
    return (0);
}


//Caputa de nombre
int    capturaNombres (){
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
    cout<<"\nTeclee la cantidad de datos a procesar ";
    cin>>n;
    return (0);
}

int main (){
    numeroDatos ();
    for (repeticion=0; repeticion==0; ){
        menu ();
        switch (opcion){
            case (1):
                capturaCaracteres ();
                impresionCaracteres ();
                break;
            case (2):    
                capturaNumeros ();
                impresionNumeros ();
                break;
            case (3):
                capturaNombres ();
                impresionNombres ();
                break;
            case (4):
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
    cout<<"\n1 - Captura de caracteres";
    cout<<"\n2 - Captura de numeros";
    cout<<"\n3 - Captura de nombres";
    cout<<"\n4 - Salir del menu";
    cout<<"\nTeclee la opcion deseada : ";
    cin>>opcion;
    return (0);
}