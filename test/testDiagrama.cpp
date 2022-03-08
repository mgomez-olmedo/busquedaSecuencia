#include<iostream>

#include "lector.h"

using namespace std;

/**
 * Programa principal para realizar pruebas con la clase
 * diagrama
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char * argv[]){
   // se crea objeto de la clase Lector para un archivo
   Lector lector("./data/car.pro");

   // se muestra el diagrama generado
   Diagrama diag = lector.obtenerDiagrama();
   cout << diag;

   // se prueba el metodo de determinacion del orden topologico
   SecuenciaEnteros ordenDecisiones = diag.ordenDecisiones();
   cout << ordenDecisiones << endl;

   vector<SecuenciaEnteros> ordenParcial = diag.ordenParcialBorrado();
   for(int i=0; i < ordenParcial.size(); i++){
      cout << "etapa " << i << ": ";
      for(int j=0; j < ordenParcial.at(i).obtenerTamanno(); j++){
         cout << ordenParcial.at(i)[j] << " ";
      }
      cout << endl;
   }

   // se intenta la resolucion mediante la heuristica de kong
   // se agregan los arcos de memoria
   diag.agregarArcosMemoria();
   diag.evaluarKong();

   // se muestra el diagrama final para var la secuencia de
   // operaciones
   cout << diag;

   // se vuelve a leer para probar la operacion de relajacion
   diag = lector.obtenerDiagrama();
   cout << endl << endl;
   cout << "aplicacion de operacion relajar " << endl;
   diag.relajar();

   // se muestra el diagrama tras la relajacion
   cout << diag;

   // se resuelve para ver el coste de evaluar sobre el diagrama relajado
   diag.evaluarKong();

   cout << diag;
}
