#pragma once

#include <cstdlib>
#include "utils.h"
#include <GL\freeglut.h>

#include <stdio.h>
#include <GL/gl.h>		// GL Header File
#include <GL/glu.h>		// GL Utility Library(GLU) Header File
#include <GL/glut.h>

class cubo {
private:

	unsigned char* texturaSuelo;
	unsigned char* texturaPared;
	unsigned char* texturaPared2;
	unsigned char* puerta;
	unsigned char* torso;

	float textures[6][4][2] =
	{
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
		
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
		0.0, 0.0,
		
		0.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
		
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
		
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
		0.0, 0.0,
	};
	float cube[6][4][3] =
	{
	-1.0, -1.0, -1.0,
	-1.0, -1.0, 1.0,
	-1.0, 1.0, 1.0,
	-1.0, 1.0, -1.0,

	-1.0, -1.0, -1.0,
	-1.0, 1.0, -1.0,
	1.0, 1.0, -1.0,
	1.0, -1.0, -1.0,

	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0, -1.0, 1.0,
	-1.0, -1.0, 1.0,

	-1.0, -1.0, 1.0,
	1.0, -1.0, 1.0,
	1.0, 1.0, 1.0,
	-1.0, 1.0, 1.0,

	-1.0, 1.0, -1.0,
	-1.0, 1.0, 1.0,
	1.0, 1.0, 1.0,
	1.0, 1.0, -1.0,

	1.0, -1.0, -1.0,
	1.0, 1.0, -1.0,
	1.0, 1.0, 1.0,
	1.0, -1.0, 1.0,
	};

	float normals[6][3] =
	{
	-1,0,0, //1
	0,0,-1, //2
	0,-1,0, //3
	0,0,1, //4
	0,1,0, //5
	1,0,0,  //6

	};

public:
	cubo();
	~cubo();

	void dibujar(float sx, float sy, float sz, unsigned int repetir, unsigned int repetiY);
	void aplicarTexturas(unsigned int x);
	void cargarCubo(unsigned int x, unsigned int repetir, unsigned int repetiY);
	void sint(unsigned int x, unsigned int repetirX, unsigned int repetiY);
		
};

