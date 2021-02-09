// Nombre: Juan José, Apellidos: Herrera Aranda, DNI/pasaporte: 26516011-R (DDGG IG curso 20-21)
#ifndef GUSANITO_HPP
#define GUSANITO_HPP

#include "grafo-escena.h"
#include "malla-ind.h"

class Barriguita : public NodoGrafoEscena{
    public:
       Barriguita();
};

class Gusanito : public NodoGrafoEscena{
    protected:
        std::vector<Matriz4f *> ptr_dz;
        int num=7;
    public:
        Gusanito(const int n, const float ang);
        void act_d(const float tSec);
        unsigned leerNumParametros() const {return 1;}
        void actualizarEstadoParametro(const unsigned iPara, const float tSec);
};



#endif 