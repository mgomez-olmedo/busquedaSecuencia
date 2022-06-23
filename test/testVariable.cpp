#include<iostream>
#include"variable.h"
using namespace std;

/**
 * Programa principal para pruebas sobre la clase Variable
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char * argv[]){
   Variable variable (1,1,"Name");
   cout << "Prueba flujo variable: " << endl << variable;
}