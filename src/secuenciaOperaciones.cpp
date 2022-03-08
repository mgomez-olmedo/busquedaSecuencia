#include "secuenciaOperaciones.h"

using namespace std;

/**
 * constructor de copia
 * @param secuencia
 */
SecuenciaOperaciones::SecuenciaOperaciones(const SecuenciaOperaciones & secuencia){
   // se reserva espacio de memoria, tanto como indique secuencia
   operaciones = reservar(secuencia.numOperaciones);

   // se copian los objetos desde secuencia
   for(int i=0; i < secuencia.numOperaciones; i++){
      operaciones[i] = secuencia.operaciones[i];
   }

   // se da valor al dato miembro numOperaciones
   numOperaciones = secuencia.numOperaciones;
}

/**
  * metodo para obtener el maximo coste de la secuencia de
  * operaciones
  * @return
  */
double SecuenciaOperaciones::maximo() const{
   // obtiene el maximo de los costes de cada una de las operaciones
   // de la secuencia
   double maximo = 0;

   for(int i=0; i < numOperaciones; i++){
      if(operaciones[i].obtenerCoste() > maximo){
         maximo = operaciones[i].obtenerCoste();
      }
   }

   // se devuelve el maximo
   return maximo;
}

/**
 * operador de asignacion
 * @param secuencia
 * @return
 */
SecuenciaOperaciones & SecuenciaOperaciones::operator=(const SecuenciaOperaciones & secuencia){
   // se libera el espacio de memoria
   liberar();

   // se hace reserva de espacio
   operaciones = reservar(secuencia.numOperaciones);

   // se copian los objetos desde secuencia
   for(int i=0; i < secuencia.numOperaciones; i++){
      operaciones[i] = secuencia.operaciones[i];
   }

   // se da valor al dato miembro numOperaciones
   numOperaciones = secuencia.numOperaciones;

   // se devuelve la referencia a this
   return *this;
}

/**
 * operador de agregacion de nueva operacion
 * @param operacion
 * @return
 */
SecuenciaOperaciones & SecuenciaOperaciones::operator+=(const Operacion & operacion){
   // se hace la reserva de espacio para agregar un objeto mas
   Operacion * espacio = reservar(numOperaciones + 1);

   // se copian los objetos desde secuencia
   for(int i=0; i < numOperaciones; i++){
      espacio[i] = operaciones[i];
   }

   // se agrega el objeto pasado como argumento
   espacio[numOperaciones] = operacion;

   // se libera el espacio previo
   liberar();

   // se hace que oepraciones apunte a espacio
   operaciones = espacio;

   // se incrementa el contador de operaciones
   numOperaciones++;

   // se devuelve la referencia a this
   return *this;
}

/**
 * metodo privado para reserva de espacio
 * @param dimension
 * @return
 */
Operacion * SecuenciaOperaciones::reservar(int dimension){
   Operacion * espacio = 0;
   if(dimension != 0) {
      espacio = new Operacion[dimension];
   }

   // se devuelve el puntero
   return espacio;
}

/**
 * metodo privado de liberacion de espacio de memoria
 */
void SecuenciaOperaciones::liberar(){
   if(numOperaciones != 0){
      delete [] operaciones;
      operaciones = 0;
   }
}
