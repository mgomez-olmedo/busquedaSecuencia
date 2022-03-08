
#ifndef MATRIZ_H
#define MATRIZ_H

#include<iostream>
#include<cstring>

#include "secuenciaEnteros.h"

class Matriz {
private:
    /**
     * almacen de datos
     */
    int *matriz;

    /**
     * dimension de la matriz cuadrada
     */
    int dimension;

    /**
     * metodo privado de reserva de espacio
     * @param dimension
     * @return
     */
    int *reservar(int dimension);

    /**
     * metodo privado para liberar espacio
     * @param dimension
     */
    void liberar();

    /**
     * metodo privado para calcular el desplazamiento en el array unidimensional
     * @param fila
     * @param columna
     * @return
     */
    int calcularIndice(int fila, int columna) const;

public:
    /**
     * constructor por defecto
     */
    Matriz() {
       matriz = 0;
    }

    /**
     * Destructor de la clase
     */
    ~Matriz(){
       liberar();
    }

    /**
     * Constructor con dimension
     * @param dimension
     */
    Matriz(int dimension);

    /**
     * Constructor de copia
     * @param origen
     */
    Matriz(const Matriz &origen);

    /**
     * operador de asignacion
     * @param matriz
     * @return
     */
    Matriz &operator=(const Matriz &origen);

    /**
     * Operador de acceso con dos dimension
     * @param i
     * @param j
     * @return
     */
    int & operator()(int i, int j);

    /**
     * Operador de acceso con dos dimension, para matrices constantes
     * @param i
     * @param j
     * @return
     */
    const int & operator()(int i, int j) const;

    /**
     * comparator operator
     * @param otra
     * @return
     */
    bool operator==(const Matriz & otra) const;

    /**
     * comparator operator
     * @param otra
     * @return
     */
    bool operator!=(const Matriz & otra) const{
       return !(*this == otra);
    }

    /**
     * operador de multiplicacion
     * @param otra
     * @return
     */
    Matriz operator*(const Matriz & otra) const;

    /**
     * determina si el nodo origen tiene como unico sucesor
     * al nodo destino
     * @param origen
     * @param destino
     * @return
     */
    bool hijoUnico(int origen, int destino) const;

    /**
     * busca todos los nodos que tiene como hijo unico
     * al nodo pasado como argumento
     * @param destino
     * @return
     */
    SecuenciaEnteros hijoUnico(int destino) const;

    /**
     * metodo para determinar los hijos del nodo pasado
     * como argumento
     * @param origen
     * @return
     */
    SecuenciaEnteros hijos(int origen) const;

    /**
     * obtiene los padres de un nodo pasado como
     * argumento
     * @param destino
     * @return
     */
    SecuenciaEnteros padres(int destino) const;

   /**
    * genera la matriz de alcanzabilidad a partir de la matriz
    * @param potencia el numero de multiplicaciones a realizar
    * @return
    */
    Matriz obtenerPotencia(int potencia);

    /**
     * elimina fila y columna de la matriz
     * @param fila
     * @param columna
     * @return
     */
    Matriz & eliminar(int fila, int columna);

    /**
     * metodo para determinar si hay enlace entre dos nodos
     * @param origen
     * @param destino
     * @return
     */
    bool hayEnlace(int origen, int destino) const;

    /**
    * operador de salida
    * @param flujo
    * @param matriz
    * @return
    */
    friend std::ostream &operator<<(std::ostream &flujo, const Matriz &matriz);
};

#endif /* MATRIZ_H */

