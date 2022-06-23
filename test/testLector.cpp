#include<iostream>

#include "lector.h"

using namespace std;

/**
 * Programa principal para pruebas con la clase lector
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char * argv[]){
   // se crea objeto de la clase Lector para un archivo
   Lector lector("../../data/car.pro");

   // se muestra el diagrama generado
   Diagrama diag = lector.obtenerDiagrama();
   cout << diag;

   // se ordenan las variables de decision
   cout << "a agregar arcos de memoria: " << endl;
   diag.agregarArcosMemoria();

   // se muestra el diagrama tras agregar los arcos de memoria
   cout << "diagrama tras agregar arcos de memoria" << endl;
   cout << diag;
 }
