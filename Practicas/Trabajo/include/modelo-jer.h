
#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP


#include "grafo-escena.h"
#include "malla-ind.h"


class PuntoApoyo :  public  NodoGrafoEscena {
    public:
        PuntoApoyo();
} ;

class Pupila : public NodoGrafoEscena{
    protected:
        Matriz4f * pm_desp_x = nullptr;
    public:
        Pupila();
        void actualizar_desplazamiento_pupila(const float tSec);
        unsigned leerNumParametros() const {return 1;};
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class Ojo : public  NodoGrafoEscena{
    protected:
        Pupila * pupila = nullptr;
    public:
        Ojo();
        unsigned leerNumParametros() const {return 1;};
        void actualizarEstadoParametro( const unsigned iParam, const float tSec);
};


class Brazo :   public NodoGrafoEscena{
    protected:
        PuntoApoyo * hombro = nullptr;
        Matriz4f * pm_rot_alpha = nullptr; //Rotazion eje Y
    public:
        Brazo(const float ang_z);
        void actualizar_rotacion_brazo(const float tSec);
        unsigned leerNumParametros() const {return 1;}
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);
} ;

class Tronco :  public NodoGrafoEscena {
    protected:
        Brazo * brazo_izq       = nullptr;
        Brazo * brazo_der       = nullptr;
        PuntoApoyo* pierna      = nullptr;
        //Matriz4f * pm_rot_y     = nullptr; //rotaccion eje Y
        //Matriz4f    * pm_desp_x = nullptr; //Desplazamiento eje X
    public:
        Tronco();
        //void actualizar_rotacion_tronco (const float tSec);
        unsigned leerNumParametros() const {return 2;};
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);
} ;





class Oreja :   public NodoGrafoEscena
{
    protected:
        Matriz4f * pm_rot_alpha = nullptr; //Rotacion eje Z
    public:
        Oreja();
        void fijarAnguloAlpha(const float rot_angulo_alpha);
} ;

class Cabeza :  public NodoGrafoEscena
{
    protected:
        Oreja * oreja_der = nullptr;
        Oreja * oreja_izq = nullptr;
        Ojo   * ojo_izq   = nullptr;
        Ojo   * ojo_der   = nullptr;
    public:
        Cabeza()   ;
        unsigned leerNumParametros(){return 2;};
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);

} ;

class Raiz  :   public  NodoGrafoEscena {

    protected:
        Tronco      * tronco    = nullptr;
        Cabeza      * cabezon   = nullptr;
        Matriz4f    * pm_rot_y  = nullptr; //rotaccion eje Y
        Matriz4f    * pm_desp_x = nullptr; 


        

    public:
        Raiz();
        void actualizar_desplazamiento_Vladimir (const float tSec);
        void actualizar_rotacion_Vladimir (const float tSec);
        unsigned leerNumParametros() const {return 6;};
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);
} ;





/*


class Pierna :  public NodoGrafoEscena
{
    public:
    Pierna()    ;
} ;

class Gorro :   public NodoGrafoEscena
{
    public:
    Gorro()     ;
} ;



*/




#endif