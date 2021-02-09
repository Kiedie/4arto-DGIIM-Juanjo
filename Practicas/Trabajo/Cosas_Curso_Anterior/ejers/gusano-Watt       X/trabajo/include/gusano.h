#ifndef GUSANO_HPP
#define GUSANO_HPP

#include "grafo-escena.h"
#include "malla-ind.h"


class Componente: public NodoGrafoEscena{
    public:
        Componente();
};

class Gusano : public NodoGrafoEscena{
    protected:
        int num=0;
        std::vector<Matriz4f *> ptr_rot;
    public:
        Gusano(const int n,const float ang);
        void act_rot(const float tSec);
        unsigned leerNumParametros() const{return 1;};
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);  
};



#endif