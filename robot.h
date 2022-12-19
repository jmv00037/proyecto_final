#ifndef __ROBOT
#define __ROBOT

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "cubo.h"
#include "igvPunto3D.h"

class robot {
private:
	bool estaMuerto = false;

	cubo* c;
	

	GLfloat color_pieza[3] = { 0,0.25,0 };
	GLfloat color_pieza2[3] = { 0.25,0,0 };
	GLfloat color_pieza3[3] = { 0.25,0.25,0 };

	int rotacionBaseX;
	int rotacionBaseY;
	int rotacionBaseZ;
	int rotacionHombro1X;
	int rotacionHombro1Z;
	int rotacionHombro2X;
	int rotacionHombro2Z;
	int rotacionCodo1;
	int rotacionCodo2;
	int rotacionCuello;
	int rotacionMano1;
	int rotacionMano2;
	int rotacionPierna1;
	int rotacionPierna2;

public:
	robot(igvPunto3D posicionRobot_, cubo* c_, int rotY);
	~robot();

	igvPunto3D posicionRobot;

	bool muerto() { return estaMuerto; }
	void revivir() { estaMuerto = false; }
	void morir() { estaMuerto = true; }

	void dibujar();

	void girar();
	void moverAdelante();
	void moverAtras();

	void ojo(double x, double y, double z);
	void dedo(double x, double y, double z);


	int get_rotacionBaseY() { return rotacionBaseY; };
	void set_rotacionBaseY(int _rotacionBaseY) { rotacionBaseY = _rotacionBaseY; };

	int get_rotacionBaseX() { return rotacionBaseX; };
	void set_rotacionBaseX(int _rotacionBaseX) { rotacionBaseX = _rotacionBaseX; };

	int get_rotacionBaseZ() { return rotacionBaseZ; };
	void set_rotacionBaseZ(int _rotacionBaseZ) { rotacionBaseZ = _rotacionBaseZ; };

	int get_rotacionHombro1X() { return rotacionHombro1X; };
	void set_rotacionHombro1X(int _rotacionHombro1X) { rotacionHombro1X = _rotacionHombro1X; };

	int get_rotacionHombro1Z() { return rotacionHombro1Z; };
	void set_rotacionHombro1Z(int _rotacionHombro1Z) { rotacionHombro1Z = _rotacionHombro1Z; };

	int get_rotacionHombro2X() { return rotacionHombro2X; };
	void set_rotacionHombro2X(int _rotacionHombro2X) { rotacionHombro2X = _rotacionHombro2X; };

	int get_rotacionHombro2Z() { return rotacionHombro2Z; };
	void set_rotacionHombro2Z(int _rotacionHombro2Z) { rotacionHombro2Z = _rotacionHombro2Z; };

	int get_rotacionCodo1() { return rotacionCodo1; };
	void set_rotacionCodo1(int _rotacionCodo1) { rotacionCodo1 = _rotacionCodo1; };

	int get_rotacionCodo2() { return rotacionCodo2; };
	void set_rotacionCodo2(int _rotacionCodo2) { rotacionCodo2 = _rotacionCodo2; };

	int get_rotacionCuello() { return rotacionCuello; };
	void set_rotacionCuello(int _rotacionCuello) { rotacionCuello = _rotacionCuello; };

	int get_rotacionMano1() { return rotacionMano1; };
	void set_rotacionMano1(int _rotacionMano1) { rotacionMano1 = _rotacionMano1; };

	int get_rotacionMano2() { return rotacionMano2; };
	void set_rotacionMano2(int _rotacionMano2) { rotacionMano2 = _rotacionMano2; };

	int get_rotacionPierna1() { return rotacionPierna1; };
	void set_rotacionPierna1(int _rotacionPierna1) { rotacionPierna1 = _rotacionPierna1; };

	int get_rotacionPierna2() { return rotacionPierna2; };
	void set_rotacionPierna2(int _rotacionPierna2) { rotacionPierna2 = _rotacionPierna2; };

	
};

#endif