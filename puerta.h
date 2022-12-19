#ifndef __IGVCAJA
#define __IGVCAJA

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "cubo.h"

class puerta
{
private:
	float* color;
	float gradosGuardados;

public:
	//Constructores y destructores
	puerta();
	puerta(float r, float g, float b);
	puerta(const puerta& orig);
	~puerta();

	//Método para visualizar una caja
	void visualizarSinT(cubo& c);
	void visualizarConT(cubo& c);

	//Devuelve el color
	float* getColor();
	GLubyte* getColorByte(); //Para comparar con el pixel obtenido en la selección
	void setColorByte(float r, float g, float b);

};

#endif
