#include<iostream>

#include "aStarSearch.h"

using namespace std;

/**
 * constructor de la clase
 * @param diagrama
 */
AStarSearch::AStarSearch(const Diagrama &diagrama) {
   // se hace copia del diagrama para evaluar mediante kong
   Diagrama diagramaInicial(diagrama);

   // se resuelve el diagrama mediante la heuristica de kong
   diagramaInicial.evaluarKong();

   // se obtiene el maximo coste de la evaluacion
   double maximoCosteKong = diagramaInicial.obtenerMaximoCosteEvaluacion();

   // se crea el estado inicial del proceso de busqueda
   raiz = new Estado(diagrama, 0,
                     Operacion(NULA, maximoCosteKong,
                               "", ""));

   // se agrega al conjunto de abiertos
   incluirAbierto(*raiz);
}

/**
 * metodo para incluir un estado en la lista de abiertos
 * @param estado
 */
void AStarSearch::incluirAbierto(Estado & estado){
   // se agrega nuevo estado al conjunto de abiertos
   abiertos += estado;
}

/**
 * metodo general de busqueda
 */
void AStarSearch::buscar(){
   // se extrae el primer elemento de la cola con prioridad
   Estado objetivo = abiertos.extraer();

   // se muestra el contenido del estado
   cout << "----------------- estado objetivo de la busqueda --------------" << endl;
   cout << objetivo;
   cout << "---------------------------------------------------------------" << endl;

   // se llama al metodo explorar sobre el estado para continuar el
   // proceso de busqueda
   cout << "llamada a explorar sobre el objetivo" << endl;
   objetivo.explorar();

   // los hijos del nodo objetivo se insertan en la cola de abiertos
   for(int i=0; i < objetivo.obtenerNumeroHijos(); i++){
      abiertos.operator+=(objetivo[i]);
   }

   // se muestra el contenido del objeto
   cout << *this;
}

/**
 * operador de salida
 * @param flujo
 * @param objeto
 * @return
 */
std::ostream & operator<<(std::ostream & flujo, const AStarSearch & objeto){
   // se muestra el estado correspondiente a la raiz
   if(objeto.raiz != 0){
      cout << "-------------------- cola de estados pos explorar -----------------" << endl;
      cout << objeto.abiertos;
   }

   // se devuelve el flujo
   return flujo;
}

