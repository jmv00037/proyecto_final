#include "puerta.h"

#include <iostream>

puerta::puerta() {
	color = new float[3];
	color[0] = 0.0;
	color[1] = 0.0;
	color[2] = 0.0;
	gradosGuardados = 0;
};

puerta::puerta(float r, float g, float b) {
	color = new float[3];
	color[0] = r;
	color[1] = g;
	color[2] = b;
	gradosGuardados = 0;
};

puerta::puerta(const puerta& orig) :color(orig.color){
};

puerta::~puerta() {
	delete color;
};

/// <summary>
/// crea la puerta sin textura
/// </summary>
void puerta::visualizarSinT(cubo& c) {
	glScalef(0.9, 4, 5);
	c.sint(PUERTA, 1, 1);
};

/// <summary>
/// crea la puerta con textura
/// </summary>
void puerta::visualizarConT(cubo& c) {
	glScalef(0.9, 4, 5);
	c.cargarCubo(PUERTA, 1, 1);
};

float* puerta::getColor() {
	return color;
}

GLubyte* puerta::getColorByte() {
	GLubyte colorubyte[3];
	colorubyte[0] = (GLubyte)(color[0] * 255);
	colorubyte[1] = (GLubyte)(color[1] * 255);
	colorubyte[2] = (GLubyte)(color[2] * 255);

	return colorubyte;
}


void puerta::setColorByte(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

