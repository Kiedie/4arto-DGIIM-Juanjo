// Nombre: Juan José, Apellidos: Herrera Aranda, DNI/pasaporte: 26516011-R (DDGG IG curso 20-21)
#include <iostream>
#include <math.h>
#include "android.h"
#include "malla-revol.h"


Apendice::Apendice(const float rot){
    
    unsigned ind = agregar(MAT_Rotacion(rot,{1,0,0}));
    agregar(MAT_Traslacion(0,-6,0));
    NodoGrafoEscena * esfera_1 = new NodoGrafoEscena();
    esfera_1->agregar(new Esfera(50,50) );
    agregar(esfera_1);

    NodoGrafoEscena * cilindro = new NodoGrafoEscena();
    cilindro->agregar(MAT_Escalado(1,5,1));
    cilindro->agregar(new Cilindro(50,50));
    agregar(cilindro);

    NodoGrafoEscena * esfera = new NodoGrafoEscena();
    esfera->agregar(MAT_Traslacion(0,5,0));
    esfera->agregar(new Esfera(50,50));
    agregar(esfera);

    pm_rot_x = leerPtrMatriz(ind);

}
void Apendice::actualizarRotacionApendice(const float tSec){
    
    float   n = 0.5;        //Oscilaciones por segundo
    float   vmin = -10,
            vmax =  10;
    float   a = (vmin + vmax)/2,
            b = (vmax - vmin)/2;
    float   v = a + b * sin(2*M_PI*n*tSec);
    
    * pm_rot_x = MAT_Rotacion(v,{0,0,1});
}
void Apendice::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    switch(iParam)
    {
        default:
            actualizarRotacionApendice(tSec);
    }
}


Cabeza_android::Cabeza_android(){
    agregar(MAT_Escalado(3,3,3));
    agregar(new Esfera(50,50));
}

Cuerpo_android::Cuerpo_android(){
    
    NodoGrafoEscena * cuerpo = new NodoGrafoEscena();
    cuerpo->agregar(MAT_Escalado(3,8,3));
    cuerpo->agregar(MAT_Traslacion(0,-0.5,0));
    cuerpo->agregar(new Cilindro(50,50));
    agregar(cuerpo);

    //Cabeza
    NodoGrafoEscena * cabeza = new NodoGrafoEscena();
    cabeza->agregar(MAT_Traslacion(0,5,0));
    cabeza->agregar( new Cabeza_android());
    agregar(cabeza);

    //Apendice
    NodoGrafoEscena *izq = new NodoGrafoEscena();
    izq->agregar(MAT_Traslacion(3,3,0));
    izq->agregar(new Apendice(30));
    agregar(izq);

    NodoGrafoEscena *der = new NodoGrafoEscena();
    der->agregar(MAT_Traslacion(-3,3,0));
    der->agregar(new Apendice(-30));
    agregar(der);
}

void Cuerpo_android::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    switch(iParam){
        case 0:
            der->actualizarEstadoParametro(iParam,tSec);
            break;
        case 1:
            izq->actualizarEstadoParametro(iParam,tSec);
            break;
    }
}