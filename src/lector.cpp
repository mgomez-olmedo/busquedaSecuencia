#include "lector.h"
#include "utilidades.h"

using namespace std;

/**
 * Constructor de la clase
 * @param nombre
 */
Lector::Lector(string nombre) {
   // se inicializa como nula la lista de variables
   listaVariables = 0;
   numVariables = 0;

   // se crea el diagrama con el contructor por defecto
   // y se van realizando operaciones
   ifstream archivo(nombre);

   // se comprueba la existencia del archivo
   if (!archivo) {
      cerr << "intento de operacion sobre archivo: " << nombre << endl;
      presentarErrores("Lector", "Lector(string)", true);
   } else {
      // procesamiento de la operacion de asignacion
      // de nombre del diagrama
      procesarNombre(archivo);

      // procesamiento de las operaciones de creacion
      // de nodos
      procesarDefinicionNodos(archivo);

      // procesar la definicion de los estados de las variables
      procesarDefinicionEstados(archivo);
      
      // se asigna la lista completa de variables al diagrama
      diagrama.asignarVariables(listaVariables, numVariables);

      // se procesa la definicion de enlaces
      procesarDefinicionEnlaces(archivo);

      // se cierra el archivo
      archivo.close();
   }
}

/**
 * metodo privado para procesar el nombre del
 * diagrama
 * @param flujo
 */
void Lector::procesarNombre(std::istream & flujo) {
   // se procesan los datos del flujo
   int codigoOperacion;
   string nombre;

   // lectura del codigo de operacion
   flujo >> codigoOperacion;

   // si no es el codigo adecuado, salir del programa
   if (codigoOperacion != ASIGNAR_NOMBRE) {
      presentarErrores("Lector", "procesarNombre", true);
   } else {
      // se lee el nombre
      flujo >> nombre;
   }

   // se asigna el nombre al diagrama
   diagrama.asignarNombre(nombre);
}

/**
 * procesa las definiciones de los nodos
 * @param flujo
 */
void Lector::procesarDefinicionNodos(std::istream & flujo) {
   // se procesan definiciones mientras el codigo
   // leido del fichero sea CREAR_NODO
   bool seguir = true;
   int codigoOperacion, id, tipo, discreto;
   string nombre;
   char caracter;

   // bucle de lectura
   while (seguir) {
      // se ignora el salto de linea previo, tras el nombre del
      // diagrama
      while(flujo.peek() == '\n') flujo.ignore(1);

      // se comprueba el primer caracter
      caracter = flujo.peek();
      codigoOperacion = caracter - '0';
      if (codigoOperacion != CREAR_NODO) {
         // ya no se continuar
         seguir = false;
      } else {
         // lectura de la linea completa
         flujo >> codigoOperacion >> id >> tipo >> discreto >> nombre;

         // si no es una operacion de creacion de nodo, 
         // se presenta el correspondiente error
         if (codigoOperacion != CREAR_NODO) {
            presentarErrores("Lector", "procesarNombre", true);
         } else {
            // se agrega la variable a la memoria del lector
            // hasta tener la informacion completa
            Variable variable(id, tipo, nombre);
            
            // se agrega a this para asignarla al diagrama cuando
            // se disponga de toda la informacion sobre las variables
            (*this)+=(variable);
         }
      }
   }
}

/**
 * procesa la defincion de los estados de la variable
 * @param flujo
 */
void Lector::procesarDefinicionEstados(std::istream & flujo){
   bool seguir = true;
   char caracter = ' ';
   int codigoOperacion;
   string nombreVariable, nombreEstado;

   // se detiene cuando se encuentre un codigo de operacion que
   // no sea ASIGNAR_VALOR
   while(seguir){
      // se ignoran saltos de linea
      while(flujo.peek() == '\n') flujo.ignore(1);

      // se controla el siguiente caracter
      caracter = flujo.peek();

      // se convierte a entero
      codigoOperacion = caracter - '0';

      // si no es ASIGNAR_VALOR, se sale del bucle
      if(codigoOperacion != ASIGNAR_VALOR){
         seguir = false;
      }
      else{
         // se leen los datos del flujo
         flujo >> codigoOperacion >> nombreVariable >> nombreEstado;

         // se asigna a la variable el estado correspondiente
         asignarEstadoVariable(nombreVariable, nombreEstado);
      }
   }
}

/**
 * procesa las definiciones de enlaces en el diagrama
 * @param flujo
*/
void Lector::procesarDefinicionEnlaces(std::istream &flujo){
   bool seguir = true;
   char caracter = ' ';
   int codigoOperacion;
   string nombreVariable1, nombreVariable2;

   // se detiene cuando se encuentre un codigo de operacion que
   // no sea ASIGNAR_VALOR
   while(seguir){
      // se ignoran saltos de linea
      while(flujo.peek() == '\n') flujo.ignore(1);

      // se lee el siguiente caracter
      caracter = flujo.peek();

      // se convierte a entero
      codigoOperacion = caracter - '0';

      // si no es ASIGNAR_VALOR, se sale del bucle
      if(codigoOperacion != ASIGNAR_PADRE){
         seguir = false;
      }
      else{
         // se leen los datos del flujo
         flujo >> codigoOperacion >> nombreVariable1 >> nombreVariable2;

         // se asigna a la variable el estado correspondiente
         // en el archivo aparece en primer lugar el destino y en segundo
         // el origen. Por eso aqui se invierte el orden
         diagrama.asignarEnlace(nombreVariable2, nombreVariable1);
      }
   }
}

/**
 * metodo privado para asignar un estado a una variable
 * @param nombreVariable
 * @param nombreEstado
 */
void Lector::asignarEstadoVariable(std::string nombreVariable, std::string nombreEstado){
   // se busca en la lista de variables la variable objetivo
   for(int i=0; i < numVariables; i++){
      if(listaVariables[i].obtenerNombre() == nombreVariable){
         // se le agrega el estado
         listaVariables[i] += nombreEstado;
      }
   }
}


/**
 * agrega la informacion de una nueva variable
 * @param variable
 * @return 
 */
Lector & Lector::operator+=(const Variable & variable){
   // se crea espacio para una nueva variable mas
   Variable *espacio = new Variable[numVariables + 1];
   
   // se copian los objetos previo
   for(int i=0; i < numVariables; i++){
      // operador de asignacion necesario en Variable
      espacio[i] = listaVariables[i];
   }
   
   // se agrega la nueva
   espacio[numVariables] = variable;
   
   // se incrementa el contador de variables
   numVariables++;
   
   // se libera el espacio previo
   liberarEspacio();
   
   // se hace que listaVariables apunte al nuevo espacio
   listaVariables = espacio;
   
   // se devuelve referencia a this
   return *this;
}
