// Nombre: Juan José, Apellidos: Herrera Aranda, DNI/pasaporte: 26516011-R (DDGG IG curso 20-21)
#ifndef LATAPEONES
#define LATAPEONES


#include "grafo-escena.h"
#include "malla-ind.h"
#include "materiales-luces.h"

class LataPeones: public NodoGrafoEscena{
    public:
        LataPeones();
};

class Lata: public NodoGrafoEscena{
    public:
        Lata(const std::string & nombreArchivoJPG);
};

class VariasLatasPeones: public NodoGrafoEscena{ 
    public: 
        VariasLatasPeones();
};




#endif 