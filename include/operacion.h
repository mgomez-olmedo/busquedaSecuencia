#ifndef OPERACION_H
#define OPERACION_H

#include<iostream>

typedef enum{
   NULA,
   BORRADO,
   INVERSION
}TIPOOPERACION;

class Operacion{
private:
   /**
    * indicacion del tipo de operacion
    */
   TIPOOPERACION tipo;

   /**
    * nombre de la variable principal
    */
   std::string variable;

   /**
    * identificador del nodo secundario de la operacion
    * (solo para el caso de inversiones)
    */
   std::string variableAuxiliar;

   /**
    * coste de la operacion
    */
   double coste;
public:

   /**
    * Constructor por defecto
    */
   Operacion(){
      tipo = NULA;
      variable = "";
      variableAuxiliar = "";
      coste = 0;
   }

   /**
    * constructor de la clase
    * @param tipo
    * @param coste
    * @param variable
    * @param variableAuxiliar
    */
   Operacion(TIPOOPERACION tipo, double coste, std::string variable, std::string variableAuxiliar = ""){
      this->tipo = tipo;
      this->coste = coste;
      this->variable = variable;
      this ->variableAuxiliar = variableAuxiliar;
   }

   /**
    * acceso al dato tipo
    * @return
    */
   TIPOOPERACION obtenerTipo() const{
      return tipo;
   }

   /**
    * acceso al dato idNodo
    * @return
    */
   std::string obtenerVariable() const{
      return variable;
   }

   /**
    * acceso al dato variableAuxiliar
    * @return
    */
   std::string obtenerVariableAuxiliar() const{
      return variableAuxiliar;
   }

   /**
    * metodo de acceso al coste
    * @return
    */
   double obtenerCoste() const{
      return coste;
   }

   /**
    * operador de salida
    * @param flujo
    * @param operacion
    * @return
    */
   friend std::ostream & operator<<(std::ostream & flujo, const Operacion & operacion){
      // se muestran los datos de la operacion
      flujo << "[ " << operacion.tipo << " " << operacion.variable;
      if(operacion.variableAuxiliar != ""){
         flujo << " " << operacion.variableAuxiliar;
      }

      // se muestra el coste
      flujo << " coste: " << operacion.coste;

      // se vuelca marca de fin de operacion
      flujo << " ]";

      // se devuelve el flujo
      return flujo;
   }
};
#endif //OPERACION_H
