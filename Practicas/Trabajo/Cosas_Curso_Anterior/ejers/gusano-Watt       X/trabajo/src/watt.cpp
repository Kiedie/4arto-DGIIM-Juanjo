#include <iostream>
#include <math.h>
#include "watt.h"
#include "malla-revol.h"

Brazo::Brazo(){

    agregar(MAT_Traslacion(0,-3,0.5));
    NodoGrafoEscena * aux= new NodoGrafoEscena();
    aux->agregar(MAT_Escalado(0.5,3,0.5));
    Cilindro * cil=new Cilindro(10,40);
    cil->ponerColor({0.5,0.5,0.5});
    aux->agregar(cil);
    agregar(aux);
    Esfera * s=new Esfera();
    s->ponerColor({0.8,0.8,0.8});
    agregar(s);
}

Watt::Watt(const float ang,const float ang_b, const float des){
    ponerNombre("Regulador de Watt");

    unsigned ind=agregar(MAT_Rotacion(ang,0,1,0));

    NodoGrafoEscena * top=new NodoGrafoEscena();
    Cubo *cub=new Cubo();
    cub->ponerIdentificador(2);
    cub->ponerColor({0.3,0.3,0.3});
    top->agregar(MAT_Traslacion(0,4,0));
    top->agregar(MAT_Escalado(0.75,0.5,0.75));
    top->agregar(cub);

    NodoGrafoEscena * gancho=new NodoGrafoEscena();
    Cubo *c=new Cubo();
    c->ponerIdentificador(3);
    c->ponerColor({0.3,0.3,0.3});
    unsigned ind1=gancho->agregar(MAT_Traslacion(0,des,0));
    gancho->agregar(MAT_Escalado(0.75,0.5,0.75));
    gancho->agregar(c);

    NodoGrafoEscena * base=new NodoGrafoEscena();
    base->agregar(MAT_Escalado(0.6,4,0.6));
    Cilindro * cil=new Cilindro(10,40);
    cil->ponerIdentificador(1);
    cil->ponerColor({0.4,0.4,0.4});
    base->agregar(cil);
    
    agregar(MAT_Traslacion(0.75,4,0));
    Brazo * b1=new Brazo();
    Brazo * b2=new Brazo();
    b1->ponerIdentificador(10);
    b2->ponerIdentificador(20);
    
    unsigned ind2=agregar(MAT_Rotacion(ang_b,0,0,1));
    agregar(b2);
    MAT_Escalado(-1,1,1);
    unsigned ind3=agregar(MAT_Rotacion(ang_b,0,0,1));
    agregar(b1);

    ptr_rot=leerPtrMatriz(ind);
    ptr_des_cub=gancho->leerPtrMatriz(ind1);
    ptr_rot_b1=leerPtrMatriz(ind3);
    ptr_rot_b2=leerPtrMatriz(ind2);;

}

void Watt::act_des(const float tsec){
    float vmin=-2;
    float vmax=2;
    float a=(vmin + vmax )/2;
    float b =(vmax-vmin )/2;
    float v=a+b*sin(2*M_PI*0.4*tsec);

    *ptr_des_cub=MAT_Traslacion(0,v,0);
}

void Watt::act_rot_b(const float tsec){
    float vmin=30;
    float vmax=80;
    float a=(vmin + vmax )/2;
    float b =(vmax-vmin )/2;
    float v=a+b*sin(2*M_PI*0.4*tsec);

    *ptr_rot_b1=MAT_Rotacion(v,0,0,1);
    *ptr_rot_b2=MAT_Rotacion(v,0,0,1);
}

void Watt::act_rot(const float tsec){
    
    *ptr_rot=MAT_Rotacion((2*M_PI*3*tsec),{0,1,0});
}

void Watt::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    switch (iParam)
    {
    case 0:
        act_rot(tSec);
        break;
    case 1:
        act_des(tSec);
        break;
    case 2:
        act_rot_b(tSec);
        break;
    default:
       break;
    }
}