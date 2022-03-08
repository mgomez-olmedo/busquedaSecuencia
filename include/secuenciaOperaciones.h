
#ifndef SECUENCIAOPERACIONES_H
#define SECUENCIAOPERACIONES_H

#include<iostream>

#include "operacion.h"

/**
 * clase para almacenar en memoria dinamica la operaciones de operaciones
 * necesarias para resolver un diagrama de influencia
 */
class SecuenciaOperaciones{
private:
   /**
    * almacen de operaciones en memoria dinamica
    */
   Operacion * operaciones;

   /**
    * contador del numero de operaciones
    */
   int numOperaciones;

   /**
    * metodo privado para reserva de espacio
    * @param dimension
    * @return
    */
   Operacion * reservar(int dimension);

   /**
    * metodo privado de liberacion de espacio de memoria
    */
   void liberar();
public:
   /**
    * constructor por defecto
    */
   SecuenciaOperaciones(){
      operaciones = 0;
      numOperaciones = 0;
   }

   /**
    * constructor de copia
    * @param secuencia
    */
   SecuenciaOperaciones(const SecuenciaOperaciones & secuencia);

   /**
    * Destructor de la clase
    */
   ~SecuenciaOperaciones(){
      liberar();
   }

   /**
    * metodo de acceso al contador de operaciones
    * @return
    */
   int obtenerNumeroOperaciones() const{
      return numOperaciones;
   }

   /**
    * metodo para obtener el maximo coste de la secuencia de
    * operaciones
    * @return
    */
   double maximo() const;

   /**
    * operador de asignacion
    * @param secuencia
    * @return
    */
   SecuenciaOperaciones & operator=(const SecuenciaOperaciones & secuencia);

   /**
    * operador de agregacion de nueva operacion
    * @param operacion
    * @return
    */
   SecuenciaOperaciones & operator+=(const Operacion & operacion);

   /**
    * operador de acceso a las operaciones de la secuencia
    * @param indice
    * @return
    */
   Operacion & operator[](int indice){
      return operaciones[indice];
   }

   /**
    * operador de acceso a las operaciones de la secuencia para
    * colecciones constantes
    * @param indice
    * @return
   */
    const Operacion & operator[](int indice) const{
       return operaciones[indice];
    }

   /**
    * operador de salida para mostrar la informacion de la secuencia
    * @param flujo
    * @param operaciones
    * @return
    */
   friend std::ostream & operator<<(std::ostream & flujo, const SecuenciaOperaciones & secuencia){
      // se muestra la secuencia
      for(int i=0; i < secuencia.numOperaciones; i++){
         // se delega en el operador de salida de Operacion
         flujo << secuencia.operaciones[i] << std::endl;
      }

      // se devuelve el flujo
      return flujo;
   }

};
#endif //SECUENCIAOPERACIONES_H
