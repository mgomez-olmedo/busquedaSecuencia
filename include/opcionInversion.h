#ifndef OPCIONINVERSION_H
#define OPCIONINVERSION_H

#include <iostream>

#include "secuenciaEnteros.h"

class OpcionInversion{
private:
   /**
    * id del nodo de azar a ser borrado
    */
   int idObjetivo;

   /**
    * operaciones de ids de nodos de azar con los
    * que habria que hacer inversion
    */
   SecuenciaEnteros inversiones;

   /**
    * coste asociado a la secuencia
    */
   double coste;

public:
    /**
     * constructor por defecto
     */
    OpcionInversion(){
    }

   /**
    * Constructor con idObjetivo como argumento
    * @param idObjetivo
    */
   OpcionInversion(int idObjetivo){
      this->idObjetivo = idObjetivo;
   }

   /**
    * obtiene acceso al dato miembro idObjetivo
    * @return
    */
   int obtenerIdObjetivo() const{
      return idObjetivo;
   }

   /**
    * metodo de acceso al coste asociado a la opcion de inversion
    * @return
    */
   double obtenerCoste() const{
      return coste;
   }

   /**
    * se agrega nueva inversion al objeto
    * @param id
    */
   OpcionInversion & operator+=(int id){
      inversiones += id;

      // se devuelve la referencia al objeto
      return *this;
   }

   /**
    * se elimina una de las opciones de inversion
    */
   OpcionInversion & operator-=(int id){
      inversiones -= id;

      // se devuelve la referencia al objeto
      return *this;
   }

   /**
    * operador [] para colecciones normales
    * @param indice
    * @return
    */
   int & operator[](int indice){
      return inversiones[indice];
   }

   /**
    * operador [] para colecciones constantes
    * @param indice
    * @return
    */
   const int & operator[](int indice) const{
      return inversiones[indice];
   }

   /**
    * devuelve el numero de inversiones a realizar
    * @return
    */
   int obtenerTamanno() const{
      return inversiones.obtenerTamanno();
   }

   /**
    * asigna el coste a la opcion de inversion
    * @param coste
    */
   void asignarCoste(double coste){
      this->coste = coste;
   }

   /**
    * operador de salida
    * @param flujo
    * @param opcion
    * @return
    */
   friend std::ostream & operator<<(std::ostream & flujo, const OpcionInversion & opcion){
      // se muestra el id del nodo de azar objetivo
      flujo << "id objetivo: " << opcion.obtenerIdObjetivo() << " -- ";

      // se muestran las opciones de inversion
      flujo << opcion.inversiones;

      // se devuelve el flujo
      return flujo;
   }
};
#endif //OPCIONINVERSION_H
