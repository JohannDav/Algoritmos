//Impresion de caracteress
int impresionCaracteres (){
  cout<<"\nContenido del arreglo \n";
  for(i=0; i<n; i++){
    cout<<arreglo[i]<<"  ";
  } 
  return (0);
}


int capturaCaracteres (){
	cout<<"\nTeclee la cantidad de caracteres a capturar : ";
	cin>>n;
	cout<<"\nTeclee "<<n<<" caracteres : ";
	for (i=0; i<n; i++){
		cin>>arreglo[i];
	}
	return (0);
}


//Llama a la función de quickSort
void ordenamientoQuick() {
    quickSort (arreglo, 0, n-1);             //Se requiere el prototipado de la funcion porque esta despues de la funcion que la llamó
} 

void quickSort (char arreglo[], char limite_izq, char limite_der){
	
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

int main (){
  //caracteresDatos ();
  for (repeticion=0; repeticion==0;  ){
    menu ();
    switch (opcion){
      case (1):
        capturaCaracteres ();
        impresionCaracteres ();
        break; 
      case (2):
		leeArchivo();
        impresionCaracteres();
        break;
      case (3):
        busquedaCaracteres();
        break;  
      case (4):
      	impresionCaracteres();
      	t_ini = clock(); 
        burbuja ();
        // guarda el tiempo de finalización que marca el reloj despues de ordenar
    	t_fin = clock();					   
    	// Imprime el tiempo que se tardo el metodo en ordenar los datos
    	cout<<"\n\n Tiempo de ordenamiento por el metodo de Burbuja :  ";
    	secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;    // determina los milisegundo utilizados
    	printf("%.16g milisegundos", secs * 1000.0);                // imprime el tiempo utilizado
    	cout<<"\n\n";  
        break;   
	  case (5):
	  	impresionCaracteres();
	  	t_ini = clock(); 
	  	ordenamientoQuick( );
	  	// guarda el tiempo de finalización que marca el reloj despues de ordenar
    	t_fin = clock();					   
    	// Imprime el tiempo que se tardo el metodo en ordenar los datos
    	cout<<"\n\n Tiempo de ordenamiento por el metodo de Burbuja :  ";
    	secs = (double)(t_fin - t_ini) / (double)CLOCKS_PER_SEC;    // determina los milisegundo utilizados
    	printf("%.16g milisegundos", secs * 1000.0);                // imprime el tiempo utilizado
    	cout<<"\n\n";  
		impresionCaracteres(); 
		break; 		       
	  case (6):
	  	guardaArchivo ();
		break;        
      case (7):
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
  cout<<"\nMiranda Chavez";
  cout<<"\n\tMenu";
  cout<<"\n1 - Captura de caracteres";
  cout<<"\n2 - Lectura de archivo de caracteres";
  cout<<"\n3 - Busqueda caracteres ";
  cout<<"\n4 - Metodo de ordenamiento Burbuja";
  cout<<"\n5 - Metodo de ordenamiento QuickSort";
  cout<<"\n6 - Guardar archivo ";
  cout<<"\n7 - Salir del menu";
  cout<<"\nTeclee la opcion deseada : ";
  cin>>opcion;
  return (0);
}}