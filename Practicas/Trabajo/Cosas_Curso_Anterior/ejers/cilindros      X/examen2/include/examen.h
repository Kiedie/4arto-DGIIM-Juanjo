#ifndef EXAMEN_HPP
#define EXAMEN_HPP

#include "grafo-escena.h"
#include "malla-ind.h"
#include "materiales-luces.h"

class MallaCil: public MallaInd{
   public:
      MallaCil(const int n);
};

class NodoCil: public NodoGrafoEscena{
   public:
      NodoCil(const int n);
};

class VariosCil: public NodoGrafoEscena{
   public:
      VariosCil(const int n);
};

#endif
