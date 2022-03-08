
#include "secuenciaEnteros.h"

using namespace std;

/**
 * constructor de copia
 * @param origen
 */
SecuenciaEnteros::SecuenciaEnteros(const SecuenciaEnteros & origen){
   // se reserva espacio para el tam indicado por origen
   secuencia = new int[origen.reservados];

   // se asigna el valor de reservados
   reservados = origen.reservados;

   // se copia el valor de usados
   usados = origen.usados;

   // copia de los datos
   for(int i=0; i < usados; i++){
      secuencia[i] = origen.secuencia[i];
   }
}

/**
 * consulta si la operaciones contiene un determinado valor
 * @param valor
 * @return
 */
bool SecuenciaEnteros::contiene(int valor) const{
   bool encontrado = false;
   for(int i=0; i < usados && !encontrado; i++){
      if(valor == secuencia[i]){
         encontrado = true;
      }
   }

   // se devuelve el valor de encontrado
   return encontrado;
}

/**
 * operador de asignacion
 * @param origen
 * @return
 */
SecuenciaEnteros & SecuenciaEnteros::operator=(const SecuenciaEnteros & origen){
   // libera el espacio previo
   liberar();

   // se reserva espacio para el tam indicado por origen
   secuencia = new int[origen.reservados];

   // se asigna el valor de reservados
   reservados = origen.reservados;

   // se copia el valor de usados
   usados = origen.usados;

   // copia de los datos
   for(int i=0; i < usados; i++){
      secuencia[i] = origen.secuencia[i];
   }

   // se devuelve referencia a this
   return *this;
}

/**
 * operador para agregar un nuevo elemento
 * @param nuevo
 * @return
 */
SecuenciaEnteros & SecuenciaEnteros::operator+=(int nuevo){
   // se comprueba si falta espacio
   if(reservados == usados){
      // hay que reservar mas espacio
      int * nuevoEspacio = new int[reservados + 10];

      // se copian los datos previos
      for(int i = 0; i < usados; i++){
         nuevoEspacio[i] = secuencia[i];
      }

      // se agrega el nuevo valor
      nuevoEspacio[usados] = nuevo;

      // se libera el espacio previo
      liberar();

      // se hace que operaciones apunte a nuevoEspacio
      secuencia = nuevoEspacio;

      // se asigna el valor de reservados
      reservados = reservados + 10;
   }
   else{
      // se asigna el nuevo valor sin mas
      secuencia[usados] = nuevo;
   }

   // en cualquier caso se incrementa el valor de usados
   usados++;

   // se devuelve referencia a this
   return *this;
}

/**
 * operador para agregar un nuevo elemento
 * @param nuevo
 * @return
 */
SecuenciaEnteros & SecuenciaEnteros::operator+=(const SecuenciaEnteros & otra){
   // se comprueba cuantos elementos de otra no estan ya incluidos en this
   SecuenciaEnteros noIncluidos;
   for(int i=0; i < otra.obtenerTamanno(); i++){
      if(!contiene(otra[i])){
         noIncluidos += otra[i];
      }
   }

   // se hace la reserva del espacio necesario
   int *nuevoEspacio = new int[reservados + noIncluidos.obtenerTamanno()];

   // se actualiza el valor de reservado
   reservados = reservados + noIncluidos.obtenerTamanno();

   // se copian los valores previos
   for(int i=0; i < usados; i++){
      nuevoEspacio[i] = secuencia[i];
   }

   // se libera el espacio previo
   liberar();

   // se agregan los valores de noIncluidos
   for(int i=0; i < noIncluidos.obtenerTamanno(); i++){
      nuevoEspacio[usados + i] = noIncluidos[i];
   }

   // se cambia el valor de usados
   usados += noIncluidos.obtenerTamanno();

   // se hace que operaciones apunte a nuevoEspacio
   secuencia = nuevoEspacio;

   // se devuelve la referencia al objeto
   return *this;
}

/**
 * operador para eliminar un elemento
 * @oaram objetivo
 */
SecuenciaEnteros & SecuenciaEnteros::operator-=(int objetivo){
   vector<int> ocurrencias;

   // se buscan los indices de ocurrencia del valor objetivo
   for(int i=0; i < usados; i++){
      if(secuencia[i] == objetivo){
         ocurrencias.push_back(i);
      }
   }

   // si hay ocurrencias, se redimensiona la operaciones
   if(ocurrencias.size() != 0){
      int * espacioNuevo = new int[reservados - ocurrencias.size()];

      // se copian los valores previos que no sean iguales a
      // objetivo
      for(int i=0, j=0; i < usados; i++){
         if(secuencia[i] != objetivo){
            espacioNuevo[j] = secuencia[i];
            j++;
         }
      }

      // se libera el espacio previo
      liberar();

      // se hace que operaciones apunte a espacioNuevo
      secuencia = espacioNuevo;

      // se cambian los valores de reservados y usados
      reservados = reservados - ocurrencias.size();
      usados = usados - ocurrencias.size();
   }

   // se devuelve referencia a this
   return *this;
}

/**
 * oeprador oara borrar todos los elementos de la operaciones
 * pasada como argumento
 * @param otra
 * @return
 */
SecuenciaEnteros & SecuenciaEnteros::operator-=(const SecuenciaEnteros & otra){
   vector<int> ocurrencias;

   // se buscan los indices de ocurrencia de los valores objetivos
   for(int i=0; i < otra.usados; i++) {
      for (int j = 0; j < usados; j++) {
         if (secuencia[j] == otra.secuencia[i]) {
            ocurrencias.push_back(i);
         }
      }
   }

   // si hay ocurrencias, se redimensiona la operaciones
   if(ocurrencias.size() != 0){
      int * espacioNuevo = new int[reservados - ocurrencias.size()];

      // se copian los valores previos que no sean iguales a
      // ninguno de los valores pasados como argumento
      for(int i=0, j=0; i < otra.usados; i++){
         for(int k=0; k < usados; k++) {
            if (secuencia[k] != otra.secuencia[i]) {
               espacioNuevo[j] = secuencia[i];
               j++;
            }
         }
      }

      // se libera el espacio previo
      liberar();

      // se hace que operaciones apunte a espacioNuevo
      secuencia = espacioNuevo;

      // se cambian los valores de reservados y usados
      reservados = reservados - ocurrencias.size();
      usados = usados - ocurrencias.size();
   }

   // se devuelve referencia a this
   return *this;
}

/**
 * invierte el contenido de la secuencia
 */
void SecuenciaEnteros::invertir(){
   SecuenciaEnteros invertida;
   for(int i=obtenerTamanno()-1; i>=0; i--){
      invertida += secuencia[i];
   }

   // se asigna la secuencia invertida a this
   *this = invertida;
}

/**
 * operador de entrada
 * @param flujo
 * @param secuencia
 * @return
 */
ostream & operator<<(ostream & flujo, const SecuenciaEnteros & objeto){
   // se vuelcan al flujo los valores de la operaciones
   flujo << "SEC - usados: " << objeto.usados << " reservados: " << objeto.reservados << endl;

   // se muestran los valores uno a uno
   for(int i=0; i < objeto.usados; i++){
      flujo << objeto.secuencia[i] << " ";
   }
   flujo << endl;

   // se devuelve el flujo
   return flujo;
}