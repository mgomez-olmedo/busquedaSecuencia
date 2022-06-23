
#include "variable.h"

using namespace std;

/**
 * constructor indicando string y tipo
 * @param id
 * @param tipo
 * @param nombre
 */
Variable::Variable(int id, int tipo, string nombre) {
   this->nombre = nombre;
   this->tipo = tipo;
   this->id = id;
   this->cardinalidad = 0;
   this->estados = 0;
}

/**
 * operador de asignacion
 * @param variable
 * @return 
 */
Variable & Variable::operator=(const Variable & variable){
   // si no hay memoria dinamica en variable (argumento),
   // simplemente copia datos simples
   if(variable.cardinalidad != 0){
      // se libera el espacio de memoria para almacenar
      // los nombres de los estados
      liberarEspacio();

      // se reserva espacio para los estados del argumento
      estados = reservarEspacio(variable.cardinalidad);

      // se copian los nombres de los estados
      for(int i=0; i < variable.cardinalidad; i++){
         estados[i] = variable.estados[i];
      }      
   }
   else{
      estados = 0;
   }
   
   // se asignan el resto de datos miembro
   nombre = variable.nombre;
   id = variable.id;
   tipo = variable.tipo;
   cardinalidad = variable.cardinalidad;

   // se devuelve referencia a this
   return *this;
}

/**
 * operador de asignacion de nuevo estado a la variable
 * @param estado
 * @return
 */
Variable & Variable::operator+=(const std::string & estado){
   // se reserva nuevo espacio
   string * nuevo = reservarEspacio(cardinalidad + 1);

   // se copian los estados previos
   for(int i=0; i < cardinalidad; i++){
      nuevo[i] = estados[i];
   }

   // se agrega el nuevo
   nuevo[cardinalidad] = estado;

   // se aumenta el valor de cardinalidad
   cardinalidad++;

   // se libera espacio pevio
   liberarEspacio();

   // se apunta al nuevo espacio
   estados = nuevo;

   // se devuelve referencia a this
   return *this;
}

/**
 * operador de salida
 * @param flujo
 * @param variable
 */
std::ostream & operator<<(std::ostream & flujo, const Variable & variable) {
   flujo << "Variable " << variable.nombre << " id: " << variable.id;

    switch (variable.tipo) {
        case 0:
            flujo << " tipo: BASURA" << endl;
            break;
        case 1:
            flujo << " tipo: AZAR" << endl;
            break;
        case 2:
            flujo << " tipo: DECISION" << endl;
            break;
        case 3:
            flujo << " tipo: UTILIDAD" << endl;
            break;
    }

   flujo << "cardinalidad: " << variable.cardinalidad << endl;
   if(variable.cardinalidad != 0) {
      flujo << "   estados: ";
      for (int i = 0; i < variable.cardinalidad; i++) {
         flujo << variable.estados[i] << " ";
      }
   }

   // se devuelve el flujo
   return flujo;
}

