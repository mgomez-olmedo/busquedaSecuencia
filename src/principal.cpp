
#include<iostream>

#include "aStarSearch.h"
#include "lector.h"

using namespace std;

/**
 * Programa principal
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char * argv[]){
   // se crea objeto de la clase Lector para un archivo
   Lector lector("./data/car.pro");
   cout << "leida definicion del diagrama...." << endl;

   // se muestra el diagrama generado
   Diagrama diag = lector.obtenerDiagrama();

   // se crea objeto de la clase AStarSearch
   AStarSearch search(diag);
   cout << "creado objeto de la clase AStarSearch" << endl;

   // se muestra el objeto
   cout << search;

   // se inicia el proceso de busqueda
   search.buscar();
}
