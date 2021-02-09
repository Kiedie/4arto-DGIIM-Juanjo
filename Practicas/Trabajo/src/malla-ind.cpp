// Nombre: Juan José, Apellidos: Herrera Aranda, DNI/pasaporte: 26516011-R (DDGG IG curso 20-21)
// *********************************************************************
// **
// ** Informática Gráfica, curso 2020-21
// ** Declaraciones de la clase Objeto3D.hpp
// **
// *********************************************************************

//#include <set>   // std::set
#include "ig-aux.h"
#include "tuplasg.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"


// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}


void MallaInd::visualizarNormales()
{
   using namespace std ;
   CError();
   if ( nor_ver.size() == 0 )
   {
      cout << "Advertencia: intentando dibujar normales de una malla que no tiene tabla (" << leerNombre() << ")." << endl ;
      return ;
   }
   std::vector<Tupla3f> segmentos ;
   for( unsigned i = 0 ; i < vertices.size() ; i++ )
   {  segmentos.push_back( vertices[i] );
      segmentos.push_back( vertices[i]+ 0.35f*(nor_ver[i]) );
   }
   CError();
   glVertexPointer( 3, GL_FLOAT, 0, segmentos.data() );
   glDrawArrays( GL_LINES,  0, segmentos.size() );
   CError();
}




//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....
   Tupla3f p,q,r,a,b,m_c;

   for (unsigned int i = 0; i < triangulos.size(); i++){
      p = vertices[triangulos[i][0]];
      q = vertices[triangulos[i][1]];
      r = vertices[triangulos[i][2]];

      a = q - p;
      b = r - p;

      m_c = a.cross(b);

      if (m_c.lengthSq() > 0)
         nor_tri.push_back(m_c.normalized());
      else
         nor_tri.push_back({0.0,0.0,0.0});
   }



}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......
   calcularNormalesTriangulos();

   for(unsigned int i=0;i<vertices.size();i++) nor_ver.push_back({0.0,0.0,0.0});

   for(unsigned int i=0;i<triangulos.size();i++){
      nor_ver[triangulos[i][0]]=nor_ver[triangulos[i][0]]+nor_tri[i];
      nor_ver[triangulos[i][1]]=nor_ver[triangulos[i][1]]+nor_tri[i];
      nor_ver[triangulos[i][2]]=nor_ver[triangulos[i][2]]+nor_tri[i];
   }

   for(unsigned int i=0;i<vertices.size();i++){
            if (nor_ver[i].lengthSq() > 0)
               nor_ver[i] = nor_ver[i].normalized();
}

}


// ----------------------------------------------------------------------------


void MallaInd::visualizarGL( ContextoVis & cv )
{

   using namespace std ;
   assert( cv.cauce_act != nullptr );

   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }
   
   if(cv.visualizando_normales){
      visualizarNormales();
      return;
   }

   // guardar el color previamente fijado
   const Tupla4f color_previo = leerFijarColVertsCauce( cv );

   // COMPLETAR: práctica 1: si el puntero 'array_verts' es nulo, crear el objeto ArrayVerts
   //   * en el constructor se dan los datos de la tabla de coordenadas de vértices (tabla 'vertices')
   //   * después hay que invocar a 'fijarIndices', usando el formato y datos de la tabla de triángulos ('triangulos')
   //   * si las tablas 'col_ver', 'cc_tt_ver' o 'nor_ver' no están vacías, hay que invocar los métodos 
   //     'fijarColores', 'fijarCoordText' y 'fijarNormales', como corresponda.
   if (array_verts == nullptr){
      array_verts =  new ArrayVertices(GL_FLOAT,3,vertices.size(),vertices.data());
      
      array_verts->fijarIndices(GL_UNSIGNED_INT,triangulos.size()*3,triangulos.data());

      if (!col_ver.empty())      array_verts->fijarColores(GL_FLOAT,3, col_ver.data() );
      if (!cc_tt_ver.empty())    array_verts->fijarCoordText(GL_FLOAT, 2, cc_tt_ver.data() );
      if (!nor_ver.empty()    )  array_verts->fijarNormales(GL_FLOAT,nor_ver.data() );

   }



   // COMPLETAR: práctica 1: visualizar según el modo (en 'cv.modo_envio')
   //   ** inmediato begin/end       : usar método 'visualizarGL_MI_BVE' de 'ArrayVerts'
   //   ** inmediato con una llamada : usar método 'visualizarGL_MI_DAE' de 'ArrayVerts'
   //   ** diferido (con un VAO)     : usar método 'visualizarGL_MD_VAO' de 'ArrayVerts'
   // (en cualquier caso hay que pasar como parámetro el tipo de primitiva adecuada a una malla de triángulos).
   // .....
   switch(cv.modo_envio){
      case ModosEnvio::inmediato_begin_end:        array_verts->visualizarGL_MI_BVE(GL_TRIANGLES);   break;
      case ModosEnvio::inmediato_drawelements:     array_verts->visualizarGL_MI_DAE(GL_TRIANGLES);   break; 
      case ModosEnvio::diferido_vao:               array_verts->visualizarGL_MD_VAO(GL_TRIANGLES);   break;
      default: assert(false);                                                 break;
   }

   // restaurar el color previamente fijado
   glColor4fv( color_previo );
}




// *****************************************************************************


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................
   
   LeerPLY(nombre_arch,this->vertices, this->triangulos);



   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................
   calcularNormales();


}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;

   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   calcularNormales();
}
// -----------------------------------------------------------------------------------------------

Tetraedro::Tetraedro(const Tupla3f & nuevo_color)
:  MallaInd(  "Tetraedro")  
{
   vertices =
      {
         {-1.0, -2.0, +1.0}, //0
         {-1.0, +2.0, +1.0}, //1
         {-1.0, -1.0, -1.0}, //2
         {+1.0, +1.0, +1.0}, //3
      };

   triangulos = 
   {
      {0,1,2}, {1,2,3},
      {0,1,3}, {0,3,2},
   };
   ponerColor(nuevo_color);
   calcularNormales();
}

CuboColores::CuboColores()
: MallaInd( "CuboColores" )
{
   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

      col_ver = 
         {
            {0.0,0.0,0.0},
            {0.0,0.0,1.0},
            {0.0,1.0,0.0},
            {0.0,1.0,1.0},
            {1.0,0.0,0.0},
            {1.0,0.0,1.0},
            {1.0,1.0,0.0},
            {1.0,1.0,1.0},
         };
         
   calcularNormales();
}

Cubo24::Cubo24()
:  MallaInd( "cubo 24 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7

	      { -1.0, -1.0, -1.0 }, // 0 +8 - 8
         { -1.0, -1.0, +1.0 }, // 1 +8 - 9 
         { -1.0, +1.0, -1.0 }, // 2 +8 - 10
         { -1.0, +1.0, +1.0 }, // 3 +8 - 11
         { +1.0, -1.0, -1.0 }, // 4 +8 - 12
         { +1.0, -1.0, +1.0 }, // 5 +8 - 13
         { +1.0, +1.0, -1.0 }, // 6 +8 - 14
         { +1.0, +1.0, +1.0 }, // 7 +8 - 15

	      { -1.0, -1.0, -1.0 }, // 0 +16
         { -1.0, -1.0, +1.0 }, // 1 +16
         { -1.0, +1.0, -1.0 }, // 2 +16 
         { -1.0, +1.0, +1.0 }, // 3 +16
         { +1.0, -1.0, -1.0 }, // 4 +16
         { +1.0, -1.0, +1.0 }, // 5 +16
         { +1.0, +1.0, -1.0 }, // 6 +16
         { +1.0, +1.0, +1.0 }  // 7 +16
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {8,13,9}, {8,12,13}, // Y-
         {10,11,15}, {10,15,14}, // Y+ (+2)

         {16,22,20}, {16,18,22}, // Z-
         {17,21,23}, {17,23,19}  // Z+ (+1)
      } ;

   cc_tt_ver=
   {
         {0,1}, //0
         {1,1}, //1
         {0,0}, //2
         {1,0}, //3
         {1,1}, //4
         {0,1}, //5
         {1,0}, //6
         {0,0}, //7

         {0,0}, //0 +8
         {1,0}, //1 +8
         {1,0}, //2 +8
         {0,0}, //3 +8
         {0,1}, //4 +8
         {1,1}, //5 +8
         {1,1}, //6 +8
         {0,1}, //7 +8

         {1,1}, // 0 +16
         {0,1}, // 1 +16
         {1,0}, // 2 +16 
         {0,0}, // 3 +16
         {0,1}, // 4 +16
         {1,1}, // 5 +16
         {0,0}, // 6 +16
         {1,0}   // 7 +16
   };

      calcularNormales();
      ponerIdentificador(5);
};

Cubo24_2ndaforma::Cubo24_2ndaforma() : MallaInd("cubo de 24 vértices")
{
   vertices = {
      {-1.0,-1.0,-1.0}, //0
      {-1.0,-1.0,1.0 }, //1
      {1.0,-1.0,-1.0 }, //2
      {1.0,-1.0,1.0  }, //3
      
      {-1.0,1.0,-1.0 }, //4
      {-1.0,1.0,1.0  }, //5
      {1.0,1.0,-1.0  }, //6
      {1.0,1.0,1.0   }, //7

      {-1.0,1.0,1.0  }, //8
      {1.0,1.0,1.0   }, //9
      {-1.0,-1.0,1.0 }, //10
      {1.0,-1.0,1.0  }, //11

      {-1.0,1.0,-1.0 }, //12
      {1.0,1.0,-1.0  }, //13
      {-1.0,-1.0,-1.0}, //14
      {1.0,-1.0,-1.0 }, //15

      {-1.0,1.0,-1.0},{-1.0,1.0,1.0},        
      {-1.0,-1.0,-1.0},{-1.0,-1.0,1.0},

      {1.0,1.0,-1.0},{1.0,1.0,1.0},
      {1.0,-1.0,-1.0},{1.0,-1.0,1.0} 
   };

    triangulos = {
      {0,2,1},{3,1,2},
      {4,5,6},{7,6,5},
      {9,8,10},{9,10,11},
      {13,14,12},{13,15,14},
      {17,16,18},{17,18,19},
      {21,20,22},{21,23,22}

   };


   cc_tt_ver = {
      {0.0, 1.0},{0.0, 0.0},
      {1.0,1.0},{1.0,0.0},

      {0.0, 0.0},{0.0, 1.0},
      {1.0,0.0},{1.0,1.0},

      {0.0,0.0},{1.0,0.0},
      {0.0,1.0},{1.0,1.0},

      {1.0,0.0},{0.0,0.0},
      {1.0,1.0},{0.0,1.0},

      {0.0,0.0},{1.0,0.0},
      {0.0,1.0},{1.0,1.0},

      {1.0,0.0},{0.0,0.0},
      {1.0,1.0},{0.0,1.0},
   };   //DUDA

   calcularNormales();
   ponerIdentificador(6);

}


EstrellaX::EstrellaX(unsigned n) : MallaInd("EstrellaX"){
   assert(n > 1);

   using namespace std;
   const unsigned num_ver = 2*n + 1;
   const unsigned num_tri = 2*n;
   const float radio_grande = 0.5;
   const float radio_peqe = 0.25; 
   const float alpha = 2*M_PI/(num_ver-1);

   //Metemos los vertices
   for (unsigned i = 0 ; i < num_ver ; i++){
      if( i%2 == 0) //vertice grande 
         vertices.push_back( {0, 0.5 + radio_grande*cos(alpha*i), 0.5 + radio_grande*sin(alpha*i)});
      else // vertice pequeño 
         vertices.push_back( {0, 0.5 + radio_peqe*cos(alpha*i),0.5 +  radio_peqe*sin(alpha*i)} );
   }
   //Metemos el centro 
   vertices.push_back({0,0.5,0.5});

   for (unsigned i = 0 ; i < num_ver ; i++){
      col_ver.push_back({vertices[i][0], vertices[i][1], vertices[i][2]});
   }
   col_ver.push_back({1,1,1});

   //Hacemos la triangulación
   for( unsigned j = 0 ; j < num_tri  ; j++){
      triangulos.push_back({ j , j + 1 ,num_ver});
   }


}

PiramideEstrellaX::PiramideEstrellaX(unsigned n) : MallaInd("PiramideEstrellaX"){
   assert (n>1);
   const unsigned num_ver_pir = 2*n +2;
   const unsigned num_tri_pir = 4*n;

   const int num_ver = 2*n + 1;
   const int num_tri = 2*n;
   const float radio_grande = 0.5;
   const float radio_peqe = 0.25; 
   const float alpha = 2*M_PI/(num_ver-1);

   //Metemos los vertices
   for (int i = 0 ; i < num_ver ; i++){
      if( i%2 == 0) //vertice grande 
         vertices.push_back( {0, 0.5 + radio_grande*cos(alpha*i), 0.5 + radio_grande*sin(alpha*i)});
      else // vertice pequeño 
         vertices.push_back( {0, 0.5 + radio_peqe*cos(alpha*i), 0.5 + radio_peqe*sin(alpha*i)});
   }
   //Metemos el centro 
   vertices.push_back({0,0.5,0.5});
   //Metemos la punta de la piramide
   vertices.push_back({0.5,0.5,0.5});

   for (int i = 0 ; i < num_ver ; i++){
      col_ver.push_back({vertices[i][0], vertices[i][1], vertices[i][2]});
   }
   col_ver.push_back({1,1,1});

   //Hacemos la triangulación
   for( int i = 0 ; i < num_tri_pir ; i++){
      for(int j = 0 ; j < num_tri_pir ; j++ ){
      int k = i*num_tri+j;
      triangulos.push_back({ k , k + 1 , num_ver_pir });
      }
   }


} 

MallaCil::MallaCil(const int n){

   vertices.push_back({0,0,0});
	nor_ver.push_back({0.0,-1.0,0.0});
	cc_tt_ver.push_back({0.5,0.5});

	for(int i = 0; i <= n; i++) {
      const float f = float(i)/float(n),
		            ang=2.0*M_PI*f, 
		            vx=cos(ang), vz=sin(ang);	

      //vertice 4*i+1 (Tapa de abajo)
		vertices.push_back({vx,0.0,vz});
		nor_ver.push_back({0.0,-1.0,0.0});
		cc_tt_ver.push_back({(1+vx)*0.5,(1+vz)*0.5});
		//vertice 4*i+2
		vertices.push_back({vx,0.0,vz});
		nor_ver.push_back({vx,0.0,vz});
		cc_tt_ver.push_back({(float)i/n,1.0});
      
      //Tapa de arriba
		//vertice 4*i+3
		vertices.push_back({vx,1.0,vz});
		nor_ver.push_back({vx,0.0,vz});
		cc_tt_ver.push_back({(float)i/n,0.0});
		//vertice 4*i+4(Tapa de arriba)
		vertices.push_back({vx,1.0,vz});
		nor_ver.push_back({0.0,1.0,0.0});
		cc_tt_ver.push_back({(1+vx)*0.5,(1-vz)*0.5});

		//triangulos
		if(i<n){
			triangulos.push_back({ 4*i+1     ,4*(i+1)+1  ,0        });
			triangulos.push_back({ 4*i+2     ,4*i+3      ,4*(i+1)+2});
			triangulos.push_back({ 4*(i+1)+2 ,4*i+3      ,4*(i+1)+3});
			triangulos.push_back({ 4*i+4     ,4*(n+1)+1  ,4*(i+1)+4});
		}
   }
	//vertice 3*(n+1)(centro de la tapa superior)
	vertices.push_back( {0.0 ,1.0,0.0});
	nor_ver.push_back(  {0.0 ,1.0,0.0});
	cc_tt_ver.push_back({0.5 ,0.5    });
}


