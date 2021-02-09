#ifndef LATA_PEONES_HPP
#define LATA_PEONES_HPP


#include <string>
#include "matrices-tr.h"
#include "objeto3d.h"
#include "grafo-escena.h"
#include "malla-revol.h"


class LataPeones : public NodoGrafoEscena
{
  
public:

  LataPeones(); 
};


class Lata: public NodoGrafoEscena
{

public:

  Lata(const std::string nombre, const std::string & texturaJPG);
};


class VariasLatasPeones : public NodoGrafoEscena
{
private:

public:

  VariasLatasPeones();
};



#endif // LATA_PEONES_HPP
  
