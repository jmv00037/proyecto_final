#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "utils.h"
#
#include "igvFuenteLuz.h"
#include "robot.h"
#include "puerta.h"

struct parte {
    std::vector<float> vertices;
    std::vector<float> normales;
    std::vector<float> texturas;
    std::vector<unsigned int> triangulos;
};

enum {
    basex,
    cuerpoinferior,
    cuerposuperior,
    brazo
};

class igvEscena3D {
protected:
    cubo c;
    ////// Apartado C: a�adir qu� los atributos para el control de los grados de libertad del modelo
    float maxCabeza = 60, minCabeza = -60, maxPie = 60, minPie = -60, maxHom = 90, minHom = -130;
    float movimientoCabeza, movimientoHombroDer, movimientoHombroIzq, movimientoTorso, movimientoPiernaIzq, movimientoPiernaDer;
    // Otros atributos		
    bool ejes;
    // Partes del objeto
    parte pistola;
    bool cargadoCorrectamente;
   
    


public:
    std::vector<unsigned int> destruirBalas;
    std::vector<std::pair<igvPunto3D, float>> balas;  //vector de balas con la posicion y la velocidad
    std::vector<igvPunto3D> direccion; //vector de la direccion de cada bala
    float x = 0, z = 0,angX=0,angY=0;
    puerta p1, p2;
    float Puerta1=0, Puerta2 = 0;
    igvFuenteLuz luz;
    robot maniqui, maniqui2;
    // Constructores por defecto y destructor
    igvEscena3D();
    ~igvEscena3D();

    // metodo con las llamadas OpenGL para visualizar la escena
    void visualizar(void);

    ///// Apartado B: M�todos para visualizar cada parte del modelo
    void visualizarPartes(std::vector<float>& v, std::vector<float>& n, std::vector<unsigned int>& tri);
    puerta& getPuerta1() { return p1; }
    puerta& getPuerta2() { return p2; }
    void visualizarVB(void);
    void paredExterior(int x, int z);

    bool get_ejes() { return ejes; };
    void set_ejes(bool _ejes) { ejes = _ejes; };

    float getMaxCabeza() const;

    float getMinCabeza() const;

    float getMaxPie() const;

    float getMinPie() const;

    float getMaxHom() const;

    float getMinHom() const;

    void setPosicionCamara(igvPunto3D _posicion);
    void moverPuerta1();
    void moverPuerta2();
    void visualizarPuertas(void);
};

#endif