#ifndef ESTADO_H
#define ESTADO_H

#include<iostream>

#include "diagrama.h"
#include "operacion.h"

/**
 * Clase para representar estados de un espacio de busqueda en el que se trabaja
 * con diagramas de influencia
 */
class Estado{
private:
    /**
     * identificador unico para cada nodo
     */
    static int id;

   /**
    * Puntero al estado del que se obtiene este estado tras alguna operacion
    */
   Estado * padre;

   /**
    * operacion que genera el diagrama de este nodo a partir del diagrama
    * del nodo padre
    */
    Operacion operacion;

   /**
    * Diagrama que caracteriza a este estado
    */
   Diagrama diagrama;

   /**
    * Coleccion de estados generados a partir de este
    */
    Estado * hijos;

    /**
     * contador de hijos
     */
    int numeroHijos;

    /**
     * coste asociado a este estado
     */
    double coste;

    /**
     * coste asociado a la obtencion del estado (por las operaciones
     * desde la raiz hasta el)
     */
     double f;

     /**
      * estimacion del coste necesario para finalizar el proceso
      * de busqueda desde este estado (heuristica)
      */
     double h;

     /**
      * flag booleano para indicar que el nodo esta podado
      */
     bool podado;

     /**
      * identificador unico asignado a partir de id
      */
     int identificador;

     /**
      * metodo privado para reserva de espacio para los hijos
      * metodo privado para reserva de espacio para los hijos
      * @param dimension
      */
     Estado * reservar(int dimension) {
        Estado *espacio = 0;
        if (dimension != 0) {
         espacio = new Estado[dimension];
        }

        // se devuelve el espacio reservado
        return espacio;
     }

     /**
      * metodo privado para liberar espacio
      */
     void liberar(){
        if(hijos != 0){
           delete [] hijos;
        }
     }

    /**
     * se ejecuta la operacion asociada al estado
     */
    void ejecutarOperacion();

public:
    /**
     * constructor por defecto
     */
    Estado(){
       padre = 0;
       hijos = 0;
       numeroHijos = 0;
       podado = false;
       identificador = id++;
       coste = 0;
       f = 0;
       h = 0;
    }

    /**
     * costructor de la clase
     * @param diagrama
     * @param operacion
     * @param padre
     */
    Estado(const Diagrama & diagrama, Estado * padre, const Operacion & operacion);

    /**
     * constructor de copia
     * @param origen
     */
    Estado(const Estado & origen);

    /**
     * destructor de la clase
     */
    ~Estado(){
       liberar();
    }

    /**
     * metodo de acceso al diagrama
     * @return
     */
    Diagrama obtenerDiagrama(){
       return diagrama;
    }

    /**
     * asigna el flad de poda
     */
    void podar(){
       podado = true;
    }

    /**
     * metodo de exploracion del estado, con el objetivo de determinar las
     * posibles operaciones y generar los estados hijos
     */
    void explorar();

    /**
     * se devuelve el numero de hijos
     * @return
     */
    int obtenerNumeroHijos(){
       return numeroHijos;
    }

    /**
     * se obtiene el hijo almacenado en una determinada posicion
     * @param indice
     * @return
     */
    Estado & operator[](int indice){
       return hijos[indice];
    }

    /**
     * se obtiene el hijo almacenado en una determinada posicion
     * @param indice
     * @return
    */
    const Estado & operator[](int indice) const{
       return hijos[indice];
    }

    /**
     * operador de asignacion
     * @param origen
     * @return
     */
    Estado & operator=(const Estado & origen);

    /**
     * comparador entre estados
     * @param estado
     * @return
     */
    bool operator<(const Estado & estado) const;

    /**
     * comparador entre estados
     * @param estado
     * @return
     */
    bool operator>(const Estado & estado) const;

    /**
     * operador de igualdad
     * @param estado
     * @return
     */
    bool operator==(const Estado & estado) const;

    /**
     * Operador de desigualdad
     * @param estado
     * @return
     */
    bool operator!=(const Estado & estado) const;

    /**
     * operador de salida
     * @param flujo
     * @param estado
     * @return
     */
    friend std::ostream & operator<<(std::ostream &flujo, const Estado & estado);
};

#endif //ESTADO_H
