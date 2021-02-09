#ifndef WATT_HPP
#define WATT_HPP

#include "grafo-escena.h"
#include "malla-ind.h"

class Brazo: public NodoGrafoEscena{
    public:
        Brazo();
};

class Watt: public NodoGrafoEscena{
    protected:
        Matriz4f *ptr_rot=nullptr;
        Matriz4f *ptr_des_cub=nullptr;
        Matriz4f *ptr_rot_b1=nullptr;
        Matriz4f *ptr_rot_b2=nullptr;
    public:
        Watt(const float ang,const float ang_b, const float des);
        void act_des(const float tsec);
        void act_rot(const float tsec);
        void act_rot_b(const float tsec);
        unsigned leerNumParametros() const{return 3;};
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

#endif