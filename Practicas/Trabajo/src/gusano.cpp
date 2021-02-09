#include <iostream>
#include <math.h>
#include "gusano.h"
#include "malla-revol.h"

Componente::Componente(){
    //ponerIdentificador(-1);
    ponerColor({0.0,0.3,0.6});
    agregar(MAT_Traslacion(1,-1,0));
    agregar(new Cubo());
}


Gusano::Gusano(const int n,const float ang){
    ponerNombre("Gusano");
    ponerIdentificador(-1);
    num=n;
    Componente *com =new Componente();
    com->ponerIdentificador(600);
    com->ponerNombre("Cubo 1");
    agregar(com);

    for(int i=0;i<n-1;i++){
        Componente * c=new Componente();
        c->ponerIdentificador(599+n-i);
        c->ponerNombre("Cubo " + std::to_string(n-i));
        agregar(MAT_Traslacion(2,0,0));
        unsigned ind= agregar(MAT_Rotacion(ang,0,0,1));
        agregar(c);

        ptr_rot.push_back(leerPtrMatriz(ind));
    }
}

void Gusano::act_rot(const float tSec){
    float vmin=0;
    float vmax=360/num;
    float a=(vmin + vmax )/2;
    float b =(vmax-vmin )/2;
    float v=a+b*sin(2*M_PI*0.5*tSec);
    
    for (int i=0;i<ptr_rot.size();i++)
        *ptr_rot[i]=MAT_Rotacion(v,{0,0,1});
    
}

void Gusano::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    switch (iParam)
    {
    case 0:
        act_rot(tSec);
        break;
    default:
        break;
    }
}



/*void Gusano::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    float vmin=0;
    float vmax=360/num;
    float a=(vmin + vmax )/2;
    float b =(vmax-vmin )/2;
    float v=a+b*sin(2*M_PI*0.5*tSec);
    
    *ptr_rot[iParam]=MAT_Rotacion(v,{0,0,1});
}*/

