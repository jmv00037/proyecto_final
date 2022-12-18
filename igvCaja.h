#ifndef __IGVCAJA
#define __IGVCAJA

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

class igvCaja
{
private:
	float* color;
	float gradosGuardados;

public:
	//Constructores y destructores
	igvCaja();
	igvCaja(float r, float g, float b);
	igvCaja(const igvCaja& orig);
	~igvCaja();

	//Método para visualizar una caja
	void visualizar();

	//Devuelve el color
	float* getColor();
	GLubyte* getColorByte(); //Para comparar con el pixel obtenido en la selección
	void setColorByte(float r, float g, float b);
	void setRotate(float grados);

};

#endif
