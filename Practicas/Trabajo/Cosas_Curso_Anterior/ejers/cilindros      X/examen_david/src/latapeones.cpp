
#include <math.h>
#include "ig-aux.h"
#include "matrices-tr.h"
#include "grafo-escena.h"
#include "malla-revol.h"
#include "materiales-luces.h"
#include "latapeones.h"

using namespace std;


LataPeones::LataPeones(){
  
  ponerNombre("Lata Peones");

  agregar(new Lata("Lata de Coca-Cola","../recursos/imgs/lata-coke.jpg"));

  entradas.back().objeto->ponerIdentificador(16711680); // Rojo en RGB
  
  agregar(MAT_Traslacion(0,1.4,4));

  // Peon 1

  NodoGrafoEscena* nodo_peon1 = new NodoGrafoEscena();

  Textura* text_peon1 = new TexturaXZ("../recursos/imgs/text-madera.jpg");
  
  Material* mat_peon1 = new Material(text_peon1,0.3,0.6,1.0,30.0);

  MallaRevol* peon1 = new MallaRevolPLY("../recursos/plys/peon.ply",30);

  peon1->ponerNombre("Peón de madera");
  peon1->ponerIdentificador(10046464); // Marrón en RGB
  
  nodo_peon1->agregar(mat_peon1);
  nodo_peon1->agregar(peon1);
  
  
  // Peon 2

  NodoGrafoEscena* nodo_peon2 = new NodoGrafoEscena();
  
  Material* mat_peon2 = new Material(0.2,0.9,0.1,1.0);

  MallaRevol* peon2 = new MallaRevolPLY("../recursos/plys/peon.ply",30);

  peon2->ponerNombre("Peón blanco");
  //peon2->ponerIdentificador(16777215); // Blanco en RGB
  peon2->ponerIdentificador(65535); // Cyan en RGB
  peon2->ponerColor({0.75,0.75,0.75});
  
  nodo_peon2->agregar(mat_peon2);
  nodo_peon2->agregar(peon2);

  
  // Peon 3

  NodoGrafoEscena* nodo_peon3 = new NodoGrafoEscena();
  
  Material* mat_peon3 = new Material(0.4,0.2,0.8,5.0);

  MallaRevol* peon3 = new MallaRevolPLY("../recursos/plys/peon.ply",30);

  peon3->ponerNombre("Peón negro");
  //peon3->ponerIdentificador(2105376); // Gris oscuro en RGB
  peon3->ponerIdentificador(13369446); // Rosa en RGB
  peon3->ponerColor({0.05,0.05,0.05});
  
  nodo_peon3->agregar(mat_peon3);
  nodo_peon3->agregar(peon3);


  agregar(nodo_peon1);  
  agregar(MAT_Traslacion(3,0,0));
  agregar(nodo_peon2);
  agregar(MAT_Traslacion(3,0,0));
  agregar(nodo_peon3);
}


Lata::Lata(const string nombre, const std::string & texturaJPG){

  ponerNombre(nombre);

  agregar(MAT_Escalado(5,5,5));

  // Parte superior
  
  NodoGrafoEscena* nodo_psup = new NodoGrafoEscena();

  Material* mat_psup = new Material(0.5,0.5,0.9,20.0);

  MallaRevol* psup = new MallaRevolPLY("../recursos/plys/lata-psup.ply",30);

  psup->ponerColor({0.5,0.5,0.5});

  nodo_psup->agregar(mat_psup);
  nodo_psup->agregar(psup);

  
  // Parte inferior
  
  NodoGrafoEscena* nodo_pinf = new NodoGrafoEscena();

  Material* mat_pinf = new Material(0.5,0.5,0.9,20.0);

  MallaRevol* pinf = new MallaRevolPLY("../recursos/plys/lata-pinf.ply",30);

  pinf->ponerColor({0.5,0.5,0.5});
  
  nodo_pinf->agregar(mat_pinf);
  nodo_pinf->agregar(pinf);


  // Parte central

  NodoGrafoEscena* nodo_pcue = new NodoGrafoEscena();

  Textura* text_pcue = new Textura(texturaJPG);
    
  Material* mat_pcue = new Material(text_pcue,0.5,0.4,1.0,40.0);

  MallaRevol* pcue = new MallaRevolPLY("../recursos/plys/lata-pcue.ply",30);

  nodo_pcue->agregar(mat_pcue);
  nodo_pcue->agregar(pcue);
  
  
  agregar(nodo_psup);
  agregar(nodo_pinf);
  agregar(nodo_pcue);
}


VariasLatasPeones::VariasLatasPeones(){

  ponerNombre("Varias Latas Peones");

  agregar(new LataPeones());

  agregar(MAT_Traslacion(4.5,0,0));

  agregar(new Lata("Lata de Pepsi", "../recursos/imgs/lata-pepsi.jpg"));

  entradas.back().objeto->ponerIdentificador(255); // Azul en RGB

  agregar(MAT_Traslacion(4.5,0,0));

  agregar(new Lata("Lata de la UGR", "../recursos/imgs/window-icon.jpg"));

  entradas.back().objeto->ponerIdentificador(8421504); // Gris en RGB
}
