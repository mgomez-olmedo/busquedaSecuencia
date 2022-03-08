
#ifndef UTILIDADES_H
#define UTILIDADES_H

#include<iostream>
#include<vector>

#include "secuenciaEnteros.h"
#include "opcionInversion.h"

/**
 * Funciones de utilidad para todos los modulos en
 * general
 */

/**
 * funcion para informacion de errores
 * @param modulo
 * @param funcion
 * @param salir
 */
void presentarErrores(std::string modulo, std::string funcion, 
                     bool salir);

/**
 * funcion para eliminar repetidos en los vectores indicando
 * las relaciones entre los nodos
 * @param orden
 */
void filtrarRepetidos(std::vector<SecuenciaEnteros> & orden);

/**
 * funcion para determinar el minimo de una operaciones de valores
 * @param valores
 * @param longitud
 * @return
 */
int buscarMinimo(double * valores, int longitud);

/**
 * metodo para para obtener el maximo valor de los pasados como
 * argumento
 * @param valor1
 * @param valor2
 * @return
 */
double obtenerMaximo(double valor1, double valor2);

#endif /* UTILIDADES_H */

