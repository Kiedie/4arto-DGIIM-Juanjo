// *********************************************************************
// **
// ** Informática Gráfica, curso 2019-20
// ** Implementación de la clase 'MallaRevol'
// **
// *********************************************************************

#include "ig-aux.h"
#include "tuplasg.h"
#include "lector-ply.h"
#include "matrices-tr.h"
#include "malla-revol.h"
#include  "math.h"         //biblioteca adicional que he incluido

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   // COMPLETAR: Práctica 2: completar: creación de la malla....

   //Creación de la tabla de vértices
      Tupla3f q;
      Matriz4f matrix_rotation;
      int num_vert = perfil.size();

      for (int i = 0 ; i < num_copias; i++)
         for(int j = 0 ; j < num_vert ; j++){
            //Queremos que haga una rotasción con respecto al eje Y, creamos la matriz Rotacion
            matrix_rotation = MAT_Rotacion( (2*180*i)/(num_copias-1), {0,1,0});
            //Aplicamos la matriz de rotación al vector vértice
            q = matrix_rotation*perfil[j];
            //Añadimos vertice
            vertices.push_back(q);
         }
         
   //Creación de la tabla de triángulos
      int k = 0;
      for (int i = 0 ; i < num_copias-1 ; i++)
         for (int j = 0 ; j < num_vert-1 ; j++){
            k = i*num_vert + j;
            triangulos.push_back({k,k+num_vert,k+num_vert+1});
            triangulos.push_back({k,k+num_vert+1,k+1});
         }



}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................
   std::vector<Tupla3f> perfil;
   LeerVerticesPLY(nombre_arch , perfil );
   inicializar(  perfil ,  nperfiles );


}

Cilindro::Cilindro(const int num_vert_per, const unsigned nperfiles){
   assert(num_vert_per>2 && "num_vert_per > 2");
   ponerNombre( "Cilindro con num_vert_per =" + std::to_string(num_vert_per) + " y nperfiles = " + std::to_string(nperfiles) );

   std::vector<Tupla3f> perfil;
   //Como estamos proyectando un perfil, la coordenaza z es CERO
   perfil.push_back({0,0,0});
   for(int i = 0 ; i < num_vert_per - 2; i++)
      perfil.push_back({1, (float)i/(num_vert_per-1),0});
   perfil.push_back({0,1,0});
   inicializar(perfil , nperfiles);
}

Cono::Cono(const int num_vert_per, const unsigned nperfiles){
   assert(num_vert_per>2 && "num_vert_per > 2");
   ponerNombre( "Cono con num_vert_per =" + std::to_string(num_vert_per) + " y nperfiles = " + std::to_string(nperfiles) );

   //Como estamos proyectando un perfil, la coordenaza z es CERO
   std::vector<Tupla3f> perfil;
   perfil.push_back({0,0,0});
   for(int i = 0 ; i < num_vert_per-1 ; i++)
      perfil.push_back({1-(float)i/(num_vert_per-1) , (float)i/(num_vert_per-1) ,0});
   inicializar(perfil,nperfiles);
}

Esfera::Esfera(const int num_vert_per, const unsigned nperfiles){
   assert(num_vert_per>2 && "num_vert_per > 2");
  ponerNombre( "Esfera con num_vert_per =" + std::to_string(num_vert_per) + " y nperfiles = " + std::to_string(nperfiles) );

   //Como estamos proyectando un perfil, la coordenaza z es CERO
   std::vector<Tupla3f> perfil;
   float alpha = 0; 
   for(int i = 0 ; i < num_vert_per ; i++){
      alpha = M_PI * ( (float)i/(num_vert_per-1) - (float)1/2 );
      perfil.push_back({cos(alpha),sin(alpha) ,0});
   }

   inicializar(perfil,nperfiles);
}
