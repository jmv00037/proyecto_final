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
#include "cubo.h"

struct parte{
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
	float maxCabeza=60,minCabeza=-60,maxPie=60,minPie=-60,maxHom=90,minHom=-130;
    float movimientoCabeza,movimientoHombroDer,movimientoHombroIzq,movimientoTorso,movimientoPiernaIzq,movimientoPiernaDer;
	// Otros atributos		
	bool ejes;
    // Partes del objeto
    parte cabeza,brazoIzq,brazoDer,piernaIzq,piernaDer,torso,hombroDer,hombroIzq,piernaSupIzq,piernaSupDer,mundo;
    bool cargadoCorrectamente;

public:

	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// metodo con las llamadas OpenGL para visualizar la escena
	void visualizar(void);

	///// Apartado B: M�todos para visualizar cada parte del modelo
    void visualizarPartes(std::vector<float>& v, std::vector<float>& n, std::vector<unsigned int>& tri, std::vector<float>& tex);

	////// Apartado C: a�adir aqu� los m�todos para modificar los grados de libertad del modelo
	float restriccion(float angle, int min, int max, float& mov);
    float moverCabeza(float angle);
    float moverHombroDer(float angle);
    float moverHombroIzq(float angle);
    float moverPiernaDer(float angle);
    float moverPiernaIzq(float angle);
    void paredExterior(int x, int z);
    float moverTorso(float angle);

	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };

    float getMaxCabeza() const;

    float getMinCabeza() const;

    float getMaxPie() const;

    float getMinPie() const;

    float getMaxHom() const;

    float getMinHom() const;

};

#endif
