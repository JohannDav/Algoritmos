#include <iostream>
#include <locale.h>
#include <vector>
#include <cmath>

using namespace std;

int intentosFallidos = 0;   // Conteo de intentos inválidos
int solucionesTotales = 0;  // Conteo total de soluciones encontradas
int solucionesMostradas = 0; // Soluciones que ya se mostraron

int limiteMostrar = 0;      // Número máximo de soluciones a mostrar
bool mostrarTodo = true;    // Bandera para saber si se deben mostrar todas

// Verifica si se puede colocar una reina en (fila, columna)
bool esPosicionSegura(const vector<int>& reinasPorFila, int fila, int columna) {
    for (int i = 0; i < fila; ++i) {
        if (reinasPorFila[i] == columna ||
            abs(reinasPorFila[i] - columna) == abs(i - fila)) {
            return false;
        }
    }
    return true;
}

void mostrarEstadisticas (){
    cout << "\n>> Estadísticas del proceso <<\n";
    cout << "Soluciones encontradas: " << solucionesTotales << endl;
    cout << "Intentos fallidos: " << intentosFallidos << endl;
    cout << "Costo computacional (intentos + soluciones): "
         << intentosFallidos + solucionesTotales << endl;
    return;

}

// Imprime visualmente el tablero con las posiciones de las reinas
void imprimirTablero(const vector<int>& reinasPorFila, int N) {
    cout << "\nSolucion #" << solucionesTotales << ":\n";
    cout << "   ";
    for (int c = 0; c < N; ++c) cout << c << " ";
    cout << "\n  +";
    for (int c = 0; c < N; ++c) cout << "--";
    cout << "+\n";

    for (int i = 0; i < N; ++i) {
        cout << i << " | ";
        for (int j = 0; j < N; ++j) {
            cout << (reinasPorFila[i] == j ? "Q " : ". ");
        }
        cout << "|\n";
    }

    cout << "  +";
    for (int c = 0; c < N; ++c) cout << "--";
    cout << "+\n";
}

// Algoritmo de backtracking que busca todas las soluciones
void colocarReinas(vector<int>& reinasPorFila, int fila, int N) {
    if (fila == N) {
        solucionesTotales++;

        if (mostrarTodo || solucionesMostradas < limiteMostrar) {
            imprimirTablero(reinasPorFila, N);
            solucionesMostradas++;
        }

        return;
    }
    if (solucionesMostradas == limiteMostrar){
        mostrarEstadisticas();
    }

    for (int col = 0; col < N; ++col) {
        if (esPosicionSegura(reinasPorFila, fila, col)) {
            reinasPorFila[fila] = col;
            colocarReinas(reinasPorFila, fila + 1, N);
            reinasPorFila[fila] = -1; // backtrack
        } else {
            intentosFallidos++;
        }
    }
}

// Función principal
int main() {
	setlocale (LC_ALL, "spanish");	
    int N;
    cout << "Problema de las N Reinas\n";
    cout << "Ingrese el tamaño del tablero (N >= 4): ";
    cin >> N;

    if (N < 4) {
        cout << "No existen soluciones para tableros menores a 4x4\n";
        return 0;
    }

    cout << "\nDesea mostrar soluciones encontradas:\n";
    cout << "1. Mostrar TODAS\n";
    cout << "2. Mostrar UNA cantidad específica\n";
    cout << "3. NO mostrar ninguna (solo estadísticas)\n";
    int opcion;
    cin >> opcion;

    switch (opcion) {
        case 1:
            mostrarTodo = true;
            break;
        case 2:
            mostrarTodo = false;
            cout << "Ingrese el numero de soluciones a mostrar: ";
            cin >> limiteMostrar;
            break;
        case 3:
            mostrarTodo = false;
            limiteMostrar = 0;
            break;
        default:
            cout << "Opción no valida. Se mostraran todas las soluciones\n";
            mostrarTodo = true;
    }

    vector<int> reinasPorFila(N, -1);
    colocarReinas(reinasPorFila, 0, N);
    mostrarEstadisticas();


    return 0;
}
/*
Los algoritmos hibridos se generan con objetivo de efientizar el tiempo
cuando dse detecta que esta pasando o aimenrando e
El algoritmo al tardar se cambia a insercion, etc
Una cubeta, una canasta es una cola o pila dentro del SO

puedes reenviarme todas las presentaciones que mandaron de probabildad? esq nd mas me aparecen 2 y en estan en desorden pipipi
*/