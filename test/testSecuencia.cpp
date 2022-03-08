#include "secuenciaEnteros.h"

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
}
