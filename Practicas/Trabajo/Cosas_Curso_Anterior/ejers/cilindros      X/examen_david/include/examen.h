#ifndef EXAMEN_HPP
#define EXAMEN_HPP


#include <string>
#include "matrices-tr.h"
#include "objeto3d.h"
#include "grafo-escena.h"
#include "malla-revol.h"


class MallaCil : public MallaInd
{
	public:
	MallaCil(const int n);
	
};


class NodoCil : public NodoGrafoEscena
{
	public:
	NodoCil(const int n);
	
};

class VariosCil : public NodoGrafoEscena
{
	public:
	VariosCil(const int n);
};

class Cilindros : public NodoGrafoEscena
{
	public:
	Cilindros(const int n);
};

class CilVertical : public NodoGrafoEscena
{
	public:
	CilVertical(const int n, float desplazamiento);	
};

#endif
