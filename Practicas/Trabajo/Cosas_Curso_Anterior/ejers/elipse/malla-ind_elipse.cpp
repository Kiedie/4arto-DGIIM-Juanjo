// *********************************************************************
// **
// ** Informática Gráfica, curso 2019-20
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

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......


}


//----------------------------------------------------------------------------
// comprueba que los valores de 'tipo' y 'tabla' son valores legales.

void Comprobar( GLuint tipo, GLuint tabla )
{
   assert( tipo == GL_ARRAY_BUFFER || tipo == GL_ELEMENT_ARRAY_BUFFER );
   if ( tipo == GL_ARRAY_BUFFER )
      assert(  tabla == GL_VERTEX_ARRAY || tabla == GL_COLOR_ARRAY ||
               tabla == GL_NORMAL_ARRAY || tabla == GL_TEXTURE_COORD_ARRAY ) ;
}
//----------------------------------------------------------------------------
// crea un VBO, devuelve:
//  ** 0 si 'num_elems' es 0, o
//  ** el identificador de VBO, si num_elems > 0
//
// deja activado el VBO 0

GLuint CrearVBO( GLuint tipo, GLuint tabla, GLuint cuenta, GLvoid * puntero )
{
   Comprobar( tipo, tabla );
   // COMPLETAR: práctica 1
   // Crear un VBO para esta tabla y enviar datos a la GPU, devolver id de VBO
   // Si 'cuenta' es 0, la tabla está vacía: devuelve 0 y no hace nada.
   // ...
   if(cuenta==0) return 0;

   // Calcular tamaño de cada elemento en bytes
   GLuint teb = (tipo == GL_ELEMENT_ARRAY_BUFFER) ? sizeof(unsigned int):
     (tabla == GL_TEXTURE_COORD_ARRAY) ? sizeof(Tupla2f): sizeof(Tupla3f);

   // Calcular tamaño tabla
   unsigned long ttb = (unsigned long) teb*(unsigned long) cuenta;
   
   GLuint id_vbo=0; // Identificador VBO

   glGenBuffers(1, &id_vbo);  // Crear nuevo identificador VBO
   glBindBuffer(tipo, id_vbo); // Activar el nuevo VBO
   glBufferData(tipo, ttb, puntero, GL_STATIC_DRAW); // Transferir RAM->GPU
   glBindBuffer(tipo, 0); // No dejar activado el VBO
   return id_vbo ; // Devolver identificador
}

//----------------------------------------------------------------------------
// Especifica localización y estructura de una tabla

void LocForTabla( GLuint tipo_tabla, GLuint tabla, GLuint id_vbo,
                  GLvoid * p )
{
  // COMPLETAR: práctica 1
  // especificar localización y formato de la tabla
  // ...

  glBindBuffer(tipo_tabla, id_vbo); // Activar VBO (id==0 si está en RAM)
  if(tipo_tabla==GL_ARRAY_BUFFER) // Especificar estructura y puntero
    switch(tabla) {
    case GL_VERTEX_ARRAY: glVertexPointer(3,GL_FLOAT,0,p); break;
    case GL_TEXTURE_COORD_ARRAY: glTexCoordPointer(2,GL_FLOAT,0,p); break;
    case GL_COLOR_ARRAY: glColorPointer(3,GL_FLOAT,0,p); break;
    case GL_NORMAL_ARRAY: glNormalPointer(GL_FLOAT, 0, p); break;
    default: assert(false); break;
    }
}


//----------------------------------------------------------------------------
// habilita o deshabilita una tabla, si la habilita, especifica localización
// y estructura

void RegistrarTabla( GLuint tipo_tabla, GLuint tabla, GLsizei cuenta,
                     GLuint id_vbo, GLvoid * puntero_offset )
{
   // COMPLETAR: Práctica 1: implementar según el comportamiento descrito arriba:
   // usar 'glBindBuffer', 'glEnableClientState', 'glDisableClientState' y 'FijarPunteroTabla'
   // (al llamar a 'FijarPunteroTabla', se asume que el puntero es el offset nulo)
   // ....

  if(cuenta == 0 && tipo_tabla == GL_ARRAY_BUFFER)
    glDisableClientState(tabla); // desabilitar uso de una tabla vacía

  else {
    LocForTabla(tipo_tabla, tabla, id_vbo, puntero_offset);
    if(tipo_tabla == GL_ARRAY_BUFFER)
      glEnableClientState(tabla); // habilitar uso de la tabla
  }
}

// -----------------------------------------------------------------------------
// crea todos los VBOs

void MallaInd::crearVBOs()
{
   if ( vbos_creados )
      return ;

   CError();
   // COMPLETAR: práctica 1
   // Crear los VBOs de las 5 tablas posibles (llamar a 'CrearVBO')
   // almacenar los identificadores en las variables de instancia 'id_vbo_...'
   // .....

   id_vbo_col = CrearVBO(GL_ARRAY_BUFFER, GL_COLOR_ARRAY, col_ver.size(), col_ver.data());
   id_vbo_nor = CrearVBO(GL_ARRAY_BUFFER, GL_NORMAL_ARRAY, nor_ver.size(), nor_ver.data());
   id_vbo_cct = CrearVBO(GL_ARRAY_BUFFER, GL_TEXTURE_COORD_ARRAY, cc_tt_ver.size(), cc_tt_ver.data());
   id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, GL_VERTEX_ARRAY, vertices.size(), vertices.data());
   id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 0, 3*triangulos.size(), triangulos.data());
   
   CError();

   vbos_creados = true ;
}

// -----------------------------------------------------------------------------
// Registrar tablas en modo inmediato

void MallaInd::registrarTablas_MI()
{
   CError();
   // COMPLETAR: práctica 1
   // registrar las 4 tablas en modo inmediato (llamar a 'RegistrarTabla')
   // .....

   RegistrarTabla(GL_ARRAY_BUFFER, GL_VERTEX_ARRAY, vertices.size(), 0, vertices.data());
   RegistrarTabla(GL_ARRAY_BUFFER, GL_COLOR_ARRAY, col_ver.size(), 0, col_ver.data());
   RegistrarTabla(GL_ARRAY_BUFFER, GL_NORMAL_ARRAY, nor_ver.size(), 0, nor_ver.data());
   RegistrarTabla(GL_ARRAY_BUFFER, GL_TEXTURE_COORD_ARRAY, cc_tt_ver.size(), 0, cc_tt_ver.data());

   CError();
}

//--------------------------------------------------------------------------------
// Registrar tablas en modo diferido

void MallaInd::registrarTablas_MD()
{
   CError();
   // COMPLETAR: práctica 1
   // crear VBOs y registrar las 5 tablas en modo diferido (llamar a 'RegistrarTabla')
   // .....

   crearVBOs();
   
   RegistrarTabla(GL_ARRAY_BUFFER, GL_VERTEX_ARRAY, vertices.size(), id_vbo_ver, 0);
   RegistrarTabla(GL_ELEMENT_ARRAY_BUFFER, 0, 3*triangulos.size(), id_vbo_tri, 0);
   RegistrarTabla(GL_ARRAY_BUFFER, GL_COLOR_ARRAY, col_ver.size(), id_vbo_col, 0);
   RegistrarTabla(GL_ARRAY_BUFFER, GL_NORMAL_ARRAY, nor_ver.size(), id_vbo_nor, 0);
   RegistrarTabla(GL_ARRAY_BUFFER, GL_TEXTURE_COORD_ARRAY, cc_tt_ver.size(), id_vbo_cct, 0);

   CError();
}


// -----------------------------------------------------------------------------
// crear los dos VAOS: 'id_vao_attr' e 'id_vao_geom' , solo si no estaban creados

void MallaInd::crearActivarVAO_MD( )
{
   CError();
   // COMPLETAR: práctica 1
   // Crear (si no lo estaba) el VAO del M.D., y activarlo.
   // .....

   if(id_vao_md == 0){ // si VAO no creado
     glGenVertexArrays(1, &id_vao_md); // crea VAO
     glBindVertexArray(id_vao_md); // activar VAO
     registrarTablas_MD(); // registrar localización y formato tablas
   }
   else
     glBindVertexArray(id_vao_md); // activar VAO ya creado

   CError();
}



// -----------------------------------------------------------------------------

void MallaInd::visualizarGL_MI_DE( ContextoVis & cv )
{
   CError();
   using namespace std ;

   // COMPLETAR: Práctica 1: visualizar en modo inmediato (glDrawElements)
   // es necesario asegurarnos antes de que el VAO para M.I. está creado
   // (usando crearActivarVAO_MI), y luego llamar a 'glDrawElements')
   // al final, dejar activado el VAO por defecto
   // ....

   glBindVertexArray(0);
   registrarTablas_MI();

   glDrawElements(GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, triangulos.data());


   CError();

}
// ----------------------------------------------------------------------------

void MallaInd::visualizarGL_MD_VAO( ContextoVis & cv )
{
   // COMPLETAR: Práctica 1: visualizar en modo diferido (glDrawElements)
   // es necesario asegurarnos antes de que el VAO para M.D. está creado
   // (usando crearActivarVAO_MD), y luego llamar a 'glDrawElements')
   // al final, dejar activado el VAO por defecto

  crearActivarVAO_MD();

  glDrawElements(GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
}

// -----------------------------------------------------------------------------
// visualizar con begin/end (modo inmediato), enviando normales de triángulos y
// cc.tt. (adecuado para modo de sombreado plano)

void MallaInd::visualizarGL_MI_BE( ContextoVis & cv )
{
   // COMPLETAR: Práctica 1:
   // Visualizacion en modo inmediato usando begin/end
   // usar 'glBegin/glVertex/glEnd'
   // ..........

  const unsigned long nv = triangulos.size();

  glBegin(GL_TRIANGLES);
  for(unsigned long i=0; i<nv; i++){
    for(unsigned long j=0; j < 3; j++){
      if(col_ver.size()>0) glColor3fv(col_ver[triangulos[i][j]]);
      if(nor_ver.size()>0) glNormal3fv(nor_tri[triangulos[i][j]]);
      if(cc_tt_ver.size()>0) glTexCoord2fv(cc_tt_ver[triangulos[i][j]]);
      glVertex3fv(vertices[triangulos[i][j]]);
    }
  }
  glEnd();
}
// ----------------------------------------------------------------------------



// ----------------------------------------------------------------------------


void MallaInd::visualizarGL( ContextoVis & cv )
{

   using namespace std ;
   assert( cv.cauce_act != nullptr );

   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // guardar el color previamente fijado
   const Tupla4f color_previo = leerFijarColVertsCauce( cv );

   // COMPLETAR: práctica 1: visualizar según el modo (en 'cv.modo_envio')
   //   ** inmediato begin/end                   : usar 'visualizarGL_MI_BE'
   //   ** inmediato con un VAO (glDrawElements) : usar 'visualizarGL_MI_VAO'
   //   ** diferido con un VAO  (glDrawElements) : usar 'visualizarGL_MD_VAO'
   // .....

   switch(cv.modo_envio){
   case ModosEnvio::inmediato_begin_end:
     visualizarGL_MI_BE(cv);
     break;
   case ModosEnvio::inmediato_drawelements:
     visualizarGL_MI_DE(cv);
     break;
   case ModosEnvio::diferido_vao:
     visualizarGL_MD_VAO(cv);
     break;
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
   // llamar a 'calcularNormales' para el cálculo de normales
   // ..........................

   LeerPLY(nombre_arch, vertices, triangulos);

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

}
// -----------------------------------------------------------------------------------------------

// Clase Tetraedro

Tetraedro::Tetraedro():Tetraedro({1.0, 1.0, 1.0}){}

Tetraedro::Tetraedro(Tupla3f color) : MallaInd("Tetraedro de 4 vértices")
{

  vertices =
    {  { 1.0, 0.0, 1.0 }, // 0
       { 1.0, 0.0, -1.0 }, // 1
       { -1.0, +1.0, 0.0 }, // 2
       { -1.0, -1.0, 0.0 }, // 3
    } ;

  triangulos =
    {  {0,1,2}, {0,1,3},
       {0,2,3}, {1,2,3},
    } ;

  ponerColor(color);
}


// Clase Cubocolores

CuboColores::CuboColores() : MallaInd("Cubo de colores")
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


   col_ver= std::vector<Tupla3f>(8);

   for(int i = 0; i < vertices.size(); i++)
     for(int j = 0; j < 3; j++)
       col_ver[i][j]=vertices[i][j]*0.5+0.5;
}


// Prueba

Diamante::Diamante() : MallaInd("Diamante")
{

  //ponerColor({0.5, 0.9, 1});

  vertices =
    {
     {0,0.5,0}, // 0
     {1,0.5,0}, // 1 
     {0.5,0.5,0.866}, // 2
     {-0.5,0.5,0.866}, // 3
     {-1,0.5,0}, // 4
     {-0.5,0.5,-0.866}, // 5
     {0.5,0.5,-0.866}, // 6

     {1.5,0,0}, // 7
     {0.75,0,1.299}, // 8
     {-0.75,0,1.299}, // 9
     {-1.5,0,0}, // 10
     {-0.75,0,-1.299}, // 11
     {0.75,0,-1.299}, // 12

     {0,-2,0} // 13
    };


  col_ver= std::vector<Tupla3f>(13);

  col_ver[0]={1,1,1};
  for(int i = 1; i < vertices.size(); i++){

    if (vertices[i][1] == 0.5) col_ver[i] = {0.5,0.9,1};
  
    else if (vertices[i][1] == 0) col_ver[i] = {0,0.4,0.8};
  
    else col_ver[i] = {0,0,0.9};
  }  

  triangulos =
    {
     {0,1,2},
     {0,2,3},
     {0,3,4},
     {0,4,5},
     {0,5,6},
     {0,6,1},

     {1,7,2},     
     {2,8,3},     
     {3,9,4},     
     {4,10,5},     
     {5,11,6},
     {6,12,1},
     
     {7,8,2},
     {8,9,3},
     {9,10,4},
     {10,11,5},
     {11,12,6},
     {12,7,1},

     {7,8,13},
     {8,9,13},
     {9,10,13},
     {10,11,13},
     {11,12,13},
     {12,7,13}
    };
}

// caja
void MallaInd::calcularVerticesCaja(){

  float max_x, min_x, max_y, min_y, max_z, min_z;

  max_x = min_x = vertices[0][X];
  max_y = min_y = vertices[0][Y];
  max_z = min_z = vertices[0][Z];

  for (int i = 1; i < vertices.size(); i++){
    if (vertices[i][X]>max_x) max_x=vertices[i][X];
    if (vertices[i][X]<min_x) min_x=vertices[i][X];
    if (vertices[i][Y]>max_y) max_y=vertices[i][Y];
    if (vertices[i][Y]<min_y) min_y=vertices[i][Y];
    if (vertices[i][Z]>max_z) max_z=vertices[i][Z];
    if (vertices[i][Z]<min_z) min_z=vertices[i][Z];
  }

  std::vector<Tupla3f> v;
  
  v.push_back({min_x,min_y,min_z}); // 0
  v.push_back({min_x,min_y,max_z}); // 1
  v.push_back({min_x,max_y,min_z}); // 2
  v.push_back({min_x,max_y,max_z}); // 3
  v.push_back({max_x,min_y,min_z}); // 4
  v.push_back({max_x,min_y,max_z}); // 5
  v.push_back({max_x,max_y,min_z}); // 6
  v.push_back({max_x,max_y,max_z}); // 7

  vertices_caja.push_back(v[0]); // a
  vertices_caja.push_back(v[1]);
  vertices_caja.push_back(v[0]); // b
  vertices_caja.push_back(v[2]);
  vertices_caja.push_back(v[0]); // c
  vertices_caja.push_back(v[4]);
  vertices_caja.push_back(v[1]); // d
  vertices_caja.push_back(v[3]);
  vertices_caja.push_back(v[1]); // e
  vertices_caja.push_back(v[5]);
  vertices_caja.push_back(v[2]); // f
  vertices_caja.push_back(v[3]);
  vertices_caja.push_back(v[2]); // g
  vertices_caja.push_back(v[6]);
  vertices_caja.push_back(v[3]); // h
  vertices_caja.push_back(v[7]);
  vertices_caja.push_back(v[4]); // i
  vertices_caja.push_back(v[5]);
  vertices_caja.push_back(v[4]); // j
  vertices_caja.push_back(v[6]);
  vertices_caja.push_back(v[5]); // k
  vertices_caja.push_back(v[7]);
  vertices_caja.push_back(v[6]); // l
  vertices_caja.push_back(v[7]);
}


void MallaInd::visualizarGL_caja(ContextoVis & cv){

  calcularVerticesCaja();

  glLineWidth(2);
  
  const Tupla4f color_previo = cv.cauce_act->leerColorActual();
  glColor3f(1.0,0.5,0.5);
  
  // CrearActivar VAO
  if(id_vao_caja == 0){ // si VAO no creado
     glGenVertexArrays(1, &id_vao_caja); // crea VAO
     glBindVertexArray(id_vao_caja);

     // Crear VBOs
     id_vbo_ver_caja=CrearVBO(GL_ARRAY_BUFFER, GL_VERTEX_ARRAY, vertices_caja.size(), vertices_caja.data());

     // Registrar tabla
     RegistrarTabla(GL_ARRAY_BUFFER, GL_VERTEX_ARRAY, vertices_caja.size(), id_vbo_ver_caja, 0);

     
   }
   else
     glBindVertexArray(id_vao_caja); // activar VAO ya creado

  // VisualizarGL MD
  glDrawArrays(GL_LINES, 0, vertices_caja.size());

  glBindVertexArray(0);

  glLineWidth(1);

  glColor4fv( color_previo );
}


void MallaInd::visualizarElipse_MI(const int n, const float alpha, const float c, const float a, const float b){
	int aux=vertices_elipse.size();
	if(aux!=n){
		vertices.clear();
		for (int i=0;i<n;i++){
			float alpha=(float)2*M_PI*i/n
			vertices_elipse.push_back({cos(alpha),sen(alpha),0});
		}
	}

	glpushMatrix();
	glTranslatef(c,0,0);
	glRotatef(alpha,0,0,1);
	glScalef(a,b,0);

	//Relleno
	glDisable(DEPTH_TEST);
	glColor3f(0.5,0.5,0.5);
	glBindVertexArray(0);	
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glVertexPointer(3,GL_FLOAT,0,vertices_elipse.data();

      	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
   	
	glDrawArrays(GL_POLYGON, 0, vertices_elipse.size());

	//Borde
	glColor3f(1.0,1.0,1.0);
	glLineWidht(2.5);
	glDrawArrays(GL_LINE_LOOP, 0, vertices_elipse.size());
	
	glpopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glLineWidht(1.0);

}

void MallaInd::visualizarElipse_MD(const int n, const float alpha, const float c, const float a, const float b){
	int aux=vertices_elipse.size();
	
	if(aux!=n){
		vertices.clear();
		for (int i=0;i<n;i++){
			float alpha=(float)2*M_PI*i/n
			vertices_elipse.push_back({cos(alpha),sen(alpha),0});
		}
	}

	glpushMatrix();
	glTranslatef(c,0,0);
	glRotatef(alpha,0,0,1);
	glScalef(a,b,0);

	//Relleno
	glDisable(DEPTH_TEST);
	glColor3f(0.5,0.5,0.5);

	if(id_vao == 0){ // si VAO no creado
		glGenVertexArrays(1, &id_vao); // crea VAO
		glBindVertexArray(id_vao); // activar VAO
	}else glBindVertexArray(id_vao);

	if(aux!=n){ 
		
  		// Calcular tamaño tabla
  		 unsigned long ttb = (unsigned long) sizeof(Tupla3f)*(unsigned long) vertices_elipse.size();
   
		   GLuint id_vbo; // Identificador VBO

		   glGenBuffers(1, &id_vbo);  // Crear nuevo identificador VBO
		   glBindBuffer(GL_ARRAY_BUFFER, id_vbo); // Activar el nuevo VBO
		   glBufferData(GL_ARRAY_BUFFER, ttb, vertices_elipse.data(), GL_STATIC_DRAW); // Transferir RAM->GPU
        	   glVertexPointer(3,GL_FLOAT,0,vertices_elipse.data();
		   glEnableClientState(GL_VERTEX_ARRAY); // registrar localización y formato tablas
		   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		   glDisableClientState(GL_COLOR_ARRAY);
	           glDisableClientState(GL_NORMAL_ARRAY);
		   glBindBuffer(GL_ARRAY_BUFFER, 0); // No dejar activado el VBO	¿Aquí?
	}

      	
   	glDrawArrays(GL_POLYGON, 0, vertices_elipse.size());

	//Borde
	glColor3f(1.0,1.0,1.0);
	glLineWidht(2.5);
	glDrawArrays(GL_LINE_LOOP, 0, vertices_elipse.size());
	
	glpopMatrix();	
	//glDisableClientState(GL_VERTEX_ARRAY);//¿?
	//glBindBuffer(GL_ARRAY_BUFFER, 0); // No dejar activado el VBO ¿O aquí?
	glBindVertexArray(0); //¿?
	glLineWidht(1.0);
}



