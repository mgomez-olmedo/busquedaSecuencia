
#ifndef COLAPRIORIDAD_H
#define COLAPRIORIDAD_H

#include "estado.h"

/**
 * clase para almacenar los estados de busqueda en la lista abiertos
 */
class ColaPrioridad{
private:
    /**
     * vector de estados
     */
    Estado * cola;

    /**
     * contador de estados
     */
    int numeroEstados;

    /**
     * contadores para obtener informacion sobre el funcionamiento
     * de la cola
     */
    int actualizaciones;
    int podas;

    /**
     * metodo privado de reserva de espacio
     */
    Estado *reservar(int dimension){
       Estado * espacio = 0;
       if(dimension != 0){
          espacio = new Estado[dimension];
       }

       // se devuelve el puntero al espacio reservado
       return espacio;
    }
    /**
     * metodo privado de liberacion de espacio
     */
    void liberar(){
       if(cola != 0){
          delete [] cola;
       }
    }

    /**
     * metodo privado para buscar un estado en la cola que
     * represente la misma situacion que el estado pasado
     * como argumento
     */
    int buscar(const Estado & referencia) const;

    /**
     * metodo de insercion de un nuevo estado en la posicion
     * correspondiente (de menor a mayor valor de coste)
     * @param estado
     */
    void insertar(const Estado & estado);

    /**
     * metodo para actualizar (si es necesario) los datos de un
     * estado ya alnacenado, al haber aparecido otro estado durante
     * el proceso de busqueda, que representa al mismo diagrama
     * @param estado1
     * @param estado2
     */
    void actualizar(Estado & estado1, Estado & estado2);

public:
    /**
     * constructor por defecto
     */
    ColaPrioridad(){
       cola = 0;
       numeroEstados = 0;
       actualizaciones = 0;
       podas = 0;
    }

    /**
     * constructor de copia
     * @param origen
     */
    ColaPrioridad(const ColaPrioridad & origen);

    /**
     * destructor de la clase
     */
    ~ColaPrioridad(){
       liberar();
    }

    /**
     * metodo de acceso al número de estados
     * @return
     */
    int obtenerNumeroEstados() const{
        return numeroEstados;
    }

    /**
     * operador de asignacion
     * @param origen
     * @return
     */
    ColaPrioridad & operator=(const ColaPrioridad & origen);

    /**
     * metodo para agregar un nuevo estado en la cola
     * @param estado
     * @return
     */
    ColaPrioridad & operator+=(Estado & estado);

    /**
     * extrae el primer elemento de la cola con prioridad
     * @return
     */
    Estado extraer();

    /**
     * operador de salida
     * @param flujo
     * @param cola
     * @return
     */
    friend std::ostream & operator<<(std::ostream & flujo, const ColaPrioridad & cola);
};
#endif //COLAPRIORIDAD_H
