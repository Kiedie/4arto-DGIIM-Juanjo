// Nombre: Juan José, Apellidos: Herrera Aranda, DNI/pasaporte: 26516011-R (DDGG IG curso 20-21)
// *********************************************************************
// **
// ** Informática Gráfica, curso 2016-17
// ** Declaraciones de la clase MallaRevol
// **
// *********************************************************************

#ifndef IG_MALLAREVOL_HPP
#define IG_MALLAREVOL_HPP

#include <vector>          // usar std::vector
#include <string>

#include "malla-ind.h"   // declaración de 'Objeto3D'
// ---------------------------------------------------------------------
// clase para mallas indexadas obtenidas a partir de la revolución de un perfil

class MallaRevol : public MallaInd
{
   private:



   protected: //

   MallaRevol() {} // solo usable desde clases derivadas con constructores especificos

   // Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
   // a partir de un perfil y el número de copias que queremos de dicho perfil.
   void inicializar
   (
      const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
      const unsigned               num_copias  // número de copias del perfil
   ) ;
} ;
// --------------------------------------------------------------------- lauvivaldi@hotmail.com


class MallaRevolPLY : public MallaRevol
{
   public:
   MallaRevolPLY( const std::string & nombre_arch,
                  const unsigned nperfiles ) ;
} ;

class Cilindro : public MallaRevol
{
   public:
      //Constuctor: crea el perfil original y llama a inicializar
      //la base tiene el centro en el orgien, el radio y la altura son 1
      Cilindro( const int num_verts_per,   //número de vértices en el perfil original(m)
                const unsigned nperfiles); //número de perfiles
} ;

class Cono : public MallaRevol
{
   public:
      //Constuctor: crea el perfil original y llama a inicializar
      //la base tiene el centro en el orgien, el radio y la altura son 1
      Cono( const int num_verts_per,   //número de vértices en el perfil original (m)
            const unsigned nperfiles); //número de perfiles(n)
} ;

class Esfera : public MallaRevol
{
   public:
      //Constuctor: crea el perfil original y llama a inicializar
      //la base tiene el centro en el orgien, el radio es 1
      Esfera(  const int num_verts_per,   //número de vértice en el perfil original (m)
               const unsigned nperfiles); // número de perfiles (n)
} ;

class Toro: public MallaRevol
{
   public:

   Toro( Tupla3f rt, const float rp,
   const int num_verts_per, 
   const unsigned nperfiles);
};

#endif