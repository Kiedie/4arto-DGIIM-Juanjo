
#include <iostream>
#include <math.h>
#include "modelo-jer.h"
#include "malla-revol.h"

using namespace std;

const int PARAM_REVOLUCION = 20;

PuntoApoyo::PuntoApoyo(){
    ponerNombre("Pierna");
    agregar(new Esfera(PARAM_REVOLUCION,PARAM_REVOLUCION));
    ponerColor({0.5,0.5,0.5});
}
//------------------------------------------------

Brazo::Brazo(const float ang_z){
    ponerNombre("Brazo");
    NodoGrafoEscena * extremidad = new NodoGrafoEscena();
    unsigned ind_1 = agregar(MAT_Rotacion(ang_z, {0,0,1}));
    extremidad->agregar(MAT_Traslacion(0.7,0,0));
    extremidad->agregar(MAT_Rotacion(-90,{0,0,1}));
    extremidad->agregar(MAT_Escalado(0.3,0.8,0.3));
    extremidad->agregar(new Cilindro(PARAM_REVOLUCION,PARAM_REVOLUCION));
    extremidad->ponerColor({0.75,0.2,0.65});
    agregar(extremidad);

    NodoGrafoEscena * mod_hombro = new NodoGrafoEscena();
    hombro     = new PuntoApoyo();
    mod_hombro->agregar(MAT_Traslacion(0.4,0,0));
    mod_hombro->agregar(MAT_Escalado(0.4,0.4,0.4));
    mod_hombro->agregar(hombro);
    agregar(mod_hombro);

    pm_rot_alpha = leerPtrMatriz(ind_1);
}

void Brazo::actualizar_rotacion_brazo(const float tSec){

    float   n = 0.5;        //Oscilaciones por segundo
    float   vmin = -30,
            vmax =  30;
    float   a = (vmin + vmax)/2,
            b = (vmax - vmin)/2;
    float   v = a + b * sin(2*M_PI*n*tSec);
    
    *pm_rot_alpha = MAT_Rotacion(v,{0,0,1});
}

void Brazo::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    
    switch(iParam)
    {
        default:
            actualizar_rotacion_brazo(tSec);
            break;
    }
}

//-----------------------------------------------------

Pupila::Pupila(){
    ponerNombre("Pupila");
    unsigned ind_0 = agregar(MAT_Traslacion(0,0,0));
    agregar(MAT_Escalado(0.12,0.12,0.12));
    agregar(new Esfera (PARAM_REVOLUCION,PARAM_REVOLUCION));
    ponerColor({0,0,0});
    pm_desp_x = leerPtrMatriz(ind_0);
}

void Pupila::actualizar_desplazamiento_pupila(const float tSec){

    float   n = 0.1;        //Oscilaciones por segundo
    float   vmin = -0.15,
            vmax =  0.15;
    float   a = (vmin + vmax)/2,
            b = (vmax - vmin)/2;
    float   v = a + b * sin(2*M_PI*n*tSec);
    
    *pm_desp_x = MAT_Traslacion(v,0,0);
}

void Pupila::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    switch (iParam)
    {
        default:
            actualizar_desplazamiento_pupila(tSec);
            break;
    }
}


//-----------------------------------
Ojo::Ojo(){
    ponerNombre("Ojo");

    NodoGrafoEscena * mod_pupila = new NodoGrafoEscena();
    pupila = new Pupila();
    mod_pupila->agregar(MAT_Traslacion(0,0,0.25));   //Salga un poco del ojo 
    mod_pupila->agregar(pupila);
    agregar(mod_pupila);

    NodoGrafoEscena * cornea = new NodoGrafoEscena();
    cornea->agregar(MAT_Escalado(0.3,0.3,0.3));
    cornea->agregar(new Esfera(PARAM_REVOLUCION,PARAM_REVOLUCION));
    agregar(cornea);

}

void Ojo::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    
    switch (iParam){
        default:
            pupila->actualizarEstadoParametro(iParam, tSec);
            break;
    }
}

//----------------------------------------------------

Oreja::Oreja(){
    agregar(MAT_Rotacion(90,{0,0,1}));
    agregar(MAT_Traslacion(0,-1,0));
    agregar(MAT_Escalado(0.6,1,0.6));
    ponerColor({0.5,0.9,0.9});
    agregar(new Cono(20,20));
}

void Oreja::fijarAnguloAlpha(const float rot_angulo_alpha){
    *pm_rot_alpha = MAT_Rotacion(rot_angulo_alpha,{0,0,1});
}

//----------------------------------------------------------


Cabeza::Cabeza(){
    //Metemos cabeza
    NodoGrafoEscena * cabeza = new NodoGrafoEscena();
    cabeza->agregar(MAT_Escalado(1,0.5,0.5));
    cabeza->agregar(new Esfera(PARAM_REVOLUCION, PARAM_REVOLUCION));
    cabeza->ponerColor({0.9,0.2,0.1});
    agregar(cabeza);

    //Orejas
    NodoGrafoEscena * mod_oreja_1 = new NodoGrafoEscena();
    oreja_der = new Oreja();
    mod_oreja_1->agregar(MAT_Traslacion(0.6,0,0));
    mod_oreja_1->agregar(MAT_Escalado(0.8,0.8,0.8));
    mod_oreja_1->agregar(oreja_der);
    agregar(mod_oreja_1);

    NodoGrafoEscena * mod_oreja_2 = new NodoGrafoEscena();
    oreja_izq = new Oreja();
    mod_oreja_2->agregar(MAT_Traslacion(-0.6,0,0));
    mod_oreja_2->agregar(MAT_Escalado(0.8,0.8,0.8));
    mod_oreja_2->agregar(MAT_Escalado(-1,1,1));
    mod_oreja_2->agregar(oreja_izq);
    agregar(mod_oreja_2);


    //Ojos
    NodoGrafoEscena * mod_ojo_der = new NodoGrafoEscena();
    ojo_der = new Ojo();
    mod_ojo_der->agregar(MAT_Traslacion(0.3,0,0.4));
    mod_ojo_der->agregar(MAT_Escalado(0.5,0.5,0.5));
    mod_ojo_der->agregar(ojo_der);
    agregar(mod_ojo_der);


    NodoGrafoEscena * mod_ojo_izq = new NodoGrafoEscena();
    ojo_izq = new Ojo();
    mod_ojo_izq->agregar(MAT_Traslacion(-0.3,0,0.4));
    mod_ojo_izq->agregar(MAT_Escalado(0.5,0.5,0.5));
    mod_ojo_izq->agregar(MAT_Escalado(1,1,1));
    mod_ojo_izq->agregar(ojo_izq);
    agregar(mod_ojo_izq);





}

void Cabeza::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    switch(iParam){
        case 4:
            ojo_izq->actualizarEstadoParametro(iParam,tSec);
            break;
        case 5:
            ojo_der->actualizarEstadoParametro(iParam,tSec);
            break;
        default:
            break;
    }
}


//----------------------------------------------------
Tronco::Tronco(){
    //Faltaría meterlo los brazos pero luego lo haremos
    ponerNombre("Tronco");

    //Barriga
    NodoGrafoEscena * barriga   = new NodoGrafoEscena();
    barriga->agregar(MAT_Escalado(0.5,1.3,0.5));
    barriga->ponerNombre("Barriguita");
    barriga->agregar(new Cilindro(PARAM_REVOLUCION,PARAM_REVOLUCION));
    barriga->ponerColor({0.2,0.2,0.6});
    agregar(barriga);

    //Hacemos un NGE de una pierna con traslacino
    NodoGrafoEscena * mod_pierna    = new NodoGrafoEscena(); //creamos el NGE
    pierna                          = new PuntoApoyo();              //Creamos la pierna
    pierna->ponerColor({0.3,0.3,1});
    mod_pierna->agregar(MAT_Escalado(0.7,0.7,0.7));
    mod_pierna->agregar(MAT_Traslacion(0,-0.7,0));
    mod_pierna->agregar(pierna);                             //Agregamos pierna a NGE
    agregar(mod_pierna);                                     //Añadimos el NGE_pierna

    //Brazos
    //derecho
    NodoGrafoEscena * mod_brazo_1 = new NodoGrafoEscena();
    brazo_der                     = new Brazo(0);
    mod_brazo_1->agregar(MAT_Traslacion(0.4,0.8,0));
    mod_brazo_1->agregar(brazo_der);
    agregar(mod_brazo_1);

    //izquierdo
    NodoGrafoEscena * mod_brazo_2 = new NodoGrafoEscena();
    brazo_izq                     = new Brazo(0);
    mod_brazo_2->agregar(MAT_Escalado(-1,1,1));
    mod_brazo_2->agregar(MAT_Traslacion(0.4,0.8,0));
    mod_brazo_2->agregar(brazo_izq);
    agregar(mod_brazo_2);

    
    

}


void Tronco::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    cout << "Tronco" << flush;
    switch(iParam)
    {
        case 0:
            cout << "\ntronco brazo derecho" << endl << flush;
            cout << tSec << flush;
            brazo_der->actualizar_rotacion_brazo(tSec);
            break;
        case 1:
            cout << "\nTronco Brazo izquierdo" << endl << flush; 
            brazo_izq->actualizar_rotacion_brazo(tSec);
            break;
        case 2:
            //cout <<"Se mueve todo el cuerpo" << flush;
            //actualizar_rotacion_tronco(tSec);
            break;
        default:
            break;
    }
        
            
}

//-----------------------------------------------------------



Raiz::Raiz(){

    ponerNombre("Nodo Raiz");
    //Si alteramoso el orden de alguna de las dos el comportamiento cambia radicalmente
    unsigned ind_3 = agregar(MAT_Rotacion(0,{0,1,0}));
    unsigned ind_4 = agregar(MAT_Traslacion(0,0,0));
    
    tronco = new Tronco();
    agregar(tronco);

    //Cabeza
    cabezon = new Cabeza();
    NodoGrafoEscena * mod_cabeza = new NodoGrafoEscena();
    mod_cabeza->agregar(MAT_Traslacion(0,1.7,0));
    mod_cabeza->agregar(cabezon);
    agregar(mod_cabeza);

    pm_rot_y = leerPtrMatriz(ind_3);
    pm_desp_x = leerPtrMatriz(ind_4);


}

void Raiz::actualizar_rotacion_Vladimir (const float tSec){
    cout << "\nNos Rotamos" << endl << flush;
    float   n = 0.5;        //Oscilaciones por segundo
    float   vmin = -30,
            vmax =  30;
    float   a = (vmin + vmax)/2,
            b = (vmax - vmin)/2;
    float   v = a + b * sin(2*M_PI*n*tSec);
    
    *pm_rot_y = MAT_Rotacion(v,{0,1,0});
}

void Raiz::actualizar_desplazamiento_Vladimir (const float tSec){
    cout << "\nNos desplazamos" << endl << flush;
    float   n = 1;        //Oscilaciones por segundo
    float   vmin = -1,
            vmax =  1;
    float   a = (vmin + vmax)/2,
            b = (vmax - vmin)/2;
    float   v = a + b * sin(2*M_PI*n*tSec);
    
    *pm_desp_x = MAT_Traslacion(v,0,0);
}


void Raiz::actualizarEstadoParametro(const unsigned iParam, const float tSec){

    switch(iParam)
    {
        case 0: //movimiento un brazo
            tronco->actualizarEstadoParametro(iParam,tSec);
            break;
        case 1: // movimiento otro brazo
            tronco->actualizarEstadoParametro(iParam,tSec);
            break;
        case 2:
            actualizar_rotacion_Vladimir(tSec);
            break;
        case 3:
            actualizar_desplazamiento_Vladimir(tSec);
            break;
        case 4: //ojo izqueirdo
            cabezon->actualizarEstadoParametro(iParam,tSec);
            break;
        case 5: // ojo derecho
            cabezon->actualizarEstadoParametro(iParam,tSec);
            break;
        default:
            break;

    }
            
}
