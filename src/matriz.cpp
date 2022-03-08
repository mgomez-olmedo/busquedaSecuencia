
#include "matriz.h"

using namespace std;

/**
 * Constructor con dimension
 * @param dimension
 */
Matriz::Matriz(int dimension) {
   // se asigna la dimension
   this->dimension = dimension;

   // se reserva espacio de memoria
   matriz = reservar(dimension);

   // se inicializa a 0
   memset(matriz, 0, sizeof(int)*dimension * dimension);
}

/**
 * Constructor de copia
 * @param origen
 */
Matriz::Matriz(const Matriz &origen) {
   // se asigna la dimension
   dimension = origen.dimension;

   // se reserva espacio para la dimension indicada
   matriz = reservar(dimension);

   // se copian los datos directamente
   memcpy(matriz, origen.matriz, sizeof(int)*dimension*dimension);
}

/**
 * operador de asignacion
 * @param matriz
 * @return 
 */
Matriz &Matriz::operator=(const Matriz &origen) {
   // se libera el espacio previo
   liberar();

   // se asigna la dimension
   dimension = origen.dimension;

   // se hace la reserva de espacio con la dimension indicada
   matriz = reservar(dimension);

   // se copian los datos desde origen
   memcpy(matriz, origen.matriz, sizeof(int)*dimension*dimension);

   // se devuelve referencia a this
   return *this;
}

/**
 * Operador de acceso con dos dimension
 * @param i
 * @param j
 * @return
*/
int &Matriz::operator()(int i, int j) {
   // devuelve el valor de interes
   return matriz[calcularIndice(i, j)];
}

/**
 * Operador de acceso con dos dimension
 * @param i
 * @param j
 * @return
*/
const int &Matriz::operator()(int i, int j) const {
   // devuelve el valor de interes
   return matriz[calcularIndice(i, j)];
}

/**
 * comparator operator
 * @param otra
 * @return
 */
bool Matriz::operator==(const Matriz & otra) const{
   bool iguales = true;

   // compara los objetos si es necesario
   if(this != &otra){
      // compara la dimension
      if(dimension != otra.dimension){
         iguales = false;
      }
      else{
         // compara valores
         for(int i=0; i < dimension && iguales; i++){
            for(int j=0; j < dimension && iguales; j++){
               if((*this)(i,j) != otra(i,j)){
                  iguales = false;
               }
            }
         }
      }
   }

   // devolver el flag
   return iguales;
}

/**
 * operador de multiplicacion
 * @param otra
 * @return
 */
Matriz Matriz::operator*(const Matriz & otra) const{
   // se crea la matriz resultado
   Matriz resultado(dimension);

   // algoritmo clasico de multiplicacion
   for(int i=0; i < dimension; i++){
      for(int j=0; j < dimension; j++){
         for(int k=0; k < dimension; k++){
            resultado(i,j) += (*this)(i,k)*otra(k,j);
         }
      }
   }

   // devuelve la matriz resultado
   return resultado;
}

/**
 * determina si el nodo origen tiene como unico sucesor
 * al nodo destino
 * @param origen
 * @param destino
 * @return
 */
bool Matriz::hijoUnico(int origen, int destino) const{
   // se obtienen los hijos de origen
   SecuenciaEnteros sucesoresOrigen = hijos(origen);

   // si hay uno solo y es del destino, devolver ok
   return sucesoresOrigen.obtenerTamanno() == 1 &&
            sucesoresOrigen[0] == destino;
}

/**
 * busca todos los nodos que tiene como hijo unico
 * al nodo pasado como argumento
 * @param destino
 * @return
 */
SecuenciaEnteros Matriz::hijoUnico(int destino) const{
   SecuenciaEnteros nodos;

   // se consideran todas las filas de la matriz
   for(int i=0; i < dimension; i++){
      if(hijoUnico(i, destino)){
         nodos += i;
      }
   }

   // se devuelve la secuencia
   return nodos;
}

/**
 * metodo para determinar los hijos del nodo pasado
 * como argumento
 * @param origen
 * @return
 */
SecuenciaEnteros Matriz::hijos(int origen) const{
   SecuenciaEnteros sucesores;

   // considera todos los nodos para comprobar si hay enlace
   // origen -> destino. En este caso, se incluye destino en
   // el vector a devolver
   for(int i=0; i < dimension; i++){
      if((*this)(origen, i) == 1){
         sucesores += i;
      }
   }

   // se devuelve la operaciones de hijos
   return sucesores;
}

/**
 * obtiene los padres de un nodo pasado como
 * argumento
 * @param destino
 * @return
 */
SecuenciaEnteros Matriz::padres(int destino) const{
   SecuenciaEnteros antecesores;

   // se consideran todos los nodos X tales que hay enlace desde
   // X hasta destino (X -> destino). En caso de ser asi, se agregan
   // a la lista de padres
   for(int i=0; i < dimension; i++){
      if((*this)(i, destino) == 1){
         antecesores += i;
      }
   }

   // se devuelve la lista de padres
   return antecesores;
}

/**
 * genera la matriz de alcanzabilidad a partir de la matriz
 * @param potencia el numero de multiplicaciones a realizar
 * @return
 */
Matriz Matriz::obtenerPotencia(int potencia){
   // se multiplica tantas veces como sea la dimension de la matriz
   // se hace copia de la matriz para no modificarla
   Matriz resultado(*this);
   cout << resultado << endl;
   for(int i=2; i <= potencia; i++){
      resultado = resultado * (*this);
   }

   // se devuelve la matriz resultado
   return resultado;
}

/**
 * elimina fila y columna de la matriz
 * @param fila
 * @param columna
 * @return
 */
Matriz & Matriz::eliminar(int fila, int columna){
   // se reserva espacio para nueva dimension
   int *nuevo = reservar(dimension-1);

   // se copian los valores que no correspondan ni a la
   // fila ni a la columna a borrar
   int in=0, jn =0;
   for(int i=0; i < dimension; i++){
      if(i != fila){
         for(int j=0; j < dimension; j++) {
            if (j != columna) {
               int indice = in*(dimension-1) + jn;
               nuevo[in*(dimension-1) + jn] = (*this)(i,j);
               // incrementa el contador de columnas en
               // la nueva matriz
               jn++;
            }
         }

         // incrementa el contador de filas en la nueva
         // matriz
         in++;

         // pone a 0 el contador de columnas de nuevo
         jn = 0;
      }
   }

   // redimension el valor de dimension
   dimension--;

   // libera el espacio previo
   liberar();

   // apunta al nuevo espacio
   matriz = nuevo;

   // se devuelve la referencia a this
   return *this;
}

/**
 * metodo para determinar si hay enlace entre dos nodos
 * @param origen
 * @param destino
 * @return
 */
bool Matriz::hayEnlace(int origen, int destino) const{
   return (*this)(origen, destino) == 1;
}

/**
 * operador de salida
 * @param flujo
 * @param matriz
 * @return
 */
std::ostream &operator<<(std::ostream &flujo, const Matriz &matriz) {
   // se vuelca al flujo la dimension
   flujo << "matriz de " << matriz.dimension << " X " << matriz.dimension << endl;

   // se vuelcan al flujo los valores
   for (int i = 0; i < matriz.dimension; i++) {
      for (int j = 0; j < matriz.dimension; j++) {
         flujo << matriz(i, j) << " ";
      }
      flujo << endl;
   }

   // se devuelve el flujo
   return flujo;
}

/**
 * metodo privado de reserva de espacio
 * @param dimension
 * @return 
 */
int *Matriz::reservar(int dimension) {
   // se reserva espacio para los datos de enlaces
   return new int[dimension * dimension];
}

/**
 * metodo privado para liberar espacio
 * @param dimension
 */
void Matriz::liberar() {
   if (matriz != 0) {
      // se borra el espacio de memoria
      delete[] matriz;

      // se hace cero el puntero
      matriz = 0;
   }
}

/**
 * metodo privado para calcular el desplazamiento en el array unidimensional
 * @param fila
 * @param columna
 * @return
 */
int Matriz::calcularIndice(int fila, int columna) const {
   // si i es distinto de cero, salta las filas necesarias
   return fila * dimension + columna;
}

