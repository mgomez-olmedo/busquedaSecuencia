#include<iostream>

#include "diagrama.h"

using namespace std;

/**
 * Constructor por defecto. El diagrama se inicializa con
 * todo vacio y se le van agregando elementos (nodos, enlaces,
 * etc)
 */
Diagrama::Diagrama() {
   nombre = "";
   numeroNodos = 0;
   listaIds = 0;
   variables = 0;
   nombres = 0;
   cardinalidades = 0;
   indiceNodoUtilidad = -1;
   matriz = 0;
}

/**
 * constructor de copia
 * @param origen
 */
Diagrama::Diagrama(const Diagrama &origen) {
   // se asigna el diagrama
   nombre = origen.nombre;

   // se asigna el numero de nodos
   numeroNodos = origen.numeroNodos;

   // se reserva espacio para la lista de ids, nombres, variables y
   // cardinalidades y se asignan
   listaIds = new int[numeroNodos];
   variables = new Variable[numeroNodos];
   nombres = new string[numeroNodos];
   cardinalidades = new int[numeroNodos];
   for (int i = 0; i < numeroNodos; i++) {
      listaIds[i] = origen.listaIds[i];
      variables[i] = origen.variables[i];
      nombres[i] = origen.nombres[i];
      cardinalidades[i] = origen.cardinalidades[i];
   }

   // se copia el indice del nodo de utilidad
   indiceNodoUtilidad = origen.indiceNodoUtilidad;

   // se copia la secuencia de operaciones
   solucion = origen.solucion;

   // se asigna la matriz a partir de copia de la de origen
   matriz = new Matriz(*origen.matriz);
}

/**
 * Destructor de la clase
 */
Diagrama::~Diagrama() {
   // se libera el espacio de memoria
   liberarEspacio();
}

/**
 * metodo para asignar la lista de variables del diagrama
 * @param lista
 * @param util
 */
void Diagrama::asignarVariables(Variable *lista, int util) {
   // asignar el numero de nodos
   numeroNodos = util;

   // se crea la lista de ids
   listaIds = new int[numeroNodos];

   // se crea la lista de variables
   variables = new Variable[util];

   // se crea la lista de cardinalidades
   cardinalidades = new int[util];

   // se crea la lista de nombres
   nombres = new string[util];

   // se recorre la lista de variables para ir asignando
   // los datos
   for (int i = 0; i < numeroNodos; i++) {
      variables[i] = lista[i];

      // si es el nodo de utilidad, almacena su indice para
      // facilitar el analisis posterior
      if (variables[i].obtenerTipo() == UTILIDAD) {
         indiceNodoUtilidad = i;
      }
      listaIds[i] = lista[i].obtenerId();
      nombres[i] = lista[i].obtenerNombre();
      cardinalidades[i] = lista[i].obtenerCardinalidad();
   }

   // ya se puede asignar la matriz
   matriz = new Matriz(numeroNodos);
}

/**
 * metodo para asignar enlace entre variables
 * @param variable1
 * @param variable2
 */
void Diagrama::asignarEnlace(const std::string &variable1, const std::string &variable2) {
   // se buscan los identificadores en la lista de ids
   int id1 = -1, id2 = -1;

   // busqueda del id de la primera variable
   bool encontrado = false;
   for (int i = 0; i < numeroNodos && !encontrado; i++) {
      if (nombres[i] == variable1) {
         id1 = i;
         encontrado = true;
      }
   }

   // busqueda del id de la segunda variable
   encontrado = false;
   for (int i = 0; i < numeroNodos && !encontrado; i++) {
      if (nombres[i] == variable2) {
         id2 = i;
         encontrado = true;
      }
   }

   // asigna un 1 en la fila de id1 y columna de id2
   asignarEnlace(id1, id2);
}

/**
 * devuelve el tamanno del diagrama tras calcularlo
 * @return
 */
double Diagrama::obtenerTamanno() const {
   double tamanno = 0.0;
   double tamVariable = 1;

   // considera todos los posibles enlaces
   for (int i = 0; i < numeroNodos; i++){
      // descarta el calculo sobre las variables de decision
      if(variables[i].obtenerTipo() != DECISION) {
         cout << "considerando variable " << variables[i].obtenerNombre() << endl;
         tamVariable = cardinalidades[i];
         if (tamVariable == 0) {
            tamVariable = 1;
         }
         cout << "tam de variable: " << tamVariable << endl;
         // se obtienen los antecesores del nodo i
         SecuenciaEnteros padresVar = padres(i);

         // considera las cardinalidades de cada uno de los padres
         for(int j=0; j < padresVar.obtenerTamanno(); j++){
            cout << "   considerando padre: " << variables[padresVar[j]].obtenerNombre() << endl;
            cout << "   cardinalidad: " << cardinalidades[padresVar[j]] << endl;
            tamVariable *= cardinalidades[padresVar[j]];
         }
         cout << "  a sumar: " << tamVariable << endl;
         tamanno += tamVariable;
      }
   }
   cout << "tam final de diagrama: " << tamanno << endl;
   cout << "fin de obtenerTamanno " << endl;
   // se devuelve el tamanno
   return tamanno;
}

/**
 * operador de asignacion
 * @param origen
 * @return
 */
Diagrama &Diagrama::operator=(const Diagrama &origen) {
   // se libera todo el espacio previamente usado
   liberarEspacio();

   // se asigna el diagrama
   nombre = origen.nombre;

   // se asigna el numero de nodos
   numeroNodos = origen.numeroNodos;

   // se reserva espacio para la lista de ids, nombres, variables y
   // cardinalidades y se asignan
   listaIds = new int[numeroNodos];
   variables = new Variable[numeroNodos];
   nombres = new string[numeroNodos];
   cardinalidades = new int[numeroNodos];
   for (int i = 0; i < numeroNodos; i++) {
      listaIds[i] = origen.listaIds[i];
      variables[i] = origen.variables[i];
      nombres[i] = origen.nombres[i];
      cardinalidades[i] = origen.cardinalidades[i];
   }

   // se asigna el indice del nodo de utilidad
   indiceNodoUtilidad = origen.indiceNodoUtilidad;

   // se copian la secuencia de operaciones
   solucion = origen.solucion;

   // se asigna la matriz a partir de copia de la de origen
   matriz = new Matriz(*origen.matriz);

   // se devuelve referencia a this
   return *this;
}

/**
 * operador de comparacion (que la matriz sea igual)
 * @param otro
 * @return
 */
bool Diagrama::operator==(const Diagrama & otro) const{
   // basta con mostrarDiferencias la igualdad de las matrices
   return (*matriz) == (*otro.matriz);
}

/**
 * operador de salida
 * @param flujo
 * @param diagrama
 * @return
 */
std::ostream &operator<<(std::ostream &flujo, const Diagrama &diagrama) {
   // se vuelcan al flujo los datos generales
   flujo << "diagrama " << diagrama.nombre << " nodos: " << diagrama.numeroNodos << endl;

   // se muestra la informacion de las variables
   flujo << " ------- variables -------------" << endl;
   for (int i = 0; i < diagrama.numeroNodos; i++) {
      flujo << diagrama.variables[i] << endl;
   }

   flujo << " ------- matriz accesibilidad ----------" << endl;
   flujo << (*diagrama.matriz);

   flujo << "-------- relacion de enlaces -----------" << endl;
   for (int i = 0; i < diagrama.numeroNodos; i++) {
      for (int j = 0; j < diagrama.numeroNodos; j++) {
         if ((*diagrama.matriz)(i, j) == 1) {
            flujo << "   " << diagrama.nombres[i] << " -> " << diagrama.nombres[j] << endl;
         }
      }
   }

   // se muestra la secuencia de operaciones para evauluar el diagrama
   flujo << "------------- secuencia de operaciones ---------------" << endl;
   flujo << diagrama.solucion;

   // se muestra el tamanno del diagrama
   flujo << "tam: " << diagrama.obtenerTamanno() << endl;

   // se devuelve el flujo
   return flujo;
}

/**
 * metodo privado para liberar espacio
 */
void Diagrama::liberarEspacio() {
   if (variables != 0) {
      delete[] variables;
   }

   if (listaIds != 0) {
      delete[] listaIds;
   }

   if (nombres != 0) {
      delete[] nombres;
   }

   if (cardinalidades != 0) {
      delete[] cardinalidades;
   }

   if (matriz != 0) {
      delete matriz;
   }

   // asignar punteros a 0
   variables = 0;
   listaIds = 0;
   nombres = 0;
   cardinalidades = 0;
   matriz = 0;
}

/**
 * se obtiene el identificador asociado a una variable
 * @param nombre
 * @return
 */
int Diagrama::buscarIdVariable(std::string nombre) const{
   int id=-1;

   // se recorren las variables, una a una
   for(int i=0; i < numeroNodos && id == -1; i++){
      if(variables[i].obtenerNombre() == nombre){
         id = i;
      }
   }

   // se devuelve el id
   return id;
}

/**
 * metodo para recuperar los nodos de de un determinado
 * tipo pasado como argumento
 * @param tipo
 * @return
 */
SecuenciaEnteros Diagrama::obtenerNodos(TIPOVARIABLE tipo) const {
   // se crea la operaciones
   SecuenciaEnteros nodos;

   // se consideran los nodos del diagrama
   for (int i = 0; i < numeroNodos; i++) {
      if (variables[i].obtenerTipo() == tipo) {
         nodos += i;
      }
   }

   // se devuelve la operaciones
   return nodos;
}

/**
 * busca los hijos de un nodo que sean de un tipo
 * determinado
 * @param id
 * @param tipo
 * @return
 */
SecuenciaEnteros Diagrama::obtenerHijos(int id, TIPOVARIABLE tipo) const {
   SecuenciaEnteros sucesores;

   // se consideran todos los nodos
   for (int i = 0; i < numeroNodos; i++) {
      if (variables[i].obtenerTipo() == tipo && comprobarEnlace(id, i) == true) {
         sucesores += i;
      }
   }

   // se devuelven los hijos
   return sucesores;
}

/**
 * busca los padres de un nodo, que sean a su vez
 * de un determinado tipo
 * @param id
 * @param tipo
 * @return
 */
SecuenciaEnteros Diagrama::obtenerPadres(int id, TIPOVARIABLE tipo) const {
   SecuenciaEnteros antecesores;

   // se consideran todos los nodos
   for (int i = 0; i < numeroNodos; i++) {
      if (variables[i].obtenerTipo() == tipo && comprobarEnlace(i, id) == true) {
         antecesores += i;
      }
   }

   // se devuelve la lista de padres
   return antecesores;
}

/**
 * busca los padres de un nodo
 * @param id
 * @param tipo
 * @return
 */
SecuenciaEnteros Diagrama::obtenerPadres(int id) const {
   SecuenciaEnteros antecesores;

   // se consideran todos los nodos
   for (int i = 0; i < numeroNodos; i++) {
      if (comprobarEnlace(i, id) == true) {
         antecesores += i;
      }
   }

   // se devuelve la lista de padres
   return antecesores;
}

/**
 * obtiene los padres de un nodo que no formen parte de la coleccion
 * de prohibidos
 * @param id
 * @param prohibidos
 * @return
 */
SecuenciaEnteros Diagrama::obtenerNuevosPadres(int id, std::vector<SecuenciaEnteros> prohibidos) const{
   SecuenciaEnteros padres;

   // se buscan los padres del nodo pasado como argumento, que no esten
   // la prohibidos
   for(int i=0; i < numeroNodos; i++){
      if(comprobarEnlace(i, id) == true){
         // se comprueba que no esta en ningunas de las secuencias de prohubidos
         bool valido = true;
         for(int j=0; j < prohibidos.size() && valido; j++){
            valido = !prohibidos.at(j).contiene(i);
         }

         // si es valido, se agrega
         if(valido){
            padres += i;
         }
      }
   }

   // se devuelve la secuencia de padres
   return padres;
}

/**
 * Determina si existe un unico camino entre dos nodos
 * @param id1 id del primer nodo
 * @param id2 id del segundo nodo
 * @return
 */
bool Diagrama::caminoUnico(int id1, int id2) const{
   // hay que generar potencias de hasta dimension
   bool unico = false;
   if((*matriz)(id1, id2) == 1){
      unico = true;
      // se generan las potencias
      for(int i=2; i <= numeroNodos && unico; i++){
         Matriz potencia = matriz->obtenerPotencia(i);
         cout << "calculo de matriz potencia: " << i << endl;
         cout << potencia << endl;
         cout << "comprobando caminos para " << id1 << " - " << id2 << endl;
         cout << "valor en matriz potencia " << i << " : " << potencia(id1, id2) << endl;
         if(potencia(id1, id2) != 0){
            unico = false;
         }
      }
   }

   // devuelve el valor de unico
   return unico;
}

/**
 * determina las variables de azar que no tienen ninguna decision como
 * hijo
 * @return
 */
SecuenciaEnteros Diagrama::variablesNoInformativas() const{
   SecuenciaEnteros resultado;

   for(int i=0; i < numeroNodos; i++){
      if(variables[i].obtenerTipo() == AZAR){
         // determina sus hijos
         SecuenciaEnteros hijosVariable = hijos(i);

         // se comprueba que no tenga decisiones como nodos hijo
         bool valido = true;
         for(int j=0; j < hijosVariable.obtenerTamanno() && valido; j++){
            if(variables[hijosVariable[j]].obtenerTipo() == DECISION){
               valido = false;
            }
         }

         // si se llega aqui con el flag valido, entonces se introduce
         // en resultado
         if(valido){
            resultado += i;
         }
      }
   }

   // se devuelve el resultado
   return resultado;
}

/**
 * metodo para determinar los nodos de azar candidatos a
 * eliminacion
 * @return
 */
SecuenciaEnteros Diagrama::determinarCandidatosAzar() const {
   // se obtienen los nodos de azar
   SecuenciaEnteros nodosAzar = obtenerNodos(AZAR);
   SecuenciaEnteros candidatos;

   // se busca entre los nodos de azar los que cumplen la
   // condicion indicada
   for (int i = 0; i < nodosAzar.obtenerTamanno(); i++) {
      // determina si tiene como sucesor unico al nodo de utilidad
      if (hijoUnico(nodosAzar[i], indiceNodoUtilidad)) {
         candidatos += nodosAzar[i];
      }
   }

   // se devuelve la operaciones de candidatos
   return candidatos;
}

/**
 * determina el nodo de decision candidato a ser eliminado
 * @return
 */
SecuenciaEnteros Diagrama::determinarCandidatosDecision() const {
   // operaciones a devolver
   SecuenciaEnteros candidatos;

   // se obtienen los nodos de decision
   SecuenciaEnteros nodosDecision = obtenerNodos(DECISION);

   // se determina cual cumple la condicion para ser eliminado:
   // es antecesor del nodo de valor y todos sus padres
   // tambien lo son del nodo de valor
   for (int i = 0; i < nodosDecision.obtenerTamanno(); i++) {
      // se comprueba que sea antecesor del nodo de utilidad
      if (comprobarEnlace(nodosDecision[i], indiceNodoUtilidad) == true) {
         // ninguno de sus hijos puede ser un nodo de decision
         SecuenciaEnteros hijosVar = hijos(nodosDecision[i]);

         // se comprueba la lista de hijos para descartar otros nodos
         // de decision como sucesores
         bool hijoDecision = false;
         for(int j=0; j < hijosVar.obtenerTamanno() && !hijoDecision; j++){
            if(variables[hijosVar[j]].obtenerTipo() == DECISION){
               hijoDecision = true;
            }
         }

         // continua analizando si no hay hijos de decision
         if(!hijoDecision) {
            // se consideran los padres del nodo de decision en
            // posicion i
            SecuenciaEnteros antecesores = padres(nodosDecision[i]);

            // todos ellos deben ser padres del nodo de utilidad
            bool todos = true;
            for (int j = 0; j < antecesores.obtenerTamanno() && todos; j++) {
               if (comprobarEnlace(antecesores[j], indiceNodoUtilidad) == false) {
                  todos = false;
               }
            }

            // si se llega aqui con flag todosa valor verdadero, se inserta
            // en la lista de candidatos
            if (todos) {
               candidatos += nodosDecision[i];
            }
         }
      }
   }

   // se devuelve la operaciones de candidatos
   return candidatos;
}

/**
 * determina las operaciones candidatas para inversion de
 * arcos
 * @return
 */
vector<OpcionInversion> Diagrama::determinarCandidatosInversion() const {
   // se crea un vector en que almacenar las opciones
   vector<OpcionInversion> opciones;

   // se buscan los nodos de azar que sean padres del nodo
   // de utilidad
   SecuenciaEnteros padres = obtenerPadres(indiceNodoUtilidad, AZAR);
   cout << " padres del nodo de valor candidatos de inversion: " << padres << endl;

   SecuenciaEnteros padresAux = padres;

   for (int i = 0; i < padresAux.obtenerTamanno(); i++){
       // ninguno de sus hijos puede ser un nodo de decision
       SecuenciaEnteros hijosVar = hijos(padresAux[i]);

       // se comprueba la lista de hijos para descartar otros nodos
       // de decision como sucesores
       bool hijoDecision = false;
       for(int j=0; j < hijosVar.obtenerTamanno() && !hijoDecision; j++){
           if(variables[hijosVar[j]].obtenerTipo() == DECISION){
               hijoDecision = true;
           }
       }

       // si el nodo azar tiene como hijo un nodo decisión se descarta de la lista
       // de padres del nodo utilidad
       if(hijoDecision){
           padres -= padresAux[i];
       }
   }

   // para cada uno de ellos se obtienen sus padres de tipo
   // AZAR, que determinan las inversiones a realizar
   for (int i = 0; i < padres.obtenerTamanno(); i++) {
      SecuenciaEnteros sucesoresAzar = obtenerHijos(padres[i], AZAR);

      // si hay hijos de azar, se crea la opcion de inversion
      // correspondiente
      if (sucesoresAzar.obtenerTamanno() != 0) {
         // se inserta el objetivo
         OpcionInversion opcion(padres[i]);

         // se agregan las variables con las que habria que invertir
         for (int j = 0; j < sucesoresAzar.obtenerTamanno(); j++) {
            // se determina si hay un unico camino entre padres[i]
            // y sucesores[j]
            cout << " a probar camino unico entre " << padres[i] << " y " << sucesoresAzar[j] << endl;
            bool unico = caminoUnico(padres[i], sucesoresAzar[j]);
            cout << " camino unico entre : " << padres[i] << " y " << sucesoresAzar[j] << " : " << unico << endl;

            // hace falta que haya un unico camino en la matriz de alcanzabilidad
            // desde padres[i] hasta sucesores[j]
            if(unico) {
               opcion += sucesoresAzar[j];
            }
         }
         // se agrega la opcion al vector de opciones
         opciones.push_back(opcion);
      }
   }

   // se devuelve el vector de opciones
   return opciones;
}


/**
 * metodo para eliminar un nodo de azar. Se modifica this
 * @param idNodo
 */
void Diagrama::eliminarNodoAzar(int idNodo) {
   // se obtienen los padresVar de idNodo
   SecuenciaEnteros padresVar = padres(idNodo);

   // se establecen los enlaces entre los padresVar y el
   // nodo de utilidad
   for (int i = 0; i < padresVar.obtenerTamanno(); i++) {
      // se usa el metodo privado para almacenar la informacion
      // de un enlace a partir de los ids de los nodos
      asignarEnlace(padresVar[i], indiceNodoUtilidad);
   }

   // se almacena el nombre de la variable a eliminar
   string nombreVariable = variables[idNodo].obtenerNombre();

   // se borran de la matriz la fila y columna correspondientes al
   // nodo eliminado. Todas operaciones necesarias para quitar la
   // informacion de un nodo se delega en el metodo privado eliminarNodo
   eliminarNodo(idNodo);

   // se agrega la operacion  de eliminacion
   Operacion operacion(BORRADO, obtenerTamanno(), nombreVariable);

   // se almacena en la solucion
   solucion += operacion;
}

/**
 * metodo para eliminar un nodo de decision. Se modifica this
 * @param idNodo
 */
void Diagrama::eliminarNodoDecision(int idNodo) {
   // se almacena el nombre de la variable a borrar
   string nombreVariable = variables[idNodo].obtenerNombre();

   // se borran de la matriz la fila y columna correspondientes al
   // nodo eliminado. Todas operaciones necesarias para quitar la
   // informacion de un nodo se delega en el metodo privado eliminarNodo
   eliminarNodo(idNodo);

   // se agrega la operacion  de eliminacion
   Operacion operacion(BORRADO, obtenerTamanno(), nombreVariable);

   // se agrega a la lista de operaciones
   solucion += operacion;
}

/**
 * metodo para inversion de arco entre nodo origen y destino
 * @param idOrigen
 * @param idDestino
 */
void Diagrama::invertir(int idOrigen, int idDestino) {
   // se buscan los padres del origen y se agregan a destino
   SecuenciaEnteros padresAzarOrigen = obtenerPadres(idOrigen, AZAR);
   SecuenciaEnteros padresDecisionOrigen = obtenerPadres(idOrigen, DECISION);

   // se unen ambas secuencias
   SecuenciaEnteros padresOrigen = padresAzarOrigen += padresDecisionOrigen;

   // se buscan los padres del destino
   SecuenciaEnteros padresAzarDestino = obtenerPadres(idDestino, AZAR);
   SecuenciaEnteros padresDecisionDestino = obtenerPadres(idDestino, DECISION);

   // se unen ambas secuencias
   SecuenciaEnteros padresDestino = padresAzarDestino += padresDecisionDestino;

   // se hace que los padres del origen sean padres del destino
   for(int i=0; i < padresOrigen.obtenerTamanno(); i++){
      asignarEnlace(padresOrigen[i], idDestino);
   }

   // se hace que los padres del destino sean padres del origen
   for(int i=0; i < padresDestino.obtenerTamanno(); i++){
      // se evita enlace de nodo a si mismo
      if(padresDestino[i] != idOrigen) {
         asignarEnlace(padresDestino[i], idOrigen);
      }
   }

   // se establece enlace desde destino a origen para representar
   // la inversion
   asignarEnlace(idDestino, idOrigen);

   // se borra el enlace entre origen y destino
   borrarEnlace(idOrigen, idDestino);

   // se almacena la operacion en la lista solucion
   Operacion inversion(INVERSION, obtenerTamanno(), variables[idOrigen].obtenerNombre(),
                       variables[idDestino].obtenerNombre());

   // se agrega a la secuencia de operaciones
   solucion += inversion;
}

/**
 * metodo para ejecutar sobre el diagrama una secuencia de operaciones
 * de invsersion, junto con la eliminacion del nodo de azar asociado
 * @param opcion
 */
void Diagrama::invertirEliminar(const OpcionInversion & opcion){
   // se realiza cada una de las inversiones indicadas
   for(int i=0; i < opcion.obtenerTamanno(); i++){
      // se realiza la inversion
      invertir(opcion.obtenerIdObjetivo(), opcion[i]);
   }
   inversionesRealizadas.push_back(opcion);
}


/**
 * metodo para agregar arcos de memoria
 */
void Diagrama::agregarArcosMemoria() {
   // se obtiene en primer lugar e
   // se obtiene la lista de decisiones
   SecuenciaEnteros decisiones = ordenDecisiones();

   // se consideran las decisiones una a una (no hace falta
   // ningun tratamiento con la ultima)
   for (int i = 0; i < decisiones.obtenerTamanno() - 1; i++) {

      // se obtienen los padres de la decision
      SecuenciaEnteros antecesores = padres(decisiones[i]);

      // se hace que estos padres sean tambien antecesores del resto
      // de decisiones
      for (int j = i + 1; j < decisiones.obtenerTamanno(); j++) {
         for (int k = 0; k < antecesores.obtenerTamanno(); k++) {
            asignarEnlace(antecesores[k], decisiones[j]);
         }
      }
   }
}

/**
 * metodo para evaluarKong el diagrama usando el criterio de kong
 * (elegir la operacion de menor coste)
 */
void Diagrama::evaluarKong() {
   // se agrega una primera operacion nula al diagrama para que
   // figure el tam. inicial del diagrama
   Operacion inicial(NULA, obtenerTamanno(), "", "");

   // se agrega a la secuencia
   solucion += inicial;
   cout << "evaluaKong: solucion inicial: " << solucion << endl;

   // se van eliminando nodos hasta que solo quede el nodo
   // de utilidad
   while (numeroNodos > 1) {
      // se eliminan sumideros en primer lugar
      eliminarSumideros();

      // se buscan candidatos de nodos de azar a eliminar
      SecuenciaEnteros azar = determinarCandidatosAzar();
      cout << " nodos de azar para eliminar: " << azar << endl;

      // si hay nodos de azar a eliminar, se procede a
      // buscar la mejor alternativa segun Kong y se ejecuta
      if (azar.obtenerTamanno() != 0) {
         // se busca la mejor alternativa
         int mejor = seleccionarMejorOpcionKong(azar, AZAR);

         // se ejecuta la operacion y se prosigue la evaluacion
         eliminarNodoAzar(azar[mejor]);
      }
      else {
         // se buscan nodos de decision a procesar
         SecuenciaEnteros decision = determinarCandidatosDecision();
         cout << " nodos de decision para eliminar: " << decision << endl;

         // si hay nodo de decision a eliminar, se procede a
         // buscar la mejor alternativa y se ejecuta
         if (decision.obtenerTamanno() != 0) {
            int mejor = seleccionarMejorOpcionKong(decision, DECISION);

            // se realiza la operacion y se prosigue
            eliminarNodoDecision(decision[mejor]);
         }
         else {
            // debe haber nodos de azar susceptibles de ser eliminados
            // despues de invertir arcos
            vector<OpcionInversion> opciones = determinarCandidatosInversion();
            cout << " obteniendo inversiones posibles" << endl;
            if (opciones.size() != 0){
                // se selecciona la mejor alternativa si es necesario
                OpcionInversion mejor = seleccionarMejorOpcionInversionKong(opciones);
                cout << "-----------------------------------------" << endl;
                cout << " opcion de inversion: " << mejor << endl;
                cout << "-----------------------------------------" << endl;

                // se realizan las inversiones y la eliminacion del nodo
                // de azar correspondiente
                invertirEliminar(mejor);
            }
         }
      }
   }
   cout << "diagrama.cpp - fin evaluacion de kong" << endl;
   cout << solucion;
   cout << "diagrama.cpp ---- fin evaluarKong" << endl;
}

/**
 * determina las operaciones posibles a realizar sobre un
 * diagrama
 * @return
 */
SecuenciaOperaciones Diagrama::determinarOperaciones(){
   SecuenciaOperaciones  candidatas;

   // se determina si hay candidatos e eliminacion de nodos de azar
   SecuenciaEnteros nodos = determinarCandidatosAzar();

   // si no hay ningun candidato, se buscan decisiones
   if(nodos.obtenerTamanno() == 0){
      nodos = determinarCandidatosDecision();
   }

   // si se obtuvieron candidatos, se compone la secuencia a devolver
   if(nodos.obtenerTamanno() != 0){
      for(int i = 0; i < nodos.obtenerTamanno(); i++){
         // se crea operacion de borrado. De momento no se asigna coste
         Operacion nueva(BORRADO, 0, variables[nodos[i]].obtenerNombre(), "");
         candidatas += nueva;
      }
   }
   else{
      // se buscan candidaturas de inversion
      vector<OpcionInversion> inversiones = determinarCandidatosInversion();

      // para cada una de ellas se crea la operacion correspondiente
      for(int i=0; i < inversiones.size(); i++){
         int nodoBase = inversiones.at(i).obtenerIdObjetivo();
         for(int j=0; j < inversiones.at(i).obtenerTamanno(); j++){
            // se crea la operacion
            Operacion nueva = Operacion(INVERSION, 0, variables[nodoBase].obtenerNombre(),
                                        variables[inversiones.at(i)[j]].obtenerNombre());

            // se agrega a la lista de candidaturas
            candidatas += nueva;
         }
      }
   }

   // se devuelve la lista completa de operaciones candidatas
   return candidatas;
}

/**
 * ordena las decisiones segun su orden topologico
 * @return
 */
SecuenciaEnteros Diagrama::ordenDecisiones() const {
   SecuenciaEnteros decisiones;
   int contadorDecisiones = numeroDecisiones();

   // se busca la ultima decision
   decisiones += ultimaDecision();
   cout << "decisiones tras agregar la ultima...." << decisiones << endl;

   // mientras queden decisiones por aagregar
   while(decisiones.obtenerTamanno() != contadorDecisiones){
      // se busca el indice de la decision que puede tener
      // como hijos las decisiones ya consideradas
      decisiones += decisionAntecesoraDe(decisiones);
   }

   // se devuelve la secuencia de decisiones, una vez invertida
   decisiones.invertir();
   return decisiones;
}

/**
 * determina el orden parcial de borrado de nodos
 * @return
 */
std::vector<SecuenciaEnteros> Diagrama::ordenParcialBorrado() const{
   // se crea la estructura para la ordenacion
   vector<SecuenciaEnteros> ordenParcial;

   // se determina el orden de las decisiones
   SecuenciaEnteros decisiones = ordenDecisiones();

   // se buscan los nodos que son padres de la primera de
   // las decisiones. Estaran en la lista de variables que
   // se eliminan tras el borrado de primera de las decisiones
   // (en orden temporal)
   ordenParcial.push_back(obtenerPadres(decisiones[0]));

   // se agrega una secuencia con la primera decision
   SecuenciaEnteros ordenDecision;
   ordenDecision += decisiones[0];
   ordenParcial.push_back(ordenDecision);
   cout << "obtenido conjunto de variables antecesores de primera decision" << endl;

   // se tratan las decisiones siguientes
   for(int i=1; i < decisiones.obtenerTamanno(); i++){
      // se buscan los padres de la decision que corresponde con
      // la condicion de no estar en los conjuntos de variables ya
      // determinados
      cout << "procesando decision: " << variables[decisiones[i]].obtenerNombre() << endl;
      ordenParcial.push_back(obtenerNuevosPadres(decisiones[i], ordenParcial));
      cout << "finalizado procesamiento de decision....." << endl;
      SecuenciaEnteros ordenDecision;
      ordenDecision += decisiones[i];
      ordenParcial.push_back(ordenDecision);
   }

   // ahora se agregan el resto de nodos que no son padres de ninguna
   // de las decisiones
   cout << "obteniendo variables no informativas...." << endl;
   ordenParcial.push_back(variablesNoInformativas());

   // se devuelve el orden parcial
   return ordenParcial;
}

/**
 * determina la decision antecesora de las decisiones pasadas
 * como argumento
 * @param decisiones
 * @return
 */
int Diagrama::decisionAntecesoraDe(SecuenciaEnteros decisiones) const{
   bool encontrada = false;
   int indiceSiguiente = -1;
   for(int i=0; i < numeroNodos && !encontrada; i++){
      if(decisiones.contiene(i) == false && variables[i].obtenerTipo() == DECISION){
         // se obtienen los hijos
         SecuenciaEnteros hijosDecision = hijos(i);

         bool hijosValidos = true;
         for(int j=0; j < hijosDecision.obtenerTamanno() && hijosValidos; j++){
            if(variables[hijosDecision[j]].obtenerTipo() == DECISION &&
               !decisiones.contiene(hijosDecision[j])){
               hijosValidos = false;
            }
         }

         // si se llega aqui con hijosValidos = true, se ha localizado
         // la decision de interes
         if(hijosValidos == true){
            encontrada = true;
            indiceSiguiente = i;
         }
      }
   }

   // se devuelve indiceSiguiente
   return indiceSiguiente;
}

/**
 * localiza la ultima decision en segun el orden de borrado, es
 * decir, en el orden temporal (la que solo tiene como sucesor
 * al nodo de utilidad)
 * @return
 */
int Diagrama::ultimaDecision() const{
   bool encontrado = false;
   int indiceDecision = -1;
   for(int i=0; i < numeroNodos && !encontrado; i++){
      // solo se analizan nodos de decision
      if(variables[i].obtenerTipo() == DECISION){
         // se obtienen los hijos
         SecuenciaEnteros hijosDecision = hijos(i);

         // se comprueba si en los hijos hay algun nodo de decision
         bool decisionUltima = true;
         for(int j=0; j < hijosDecision.obtenerTamanno() && decisionUltima; j++){
            if(variables[hijosDecision[j]].obtenerTipo() == DECISION){
               // no es la decision buscada
               decisionUltima = false;
            }
         }

         // si se llega aqui con decisionUltima = true, entonces
         // es el nodo buscado
         if(decisionUltima == true){
            encontrado=true;
            indiceDecision = i;
         }
      }
   }

   // se devuelve el valor de indice de la decision
   return indiceDecision;
}

/**
 * cuenta el numero de decisiones presentes en el diagrama
 * @return
 */
int Diagrama::numeroDecisiones() const{
   int numeroDecisiones = 0;
   for(int i=0; i < numeroNodos; i++){
      if(variables[i].obtenerTipo() == DECISION){
         numeroDecisiones++;
      }
   }

   // devuelve el numero de decisiones
   return numeroDecisiones;
}


/**
 * metodo para simplificar el diagrama con el objeto de calcular
 * heuristicas de evaluacion. Para ello se eliminan los arcos de
 * decision del modelo: si una variable X es padre de una decision
 * D_i entonces ya no sera padre de D_(i+1), etc
 */
void Diagrama::relajar(){
   // de determina el orden de las decisiones
   SecuenciaEnteros decisiones = ordenDecisiones();
   cout << "orden de las decisiones: ";
   for(int i=0; i < decisiones.obtenerTamanno(); i++){
      cout << variables[decisiones[i]].obtenerNombre() << " ";
   }
   cout << endl;

   // se considera cada decision y se eliminan los padres
   // de ella al resto de decisiones
   for(int i=0; i < decisiones.obtenerTamanno(); i++){
      // se determinan los padresVar de la decision considerada
      SecuenciaEnteros padresVar = padres(decisiones[i]);

      // se elimina el enlace entre cada padre y el resto
      // de decisiones, si fuera necesario
      for(int j=0; j < padresVar.obtenerTamanno(); j++){
         // se considera cada una de las restantes decisiones
         for(int k=i+1; k < decisiones.obtenerTamanno(); k++){
            // se elimina el enlace entre padresVar[j] y decisiones[k]
            cout << "  borrando enlace entre " << variables[padresVar[j]].obtenerNombre() <<
            " y " << variables[decisiones[k]].obtenerNombre() << endl;
            borrarEnlace(padresVar[j], decisiones[k]);
         }
      }
   }

   // se eliminan tambien los enlaces entre decisiones
   eliminarEnlacesDecisiones();
}

/**
 * metodo de eliminacion de sumideros
 */
void Diagrama::eliminarSumideros(){
   SecuenciaEnteros sumideros;

   // determina los nodos que de azar o decision que no tienen
   // sucesores
   for(int i=0; i < numeroNodos; i++){
      if(variables[i].obtenerTipo() != UTILIDAD){
         // determina el conjunto de hijosVar
         SecuenciaEnteros hijosVar = hijos(i);

         // si no hay hijosVar, agrega a sumideros
         if(hijosVar.obtenerTamanno() == 0){
            sumideros += i;
         }
      }
   }

   // una vez determinados, basta con eliminarlos
   for(int i=0; i < sumideros.obtenerTamanno(); i++){
      eliminarNodo(i);
   }
}

/**
 * elimina los enlaces entre las decisiones
 */
void Diagrama::eliminarEnlacesDecisiones(){
   // se consideran las decisiones y se eliminan los enlaces entre
   // ellas
   SecuenciaEnteros decisiones = ordenDecisiones();

   for(int i=0; i < decisiones.obtenerTamanno()-1; i++){
      if(comprobarEnlace(decisiones[i], decisiones[i+1])){
         borrarEnlace(decisiones[i], decisiones[i+1]);
      }
   }
}


/**
 * metodo para eliminar toda la informacion de un nodo
 * @param idNodo
 */
void Diagrama::eliminarNodo(int idNodo) {
    if(variables[idNodo].obtenerTipo() == AZAR){
        // se obtienen los padres de idNodo
        SecuenciaEnteros padresIdNodo = padres(idNodo);

        // se establecen los enlaces entre los padresIdNodo y el
        // nodo de utilidad
        for (int i = 0; i < padresIdNodo.obtenerTamanno(); i++){
            // se usa un método privado para almacenar la información
            // de un enlace a partir de los ids de los nodos
            asignarEnlace(padresIdNodo[i], indiceNodoUtilidad);
        }
    }

   // se elimina toda la informacion del nodo indicado
   int *nuevaListaIds = new int[numeroNodos - 1];
   Variable *nuevaVaribles = new Variable[numeroNodos - 1];
   string *nuevaNombres = new string[numeroNodos - 1];
   int *nuevaCardinalidades = new int[numeroNodos - 1];

   // se asigna la informacion
   for (int i = 0, in = 0; i < numeroNodos; i++) {
      if (i != idNodo) {
         // se copian los datos
         nuevaListaIds[in] = listaIds[i];
         nuevaVaribles[in] = variables[i];
         nuevaNombres[in] = nombres[i];
         nuevaCardinalidades[in] = cardinalidades[i];

         // se incrementa el valor de in
         in++;
      }
   }

   // se borra el espacio previo
   delete[] listaIds;
   delete[] variables;
   delete[] nombres;
   delete[] cardinalidades;

   // se apuntan los punteros originales al nuevo espacio
   listaIds = nuevaListaIds;
   variables = nuevaVaribles;
   nombres = nuevaNombres;
   cardinalidades = nuevaCardinalidades;

   // se borra de la matriz las filas y columnas de idNodo
   matriz->eliminar(idNodo, idNodo);

   // se cambia el valor de indiceNodoUtilidad si hace falta
   if (indiceNodoUtilidad > idNodo) {
      indiceNodoUtilidad--;
   }

   // se reduce el numero de nodos
   numeroNodos--;
}

/**
 * selecciona la mejor opcion posible mediante la heuristica de Kong
 * @param opciones
 * @param operacion
 * @return
 */
int Diagrama::seleccionarMejorOpcionKong(SecuenciaEnteros opciones, TIPOVARIABLE operacion) const {
   // se crea la operaciones de diagramas para probar cada una
   // de las operaciones
   // solo se ejecuta en realidad si hay mas de una opcion. En caso de haber
   // solo una, se devuelve
   int indiceMejor = 0;

   if(opciones.obtenerTamanno() > 1) {
      Diagrama *diagramas = new Diagrama[opciones.obtenerTamanno()];
      double *costes = new double[opciones.obtenerTamanno()];

      // cada una de las operaciones se realiza sobre su copia
      for (int i = 0; i < opciones.obtenerTamanno(); i++) {
         // se crea copia del diagrama
         diagramas[i] = *this;
         switch (operacion) {
            case AZAR: // se realiza la operacion sobre el diagrama correspondiente
               diagramas[i].eliminarNodoAzar(opciones[i]);
               break;
            case DECISION: // se realiza la operacion sobre el diagrama
               diagramas[i].eliminarNodoDecision(opciones[i]);
               break;
            default:
               // presenta el mensaje de error
               presentarErrores("diagrama.cpp", "seleccionarMejorOpcionKong",
                                "realizacion erronea de operacion");
         }

         // se calcula el coste asociado
         costes[i] = diagramas[i].obtenerTamanno();
      }

      // se libera la memoria usada
      delete[] diagramas;
      delete[] costes;

      // se selecciona la de menor coste
      indiceMejor = buscarMinimo(costes, opciones.obtenerTamanno());
   }

   // se devuelve el indice mejor
   return indiceMejor;
}

/**
 * metodo de seleccion de la mejor opcion de inversion. Aunque haya una
 * sola opcion, debe ejecutarse el metodo para determinar el orden de
 * las inversiones
 * @param opciones vector con los ids de las variables de azar sobre las
 * que realizar las invsersiones
 * @return
 */
OpcionInversion Diagrama::seleccionarMejorOpcionInversionKong(const std::vector<OpcionInversion> &opciones) {
   OpcionInversion opcionMinimo;
   int size = opciones.size();
   bool encontrado = false;
   if (size != 0){
       // se crean las operaciones de diagramas para cada una de las alternativas
       double *costes = new double[size];
       OpcionInversion *opcionesKong = new OpcionInversion[size];

       // se realizan las diferentes alternativas
       for (int i = 0; i < size; i++) {
           opcionesKong[i] = evaluarInversionKong(opciones[i]);
           costes[i] = opcionesKong[i].obtenerCoste();
           cout << "  evaluada inversion con " << opcionesKong[i] << " coste: " << costes[i] << endl;
       }

       // se obtiene el minimo
       int minimo = buscarMinimo(costes, size);
       cout << " minimo coste: " << minimo << endl;

       // se selecciona la mejor opcion de inversion
       opcionMinimo = opcionesKong[minimo];

       if(size > 1){
           // se comprueba si la mejor opción ya ha sido invertida de manera contrapuesta,
           // en ese caso, el flag encontrado se pone a true
           for(int i = 0; i < inversionesRealizadas.size() && !encontrado; i++){
               if(inversionesRealizadas[i][0] == opcionMinimo.obtenerIdObjetivo() &&
                  inversionesRealizadas[i].obtenerIdObjetivo() == opcionMinimo[0]){
                   encontrado = true;
               }
           }

           if(encontrado){
               vector<int> opcionesYaInvertidas;
               bool longevaEncontrada = false;
               bool todasInvertidas = true;
               bool found = false;
               int opcionLongeva;
               // comprobamos cuantas opciones ya han sido tomadas como inversión:
               // - en caso de que todas hayan sido ya tomadas de manera contrapuesta como inversión se escoge la menos reciente
               // - si esto por lo contrario no ocurre, se eliminan las opciones ya tomadas y se hace el mínimo sobre las restantes
               for(int i = 0; i < size; i++){
                   for(int j = 0; j < inversionesRealizadas.size() && !found; j++){
                       if(inversionesRealizadas[j][0] == opcionesKong[i].obtenerIdObjetivo() &&
                          inversionesRealizadas[j].obtenerIdObjetivo() == opcionesKong[i][0]){
                           if(longevaEncontrada == false){
                               longevaEncontrada = true;
                               opcionLongeva = i;
                           }
                           opcionesYaInvertidas.push_back(i);
                           found = true;
                       }
                   }
                   if(!found){
                       todasInvertidas = false;
                   }
                   else{
                       found = false;
                   }
               }

               if(todasInvertidas){
                   opcionMinimo = opcionesKong[opcionLongeva];
               }
               else{
                   double *nuevoCostes = new double[size-opcionesYaInvertidas.size()];
                   OpcionInversion *nuevoOpcionesKong = new OpcionInversion[size-opcionesYaInvertidas.size()];
                   bool yaRealizada = false;
                   int newSize = 0;

                   // ordenamos el vector de índices de opciones ya invertidas
                   std::sort(opcionesYaInvertidas.begin(), opcionesYaInvertidas.end());

                   // se asigna la información acerca de las alternativas excepto las ya realizadas
                   for(int i = 0; i < size; i++){
                       for(int j = 0; j < opcionesYaInvertidas.size() && !yaRealizada; j++){
                           if(i == opcionesYaInvertidas[j]){
                               yaRealizada = true;
                           }
                       }
                       if(!yaRealizada){
                           // se copian los datos
                           nuevoCostes[newSize] = costes[i];
                           nuevoOpcionesKong[newSize] = opcionesKong[i];
                           newSize++;
                       }
                       yaRealizada = false;
                   }

                   // se asigna nuevo tamaño(size)
                   newSize;

                   // se borra el espacio previo
                   delete[] costes;
                   delete[] opcionesKong;

                   // se apuntan los punteros originales al nuevo espacio
                   costes = nuevoCostes;
                   opcionesKong = nuevoOpcionesKong;

                   // se vuelve a obtener el mínimo
                   minimo = buscarMinimo(costes, newSize);
                   cout << " operacion ya realizada, se recalcula el minimo: " << minimo << endl;

                   // se selecciona de nuevo la mejor opcion de inversion
                   opcionMinimo = opcionesKong[minimo];
               }
           }
       }

       // se eliminan las estructuras dinamicas usadas
       delete[] opcionesKong;
       delete[] costes;

       // se devuelve la opcion de inversion seleccionada (que puede ser
       // objeto nulo en caso de que no haya opciones de inversion)
   }

   return opcionMinimo;
}

/**
 * metodo para evaluar el coste de realizar una operacion de invsersion
 * sobre un nodo de azar, incluyendo las inversiones y la eliminacion del
 * nodo objetivo
 * @param opcion
 * @return
*/
OpcionInversion Diagrama::evaluarInversionKong(OpcionInversion opcion) const{
   double coste=0;
   OpcionInversion opcionKong(opcion.obtenerIdObjetivo());

   // se hace una copia del diagrama actual
   Diagrama base(*this);

   // se considera cada una de las posibilidades de inversión
   while(opcion.obtenerTamanno() != 0){
      // se considera cada una de las alternativas
      double *costes = new double[opcion.obtenerTamanno()];

      for(int i=0; i < opcion.obtenerTamanno(); i++){
         // se crea una copia del diagrama para probar la opcion
         // y obtener el coste
         Diagrama diagramaAlti(base);

         // se realiza la operacion de inversion con el nodo
         // correspondiente a la opcion i
         int idNodoDestino = opcion[i];
         int idNodoOrigen = opcion.obtenerIdObjetivo();

         // se realiza la inversion sobre el diagrama
         diagramaAlti.invertir(idNodoOrigen, idNodoDestino);

         // se calcula el coste
         costes[i] = diagramaAlti.obtenerTamanno();
      }

      // se busca el minimo de los costes
      int minimo = buscarMinimo(costes, opcion.obtenerTamanno());

      // se asigna la inversion seleccionada como minima
      opcionKong += opcion[minimo];

      // se actualiza el coste global
      if(costes[minimo] > coste){
         coste = costes[minimo];
      }

      // se borra el espacio reservado para los costes
      delete [] costes;

      // se realiza la operacion sobre el diagrama base
      base.invertir(opcion.obtenerIdObjetivo(), opcion[minimo]);

      // se elimina la opcion seleccionada
      opcion-=(opcion[minimo]);
   }

   // se asigna el coste global
   opcionKong.asignarCoste(coste);

   // se devuelve la opcion de inversion
   return opcionKong;
}

/**
 * metodo para ejecutar la operacion pasada como argumento sobre
 * el diagrama
 * @param operacion
 */
void Diagrama::ejecutarOperacion(const Operacion & operacion){
   int tipo = operacion.obtenerTipo();

   // si la operacion es nula, nada mas que hacer
   if(tipo != NULA){
      // se obtienen el nombre de la variable principal
      int id = buscarIdVariable(operacion.obtenerVariable());

      // si es una inversion hay que obtener el nombre de la
      // variable auxiliar
      int idAuxiliar = -1;
      if(tipo == INVERSION){
         // se busca el idAuxiliar para la inversion
         idAuxiliar = buscarIdVariable(operacion.obtenerVariableAuxiliar());

         // se realiza la operacion de inversion
         invertir(id, idAuxiliar);
      }
      else{
         // se elimina el nodo correspondiente
         eliminarNodo(id);
      }
   }
}

/**
 * metodo para depuracion, que muestra las diferencias entre
 * this y el diagrama pasado como argumento
 * @param otro
 */
void Diagrama::mostrarDiferencias(const Diagrama & otro) const{
   cout << "------------- diferencias entre diagrama base y argumento --------------" << endl;
   if(numeroNodos != otro.numeroNodos){
      cout << "diferencia entre numero de nodos " << endl;
      // se busca el nodo que falta en otro (nunca se agregan nodos al
      // diagrama)
      for(int i=0; i < numeroNodos; i++){
         Variable variable = variables[i];
         int idEnOtro = otro.buscarIdVariable(variable.obtenerNombre());

         // si no se encontro, mostrar el nombre de la variable
         if(idEnOtro == -1) {
            cout << "variable ausente en otro: " << variable.obtenerNombre();
         }
      }
   }

   // se buscan las diferencias entre enlaces tomando como patron this
   for(int i=0; i < numeroNodos; i++){
      for(int j=0; j < numeroNodos; j++){
         // se consideran los enlaces en this
         if(comprobarEnlace(i,j) == true){
            // se buscan las variables en el diagrama pasado como argumento
            int idVariablei = otro.buscarIdVariable(variables[i].obtenerNombre());
            int idVariablej = otro.buscarIdVariable(variables[j].obtenerNombre());

            // si ambos ids existen, se busca el enlace. En caso contrario, el enlace
            // no existira
            if(idVariablei != -1 && idVariablej != -1){
               // se busca en otro y si no esta, se muestra el mensaje correspondiente
               if(otro.comprobarEnlace(idVariablei, idVariablej) == false){
                  cout << "enlace ausente en otro: " << variables[i].obtenerNombre() << " -> " << variables[j].obtenerNombre() << endl;
               }
            }
            else{
               cout << "enlace ausente en otro: " << variables[i].obtenerNombre() << " -> " << variables[j].obtenerNombre() << endl;
            }
         }
      }
   }

   // se buscan lsa diferencias de enlaces tomando como patron otro
   for(int i=0; i < otro.numeroNodos; i++){
      for(int j=0; j < otro.numeroNodos; j++){
         // se comprueba la existencia del enlace en otro
         if(otro.comprobarEnlace(i,j) == true){
            // se buscan los indices de las variables en this
            int idVariablei = buscarIdVariable(otro.variables[i].obtenerNombre());
            int idVariablej = buscarIdVariable(otro.variables[j].obtenerNombre());

            // ambas variables estan presentes a la fuerza: solo se comprueba la
            // existencia del enlace
            if(comprobarEnlace(idVariablei, idVariablej) == false){
               cout << "enlace ausente en this: " << otro.variables[i].obtenerNombre() << " -> " << otro.variables[j].obtenerNombre() << endl;
            }
         }
      }
   }
   cout << "----------------------------------------------------" << endl;
}
