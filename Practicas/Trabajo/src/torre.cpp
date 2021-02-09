// Nombre: Juan José, Apellidos: Herrera Aranda, DNI/pasaporte: 26516011-R (DDGG IG curso 20-21)
#include <iostream>
#include <math.h>
#include "torre.h"
#include "malla-revol.h"



Torre::Torre(const int n) : MallaInd("Torre de tamaño n"){

    //Vamos a generar n cubos, solo nos hacen falta 4 vertices y el resto
    //los conseguimos por traslación
    vertices = {
        {-1, -1,  -1},
        {-1, -1,  +1},
        {+1, -1,  +1},
        {+1, -1,  -1},
    };

    //Ahora metemos el resto de vertices
    //En verdad lo que estamos haciendo es meter las caras
    for (unsigned i = 0 ; i < n ; i++){     //Metemos n veces
        for(int j = 0 ; j < 4; j++)         //Los cuator vertices
            vertices.push_back((Tupla3f)(MAT_Traslacion(0,i,0)*vertices[j]));
    }

    //Ahora metemos el pico de la torre 
    vertices.push_back({0.0,n+1,0.0});

    //Hacemos la triangulación de los cubos
    for (unsigned i = 0 ; i < vertices.size() ; i++)
        for(int j = 0 ; j < 4 ; j++){
            int k=i*4+j;
            triangulos.push_back({k,k+4,k+4+1});
            triangulos.push_back({k,k+4+1,k+1});            
        }
    //Hacemos la triangulación de la cuspid de la tore

    triangulos.push_back({4*n,      4*n+1,  4*(n+1)});
    triangulos.push_back({4*n+1,    4*n+2,  4*(n+1)});
    triangulos.push_back({4*n+2,    4*n+3,  4*(n+1)});
    triangulos.push_back({4*n+3,    4*n,    4*(n+1)});
}


ConjuntoTorres::ConjuntoTorres(const int alt, const int ntorres){
    
    assert(ntorres>0);
    tam = ntorres;
    float alpha = 2*M_PI/tam;

    //Metemos la primera torre por cortesía
    NodoGrafoEscena * torre = new NodoGrafoEscena();
    torre->ponerNombre("Torre" + std::to_string(1));

    //unsigned  ind_rt = agregar(MAT_Rotacion(0,0,1,0));
    //unsigned  ind = torre->agregar(MAT_Rotacion(0,0,1,0)); //Vamos a animarla con una rotación en torno al eje Y
    torre->agregar(MAT_Traslacion(ntorres*cos(0*alpha),0,ntorres*sin(0*alpha)));               
    torre->agregar(new Torre(alt));
    agregar(torre);                 
    //rota.push_back(torre->leerPtrMatriz(ind));           
    //rotacion_general = leerPtrMatriz(ind_rt);
    
    for(int i = 1 ; i < tam; i++){
        NodoGrafoEscena * torrecita = new NodoGrafoEscena();
        torrecita->ponerNombre("Torre"  + std::to_string(i));
        //ind = torrecita->agregar(MAT_Rotacion(0,0,1,0));
        torrecita->agregar(MAT_Traslacion(ntorres*cos(alpha*i),0,ntorres*sin(i*alpha)));
        torrecita->agregar (new Torre(alt));
        agregar(torrecita);
        //rota.push_back(torre->leerPtrMatriz(ind));
    }
}



/**void ConjuntoTorres::actualizar_rotacion(const float tSec){
       
    float   n = 4;        //Oscilaciones por segundo
    for(unsigned i = 0 ; i <= tam ; i++)
        *rota[i] = MAT_Rotacion(2*M_PI*tSec*n,0,1,0);
}
*/

/**void ConjuntoTorres::actualizar_rotacion_general(const float tSec){
    float   n = 0.5;        //Oscilaciones por segundo
    float   v = 2*M_PI*n*tSec;
    *rotacion_general = MAT_Rotacion(v,0,1,0);
}*/

/**void ConjuntoTorres::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    assert(iParam < leerNumParametros());
    switch(iParam){
        default:
            //std::cout << "bucle" << std::endl;
            //actualizar_rotacion(tSec);
        break;
    }  
    
}*/

