// Nombre: Juan José, Apellidos: Herrera Aranda, DNI/pasaporte: 26516011-R (DDGG IG curso 20-21)
// *********************************************************************
// **
// ** Gestión de una grafo de escena (implementación)
// ** Copyright (C) 2016 Carlos Ureña
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"
#include "matrices-tr.h"
#include "grafo-escena.h"
#include "malla-ind.h"
#include "malla-revol.h"

using namespace std ;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != NULL );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const Matriz4f & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new Matriz4f() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != NULL );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL( ContextoVis & cv )
{
   // COMPLETAR: práctica 3: recorrer las entradas y visualizar cada nodo.

   //Guardamos el color rpevviamente fijado
   Tupla4f color_previo = leerFijarColVertsCauce(cv); 

   //Regisramos el material activo  
   Material * material_pre = nullptr;
   if(cv.iluminacion)
      material_pre = cv.material_act;

   //guardar ModelView actual
   cv.cauce_act->pushMM();
   for ( unsigned int i = 0 ; i < entradas.size() ; i++)
   {
      switch (entradas[i].tipo)
      {
         case TipoEntNGE::objeto:                     //Si es un objeto se visualiza
            entradas[i].objeto->visualizarGL(cv);
         break;

         case TipoEntNGE::transformacion:             //Si es una transformacion la aplciamos
            cv.cauce_act->compMM( *(entradas[i].matriz) );
         break;

         case TipoEntNGE::material:
            if(cv.iluminacion){
               cv.material_act = entradas[i].material;
               cv.material_act->activar(*cv.cauce_act);
            }
         break;

         case TipoEntNGE::noInicializado:             //No se hace nada 
         break;
      }
   }

   //Restaurar model view Guardada
   cv.cauce_act->popMM();

   //Restaurar el material previo   
   if(cv.iluminacion){
      cv.material_act = material_pre;
      cv.material_act->activar(*cv.cauce_act);
   }

   //Restauramos el color previoafmente fijado
   glColor4fv( color_previo );



   
   // COMPLETAR: práctica 4: en la práctica 4, si 'cv.iluminacion' es 'true',
   // se deben de gestionar los materiales:
   //   1. guardar puntero al material activo al inicio (está en cv.material_act)
   //   2. si una entrada des de tipo material, activarlo y actualizar 'cv.material_act'
   //   3. al finalizar, restaurar el material activo al inicio (si es distinto del actual)

//ESTA HECHO ARRIBA

}




// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...
// ignora el colo o identificador del nodo, ignora las entradas de tipo material
// (se supone que el estado de OpenGL está fijado antes de esta llamada de alguna forma adecuada)




// -----------------------------------------------------------------------------

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   entradas.push_back(entrada);
   return entradas.size()-1 ; // sustituir por lo que corresponda ....

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const Matriz4f & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
Matriz4f * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{
   // COMPLETAR: práctica 3: devolver puntero la matriz en ese índice
   //   (debe de dar error y abortar si no hay una matriz en esa entrada)
   // ........(sustituir 'return nullptr' por lo que corresponda)

   assert ( indice < entradas.size());
   assert ( entradas[indice].tipo == TipoEntNGE::transformacion);
   assert ( entradas[indice].matriz != nullptr);
   return entradas[indice].matriz ;


}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   if(centro_calculado) return;
   
   vector<Tupla3f> centros;
   Tupla3f centro_promedio;
   Matriz4f mmodelado=MAT_Ident();

   for(int i=0;i<entradas.size();i++){
         switch (entradas[i].tipo)
         {
            case TipoEntNGE::objeto:
               entradas[i].objeto->calcularCentroOC();
               centro_promedio=entradas[i].objeto->leerCentroOC();
               centros.push_back(mmodelado*centro_promedio);
               break;
            
            case TipoEntNGE::transformacion:
               mmodelado=mmodelado*(*entradas[i].matriz);
               break;
            
            default:
               break;
         }
      }

   centro_promedio={0.0,0.0,0.0};

   for(int i=0;i<centros.size();i++) centro_promedio=centro_promedio+centros[i];
   
   centro_promedio=centro_promedio/(float)centros.size();

   ponerCentroOC(centro_promedio);

   centro_calculado=true;
}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int         ident_busc, // identificador a buscar
   const Matriz4f &  mmodelado,  // matriz de modelado
   Objeto3D       ** objeto,     // (salida) puntero al puntero al objeto
   Tupla3f &         centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   assert( 0 < ident_busc );

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:

   // 1. calcula el centro del objeto, (solo la primera vez)
   calcularCentroOC();


   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   if (ident_busc == leerIdentificador()){
      centro_wc = mmodelado*leerCentroOC();
      if (objeto == nullptr)
         cout << "\nEl identificador encontrado tiene un objeto nulo" << endl;
      *objeto = this;
      return true;
   }


   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   Matriz4f matriz = mmodelado;

   bool found  = false;
   for (unsigned i = 0 ; i < entradas.size() && !found ; i++){
         switch (entradas[i].tipo)
         {
            case TipoEntNGE::objeto:
               found=entradas[i].objeto->buscarObjeto(ident_busc,matriz,objeto,centro_wc);
               break;
            
            case TipoEntNGE::transformacion:
               matriz=matriz*(*entradas[i].matriz);
               break;
            
            default:
               break;
         }
   }


   // ni este nodo ni ningún hijo es el buscado: terminar
   return found ;
}


GrafoEstrellaX::GrafoEstrellaX(unsigned n){
   
   assert( n > 1);
   ponerNombre("GrafoEstrellaX");
   const float          prop_esc             = 1.3/0.5; //Proporcion para el escalado deseado
   const int            nvertices_cono       = 30;
   const unsigned       num_perfiles_cono    = 30;
   const float          alpha                = 2*M_PI/n; //Angulo standar para el giro del cono  
   const float          traslacion_cono      = 1.3;      //Distancia a la cual trasladaremos el cono

   NodoGrafoEscena * estrella = new NodoGrafoEscena();
   unsigned ind = agregar(MAT_Rotacion(0,1,0,0));
   estrella->agregar(MAT_Escalado(prop_esc,prop_esc,prop_esc));   ///Hacemos que sus puntas tengan un radio de 1.3
   estrella->agregar(MAT_Traslacion(0,-0.5,-0.5));                //Centramos el punto central en el ejed e coordenadas
   estrella->agregar(new EstrellaX(n));                           //Por construcción es perpendicula al eje X
   agregar(estrella);

   for(unsigned i = 0 ; i < n ; i++ ){
      NodoGrafoEscena * cono = new NodoGrafoEscena();
      cono->agregar(MAT_Traslacion(0,traslacion_cono,0)); //Tras Rotar el cono lo trasladamos a su respectiva posicion 
      cono->agregar(MAT_Rotacion(alpha*i,0,1,0));            //Rotamos el cono respecto al eje Y
      cono->agregar(MAT_Escalado(0.14,0.15,0.14));          //Escalamos el cono para que tenga radio=0.14 y altura = 0.15
      cono->agregar(new Cono(nvertices_cono, num_perfiles_cono));
      agregar(cono); 
   }
   rotx = leerPtrMatriz(ind);
}

void GrafoEstrellaX::actualizarRotacion(const float tSec){
   const float n = 2.5;         //Numero de oscilaciones por segundo
   const float v = 2 * M_PI * tSec * n; //Queremos que haga un giro constante
   *rotx = MAT_Rotacion(v,{1,0,0});     //Sobre el eje X
}

void GrafoEstrellaX::actualizarEstadoParametro( const unsigned iParam, const float tSec){
   assert ( iParam < leerNumParametros());
   //Al tener solo un movimiento hacemos que el swith por defecto 
   //aplique la animación
   //En caso de tener más animaciones lo que hacemos será distinguir segur el valor de iParam
   switch(iParam){
      default:
         actualizarRotacion(tSec);
      break;
   }
}

NodoCubo24::NodoCubo24(){
   ponerNombre("Cubo de la UGR");
   Textura * textura = new Textura("../recursos/imgs/window-icon.jpg");
   Material * material = new Material(textura, 0.5,0.3,0.7,30.0);

   agregar(material);
   agregar(new Cubo24());
}

NodoCubo24_2ndaforma::NodoCubo24_2ndaforma(){
   ponerNombre("NodoCubo 24");
   ponerIdentificador(15);
   Textura * textura = new Textura("../recursos/imgs/window-icon.jpg");
   Material * material = new Material(textura,0.5,0.3,0.7,30);

   agregar(material);
   agregar(new Cubo24_2ndaforma());
}

NodoToro::NodoToro(){
   ponerIdentificador(75);
   ponerNombre("Toro texturizado");
   agregar(new Material(new Textura("../recursos/imgs/window-icon.jpg"),0.5,0.3,0.2,5));
   agregar(new Toro((Tupla3f){4,0,0}, 3, 30,40 ));
}

MallaDiscoP4::MallaDiscoP4()
{
   ponerColor({1.0, 1.0, 1.0});

   const unsigned ni = 23, nj = 31 ;

   for( unsigned i= 0 ; i < ni ; i++ )
      for( unsigned j= 0 ; j < nj ; j++ )
         {
            const float
               fi  = float(i)/float(ni-1),
               fj  = float(j)/float(nj-1),
               ai  = 2.0*M_PI*fi,
               x   = fj * cos( ai ),
               y   = fj * sin( ai ),
               z   = 0.0 ;
            vertices.push_back({ x, y, z });
            nor_ver.push_back({0,0,1.0});

            if(nor_ver[i](0) != 0 or nor_ver[i](1) != 0 or nor_ver[i](2))
               nor_ver[i] = nor_ver[i].normalized();

            cc_tt_ver.push_back({1-(float)i/(ni-1),(float)j/(nj-1)});
         }
         
   for( unsigned i= 0 ; i < ni-1 ; i++ )
      for( unsigned j= 0 ; j < nj-1 ; j++ )
      {
         triangulos.push_back({ i*nj+j, i*nj+(j+1), (i+1)*nj+(j+1) });
         triangulos.push_back({ i*nj+j, (i+1)*nj+(j+1), (i+1)*nj+j });
      }
}

NodoDiscoP4::NodoDiscoP4()
{
   ponerNombre("Nodo práctica 4, examen 27 enero");
    agregar(new Material(new Textura("../recursos/imgs/cuadricula.jpg"),0.5,0.5,0.1,5));
   agregar( new MallaDiscoP4() );
}


GrafoEsferasP5::GrafoEsferasP5()
{
   const unsigned
      n_filas_esferas    = 8,
      n_esferas_x_fila   = 5 ;
   int identificador     = 0 ;

  agregar( MAT_Escalado( 0.4/n_esferas_x_fila, 0.4/n_esferas_x_fila, 0.4/n_esferas_x_fila ));
  for( unsigned i = 0 ; i < n_filas_esferas ; i++ )
  {
      NodoGrafoEscena * fila_esferas = new NodoGrafoEscena() ;
      for( unsigned j = 0 ; j < n_esferas_x_fila ; j++ )
      {
          MallaInd * esfera = new Esfera(30,30) ;
          identificador = (i+1)*10000 + (j+1)*1000;
          
          esfera->ponerNombre("Esfera");
          esfera->ponerIdentificador(identificador);
          fila_esferas->agregar( MAT_Traslacion( 2.2, 0.0, 0.0 ));
          fila_esferas->agregar( esfera );
      }
      agregar( fila_esferas );
      agregar( MAT_Traslacion( 0.0, 0.0, 5.0 ));
  }
}