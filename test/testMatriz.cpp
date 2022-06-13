
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

    cout << "\n********************************************************\n";

    // Trabajamos sobre una segunda matriz copia
    Matriz mCopia (matriz);

    cout << "Calculamos index: i=0, j=1" << endl;
    cout << "index: " << mCopia(0,1);

    cout << "\nmatriz == mCopia? => " << (matriz == mCopia) << endl;

    cout << "matriz: " << matriz << endl;
    cout << "matriz: " << mCopia << endl;

    cout << "eliminamos fila 1 y columna 1" << endl;
    mCopia.eliminar(1, 1);

    cout << "\nmatriz == mCopia? => " << (matriz == mCopia) << endl;

    cout << "matriz: " << matriz << endl;
    cout << "matriz: " << mCopia << endl;

    cout << "\n********************************************************\n";

    Matriz matrizMulti = matriz*mCopia;
    cout << "matriz resultado matriz*mCopia: " << matrizMulti << endl;

    cout << "\n********************************************************\n";
    cout << "nodo origen A tiene como unico sucesor nodo B? => " << matriz.hijoUnico(0,1) << endl;

    cout << "nodos que tienen como hijo unico al nodo B => " << matriz.hijoUnico(1) << endl;

    cout << "\n********************************************************\n";

    Matriz mPotencia(3);
    mPotencia(0, 1) = 1;
    mPotencia(1, 2) = 1;
    mPotencia(0, 2) = 1;
    mPotencia(1, 2) = 1;
    mPotencia(1, 0) = 1;
    mPotencia(2, 1) = 1;
    mPotencia(2, 0) = 1;

    cout << "Matriz potencia 1\n" << endl;
    mPotencia=mPotencia.obtenerPotencia(1);

    cout << "Matriz potencia 2\n" << endl;
    mPotencia=mPotencia.obtenerPotencia(2);

    cout << "Matriz potencia 3\n" << endl;
    mPotencia=mPotencia.obtenerPotencia(3);

}
