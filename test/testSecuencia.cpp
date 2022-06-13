#include "secuenciaEnteros.h"
#include "secuenciaOperaciones.h"

using namespace std;

/**
 * Programa principal para pruebas
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]){
   SecuenciaEnteros secuencia;

   // se agranan unos cuantos valores
   secuencia += 1;
   secuencia += 2;
   secuencia += 3;

   cout << "tras agregar 3 valores --------------- " << endl;
   cout << secuencia;

   // se quita el 1
   secuencia -= 1;

   cout << "tras quitar valor 1 --------------- " << endl;
   cout << secuencia;

   secuencia.invertir();
   cout << "tras invertir --------------- " << endl;
   cout << secuencia;

   SecuenciaEnteros secuencia2(secuencia);

   cout << "Secuencia2 copia de Secuencia" << secuencia2;
   secuencia2.invertir();
   cout << "Inversion de secuencia2" << secuencia2;

   cout << "*****************************************************************";
   cout << "\n***+++++++++++++++++ SecuenciaOperaciones ++++++++++++++++++++***\n";
   cout << "*****************************************************************\n";

   SecuenciaOperaciones ops;
   Operacion op (TIPOOPERACION::BORRADO, 15.0, "var");
   ops += op;

   cout << "Operacion\n" << op;
   cout << "Operaciones\n" << ops;

}
