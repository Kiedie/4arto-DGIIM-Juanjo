
#include <math.h>
#include "ig-aux.h"
#include "matrices-tr.h"
#include "grafo-escena.h"
#include "malla-revol.h"

#include "gusano.h"

using namespace std;

Gusano::Gusano(int n){
  
  n_cubos = n;

  ponerNombre("Gusano de tamaño "+to_string(n));
  ponerColor({1.0,0,0});

  agregar(new Componente());
  
  for(int i = 1; i < n_cubos; i++){
    agregar(MAT_Traslacion(2,0,0));
    int j = agregar(MAT_Rotacion((float)360/(2*n_cubos),0,0,1));
    rotaciones.push_back(leerPtrMatriz(j));
    agregar(new Componente());
  }
}

unsigned Gusano::leerNumParametros() const{
  
  return 1;
}


void Gusano::actualizarEstadoParametro(const unsigned iParam, const float t_sec){

  assert(iParam<leerNumParametros());

  float v;
  
  switch(iParam){

  case 0:
    v=(float)360/(2*n_cubos)+sin(M_PI*t_sec*0.5)*(float)360/(2*n_cubos);
    for(int i = 0; i < n_cubos-1; i++)
      *rotaciones[i] = MAT_Rotacion(v,0,0,1);
    break;
  }
}


Componente::Componente(){
  agregar(MAT_Traslacion(1,-1,0));
  agregar(new Cubo());
}

