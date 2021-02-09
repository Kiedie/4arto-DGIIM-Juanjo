// Nombre: Juan José, Apellidos: Herrera Aranda, DNI/pasaporte: 26516011-R (DDGG IG curso 20-21)
#ifndef TORRE_HPP
#define TORRE_HPP

#include "grafo-escena.h"
#include "malla-ind.h"


class Torre : public MallaInd{
    public:
        Torre(const int n);
};



class ConjuntoTorres : public NodoGrafoEscena{
    protected:
        //std::vector<Matriz4f *> rota;
        int tam = 0;
        //Matriz4f * rotacion_general;
    public:
        ConjuntoTorres(const int alt, const int ntorres);
        //unsigned leerNumParametros() const {2;};
        //void actualizar_rotacion(const float tSec);
        //void actualizar_rotacion_general(const float tSec);
        //void actualizarEstadoParametro( const unsigned iParam, const float tSec);
};

#endif