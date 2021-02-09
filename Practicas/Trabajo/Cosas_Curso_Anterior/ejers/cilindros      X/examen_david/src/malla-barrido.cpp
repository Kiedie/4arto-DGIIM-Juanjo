
// Pruebas

#include "ig-aux.h"
#include "tuplasg.h"
#include "lector-ply.h"
#include "matrices-tr.h"
#include "malla-barrido.h"
#include <math.h>

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaBarrido::inicializar
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias,  // número de copias del perfil
   const float inicio,
   const float fin
 )
{
  int m = perfil.size();

  float amplitud = (float) fin-inicio;
  
  // Inicializar tabla de vértices
  for(int i = 0; i < num_copias; i++)
    for(int j = 0; j < m; j++)
      {
	float h = inicio+amplitud*(float)i/(num_copias-1);

	vertices.push_back({perfil[j][X], perfil[j][Y], h});
      }

  // Inicializar tabla de triángulos
  for(int i = 0; i < num_copias-1; i++)
    for(int j = 0; j < m-1; j++)
      {
	int k = i*m+j;
	triangulos.push_back({k, k+m, k+m+1});
	triangulos.push_back({k, k+m+1, k+1});
      }
}


// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaBarridoPLY::MallaBarridoPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles,
   const float inicio,
   const float fin
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   
   std::vector<Tupla3f> perfil;
   
   LeerVerticesPLY(nombre_arch, perfil);

   inicializar(perfil, nperfiles, inicio, fin);   
}

Tunel::Tunel(const int num_verts_curva, const float inicio, const float fin, const unsigned nperfiles)
{

  ponerNombre("Túnel");
  ponerColor({0.5,0.6,0.3});
    
  std::vector<Tupla3f> perfil;

  perfil.push_back({-1.5,0,0});
  perfil.push_back({-1.5,1.5,0});
  perfil.push_back({0,1.5,0});
  perfil.push_back({1.5,1.5,0});
  perfil.push_back({1.5,0,0});

  for(int i = 0; i < num_verts_curva; i++){
    float alpha = M_PI*(float)i/(num_verts_curva-1);
    perfil.push_back({cos(alpha),sin(alpha),0});
  }
    
  perfil.push_back({-1.5,0,0});

  inicializar(perfil, nperfiles, inicio, fin);
}
