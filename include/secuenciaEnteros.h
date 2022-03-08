#ifndef SECUENCIAENTEROS_H
#define SECUENCIAENTEROS_H

#include<iostream>
#include<vector>

class SecuenciaEnteros{
private:
    /**
     * memoria de almacenamiento
     */
    int *secuencia;

    /**
     * numero de posiciones reservadas
     */
    int reservados;

    /**
     * contador de datos usados
     */
    int usados;

    /**
     * metodo privado para reservar espacio
     * @param dimension
     * @return
     */
    int * reservar(int dimension){
       return new int[dimension];
    }

    /**
     * metodo privado para liberar espacio
     */
    void liberar(){
       if(secuencia != 0){
          delete [] secuencia;
          secuencia = 0;
       }
    }
public:

    /**
     * constructor por defecto
     */
    SecuenciaEnteros(){
       secuencia = 0;
       reservados = 0;
       usados = 0;
    }

    /**
     * Destructor de la clase
     */
    ~SecuenciaEnteros(){
       liberar();
       secuencia = 0;
       usados = 0;
       reservados = 0;
    }

    /**
     * constructor de copia
     * @param origen
     */
    SecuenciaEnteros(const SecuenciaEnteros & origen);

    /**
     * consulta si la operaciones contiene un determinado valor
     * @param valor
     * @return
     */
    bool contiene(int valor) const;

    /**
     * operador de asignacion
     * @param origen
     * @return
     */
    SecuenciaEnteros & operator=(const SecuenciaEnteros & origen);

    /**
     * metodo de acceso al tam. de la operaciones
     * @return
     */
    int obtenerTamanno() const{
       return usados;
    }

    /**
     * operador corchete
     * @param indice
     * @return
     */
    int & operator[](int indice) {
       return secuencia[indice];
    }

    /**
     * operador corchete para colecciones constantes
     * @param indice
     * @return
     */
    const int & operator[](int indice) const {
       return secuencia[indice];
    }

    /**
     * operador para agregar un nuevo elemento
     * @param nuevo
     * @return
     */
    SecuenciaEnteros & operator+=(int nuevo);

    /**
     * operador para agregar un nuevo elemento
     * @param nuevo
     * @return
     */
    SecuenciaEnteros & operator+=(const SecuenciaEnteros & otra);

    /**
     * operador para eliminar un elemento
     * @param objetivo
     */
    SecuenciaEnteros & operator-=(int objetivo);

    /**
     * operador oara borrar todos los elementos de la operaciones
     * pasada como argumento
     * @param otra
     * @return
     */
    SecuenciaEnteros & operator-=(const SecuenciaEnteros & otra);

    /**
     * invierte el contenido de la secuencia
     */
    void invertir();

    /**
     * operador de entrada
     * @param flujo
     * @param secuencia
     * @return
     */
    friend std::ostream & operator<<(std::ostream & flujo, const SecuenciaEnteros & secuencia);
};
#endif //SECUENCIAENTEROS_H
