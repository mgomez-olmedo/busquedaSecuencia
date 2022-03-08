
#include "colaPrioridad.h"

using namespace std;

/**
 * constructor de copia
 * @param origen
 */
ColaPrioridad::ColaPrioridad(const ColaPrioridad & origen){
   // se reserva espacio para tantos estados como indique origen
   cola = reservar(origen.numeroEstados);

   // se asignan los estados uno a uno
   for(int i=0; i < origen.numeroEstados; i++){
      // implica el operador de asignacion de Estado
      cola[i] = origen.cola[i];
   }

   // se copia el valor de numero de estados
   numeroEstados = origen.numeroEstados;

   // se copian las estadisticas de uso
   actualizaciones = origen.actualizaciones;
   podas = origen.podas;
}

/**
 * operador de asignacion
 * @param origen
 * @return
 */
ColaPrioridad & ColaPrioridad::operator=(const ColaPrioridad & origen){
   // se libera espacio previo
   liberar();

   // se reserva espacio para tantos estados como indique origen
   cola = reservar(origen.numeroEstados);

   // se asignan los estados uno a uno
   for(int i=0; i < origen.numeroEstados; i++){
      // implica el operador de asignacion de Estado
      cola[i] = origen.cola[i];
   }

   // se copia el valor de numero de estados
   numeroEstados = origen.numeroEstados;

   // se copian las estadisticas de uso
   actualizaciones = origen.actualizaciones;
   podas = origen.podas;

   // se devuelve referencia a this
   return *this;
}

/**
 * metodo para agregar un nuevo estado en la cola
 * @param estado
 * @return
 */
ColaPrioridad & ColaPrioridad::operator+=(Estado & estado){
   // se precisa insercion en el lugar adecuado y solo se hace la
   // insercion si no hay ya estado igual al pasado como argumento
   // (representando al mismo diagrama)
   int indiceEstado = buscar(estado);

   // si no se encuentra, debe insertarse en la posicion correspondiente
   // de acuerdo al coste
   if(indiceEstado == -1){
      insertar(estado);
   }
   else{
      // actualizar los datos de los estados para seguir solo
      // con el mas prometedor
      actualizar(cola[indiceEstado], estado);
   }

   // se devuelve la referencia a this
   return *this;
}

/**
 * extrae el primer elemento de la cola con prioridad
 * @return
 */
Estado ColaPrioridad::extraer(){
   // se almacena el estado que esta en la posicion 0
   Estado primero = cola[0];

   // se reserva espacio para almacenar los estados que se
   // quedaran almacenados
   Estado * espacio = reservar((numeroEstados-1));

   // se copian los estados desde 1 en adelante
   for(int i=1; i < numeroEstados; i++){
      espacio[i-1] = cola[i];
   }

   // se libera el espacio previo
   liberar();

   // se hace que cola apunte a espacio
   cola = espacio;

   // se decrementa el numero de estados
   numeroEstados--;

   // se devuelve el estado
   return primero;
}

/**
 * metodo privado para buscar un estado en la cola que
 * represente la misma situacion que el estado pasado
 * como argumento
 */
int ColaPrioridad::buscar(const Estado & referencia) const{
   int indice = -1;
   for(int i=0; i < numeroEstados && indice == -1; i++){
      if(cola[i] == referencia){
         indice = i;
      }
   }

   // se devuelve el valor de indice
   return indice;
}

/**
     * metodo de insercion de un nuevo estado en la posicion
     * correspondiente (de menor a mayor valor de coste)
     * @param estado
     */
void ColaPrioridad::insertar(const Estado & estado){
   // se busca el indice del estado cuyo valor de coste es ya
   // mayor que el del estado pasado como argumento
   int indiceInsercion=0;
   bool continuar = true;
   for(int i=0; i < numeroEstados && continuar; i++){
      if(cola[i].operator>(estado)){
         // debe insertarse justo en la posicion i
         indiceInsercion = i;

         // rompe el bucle
         continuar = false;
      }
   }

   // se reserva nuevo espacio para los estados
   Estado * espacio = reservar(numeroEstados + 1);

   // se copian los estados hasta posicion indiceInsercion-1
   for(int i=0; i < indiceInsercion; i++){
      espacio[i] = cola[i];
   }

   // se inserta el estado pasado como argumento en la posicion
   // dada por indiceInsercion
   espacio[indiceInsercion] = estado;

   // se copian los estados desde indiceInsercion (en la cola original)
   // hasta el final
   for(int i=indiceInsercion; i < numeroEstados; i++){
      espacio[i+1] = cola[i];
   }

   // se libera el espacio previo
   liberar();

   // se hace que cola apunte a espacio
   cola = espacio;

   // se incrementa el contador de estados
   numeroEstados++;
}

/**
 * metodo para actualizar (si es necesario) los datos de un
 * estado ya alnacenado, al haber aparecido otro estado durante
 * el proceso de busqueda, que representa al mismo diagrama
 * @param estado1
 * @param estado2
 */
void ColaPrioridad::actualizar(Estado & estado1, Estado & estado2){
   // se trata de dos estados que equivalen a la misma situacion del
   // diagrama y hay que seguir con el estado que tenga menor coste
   if(estado1 < estado2){
      // es mas prometedor el estado 1; se deja la situacion como
      // esta y ho hace falta insertar estado2
      estado2.podar();

      // se incrementa el contador de podas
      podas++;
   }
   else{
      // se hace que estado1 tome todos los valores de estado2
      estado1 = estado2;

      // se hace que estado2 quede como podado
      estado2.podar();

      // se incrementa contador de actualizaciones
      actualizaciones++;
   }
}

/**
 * operador de salida
 * @param flujo
 * @param cola
 * @return
 */
std::ostream & operator<<(std::ostream & flujo, const ColaPrioridad & cola){
   // se indica el numero de estados almacenados
   flujo << "------------------- cola con prioridad ------------------" << endl;
   flujo << "numero de estados: " << cola.numeroEstados << endl;

   // se muestra informacion sobre el contador de actualizaciones

   // se muestra informacion de cada uno de ellos
   for(int i=0; i < cola.numeroEstados; i++){
      flujo << cola.cola[i];
   }
   flujo << "---------------------------------------------------------" << endl;

   // se devuelve el flujo
   return flujo;
}