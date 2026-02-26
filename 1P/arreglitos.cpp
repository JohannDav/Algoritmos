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
    cout<<"\nUsted tecleo "<< n << " caracteres : ";
    for(i=0; i<n; i++){
        cout<<caracteres[i]<<" ";
    }
    return (0);
}    

//Captura de numeros
int capturaNumeros (){
    cout<<"\nTeclee 5 numeros separados por un espacio : ";
    for (i=0; i<5; i++){
        cin>>numeros[i];
    }
    return (0);
}

//Impresion de numeros
int impresionNumeros (){
    cout<<"\n\nNumeros : ";
    for(i=0; i<5; i++){
        cout<<numeros[i]<<" ";
    }
    return (0);
}


//Caputa de nombre
int    capturaNombres (){
    cout<<"\nTeclee 5 nombres";
    for (i=0; i<5; i++){
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
    for(i=0; i<5; i++){
        cout<<endl<<nombres[i];
    }
    return (0);
}


int main (){
    cout<<"\nTeclee la cantidad de datos a procesar ";
    cin>>n;
    capturaCaracteres ();
    impresionCaracteres ();
    capturaNumeros ();
    impresionNumeros ();
    capturaNombres ();
    impresionNombres ();

    //Fin de programa
    cout<<endl;
    system("pause");
}