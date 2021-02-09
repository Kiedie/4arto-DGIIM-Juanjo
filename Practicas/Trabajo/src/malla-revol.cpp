// Nombre: Juan José, Apellidos: Herrera Aranda, DNI/pasaporte: 26516011-R (DDGG IG curso 20-21)
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


//OJO EL INICIALIZAR REVOLUCIONES EN TORNO AL EJE Y

// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   // COMPLETAR: Práctica 2: completar: creación de la malla....

   //Calculo de las normales
   vector<Tupla3f> nor_aristas;
   Tupla3f m;
   for (int i = 0 ; i < perfil.size()-1 ; i++){
      m = perfil[i+1] - perfil[i];
      nor_aristas.push_back({m(1), -m(0), 0.0}); //OJITO   
      if(nor_aristas[i](0)!=0 || nor_aristas[i](1)!=0 || nor_aristas[i](2)!=0)
         nor_aristas[i]=nor_aristas[i].normalized();
   }

   //Calculo de normales de vertices 
   vector<Tupla3f> nor_ver_aux;

   nor_ver_aux.push_back(nor_aristas[0]);

   for (int i=1;i<perfil.size()-1;i++){
      nor_ver_aux.push_back(nor_aristas[i-1]+nor_aristas[i]);
      if(nor_ver_aux[i](0)!=0 || nor_ver_aux[i](1)!=0 || nor_ver_aux[i](2)!=0)
         nor_ver_aux[i]=nor_ver_aux[i].normalized();
   }

   nor_ver_aux.push_back(nor_aristas[nor_aristas.size()-1]);

   //Calculo de las coordenadas de Textura  
   vector<float> d;
   for(int i=0;i<perfil.size()-1;i++){
      d.push_back(
         sqrt( pow(perfil[i][X]-perfil[i+1][X],2.0) + 
               pow(perfil[i][Y]-perfil[i+1][Y],2.0)));
   }

   float tam=0.0;
   for (int i=0 ; i<d.size() ; i++)
      tam+=d[i];
   

   vector<float> t (perfil.size(),0.0);
   for (int i=0 ; i<t.size()-1 ; i++){
      for (int j=0;j<i;j++)
         t[i]+=d[j];
      
      t[i]=t[i]/tam;
   }

   t.back()=1.0;  


   //Creación de la tabla de vértices
      Tupla3f q,n;
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

            //Metemos normales y coordenadas de textura  
            n=MAT_Rotacion((2*180*i)/(num_copias-1),{0,1,0})*nor_ver_aux[j];
            nor_ver.push_back(n);
            cc_tt_ver.push_back({(float)i/(num_copias-1),1-t[j]}); //OJO PELIGRO
         }
         
   //Creación de la tabla de triángulos
      int k = 0;
      for (int i = 0 ; i < num_copias-1 ; i++)
         for (int j = 0 ; j < num_vert-1 ; j++){
            k = i*num_vert + j;        //j-esimo vertices de la iésima instancia
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


Toro::Toro (Tupla3f rt, const float rp, const int num_vert_per, const unsigned nperfiles){
   //rp es el radio del circulo en dos 2D
   //rt es donde está el centro del toro 
   const int m = num_vert_per;
   const unsigned n = nperfiles;
   ponerNombre("Toro por revolución");

   //Metemos vértices
   float alpha;
   std::vector<Tupla3f> perfiles;

   //Primer Perfil
   for(int i = 0 ; i < m ; i++ ){
      //Vertice
      alpha = (float)2*M_PI*i/(m-1);
      Tupla3f vertice = rt + (Tupla3f){rp*cos(alpha), rp*sin(alpha), 0};
      vertices.push_back( vertice );     

      //Normales
      nor_ver.push_back((Tupla3f){rp*cos(alpha),rp*sin(alpha),0});
      if(nor_ver[i](0) != 0 or nor_ver[i](1) != 0 or nor_ver[i](2))
         nor_ver[i] = nor_ver[i].normalized();

      //Textura
      cc_tt_ver.push_back({1,float(i/m-1)});
   }

   //Revolucionamos
   CError();
    for (int i=1;i<nperfiles;i++){
      for(int j=0;j<num_vert_per;j++){
         float theta=(float)360*i/(n-1);
         Tupla3f q=MAT_Rotacion(theta,0,1,0)*vertices[j];
         vertices.push_back(q);

         Tupla3f nor=MAT_Rotacion(theta,0,1,0)*nor_ver[j];
         nor_ver.push_back(nor);

         cc_tt_ver.push_back({1-(float)i/(n-1),(float)j/(m-1)});
      }
   }

   for (int i=0;i<nperfiles-1;i++){
      for(int j=0;j<num_vert_per-1;j++){
         int k=i*m+j;
         triangulos.push_back({k,k+m,k+m+1});
         triangulos.push_back({k,k+m+1,k+1});
      }
   }
   CError();
}