
#ifndef VARIABLE_H
#define VARIABLE_H

#include<iostream>

typedef enum{
   BASURA,
   AZAR,
   DECISION,
   UTILIDAD
}TIPOVARIABLE;

/**
 * Almacena la informacion completa de una variables
 */
class Variable{
private:
   /**
    * identificador unico para la variable
    */
   int id;
   
   /**
    * nombre de la variable
    */
   std::string nombre;   
   
   /**
    * lista de nombres de los estados
    */
   std::string *estados;
   
   /**
    * cardinalidad de la variable
    */
   int cardinalidad;
   
   /**
    * tipo de variable - nodo
    */
   int tipo;
   
   /**
    * metodo privado de reserva de espacio
    * @param dimension
    * @return 
    */
   std::string * reservarEspacio(int dimension){
      return new std::string[dimension];
   }
   
   /**
    * metodo privado para liberar espacio
    */
   void liberarEspacio(){
      if(estados != 0){
         delete [] estados;
      }
      estados = 0;
   }
   
public:
   
   /**
    * Constructor por defecto
    */
   Variable(){
      id = -1;
      tipo = -1;
      cardinalidad = 0;
      nombre = "";
      estados = 0;
   }

   /**
    * constructor indicando string y tipo
    * @param id
    * @param tipo
    * @param nombre
    */
   Variable(int id, int tipo, std::string nombre);
   
   /**
    * Destructor de la clase
    */
   ~Variable(){
      liberarEspacio();
   }
   
   /**
    * metodo de acceso al id
    * @return
    */
   int obtenerId() const{
      return id;
   }
   
   /**
    * Metodo de acceso al nombre
    * @return 
    */
   std::string obtenerNombre() const{
      return nombre;
   }
   
   /**
    * metodo de acceso a la cardinalidad
    * @return 
    */
   int obtenerCardinalidad() const{
      return cardinalidad;
   }

   /**
    * metodo de acceso al tipo
    * @return
    */
   int obtenerTipo() const{
      return tipo;
   }
   
   /**
    * operador de asignacion
    * @param variable
    * @return 
    */
   Variable & operator=(const Variable & variable);

   /**
    * operador de asignacion de nuevo estado a la variable
    * @param estado
    * @return
    */
   Variable & operator+=(const std::string & estado);
   
   /**
    * operador de salida
    * @param flujo
    * @param variable
    */
   friend std::ostream & operator<<(std::ostream & flujo, const Variable & variable);
};

#endif /* VARIABLE_H */

