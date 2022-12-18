#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"
#include "igvTextura.h"
#include <iostream>
#include "igvInterfaz.h"
#include "igvCamara.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Metodos constructores 

igvEscena3D::igvEscena3D() : maniqui(igvPunto3D(5, 5, 5)) {
	ejes = true;
    movimientoCabeza=0; movimientoHombroDer=0,movimientoHombroIzq=0;
    //Se cargan del fichero los objetos y se guardan
    
    posicionCamara.set(0.0,0.0,0.0);
    
    system("cd");
    std::string ruta = "modelos\\";
    std::string pMundo = ruta + "Dungeon.obj";
    utils::cargaOBJ(&pMundo[0], mundo.vertices, mundo.texturas, mundo.normales, mundo.triangulos);
    
    std::string pCabeza = ruta + "cabeza.obj";
    std::string pTorso = ruta +"torso.obj";
    std::string pBrazoIzq = ruta +"brazoIzq.obj";
    std::string pBrazoDer = ruta +"brazoDer.obj";
    std::string pPiernaIzq = ruta +"piernaIzq.obj";
    std::string pPiernaDer = ruta +"piernaDer.obj";
    std::string pHombroIzq = ruta +"hombroIzq.obj";
    std::string pHombroDer = ruta +"hombroDer.obj";
    std::string pPiernaSupIzq = ruta +"piernaSuperiorIzq.obj";
    std::string pPiernaSupDer = ruta +"piernaSuperiorDer.obj";
    if(utils::cargaOBJ(&pCabeza[0],cabeza.vertices,cabeza.texturas,cabeza.normales,cabeza.triangulos) &&
       utils::cargaOBJ(&pTorso[0],torso.vertices,torso.texturas,torso.normales,torso.triangulos) &&
       utils::cargaOBJ(&pBrazoIzq[0],brazoIzq.vertices,brazoIzq.texturas,brazoIzq.normales,brazoIzq.triangulos) &&
       utils::cargaOBJ(&pBrazoDer[0],brazoDer.vertices,brazoDer.texturas,brazoDer.normales,brazoDer.triangulos) &&
       utils::cargaOBJ(&pPiernaIzq[0],piernaIzq.vertices,piernaIzq.texturas,piernaIzq.normales,piernaIzq.triangulos) &&
       utils::cargaOBJ(&pPiernaDer[0],piernaDer.vertices,piernaDer.texturas,piernaDer.normales,piernaDer.triangulos) &&
       utils::cargaOBJ(&pHombroIzq[0],hombroIzq.vertices,hombroIzq.texturas,hombroIzq.normales,hombroIzq.triangulos) &&
       utils::cargaOBJ(&pHombroDer[0],hombroDer.vertices,hombroDer.texturas,hombroDer.normales,hombroDer.triangulos) &&
       utils::cargaOBJ(&pPiernaSupIzq[0],piernaSupIzq.vertices,piernaSupIzq.texturas,piernaSupIzq.normales,piernaSupIzq.triangulos) &&
       utils::cargaOBJ(&pPiernaSupDer[0],piernaSupDer.vertices,piernaSupDer.texturas,piernaSupDer.normales,piernaSupDer.triangulos))
        cargadoCorrectamente = true;
    else
        cargadoCorrectamente = false;
	// Apartado C: inicializar los atributos para el control de los grados de libertad del modelo 


    pulsaY = 1;
    pulsaX = 1;
    pulsaZ = 1;



    int numero = 50;
    for (int i = 0; i < 10; i++) {
        r[i] = g[i] = b[i] = numero;
        numero++;
    }

    //r[0] = g[0] = b[0] = 52;
    //r[1] = g[1] = b[1] = 51;
    //r[2] = g[2] = b[2] = 50;

    //GLfloat r[] = { 254, 150, 50 };
    //GLfloat g[] = { 254, 150, 50 };
    //GLfloat b[] = { 254, 150, 50 };

    for (int pilasY = 0; pilasY < pulsaY; pilasY++) {
        //r[pilasY] += 1;
        for (int pilasX = 0; pilasX < pulsaX; pilasX++) {
            //g[pilasX] += 1;
            for (int pilasZ = 0; pilasZ < pulsaZ; pilasZ++) {
                cajas.push_back(new igvCaja(r[pilasY] / 255, g[pilasX] / 255, b[pilasZ] / 255)); //Se crea una nueva caja con el color indicado
                //b[pilasZ] += 1;
            }
        }
    }
    
}

igvEscena3D::~igvEscena3D() {

}


// Metodos publicos 

void pintar_ejes(void) {
	GLfloat rojo[] = { 1,0,0,1.0 };
	GLfloat verde[] = { 0,1,0,1.0 };
	GLfloat azul[] = { 0,0,1,1.0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
	glBegin(GL_LINES);
	glVertex3f(1000, 0, 0);
	glVertex3f(-1000, 0, 0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_EMISSION, verde);
	glBegin(GL_LINES);
	glVertex3f(0, 1000, 0);
	glVertex3f(0, -1000, 0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_EMISSION, azul);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 1000);
	glVertex3f(0, 0, -1000);
	glEnd();
}

///// Apartado B: M�todos para visualizar cada parte del modelo

void igvEscena3D::visualizarPartes(std::vector<float> &v, std::vector<float> &n, std::vector<unsigned int> &tri, std::vector<float>& tex) {
    glFlush();

    glEnable(GL_TRIANGLES);
    glShadeModel(GL_SMOOTH);


    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &v[0]);

    glDrawElements(GL_TRIANGLES, tri.size(), GL_UNSIGNED_INT, &tri[0]);
    glDisableClientState(GL_VERTEX_ARRAY);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT,0,&n[0]);

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    t.aplicar();
    glTexCoordPointer(2,GL_FLOAT,0, &n[0]);
    glDrawArrays(GL_QUADS, 0, 4);
    t.aplicar();
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

////// Apartado C: a�adir aqu� los m�todos para modificar los grados de libertad del modelo
float igvEscena3D::restriccion(float angle, int min, int max, float& mov){
    return (angle<=max && angle>=min) ? mov=angle : mov;
}

float igvEscena3D::moverCabeza(float angle) {
    return restriccion(angle,minCabeza,maxCabeza,movimientoCabeza);
}

float igvEscena3D::moverHombroDer(float angle) {
    return restriccion(angle,minHom,maxHom,movimientoHombroDer);
}

float igvEscena3D::moverHombroIzq(float angle) {
    return restriccion(angle,minHom,maxHom,movimientoHombroIzq);
}

float igvEscena3D::moverTorso(float angle) {
    return movimientoTorso = angle;
}

float igvEscena3D::moverPiernaDer(float angle) {
    return restriccion(angle,minPie,maxPie,movimientoPiernaDer);
}

float igvEscena3D::moverPiernaIzq(float angle) {
    return restriccion(angle,minPie,maxPie,movimientoPiernaIzq);
}

/*static void drawBox(GLfloat size, GLenum type)
{
    static GLfloat n[6][3] =
    {
      {-1.0, 0.0, 0.0},
      {0.0, 1.0, 0.0},
      {1.0, 0.0, 0.0},
      {0.0, -1.0, 0.0},
      {0.0, 0.0, 1.0},
      {0.0, 0.0, -1.0}
    };
    static GLint faces[6][4] =
    {
      {0, 1, 2, 3},
      {3, 2, 6, 7},
      {7, 6, 5, 4},
      {4, 5, 1, 0},
      {5, 6, 2, 1},
      {7, 4, 0, 3}
    };
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

    for (i = 5; i >= 0; i--) {
        glBegin(type);
        glNormal3fv(&n[i][0]);
        glTexCoord2f(0, 0);
        glVertex3fv(&v[faces[i][0]][0]);
        glTexCoord2f(0, 1);
        glVertex3fv(&v[faces[i][1]][0]);
        glTexCoord2f(1, 1);
        glVertex3fv(&v[faces[i][2]][0]);
        glTexCoord2f(1, 0);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}*/

/*
Esta funci�n genera un cubo s�lido al que se le pueden a�adir texturas (la funci�n glutSolidCube por defecto de GLUT no permite esto).
@param size Tama�o.
*/
void glutSolidCubeTextured(GLdouble size)
{
    /*drawBox(size, GL_QUADS);*/
}


void igvEscena3D::setPosicionCamara(igvPunto3D _posicion) {
    posicionCamara = _posicion;
}


void igvEscena3D::visualizar() {
	// crear luces
	//GLfloat luz0[4] = { 5.0,5.0,5.0,1 }; // luz puntual
	//glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aqu� si permanece fija y no se mueve con la escena
	//glEnable(GL_LIGHT0);

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

    pintar_ejes();

    //igvFuenteLuz luzPuntual(GL_LIGHT0, posicionCamara, igvColor(0.0, 0.0, 0.0, 1.0), igvColor(1.0, 1.0, 1.0, 1.0), igvColor(1.0, 1.0, 1.0, 1.0), double(1.0), double(0.0), double(0.0));
    //luzPuntual.aplicar();

    igvPunto3D posicionFoco(0.0, 3.0, 0.0);
    igvColor ambiental(0.0, 0.0, 0.0, 1.0);
    igvColor diferencial(1.0, 1.0, 1.0, 1.0);
    igvColor especular(1.0, 1.0, 1.0, 1.0);
    double a0 = 1.0;
    double a1 = 0.1;
    double a2 = 0.1;
    igvPunto3D direccionFoco(0.0, -1.0, 0.0);
    double angulo2 = 35.0;
    double exponente2 = 0.0;



    igvFuenteLuz luzFoco(GL_LIGHT1, posicionFoco, ambiental, diferencial, especular, a0, a1, a2, direccionFoco, angulo2, exponente2);
    luzFoco.encender();
    luzFoco.aplicar();


    maniqui = robot(igvPunto3D(5, 5, 5));
    

	// se pintan los ejes
	//if (ejes) pintar_ejes();

	//glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aqu� si se mueve junto con la escena (tambi�n habr�a que desactivar la de arriba).

    float color_paredes[3] = { 40 / 255.0, 40 / 255.0, 40 / 255.0 };

    t.aplicar(); //Textura para las paredes
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, color_paredes); //Aplicar el color de la pared
    //glTranslatef(1, 4, 1); //Colocar en la posici�n actual el cubo creado.
    glScalef(1, 5, 1); //Hacer el cubo m�s alto para que no se pueda ver el laberinto por arriba
    glutSolidCubeTextured(1);
    glPopMatrix();
    
	glPopMatrix(); // restaura la matriz de modelado


    glPushMatrix();
    visualizarVB();
    glPopMatrix();
    

}

//Método para la visualización del modelo sin luces (se utiliza durante la selección)
void igvEscena3D::visualizarVB() {
    GLfloat separacionX = 2.5;
    GLfloat separacionZ = 2.5;

    int cont = 0;
    // Practica 2a. Parte B y C.
    for (int pilasY = 0; pilasY < pulsaY; pilasY++) {
        for (int pilasX = 0; pilasX < pulsaX; pilasX++) {
            for (int pilasZ = 0; pilasZ < pulsaZ; pilasZ++) {
                glPushMatrix();
                glTranslatef(pilasX * separacionX, pilasY, pilasZ * separacionZ);
                cajas[cont++]->visualizar(); //Se visualiza la caja
                glPopMatrix();
            }
        }
    }

    //glutSolidCube(2);

}

float igvEscena3D::getMaxCabeza() const {
    return maxCabeza;
}

float igvEscena3D::getMinCabeza() const {
    return minCabeza;
}

float igvEscena3D::getMaxPie() const {
    return maxPie;
}

float igvEscena3D::getMinPie() const {
    return minPie;
}

float igvEscena3D::getMaxHom() const {
    return maxHom;
}

float igvEscena3D::getMinHom() const {
    return minHom;
}


