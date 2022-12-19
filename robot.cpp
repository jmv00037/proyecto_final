#include "robot.h"






robot::robot(igvPunto3D posicionRobot_, cubo* c_, int rotY) {

	posicionRobot = posicionRobot_;
	c = c_;

	rotacionBaseX = 0;
	rotacionBaseY = rotY;
	rotacionBaseZ = 0;
	rotacionHombro1X = 0;
	rotacionHombro1Z = 0;
	rotacionHombro2X = 0;
	rotacionHombro2Z = 0;
	rotacionCodo1 = 0;
	rotacionCodo2 = 0;
	rotacionCuello = 0;
	rotacionMano1 = 0;
	rotacionMano2 = 0;
	rotacionPierna1 = 0;
	rotacionPierna2 = 0;

}

robot::~robot() {
	c = nullptr;
}

void robot::dibujar(){


	glTranslated(posicionRobot[0], posicionRobot[1], posicionRobot[2]);
	glRotated(rotacionBaseY, 0, 1, 0);
	glRotated(rotacionBaseX, 1, 0, 0);
	glRotated(rotacionBaseZ, 0, 0, 1);
	glPushMatrix(); //base
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza3);//base
	c->cargarCubo(TORSO, 1,1);
	//glutSolidCube(2);//base

	//----------------------

	glPushMatrix(); //NodoPierna 1
	glTranslated(-0.5, -1.25, 0); //NodoPierna 1
	glRotated(rotacionPierna1, 1, 0, 0); //NodoPierna1
	glScaled(0.5, 0.5, 0.5); //NodoPierna 1
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza2); //NodoPierna 1
	glutSolidCube(1); //NodoPierna 1


	glPushMatrix(); //Pierna1
	glTranslated(0, -2.75, 0); //Pierna1
	glScaled(1, 4.5, 1); //Pierna1
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza); //Pierna1
	glutSolidCube(1); //Pierna1


	glPushMatrix(); //Pie1
	glTranslated(0, -0.55, 0.75); //Pie1
	glScaled(1, 0.1, 2.5); //Pie1
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza3); //Pie1
	glutSolidCube(1); //Pie1
	glPopMatrix(); //Pie1


	glPopMatrix();	//Pierna1

	glPopMatrix(); //NodoPierna 1

	//------


	glPushMatrix(); //NodoPierna 2
	glTranslated(0.5, -1.25, 0); //NodoPierna 2
	glRotated(rotacionPierna2, 1, 0, 0); //NodoPierna2
	glScaled(0.5, 0.5, 0.5); //NodoPierna 2
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza2); //NodoPierna 2
	glutSolidCube(1); //NodoPierna 2


	glPushMatrix(); //Pierna2
	glTranslated(0, -2.75, 0); //Pierna2
	glScaled(1, 4.5, 1); //Pierna2
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza); //Pierna2
	glutSolidCube(1); //Pierna2


	glPushMatrix(); //Pie2
	glTranslated(0, -0.55, 0.75); //Pie2
	glScaled(1, 0.1, 2.5); //Pie2
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza3); //Pie2
	glutSolidCube(1); //Pie2
	glPopMatrix(); //Pie2

	glPopMatrix();	//Pierna2

	glPopMatrix(); //NodoPierna 2

	//----------------------

	glPushMatrix();//cuello
	glTranslated(0, 1.25, 0); //cuello
	glRotated(rotacionCuello, 0, 1, 0);//cuello
	glScaled(0.3, 0.5, 0.3); //cuello
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza);//cuello
	glutSolidCube(1); //cuello

	glPushMatrix(); //cabeza
	glTranslated(0, 1.8, 0); //cabeza
	glScaled(4.16, 2.5, 4.16); //cabeza
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza2);//cabeza
	glutSolidCube(1); //cabeza

	ojo(0.2, 0.1, 0.35);
	ojo(-0.2, 0.1, 0.35);

	glPopMatrix(); //cabeza

	glPopMatrix();//cuello

	//-------------------------------------------------------------

	glPushMatrix();//Hombro 1
	glTranslated(1.25, 0.75, 0); //Hombro 1
	glRotated(rotacionHombro1X, 1, 0, 0);//Hombro 1
	glRotated(rotacionHombro1Z, 0, 0, 1);//Hombro 1
	glScaled(0.5, 0.5, 0.5);//Hombro 1
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza2); //Hombro 1
	glutSolidCube(1); //Hombro 1


	glPushMatrix(); //brazo superior 1
	glTranslated(0, -1.75, 0); //brazo superior 1
	glScaled(1, 2.5, 1); //brazo superior 1
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza); //brazo superior 1
	glutSolidCube(1); //brazo superior 1


	glPushMatrix();//Codo 1 
	glTranslated(0, -0.60, 0);//Codo 1
	glScaled(1, 0.4, 1);//Codo 1
	glRotated(rotacionCodo1, 1, 0, 0);//Codo 1
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza2);//Codo 1
	glutSolidCube(1); //Codo 1


	glPushMatrix(); //brazo inferior 1
	glTranslated(0, -1.75, 0); //brazo inferior 1
	glScaled(1, 2.5, 1); //brazo inferior 1
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza); //brazo inferior 1
	glutSolidCube(1); //brazo inferior 1


	glPushMatrix();//Mano 1
	glTranslated(0, -0.60, 0);//Mano 1
	glScaled(1, 0.4, 1);//Mano 1
	glRotated(rotacionMano1, 1, 0, 0);//Mano 1
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza2);//Mano 1
	glutSolidCube(1); //Mano 1

	dedo(-0.2, -0.8, 0.4);
	dedo(0, -0.8, 0.4);
	dedo(0.2, -0.8, 0.4);
	dedo(0.4, -0.8, 0.4);
	dedo(-0.4, -0.8, 0);

	glPopMatrix(); //Mano 1

	glPopMatrix(); //brazo inferior 1

	glPopMatrix();//Codo 1

	glPopMatrix(); //brazo superior 1

	glPopMatrix();//Hombro 1

	//-------------------------------------------------------------

	glPushMatrix();//Hombro 2
	glTranslated(-1.25, 0.75, 0); //Hombro 2
	glRotated(rotacionHombro2X, 1, 0, 0);//Hombro 2
	glRotated(rotacionHombro2Z, 0, 0, 1);//Hombro 2
	glScaled(0.5, 0.5, 0.5);//Hombro 2
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza2); //Hombro 2
	glutSolidCube(1); //Hombro 2


	glPushMatrix(); //brazo superior 2
	glTranslated(0, -1.75, 0); //brazo superior 2
	glScaled(1, 2.5, 1); //brazo superior 2
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza); //brazo superior 2
	glutSolidCube(1); //brazo superior 2


	glPushMatrix();//Codo 2
	glTranslated(0, -0.60, 0);//Codo 2
	glScaled(1, 0.4, 1);//Codo 2
	glRotated(rotacionCodo2, 1, 0, 0);//Codo 2
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza2);//Codo 2
	glutSolidCube(1); //Codo 2


	glPushMatrix(); //brazo inferior 2
	glTranslated(0, -1.75, 0); //brazo inferior 2
	glScaled(1, 2.5, 1); //brazo inferior 2
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza); //brazo inferior 2
	glutSolidCube(1); //brazo inferior 2


	glPushMatrix();//Mano 2
	glTranslated(0, -0.60, 0);//Mano 2
	glScaled(1, 0.4, 1);//Mano 2
	glRotated(rotacionMano2, 1, 0, 0);//Mano 2
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza2);//Mano 2
	glutSolidCube(1); //Mano 2


	dedo(-0.2, -0.8, 0.4);
	dedo(0, -0.8, 0.4);
	dedo(0.2, -0.8, 0.4);
	dedo(0.4, -0.8, 0.4);
	dedo(-0.4, -0.8, 0);


	glPopMatrix(); //Mano 2

	glPopMatrix(); //brazo inferior 2

	glPopMatrix();//Codo 2

	glPopMatrix(); //brazo superior 2

	glPopMatrix();//Hombro 2





	glPopMatrix(); //base
}

void robot::girar() {
	if (rotacionBaseY == 180)
		rotacionBaseY = 0;
	else
		rotacionBaseY = 180;
}

void robot::ojo(double x, double y, double z) {
	GLfloat color_pieza[] = { 0,0.25,0 };
	GLfloat color_pieza2[] = { 0.25,0,0 };
	GLfloat color_pieza3[] = { 0.25,0.25,0 };

	glPushMatrix();
	glTranslated(x, y, z);
	glScaled(0.1, 0.1, 0.1);
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza3);
	glutSolidSphere(2, 100, 100);
	glPopMatrix();
}

void robot::moverAdelante(){
	posicionRobot[Z] += 0.05;
}

void robot::moverAtras() {
	posicionRobot[Z] -= 0.05;
}

void robot::dedo(double x, double y, double z) {
	GLfloat color_pieza[] = { 0,0.25,0 };
	GLfloat color_pieza2[] = { 0.25,0,0 };
	GLfloat color_pieza3[] = { 0.25,0.25,0 };

	glPushMatrix();//Dedo
	glTranslated(x, y, z);//Dedo
	glScaled(0.2, 0.8, 0.2);//Dedo
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza3);//Dedo
	glutSolidCube(1); //Dedo
	glPopMatrix(); //dedo
}

