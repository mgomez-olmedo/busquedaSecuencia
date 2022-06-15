
#ifndef DIAGRAMA_H
#define DIAGRAMA_H

#include<iostream>

#include "variable.h"
#include "matriz.h"
#include "secuenciaEnteros.h"
#include "secuenciaOperaciones.h"
#include "opcionInversion.h"
#include "utilidades.h"
#include "operacion.h"

class Diagrama {
private:
   /**
    * nombre del diagrama
    */
   std::string nombre;

   /**
    * contador del numero de nodos
    */
   int numeroNodos;

   /**
    * lista de identificadores de los nodos. Estos identificadores
    * son internos, desde 0 en adelante y sirven de guia para
    * acceder al resto de informacion de los nodos
    */
   int *listaIds;

   /**
    * informacion completa de las variables
    */
   Variable *variables;

   /**
    * lista de nombres de las variables
    */
   std::string *nombres;

   /**
    * lista de cardinalidades de las variables
    */
   int *cardinalidades;

   /**
    * Matriz de accesibilidad: de dimension numeroNodos
    * x numeroNodos. Es un objeto que se gestiona en
    * memoria dinamica
    */
   Matriz *matriz;

   /**
    * indice del nodo de utilidad
    */
   int indiceNodoUtilidad;

   /**
    * secuencia de operaciones para representar la solucion
    * del diagrama
    */
   SecuenciaOperaciones solucion;

   /**
    * vector de inversiones realizadas
    */
   std::vector<OpcionInversion> inversionesRealizadas;

   /**
    * metodo privado para liberar espacio
    */
   void liberarEspacio();

   /**
    * se obtiene el identificador asociado a una variable
    * @param nombre
    * @return
    */
   int buscarIdVariable(std::string nombre) const;

   /**
    * metodo para recuperar los nodos de un determinado tipo
    * @param tipo
    * @return
    */
   SecuenciaEnteros obtenerNodos(TIPOVARIABLE tipo) const;

   /**
    * busca los hijos de un nodo que sean de un tipo
    * determinado
    * @param id
    * @param tipo
    * @return
    */
   SecuenciaEnteros obtenerHijos(int id, TIPOVARIABLE tipo) const;

   /**
    * busca los padres de un nodo, que sean a su vez
    * de un determinado tipo
    * @param id
    * @param tipo
    * @return
    */
   SecuenciaEnteros obtenerPadres(int id, TIPOVARIABLE tipo) const;

    /**
     * busca los padres de un nodo, sea cual sea su tipo
     * @param id
     * @param tipo
     * @return
     */
    SecuenciaEnteros obtenerPadres(int id) const;

    /**
     * obtiene los padres de un nodo que no formen parte de la coleccion
     * de prohibidos
     * @param id
     * @param prohibidos
     * @return
     */
    SecuenciaEnteros obtenerNuevosPadres(int id, std::vector<SecuenciaEnteros> prohibidos) const;

    /**
     * Determina si existe un unico camino entre dos nodos
     * @param id1 id del primer nodo
     * @param id2 id del segundo nodo
     * @return
     */
    bool caminoUnico(int id1, int id2) const;

    /**
     * determina las variables de azar que no tienen ninguna decision como
     * hijo
     * @return
     */
    SecuenciaEnteros variablesNoInformativas() const;

   /**
    * metodo para determinar los nodos de azar candidatos a
    * eliminacion
    * @return
    */
   SecuenciaEnteros determinarCandidatosAzar() const;

   /**
    * determina el nodo de decision candidato a ser eliminado
    * @return
    */
   SecuenciaEnteros determinarCandidatosDecision() const;

   /**
    * determina las operaciones candidatas para inversion de
    * arcos
    * @return
    */
   std::vector<OpcionInversion> determinarCandidatosInversion() const;

   /**
    * metodo para eliminar un nodo de azar. Se modifica el
    * objeto sobre el que se hace la llamada
    * @param idNodo
    */
   void eliminarNodoAzar(int idNodo);

   /**
    * metodo para eliminar un nodo de decision. Se modifica el
    * objeto sobre el que se hace la llamada
    * @param idNodo
    */
   void eliminarNodoDecision(int idNodo);

   /**
    * metodo para invertir arco entre nodo origen y destino
    * @param idOrigen
    * @param idDestino
    */
   void invertir(int idOrigen, int idDestino);

   /**
    * metodo para ejecutar sobre el diagrama una secuencia de operaciones
    * de invsersion, junto con la eliminacion del nodo de azar asociado
    * @param opcion
    * @return
    */
   void invertirEliminar(const OpcionInversion & opcion);

   /**
    * localiza la ultima decision en segun el orden de borrado, es
    * decir, en el orden temporal (la que solo tiene como sucesor
    * al nodo de utilidad)
    * @return
    */
   int ultimaDecision() const;

   /**
    * busca la decision que puede tener como sucesores a las
    * decisiones pasadas como argumento
    * @param decisiones
    * @return
    */
   int decisionAntecesoraDe(SecuenciaEnteros decisiones) const;

   /**
    * cuenta el numero de decisiones presentes en el diagrama
    * @return
    */
   int numeroDecisiones() const;

   /**
    * metodo privado para asignar los enlaces a partir de los
    * id de los nodos
    * @param origen
    * @param destino
    */
   void asignarEnlace(int origen, int destino){
      (*matriz)(origen, destino) = 1;
   }

   /**
   * metodo privado para eliminar los enlaces a partir de los
   * id de los nodos
   * @param origen
   * @param destino
   */
   void borrarEnlace(int origen, int destino){
      (*matriz)(origen, destino) = 0;
   }

   /**
    * se borran todos los anlces al nodo destino
    * @param destino
    */
   void borrarEnlacesA(int destino){
      for(int i=0; i < numeroNodos; i++){
         std::cout << "   borrado enlace entre " << variables[i].obtenerNombre() <<
            " y " << variables[destino].obtenerNombre() << std::endl;
         borrarEnlace(i, destino);
      }
   }

   /**
    * metodo privado para comprobar la existencia de un enlace
    * @param origen
    * @param destino
    */
   bool comprobarEnlace(int origen, int destino) const{
      return (*matriz)(origen, destino) == 1;
   }

   /**
    * determina si origen tiene como hijo unico a destino
    * @param origen
    * @param destino
    * @return
    */
   bool hijoUnico(int origen, int destino) const{
      // delega la operacion en la matriz
      return matriz->hijoUnico(origen, destino);
   }

   /**
     * busca todos los nodos que tiene como hijo unico
     * al nodo pasado como argumento
     * @param destino
     * @return
     */
   SecuenciaEnteros hijoUnico(int destino) const{
      // delega la operacion en matriz
      return matriz->hijoUnico(destino);
   }

   /**
     * busca todos los nodos que tiene como hijo unico
     * al nodo pasado como argumento
     * @param destino
     * @return
     */
   SecuenciaEnteros hijoUnico(int destino, SecuenciaEnteros considerados) const{
      // delega la operacion en matriz
      SecuenciaEnteros padres = matriz->hijoUnico(destino);

      // se crea la lista resultado
      SecuenciaEnteros resultado;

      // se agregan los padres que no esten ya en considerados
      for(int i=0; i < padres.obtenerTamanno(); i++){
         if(!considerados.contiene(padres[i])){
            resultado += padres[i];
         }
      }

      // se devuelve el resultado
      return resultado;
   }

   /**
     * metodo para determinar los hijos del nodo pasado
     * como argumento
     * @param origen
     * @return
     */
   SecuenciaEnteros hijos(int origen) const{
      // delega en matriz
      return matriz->hijos(origen);
   }

   /**
    * obtiene los padres de un nodo pasado como
    * argumento
    * @param destino
    * @return
    */
   SecuenciaEnteros padres(int destino) const{
      // delega en matriz
      return matriz->padres(destino);
   }

   /**
    * metodo para eliminar toda la informacion de un nodo
    * @param idNodo
    */
   void eliminarNodo(int idNodo);

   /**
    * metodo de eliminacion de sumideros
    */
   void eliminarSumideros();

   /**
    * elimina los enlaces entre las decisiones
    */
   void eliminarEnlacesDecisiones();

   /**
    * selecciona la mejor opcion posible mediante la heuristica de Kong
    * @param opciones
    * @param operacion
    * @return
    */
   int seleccionarMejorOpcionKong(SecuenciaEnteros opciones, TIPOVARIABLE operacion) const;

   /**
    * metodo de seleccion de la mejor opcion de inversion. NOTA: se realiza un solo
    * paso, sin vincular la inversion con el siguiente nodo a eliminar. Es decir,
    * podria ocurrir que se generasen de forma consecutiva dos inversiones
    * correspondientes a nodos de azar distintos
    * @param opciones
    * @return
    */
   OpcionInversion seleccionarMejorOpcionInversionKong(const std::vector<OpcionInversion> & opciones);

   /**
    * metodo para evaluar el coste de realizar una operacion de invsersion
    * sobre un nodo de azar, incluyendo las inversiones y la eliminacion del
    * nodo objetivo
    * @param opcion
    * @return
    */
   OpcionInversion evaluarInversionKong(OpcionInversion opcion) const;

public:

   /**
    * Constructor por defecto. El diagrama se inicializa con
    * todo vacio y se le van agregando elementos (nodos, enlaces,
    * etc)
    */
   Diagrama();

   /**
    * constructor de copia
    * @param origen
    */
   Diagrama(const Diagrama &origen);

   /**
    * Destructor de la clase
    */
   ~Diagrama();

   /**
    * metodo de asignacion del nombre
    * @param nombre
    */
   void asignarNombre(const std::string &nombre) {
      this->nombre = nombre;
   }

   /**
    * metodo para asignar la lista de variables del diagrama
    * @param lista
    * @param util
    */
   void asignarVariables(Variable *lista, int util);

   /**
    * metodo para asignar enlace entre variables
    * @param variable1
    * @param variable2
   */
   void asignarEnlace(const std::string &variable1, const std::string &variable2);

   /**
    * metodo para calcular y devolver el tamanno del diagrama
    * @return
    */
   double obtenerTamanno() const;

   /**
    * devuelve la solucion
    * @return
    */
   SecuenciaOperaciones obtenerSolucion() const{
      return solucion;
   }

   /**
    * accede al maximo valor alcanzado al evaluar el diagrama
    * @return
    */
   double obtenerMaximoCosteEvaluacion() const{
      return solucion.maximo();
   }

   /**
    * metodo privado para agregar arcos de memoria
    */
   void agregarArcosMemoria();

   /**
    * metodo para evaluarKong el diagrama
    * usando el criterio de kong
    * (elegir la operacion de menor coste)
    */
   void evaluarKong();

   /**
    * determina las operaciones posibles a realizar sobre un
    * diagrama
    * @return
    */
   SecuenciaOperaciones determinarOperaciones();

   /**
    * metodo para simplificar el diagrama con el objeto de calcular
    * heuristicas de evaluacion. Para ello se eliminan los arcos de
    * decision del modelo: si una variable X es padre de una decision
    * D_i entonces ya no sera padre de D_(i+1), etc
    */
   void relajar();

   /**
    * operador de asignacion
    * @param origen
    * @return
    */
   Diagrama &operator=(const Diagrama &origen);

   /**
    * operador de comparacion (que la matriz sea igual)
    * @param otro
    * @return
    */
   bool operator==(const Diagrama & otro) const;

   /**
    * muestra la matriz a traves de un flujo pasado como
    * argumento
    * @param flujo
    */
   void mostrarMatriz(std::ostream & flujo) const{
      flujo << (*matriz);
   }

   /**
    * metodo para ejecutar la operacion pasada como argumento sobre
    * el diagrama
    * @param operacion
    */
   void ejecutarOperacion(const Operacion & operacion);

   /**
    * metodo para depuracion, que muestra las diferencias entre
    * this y el diagrama pasado como argumento
    * @param otro
    */
   void mostrarDiferencias(const Diagrama & otro) const;

    std::vector<SecuenciaEnteros> ordenTopologicoNew() const;

    /**
     * determina el orden parcial de borrado de nodos
     * @return
     */
    std::vector<SecuenciaEnteros> ordenParcialBorrado() const;

    /**
     * ordena las decisiones segun su orden topologico
     * @return
     */
    SecuenciaEnteros ordenDecisiones() const;

    /**
    * operador de salida
    * @param flujo
    * @param diagrama
    * @return
    */
   friend std::ostream &operator<<(std::ostream &flujo, const Diagrama &diagrama);
};


#endif /* DIAGRAMA_H */

