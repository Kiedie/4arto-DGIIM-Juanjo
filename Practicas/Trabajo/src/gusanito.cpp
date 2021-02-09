// Nombre: Juan José, Apellidos: Herrera Aranda, DNI/pasaporte: 26516011-R (DDGG IG curso 20-21)
#include <iostream>
#include <math.h>
#include "gusanito.h"
#include "grafo-escena.h"
#include "malla-ind.h"  

Barriguita::Barriguita(){
    ponerColor({0.5,0.5,0.5});
    agregar(MAT_Traslacion(1,1,0));
    agregar(new Cubo());
}

Gusanito::Gusanito(const int n, const float ang){
    ponerNombre("Susanita busca un raton ");
    num = n;

    Barriguita *barri = new Barriguita();
    barri->ponerNombre("barriga 1");
    agregar(barri);

    for(int i = 1 ; i < num-1 ; i++){
        Barriguita * barriga = new Barriguita();
        agregar(MAT_Traslacion(2,0,0));  //Las traslaciones son acumulativas a lo largo del bucle
        unsigned ind = agregar(MAT_Traslacion(0,0,ang));
        agregar(barriga);

        ptr_dz.push_back(leerPtrMatriz(ind));
    }
}

void Gusanito:: act_d(const float tSec){
    
    float n_osc = 0.5;
    float vmin=-1;
    float vmax=1;
    float a=(vmin + vmax )/2;
    float b =(vmax-vmin )/2;
    float v=a+b*sin(2*M_PI*n_osc*tSec);
    float vi = -a-b*sin(2*M_PI*n_osc*tSec);

    for(unsigned i = 0 ; i < ptr_dz.size(); i++){
        if ( i%2 == 0)
            *ptr_dz[i] = MAT_Traslacion(0,0,v);
        else 
            *ptr_dz[i] = MAT_Traslacion(0,0,vi);

    }   
}

void Gusanito::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    
    assert(iParam < leerNumParametros());

    switch(iParam){
        default:
            act_d(tSec);
            break;
    }
}