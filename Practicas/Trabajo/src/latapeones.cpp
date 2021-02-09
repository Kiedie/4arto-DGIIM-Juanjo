// Nombre: Juan José, Apellidos: Herrera Aranda, DNI/pasaporte: 26516011-R (DDGG IG curso 20-21)
#include <iostream>
#include <math.h>
#include "latapeones.h"
#include "malla-revol.h"

using namespace std;

Lata::Lata (const std::string & nombreArchivoJPG){

    agregar(MAT_Escalado(4.0,4.0,4.0));
    agregar(new Material(new Textura(nombreArchivoJPG),0.5,0.5,0.9,20));
    agregar(new MallaRevolPLY("../recursos/plys/lata-pcue.ply",50));

    agregar(new Material(0.3,0.3,0.7,30));
    agregar( new MallaRevolPLY("../recursos/plys/lata-psup.ply",50));

    agregar(new Material(0.3,0.3,0.7,30));
    agregar( new MallaRevolPLY("../recursos/plys/lata-pinf.ply",50));
}

LataPeones::LataPeones(){

    ponerNombre("LataPeones");

    NodoGrafoEscena * lata = new NodoGrafoEscena();
    lata->ponerIdentificador(411);
    lata->ponerNombre("Lata de Coca-Cola");
    lata->agregar ( new Lata("../recursos/imgs/lata-coke.jpg") );
    agregar(lata);


    //PEON DE MADERA
    agregar(MAT_Traslacion(0.0,1.4,3.0));
    NodoGrafoEscena * peon_m = new NodoGrafoEscena();
    peon_m->ponerIdentificador(421);
    peon_m->ponerNombre("Peon de madera");
    peon_m->agregar ( new Material (new TexturaXY("../recursos/imgs/text-madera.jpg"),0.2,0.3,0.4,30));
    peon_m->agregar ( new MallaRevolPLY("../recursos/plys/peon.ply",40));
    agregar(peon_m);


    //PEON BLANCO
    agregar(MAT_Traslacion(2.5,0,0));
    NodoGrafoEscena * peon_b = new NodoGrafoEscena();
    peon_b->ponerIdentificador(422);
    peon_b->ponerNombre("Peon blanco");
    peon_b->agregar ( new Material (0.1,0.9,0.0,1));
    peon_b->ponerColor({1,1,1});
    peon_b->agregar ( new MallaRevolPLY("../recursos/plys/peon.ply",40));
    agregar(peon_b);


    //PEON NEGRO
    agregar(MAT_Traslacion(2.5,0,2.5));
    NodoGrafoEscena * peon_n = new NodoGrafoEscena();
    peon_n->ponerIdentificador(423);
    peon_n->ponerNombre("Peon negro");
    peon_n->agregar ( new Material (0.1,0.9,0.0,1));
    peon_n->ponerColor({0.1,0.1,0.1});
    peon_n->agregar ( new MallaRevolPLY("../recursos/plys/peon.ply",40));
    agregar(peon_n);

}

VariasLatasPeones::VariasLatasPeones(){
    
    ponerNombre("Varias Latas Peones");
    agregar(new LataPeones());

    agregar(MAT_Traslacion(4.0,0.0,0.0));
    NodoGrafoEscena * lata_pepsi = new NodoGrafoEscena();
    lata_pepsi->ponerIdentificador(333);
    lata_pepsi->ponerNombre("pepsi");
    lata_pepsi->ponerIdentificador(412);
    lata_pepsi->ponerNombre("Lata de Pepsi");
    lata_pepsi->agregar(new Lata("""../recursos/imgs/lata-pepsi.jpg"));
    agregar(lata_pepsi);


    agregar(MAT_Traslacion(4.0,0.0,0.0));
    NodoGrafoEscena * lata_ugr = new NodoGrafoEscena();
    lata_ugr->ponerIdentificador(413);
    lata_ugr->ponerNombre("Lata de la UGR");
    lata_ugr->agregar(new Lata("../recursos/imgs/window-icon.jpg"));
    agregar(lata_ugr);
}



/** 

#include "malla-ind.h"
#include "malla-revol.h"
#include "objeto3d.h"
#include "latapeones.h"

Lata::Lata(const std::string & textura){
    agregar(MAT_Escalado(5.0,5.0,5.0));
    agregar(new BaseInferiorLata());
    agregar(new TapaSuperiorLata());
    agregar(new CuerpoLata(textura));

    ponerNombre("Lata completa");
}

BaseInferiorLata::BaseInferiorLata(){
    agregar(new Material(0.2,0.5,0.7,20.0));
    agregar(new MallaRevolPLY("../recursos/plys/lata-pinf.ply",50));

    ponerNombre("Base inferior de la lata");
}

TapaSuperiorLata::TapaSuperiorLata(){
    agregar(new Material(0.2,0.5,0.7,20.0));
    agregar(new MallaRevolPLY("../recursos/plys/lata-psup.ply",50));

    ponerNombre("Tapa superior de la lata");
}

CuerpoLata::CuerpoLata(const std::string & fichero){
    Textura * textura = new Textura(fichero);
    agregar(new Material(textura,0.3,0.5,0.3,20.0));
    agregar(new MallaRevolPLY("../recursos/plys/lata-pcue.ply",50));

    ponerNombre("Cuerpo de la lata");
}

PeonMadera::PeonMadera(){
    Textura * textura = new Textura("../recursos/imgs/text-madera.jpg");
    agregar(MAT_Traslacion(0.0,1.4,0.0));

    agregar(new Material(textura,0.3,0.5,0.3,20.0));
    agregar(new MallaRevolPLY("../recursos/plys/peon.ply",50));

    ponerNombre("Peón Madera");
}

PeonBlanco::PeonBlanco(){
    ponerColor({1.0,1.0,1.0});    
    agregar(MAT_Traslacion(0.0,1.4,0.0));

    agregar(new Material(0.3,0.5,0.3,20.0));
    agregar(new MallaRevolPLY("../recursos/plys/peon.ply",50));

    ponerNombre("Peón Blanco");
}

PeonNegro::PeonNegro(){
    ponerColor({0.0,0.0,0.0});    
    agregar(MAT_Traslacion(0.0,1.4,0.0));

    agregar(new Material(0.3,0.5,0.3,20.0));
    agregar(new MallaRevolPLY("../recursos/plys/peon.ply",50));

    ponerNombre("Peón Negro");
}

LataPeones::LataPeones(){
    agregar(new Lata("../recursos/imgs/lata-coke.jpg"));
    agregar(MAT_Traslacion(0.0,0.0,5.0));
    agregar(new PeonMadera());
    agregar(MAT_Traslacion(3.0,0.0,0.0));
    agregar(new PeonBlanco());
    agregar(MAT_Traslacion(3.0,0.0,0.0));
    agregar(new PeonNegro());

    ponerNombre("LataPeones");
}   */