
#include<iostream>

#include "matriz.h"

using namespace std;

/**
 * programa principal para pruebas unitarias con matrices
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]){
    Matriz matriz(5);

    // asigna valores a la matriz como si fuera el
    // diagrama sencillo A -> B -> C
    matriz(0, 1) = 1;
    matriz(1, 2) = 1;

    // se muestra por pantalla
    cout << matriz;

    // se eliminan la fila 1 y la columna 4
    matriz.eliminar(1, 4);

    // se vuelve a visualizar la matriz
    cout << matriz;
}
