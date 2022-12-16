#ifndef __IGVTEXTURA
#define __IGVTEXTURA

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>

#include "bmp.h"

class igvTextura {

	public:
		// Atributos

		unsigned int idTextura; // identificador de la textura
		unsigned int alto,  // alto de la textura
			           ancho; // ancho de la textura
		GLubyte* imagen;

		// Metodos

	public:
		// Constructores por defecto y destructor
		igvTextura() = default; // Textura ajedrez de 64 x 64 texeles
		igvTextura(const char *fichero); // Textura cargada desde un fichero BMP
		~igvTextura();

		// Metodos
		void aplicar(void);
};

#endif

