#include "utilidades.h"

using namespace std;

/**
 * funcion de presentacion de errores
 * @param modulo
 * @param funcion
 * @param salir
 */
void presentarErrores(std::string modulo, std::string funcion, 
                     bool salir) {
   cout << "********************* GESTION DE ERRORES ********************" << endl;
   cout << "ERROR en modulo : " << modulo << endl;
   cout << "ERROR en funcion : " << funcion << endl;
   if (salir == true) {
      cerr << "saliendo del programa.........." << endl;
      exit(-1);
   }
}

/**
 * funcion para eliminar repetidos en los vectores indicando
 * las relaciones entre los nodos
 * @param orden
 */
void filtrarRepetidos(vector<SecuenciaEnteros> & orden){
   // para cada nodo en una etapa, se borran todas las
   // ocurrencias en vectores de indice inferior
   for(int i=orden.size()-1; i >= 0; i--){
      SecuenciaEnteros etapa = orden.at(i);

      // se considera cada variable en etapa
      for(int j=0; j < etapa.obtenerTamanno(); j++){
         // se elimina su ocurrencia en etapas posteriores
         for(int k=i-1; k >= 0; k--){
            // en la etapa k se elimina la variable que esta en posicion
            // j en la etapa i
            orden.at(k) -= etapa[j];
         }
      }
   }
}

/**
 * funcion para determinar el minimo de una operaciones de valores
 * @param valores
 * @param longitud
 * @return
 */
int buscarMinimo(double * valores, int longitud){
   int indiceMinimo = 0;

   for(int i=1; i < longitud; i++){
      if(valores[i] < valores[indiceMinimo]){
         // se acualiza indiceMinimo
         indiceMinimo = i;
      }
   }

   // se devuelve el indice minimo
   return indiceMinimo;
}

/**
 * metodo para para obtener el maximo valor de los pasados como
 * argumento
 * @param valor1
 * @param valor2
 * @return
 */
double obtenerMaximo(double valor1, double valor2){
   double maximo = valor1;
   if(valor2 > maximo){
      maximo = valor2;
   }

   // se devuelve el valor de maximo
   return maximo;
}


