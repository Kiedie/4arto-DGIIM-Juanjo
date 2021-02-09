// Nombre: Juan José, Apellidos: Herrera Aranda, DNI/pasaporte: 26516011-R (DDGG IG curso 20-21)
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
    extremidad->agregar(new Material(new TexturaXY("./imgs/marmol.jpg"), 0.5,0.3,0.2,5));
    extremidad->agregar(MAT_Traslacion(0.7,0,0));
    extremidad->agregar(MAT_Rotacion(-90,{0,0,1}));
    extremidad->agregar(MAT_Escalado(0.3,0.8,0.3));
    extremidad->agregar(new Cilindro(PARAM_REVOLUCION,PARAM_REVOLUCION));
    extremidad->ponerColor({0.75,0.2,0.65});
    agregar(extremidad);

    NodoGrafoEscena * mod_hombro = new NodoGrafoEscena();
    hombro     = new PuntoApoyo();
    mod_hombro->agregar(new Material(new Textura("./imgs/bambu.jpg"),0.5,0.3,0.2,5));
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
    cornea->agregar(new Material(new Textura("./imgs/pupila4.jpg"),0.5,0.3,0.2,5));
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
    cabeza->ponerIdentificador(10);
    cabeza->ponerNombre("Craneo");
    cabeza->agregar(MAT_Escalado(1,0.5,0.5));
    cabeza->agregar(new Esfera(PARAM_REVOLUCION, PARAM_REVOLUCION));
    cabeza->ponerColor({0.9,0.2,0.1});
    cabeza->agregar(new Material(new Textura("./imgs/madera2.jpg"),0.5,0.3,0.2,5));
    agregar(cabeza);

    //Orejas
    NodoGrafoEscena * mod_oreja_1 = new NodoGrafoEscena();
    oreja_der = new Oreja();
    mod_oreja_1->ponerNombre("Oreja Derecha");
    mod_oreja_1->ponerIdentificador(20);
    mod_oreja_1->agregar(MAT_Traslacion(0.6,0,0));
    mod_oreja_1->agregar(MAT_Escalado(0.8,0.8,0.8));
    mod_oreja_1->agregar(oreja_der);
    agregar(mod_oreja_1);

    NodoGrafoEscena * mod_oreja_2 = new NodoGrafoEscena();
    oreja_izq = new Oreja();
    mod_oreja_2->ponerNombre("Oreja Izquierda");
    mod_oreja_2->ponerIdentificador(21);
    mod_oreja_2->agregar(MAT_Traslacion(-0.6,0,0));
    mod_oreja_2->agregar(MAT_Escalado(0.8,0.8,0.8));
    mod_oreja_2->agregar(MAT_Escalado(-1,1,1));
    mod_oreja_2->agregar(oreja_izq);
    agregar(mod_oreja_2);


    //Ojos
    NodoGrafoEscena * mod_ojo_der = new NodoGrafoEscena();
    ojo_der = new Ojo();
    mod_ojo_der->ponerNombre("Ojo Derecho");
    mod_ojo_der->ponerIdentificador(30);
    mod_ojo_der->agregar(MAT_Traslacion(0.3,0,0.4));
    mod_ojo_der->agregar(MAT_Escalado(0.5,0.5,0.5));
    mod_ojo_der->agregar(ojo_der);
    agregar(mod_ojo_der);


    NodoGrafoEscena * mod_ojo_izq = new NodoGrafoEscena();
    ojo_izq = new Ojo();
    mod_ojo_izq->ponerNombre("Ojo Izquierdo");
    mod_ojo_izq->ponerIdentificador(31);
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
    barriga->ponerIdentificador(40);
    barriga->agregar(MAT_Escalado(0.5,1.3,0.5));
    barriga->ponerNombre("Barriguita");
    barriga->agregar(new Cilindro(PARAM_REVOLUCION,PARAM_REVOLUCION));
    barriga->ponerColor({0.2,0.2,0.6});
    barriga->agregar(new Material(new Textura("./imgs/cesped2.jpg"),0.5,0.3,0.2,5));
    agregar(barriga);

    //Hacemos un NGE de una pierna con traslacino
    NodoGrafoEscena * mod_pierna    = new NodoGrafoEscena(); //creamos el NGE
    pierna                          = new PuntoApoyo();              //Creamos la pierna
    pierna->ponerColor({0.3,0.3,1});
    mod_pierna->ponerNombre("Pierna"),
    mod_pierna->ponerIdentificador(50);
    mod_pierna->agregar(MAT_Escalado(0.7,0.7,0.7));
    mod_pierna->agregar(MAT_Traslacion(0,-0.7,0));
    mod_pierna->agregar(pierna);                             //Agregamos pierna a NGE
    agregar(mod_pierna);                                     //Añadimos el NGE_pierna

    //Brazos
    //derecho
    NodoGrafoEscena * mod_brazo_1 = new NodoGrafoEscena();
    brazo_der                     = new Brazo(0);
    mod_brazo_1->ponerNombre("Brazo Derecho");
    mod_brazo_1->ponerIdentificador(60);
    mod_brazo_1->agregar(MAT_Traslacion(0.4,0.8,0));
    mod_brazo_1->agregar(brazo_der);
    agregar(mod_brazo_1);

    //izquierdo
    NodoGrafoEscena * mod_brazo_2 = new NodoGrafoEscena();
    brazo_izq                     = new Brazo(0);
    mod_brazo_2->ponerNombre("Brazo Izquierdo");
    mod_brazo_2->ponerIdentificador(61);
    mod_brazo_2->agregar(MAT_Escalado(-1,1,1));
    mod_brazo_2->agregar(MAT_Traslacion(0.4,0.8,0));
    mod_brazo_2->agregar(brazo_izq);
    agregar(mod_brazo_2);

    
    

}


void Tronco::actualizarEstadoParametro(const unsigned iParam, const float tSec){

    switch(iParam)
    {
        case 0:
            brazo_der->actualizar_rotacion_brazo(tSec);
            break;
        case 1:
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
    float   n = 0.5;        //Oscilaciones por segundo
    float   vmin = -30,
            vmax =  30;
    float   a = (vmin + vmax)/2,
            b = (vmax - vmin)/2;
    float   v = a + b * sin(2*M_PI*n*tSec);
    
    *pm_rot_y = MAT_Rotacion(v,{0,1,0});
}

void Raiz::actualizar_desplazamiento_Vladimir (const float tSec){
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



//================================================
Sistema_cilindros::Sistema_cilindros(float radio, int copias) {
    double angulo = 2 * M_PI * 180 / (M_PI * copias);
    agregar(MAT_Traslacion(radio, 0, radio));

    for (int i = 0; i < copias; i++) {
        agregar ( MAT_Traslacion(radio, 0, 0) );
        NodoGrafoEscena * cilindro = new NodoGrafoEscena();
        cilindro->agregar(new Cilindro_escena());
        cilindro->ponerNombre("Un cilindro salseante");
        cilindro->ponerIdentificador(650-i);
        cilindro->agregar (MAT_Traslacion(-radio, 0, 0));
        cilindro->agregar(MAT_Rotacion(angulo, 0, 1, 0));
        agregar(cilindro);
    }
    agregar (MAT_Traslacion(-2 * radio, 0, -2 * radio));

    for (int i = 0; i < copias; i++) {
        agregar ( MAT_Traslacion(radio, 0, 0) );
        NodoGrafoEscena * cilindro = new NodoGrafoEscena();
        cilindro->ponerNombre("Un cilindro picante");
        cilindro->ponerIdentificador(750-i);
        cilindro->agregar( new Cilindro_alt() );
        cilindro->agregar (MAT_Traslacion(-radio, 0, 0));
        cilindro->agregar(MAT_Rotacion(angulo, 0, 1, 0));
        agregar(cilindro);
    }

    ponerIdentificador(-1);
}

Cilindro_alt::Cilindro_alt(int n) {
    Textura * tex = new Textura("./imgs/bambu.jpg");
    agregar( new Material(tex, 0.3, 0.1, 0.1, 4));
    agregar(new MallaCil(n));

}

Cilindro_escena::Cilindro_escena() {
    Textura * tex = new Textura("../recursos/imgs/window-icon.jpg");
    agregar( new Material(tex, 0.3, 0.1, 0.1, 4));

    agregar ( new Cilindro(30, 30) );

}