// Nombre: Juan José, Apellidos: Herrera Aranda, DNI/pasaporte: 26516011-R (DDGG IG curso 20-21)
#ifndef ANDROID
#define ANDROID

#include "grafo-escena.h"
#include "malla-ind.h"
#include "materiales-luces.h"

class Apendice: public NodoGrafoEscena{
    protected:
        Matriz4f * pm_rot_x = nullptr;
    public:
        Apendice(const float rot);
        unsigned leerNumParametros() const {return 1;};
        void actualizarRotacionApendice(const float tSec);
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class Cabeza_android: public NodoGrafoEscena{
    public: 
        Cabeza_android();
};

class Cuerpo_android: public NodoGrafoEscena{
    protected:
        Apendice * der;
        Apendice * izq;
    public:
        Cuerpo_android();
        unsigned leerNumParametros() const {return 2;};
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

#endif