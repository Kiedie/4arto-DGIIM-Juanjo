// *********************************************************************
// **
// ** Informática Gráfica, curso 2016-17
// ** Declaraciones de la clase Objeto3D.hpp
// **
// *********************************************************************

#ifndef IG_MALLAIND_HPP
#define IG_MALLAIND_HPP

#include <vector>          // usar std::vector

#include "objeto3d.h"   // declaración de 'Objeto3D'
// ---------------------------------------------------------------------
// clase para objetos gráficos genéricos

class MallaInd : public Objeto3D
{

protected:
  // COMPLETAR: incluir aquí las variables y métodos privados que sean
  // necesarios para una malla indexada
  // ......


  //caja
  std::vector<Tupla3f> vertices_caja;
  GLuint id_vao_caja=0, id_vbo_ver_caja;
  
  void calcularVerticesCaja();
  void visualizarGL_caja(ContextoVis & cv);

  std::vector<Tupla3f> vertices_elipse;
  GLuint id_vao=0, id_vbo;
  //void calcularVerticesElipse(const int n, const float alpha, const float a, const float b);
  void visualizarElipse_MI(const int n, const float alpha, const float c, const float a, const float b);
  void visualizarElipse_MD(const int n, const float alpha, const float c, const float a, const float b);

  //caja
  
  std::vector<Tupla3f> vertices ;
  std::vector<Tupla3i> triangulos ;

  std::vector<Tupla3f> col_ver ;  // colores de los vértices
  std::vector<Tupla3f> nor_ver ;  // normales de vértices
  std::vector<Tupla3f> nor_tri ;  // normales de triangulos
  std::vector<Tupla2f> cc_tt_ver ; // coordenadas de textura de los vértices

  // identificadores de VBO
  GLuint
  id_vbo_col, // colores
    id_vbo_nor, // normales
    id_vbo_cct, // coord. de textura
    id_vbo_ver, // posiciones o coordenadas de vértices
    id_vbo_tri; // triángulos (índices)

  bool vbos_creados = false ;

  // identificadores de 'vertex array object' (VAO)
  // (si no se han creado todavía, es 0)
  GLuint id_vao_md = 0; // VAO del modo diferido, (0 si no inicializado aún)

      
  // VAOs para modo inmediato y modo diferido
  void crearActivarVAO_MD(  ) ;

  void crearActivarVAO_MD_geom(  ) ;

  // crea todos los VBOS (solo la primera vez)
  void crearVBOs();

  // resgistrar las tablas en los distintos modos de envío
  void registrarTablas_MI();
  void registrarTablas_MD();

  void registrarTablas_MD_geom();

  // visualizar con begin/end (modo inmediato)
  void visualizarGL_MI_BE( ContextoVis & cv );

  // visualizar con 'draw elements', en modo inmediato, usando 'id_vao_mi'
  void visualizarGL_MI_DE( ContextoVis & cv );

  // visualizar con 'draw elements', en modo diferido, usando 'id_vao_md'
  void visualizarGL_MD_VAO( ContextoVis & cv );

  // normales de triángulos y vértices
  void calcularNormales();

  // calculo de las normales de triángulos (solo si no están creadas ya)
  void calcularNormalesTriangulos() ;

public:
  // crea una malla vacía (nombre: "malla indexada nueva vacía")
  MallaInd() ;

  // crea una malla vacía con un nombre concreto:
  MallaInd( const std::string & nombreIni );

  // visualizar el objeto con OpenGL
  virtual void visualizarGL( ContextoVis & cv ) ;




} ;
// ---------------------------------------------------------------------
// Clase para mallas obtenidas de un archivo 'ply'
// es un tipo de malla indexada que define un nuevo constructor
// que recibe el nombre del archivo ply como parámetro

class MallaPLY : public MallaInd
{
public:
  MallaPLY( const std::string & nombre_arch ) ;
} ;


// ---------------------------------------------------------------------

class Cubo : public MallaInd
{
public:
  Cubo();
};

class Tetraedro : public MallaInd
{
public:
  Tetraedro();
  Tetraedro(Tupla3f color);
};

class CuboColores : public MallaInd
{
public:
  CuboColores();
};


// Prueba

class Diamante : public MallaInd
{

public:
  Diamante();
};

#endif
