
#include <math.h>
#include "ig-aux.h"
#include "matrices-tr.h"
#include "grafo-escena.h"
#include "malla-revol.h"
#include "materiales-luces.h"
#include "examen.h"
#include "latapeones.h"

using namespace std;


MallaCil::MallaCil(const int n)
{
	for(int i = 0; i <= n; i++){
		const float
		f=float(i)/float(n),
		ang=2.0*M_PI*f, vx=cos(ang),vy=sin(ang);
		
		vertices.push_back({vx,vy,-1.0}); // trasero	
		nor_ver.push_back({vx,vy,0});
		cc_tt_ver.push_back({1-f,0});
		
		vertices.push_back({vx,vy,0.0});  // delantero
		nor_ver.push_back({vx,vy,0});
		cc_tt_ver.push_back({1-f,1});
		
		vertices.push_back({vx,vy,0.0});  // delantero tapa
		nor_ver.push_back({0,0,1});
		cc_tt_ver.push_back({(vx+1)*0.5,(1-vy)*0.5});
		
		if(i<n){
			triangulos.push_back({3*i,3*i+1,3*(i+1)});
			triangulos.push_back({3*(i+1),3*i+1,3*(i+1)+1});
			triangulos.push_back({3*i+2,3*(n+1),3*(i+1)+2});
		}
	}
	vertices.push_back({0.0,0.0,0.0});
	nor_ver.push_back({0,0,1});
	cc_tt_ver.push_back({0.5,0.5});	
}

NodoCil::NodoCil(const int n)
{
    Textura* text_ugr = new Textura("../recursos/imgs/window-icon.jpg");
    agregar(MAT_Escalado(1,1,2.5));
    agregar(new Material(text_ugr,0.5,0.3,0.7,20.0));
	agregar(new MallaCil(n));
}

Cilindros::Cilindros(const int n){
	
	int id = 0;
	CilVertical* cil;
	
	cil = new CilVertical(24,n*0.5);
	cil->ponerIdentificador(10+id);
	cil->ponerNombre("Cilindro UGR");
	id++;
	agregar(cil);
	
	
	for(int i = 0; i < n-1; i++){
		agregar(MAT_Rotacion(360.0/n,0,1,0));
		cil = new CilVertical(24,n*0.5);
		cil->ponerIdentificador(10+id);
		cil->ponerNombre("Cilindro UGR");
		id++;
		agregar(cil);
	}
}

VariosCil::VariosCil(const int n){
	
	ponerNombre("Varios Cilindros");
	
	agregar(new VariasLatasPeones());
	agregar(MAT_Traslacion(n*0.5+8,0,n*0.5+8));
	agregar(new Cilindros(n));
	
}


CilVertical::CilVertical(const int n, float desplazamiento){
	
	agregar(MAT_Traslacion(desplazamiento,2.5,0));
	agregar(MAT_Rotacion(-90,1,0,0));
	agregar(new NodoCil(n));	
}

