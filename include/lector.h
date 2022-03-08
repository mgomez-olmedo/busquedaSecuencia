
#ifndef LECTOR_H
#define LECTOR_H

#include<iostream>
#include<fstream>

#include "diagrama.h"
#include "variable.h"

typedef enum {
    ASIGNAR_NOMBRE,
    CREAR_NODO,
    ASIGNAR_VALOR,
    ASIGNAR_PADRE
} OPERACIONES;

/**
 * Clase para procesar los archivos con la descripcion
 * del diagrama. Generan un diagrama como resultado de
 * la operacion de procesamiento
 */
class Lector {
private:
    /**
     * nombre del archivo a procesar
     */
    std::string nombre;

    /**
     * diagrama resultante del procesamiento del archivo
     */
    Diagrama diagrama;

    /**
     * almacenamiento temporal de variables hasta tener
     * toda la informacion sobre ellas
     */
    Variable *listaVariables;

    /**
     * contador de variables
     */
    int numVariables;

    /**
     * metodo privado para reserva de espacio
     * @param flujo
     */
    Variable *reservarEspacio(int dimension) {
       return new Variable[dimension];
    }

    /**
     * metodo privado de liberacion de espacio
     */
    void liberarEspacio() {
       if (listaVariables != 0) {
          delete[] listaVariables;
       }

       // asigna puntero nulo a listaVariables
       listaVariables = 0;
    }

    /**
     * metodo privado para procesar el nombre del
     * diagrama
     * @param flujo
     */
    void procesarNombre(std::istream &flujo);

    /**
     * procesa las definiciones de los nodos
     * @param flujo
     */
    void procesarDefinicionNodos(std::istream &flujo);

    /**
     * procesa la defincion de los estados de la variable
     * @param flujo
     */
    void procesarDefinicionEstados(std::istream &flujo);

    /**
     * procesa las definiciones de enlaces en el diagrama
     * @param flujo
     */
    void procesarDefinicionEnlaces(std::istream &flujo);

    /**
     * metodo privado para asignar un estado a una variable
     * @param nombreVariable
     * @param nombreEstado
     */
    void asignarEstadoVariable(std::string nombreVariable, std::string nombreEstado);

    /**
     * agrega la informacion de una nueva variable
     * @param variable
     * @return
     */
    Lector &operator+=(const Variable &variable);

public:

    /**
     * Constructor de la clase
     * @param nombre
     */
    Lector(std::string nombre);

    /**
     * Destructor de la clase
     */
    ~Lector() {
       liberarEspacio();
    }

    /**
     * devuelve el diagrama generado
     * @return
     */
    Diagrama & obtenerDiagrama() {
       return diagrama;
    }
};

#endif /* LECTOR_H */

