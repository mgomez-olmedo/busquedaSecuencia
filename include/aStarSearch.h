//
// Created by Manuel Gomez Olmedo on 19/7/21.
//

#ifndef ASTARSEARCH_H
#define ASTARSEARCH_H

#include "colaPrioridad.h"
#include "diagrama.h"
#include "estado.h"

class AStarSearch{
private:
    /**
     * Estado inicial para desencadenar la busqueda
     */
    Estado * raiz;

    /**
     * cola de prioridad de los estados por examinar
     */
    ColaPrioridad abiertos;

    /**
     * vector con los estados ya explorados
     */
    std::vector<Estado> cerrado;
public:
    /**
     * constructor de la clase
     * @param diagrama
     */
    AStarSearch(const Diagrama & diagrama);

    /**
     * Destructor de la clase
     */
    ~AStarSearch(){
       if(raiz != 0){
          delete raiz;
       }
    }

    /**
     * metodo para incluir un estado en la lista de abiertos
     * @param estado
     */
    void incluirAbierto(Estado & estado);

    /**
     * metodo general de busqueda
     */
    void buscar();

    /**
     * operador de salida
     * @param flujo
     * @param objeto
     * @return
     */
    friend std::ostream & operator<<(std::ostream & flujo, const AStarSearch & objeto);
};
#endif //ASTARSEARCH_H
