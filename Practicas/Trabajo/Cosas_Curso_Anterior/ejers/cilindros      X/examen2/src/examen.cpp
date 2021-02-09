#include <iostream>
#include <math.h>
#include "examen.h"
#include "malla-revol.h"
#include "latapeones.h"

using namespace std;

MallaCil::MallaCil(const int n): MallaInd( "Cilindro EXAMEN" ) {
	
	vertices.push_back({0,0,0});
	nor_ver.push_back({0.0,-1.0,0.0});
	cc_tt_ver.push_back({0.5,0.5});
	
	for(int i=0;i<=n;i++){
		const float 
		f=float(i)/float(n),
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
			triangulos.push_back({4*i+1,4*(i+1)+1,0});
			triangulos.push_back({4*i+2,4*i+3,4*(i+1)+2});
			triangulos.push_back({4*(i+1)+2,4*i+3,4*(i+1)+3});
			triangulos.push_back({4*i+4,4*(n+1)+1,4*(i+1)+4});
		}
		
	}
		vertices.push_back({0.0,1.0,0.0});
		nor_ver.push_back({0.0,1.0,0.0});
		cc_tt_ver.push_back({0.5,0.5});
}


NodoCil::NodoCil(const int n){
   ponerNombre("Cilindro ugr");
   agregar(MAT_Escalado(1.0,2.5,1.0));
   agregar(new Material(new Textura("../recursos/imgs/window-icon.jpg"),0.6,0.4,0.0,0.0));
   agregar(new MallaCil(n));
}

VariosCil::VariosCil(const int n){
   	agregar(new VariasLatasPeones()); 
	agregar(MAT_Traslacion(n*0.5+12,0,n*0.5+12));

	for(int i = 0; i < n; i++){
		NodoCil * cil=new NodoCil(20);
		cil->ponerIdentificador(i+801);
		NodoGrafoEscena * aux=new NodoGrafoEscena(); 
		aux->agregar(MAT_Rotacion((float)i*(float)360/n,0,1,0));	
		aux->agregar(MAT_Traslacion(n/2,0,0));
		cil->ponerNombre("Cilindro "+to_string(i+1));
		aux->agregar(cil);
		agregar(aux);
	}
}
