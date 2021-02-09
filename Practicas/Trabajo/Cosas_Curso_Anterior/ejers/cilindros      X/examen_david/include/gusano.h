#ifndef GUSANO_HPP
#define GUSANO_HPP


#include "matrices-tr.h"
#include "objeto3d.h"
#include "grafo-escena.h"
#include "malla-revol.h"
#include "malla-ind.h"
#include <vector>


class Gusano : public NodoGrafoEscena
{

private:

  int n_cubos;
  std::vector<Matriz4f*> rotaciones;
  
 public:

  Gusano(int n);

  void actualizarEstadoParametro(const unsigned iParam, const float t_sec);

  unsigned leerNumParametros() const;
  
};


class Componente : public NodoGrafoEscena
{
public:
  Componente();
};


#endif // GUSANO_HPP
  
