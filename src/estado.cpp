#include "estado.h"

using namespace std;

// inicializacion de dato miembro estatico
int Estado::id = 0;

/**
 * costructor de la clase
 * @param diagrama
 * @param operacion
 * @param padre
 */
Estado::Estado(const Diagrama & diagrama, Estado * padre, const Operacion & operacion){
   // se asigna los datos miembro
   this->diagrama = diagrama;
   this->padre = padre;
   this->operacion = operacion;
   this->podado = false;
   this->identificador = id++;

   // inicialmente no tiene hijos
   numeroHijos = 0;
   hijos = 0;

   // se ponen a 0 los valores de coste
   coste = 0;
   f = 0;
   h = 0;
}

/**
 * constructor de copia
 * @param origen
 */
Estado::Estado(const Estado & origen){
   // se asignan los datos miembro
   operacion = origen.operacion;
   diagrama = origen.diagrama;

   // se asigna el padre
   padre = origen.padre;

   // se copia el flag de poda
   podado = origen.podado;

   // se reserva espacio para los hijos
   hijos = reservar(origen.numeroHijos);
   numeroHijos = origen.numeroHijos;

   // se asignan los hijos
   for(int i=0; i < numeroHijos; i++){
      hijos[i] = origen.hijos[i];
   }

   // se asigna el valor de coste
   coste = origen.coste;
   f = origen.f;
   h = origen.h;

   // se asigna el mismo identificador
   identificador = origen.identificador;
}

/**
 * metodo de exploracion del estado, con el objetivo de determinar las
 * posibles operaciones y generar los estados hijos
 */
void Estado::explorar(){
   // se determina las operaciones posibles sobre el diagrama asociado
   // al estado
   SecuenciaOperaciones alternativas = diagrama.determinarOperaciones();

   cout << "----------------- operaciones disponibles --------------------" << endl;
   cout << alternativas;
   cout << "---------------------------------------------------------------" << endl;

   // se reserva espacio para el array de hijos
   hijos = new Estado[alternativas.obtenerNumeroOperaciones()];

   // generacion de nuevos estados para representar las operaciones
   // posibles sobre el
   for(int i=0; i < alternativas.obtenerNumeroOperaciones(); i++){
      cout << "   tratamiento de opcion numero " << i << endl;
      // se crea una copia del diagrama para la operacion
      Diagrama copia(diagrama);

      // se crea estado para representar la operacion
      Estado nuevo(copia, padre, alternativas[i]);

      // se ejecuta la operacion sobre el
      nuevo.ejecutarOperacion();

      // el estado se asigna como hijo
      hijos[i] = nuevo;
      cout << "   fin de tratamiento de alternativa " << i << endl;
      cout << "------------------------------------------------" << endl;
   }
}

/**
 * operador de asignacion
 * @param origen
 * @return
 */
Estado & Estado::operator=(const Estado & origen){
   // se libera el espacio previo
   liberar();

   // se asignan los datos miembro
   operacion = origen.operacion;
   diagrama = origen.diagrama;

   // se asigna el flag de poda
   podado = origen.podado;

   // se asigna el padre
   padre = origen.padre;

   // se reserva espacio para los hijos
   hijos = reservar(origen.numeroHijos);
   numeroHijos = origen.numeroHijos;

   // se asignan los hijos
   for(int i=0; i < numeroHijos; i++){
      hijos[i] = origen.hijos[i];
   }

   // se asigna el valor de coste
   coste = origen.coste;
   f = origen.f;
   h = origen.h;

   // se asigna el mismo identificador
   identificador = origen.identificador;

   // se devuelve la referencia a this
   return *this;
}

/**
 * comparador entre estados
 * @param estado
 * @return
 */
bool Estado::operator<(const Estado &estado) const{
   return coste < estado.coste;
}

/**
 * comparador entre estados
 * @param estado
 * @return
 */
bool Estado::operator>(const Estado &estado) const{
   return coste > estado.coste;
}

/**
     * operador de igualdad: se trata del mismo diagrama
     * @param estado
     * @return
     */
bool Estado::operator==(const Estado & estado) const{
   return diagrama == estado.diagrama;
}

/**
 * Operador de desigualdad
 * @param estado
 * @return
 */
bool Estado::operator!=(const Estado & estado) const{
   return !(*this == estado);
}

/**
 * operador de salida
 * @param flujo
 * @param estado
 * @return
 */
std::ostream & operator<<(std::ostream &flujo, const Estado & estado){
   // se muestra el identificador
   flujo << "----------------- " << estado.identificador << "--------------------"  << endl;

   // se muestra el identificador del padre si es necesario
   if(estado.padre != 0) {
      flujo << "identificador de estado padre: " << estado.padre->identificador << endl;
   }
   else{
      flujo << "padre nulo - raiz" << endl;
   }

   // se muestra el diagrama (la matriz del diagrama)
   flujo << "matriz de accesibilidad " << endl;
   estado.diagrama.mostrarMatriz(flujo);
   flujo << endl;

   // se muestran los valores de coste
   flujo << "coste: " << estado.coste << " f: " << estado.f << " h: " << estado.h << endl;

   // se muestra si esta podado
   flujo << "podado: " << estado.podado << endl;

   // se muestra la operacion que ha generado este diagrama (aplicada al padre)
   flujo << "operacion: " << estado.operacion << endl;

   // se muestra el numero de hijos
   flujo << "contador de hijos: " << estado.numeroHijos << endl;

   // se muestran los identificadores de los nodos hijo
   for(int i=0; i < estado.numeroHijos; i++){
      flujo << estado.hijos[i].identificador << " ";
   }

   flujo << endl;
   flujo << "------------------------------------------------" << endl;

   // se devuelve el flujo
   return flujo;
}

/**
 * metodo privado para ejecutar la operacion asociada al estado
 */
void Estado::ejecutarOperacion(){
   // se ejecuta la operacion asociada al estado
   diagrama.ejecutarOperacion(operacion);
   if(padre != 0) {
      cout << "diferencia con diagrama padre tras ejecutar la operacion " << endl;
      padre->diagrama.mostrarDiferencias(diagrama);
      cout << "---------------------------------------------" << endl;
   }
   else{
      // se muestra el diagrama tal cual
      cout << "estado del diagrama tras ejecutar operacion " << endl;
      cout << diagrama;
      cout << "--------------------------------------------" << endl;
   }

   // el maximo entre el valor de h del estado padre y el valor
   // del tamaño del diagrama resultante se asigna a f
   cout << "   se obtiene el maximo entre el tamaño y el valor de f" << endl;
   f = diagrama.obtenerTamanno();
   if(padre != 0) {
      f = obtenerMaximo(padre->f, diagrama.obtenerTamanno());
   }
   cout << "   asignado valor de f: " << f << endl;

   // el diagrama resultante se relaja para estimar el coste asociado
   // a evaluar mediante Kong
   Diagrama copiaDiagrama(diagrama);

   // se determina la evaluacion mediante Kong tras relajar el diagrama
   cout << "   se procede a relajar el diagrama " << endl;
   copiaDiagrama.relajar();
   cout << "diagrama tras relajar el diagrama" << endl;
   diagrama.mostrarDiferencias(copiaDiagrama);
   cout << "........................................." << endl;
   cout << "   se procede a realizar la evaluacion mediante Kong" << endl;
   copiaDiagrama.evaluarKong();

   // se obtiene la solucion del diagrama
   SecuenciaOperaciones solucion = copiaDiagrama.obtenerSolucion();

   // se asigna a h el maximo valor obtenido de la solucion a la
   // heuristica
   h = solucion.maximo();
   cout << "valor de h: " << h << endl;

   // se asigna el valor de coste
   coste = f + h;
   cout << "   cotse global del estado: " << coste << endl;
}
