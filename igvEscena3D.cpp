#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"
#include <iostream>
#include "igvInterfaz.h"
#include "igvCamara.h"

// Metodos constructores 

igvEscena3D::igvEscena3D():luz(GL_LIGHT1, igvPunto3D(0, 5, 0), igvColor(1, 1, 1, 1), igvColor(0,0,0,0), igvColor(1, 1, 1, 1), 1, 0, 0, igvPunto3D(-1, -1, 0), 50, 0), maniqui(igvPunto3D(-40,5,-40),&c), p1(0.0,1.0,0.0), p2(0.0,0.0,1.0) {
    ejes = true;
    movimientoCabeza = 0; movimientoHombroDer = 0, movimientoHombroIzq = 0;
    //Se cargan del fichero los objetos y se guardan
    luz.aplicar();
    // Apartado C: inicializar los atributos para el control de los grados de libertad del modelo 

}

igvEscena3D::~igvEscena3D() {

}

///// Apartado B: M�todos para visualizar cada parte del modelo

void igvEscena3D::visualizarPartes(std::vector<float>& v, std::vector<float>& n, std::vector<unsigned int>& tri, std::vector<float>& tex) {
    glFlush();



    /* clear screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TRIANGLES);
    glShadeModel(GL_SMOOTH);

    //glColor3d(1, 1, 1);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindTexture(GL_TEXTURE_2D, 2);
    glVertexPointer(3, GL_FLOAT, 0, &v[0]);
    glNormalPointer(GL_FLOAT, 0, &n[0]);

    glTexCoordPointer(4, GL_FLOAT, 3, &tex[0]);

    //TRIANGULOS
    glDrawElements(GL_TRIANGLES, tri.size(), GL_UNSIGNED_INT, &tri[0]);

    // NORMALES


    //glDisableClientState(GL_NORMAL_ARRAY);



    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);


}

void igvEscena3D::visualizarVB(void){
    glPushMatrix();//Crea puerta
        glTranslatef(-25, 5, 0 + Puerta1);
        p1.visualizarSinT(c);
        glColor3f(0.0,1.0,0.0);
    glPopMatrix();

    glPushMatrix();//Crea puerta
        glTranslatef(25, 5, 0 - Puerta2);
        p2.visualizarSinT(c);
        glColor3f(0.0, 0.0, 1.0);
    glPopMatrix();
}

void igvEscena3D::visualizarPuertas(void) {
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();//Crea puerta
        glTranslatef(-25, 5, 0 + Puerta1);
        p1.visualizarConT(c);
    glPopMatrix();

    glPushMatrix();//Crea puerta
        glTranslatef(25, 5, 0 - Puerta2);
        p2.visualizarConT(c);
    glPopMatrix();
}

////// Apartado C: a�adir aqu� los m�todos para modificar los grados de libertad del modelo
float igvEscena3D::restriccion(float angle, int min, int max, float& mov) {
    return (angle <= max && angle >= min) ? mov = angle : mov;
}

float igvEscena3D::moverCabeza(float angle) {
    return restriccion(angle, minCabeza, maxCabeza, movimientoCabeza);
}

float igvEscena3D::moverHombroDer(float angle) {
    return restriccion(angle, minHom, maxHom, movimientoHombroDer);
}

float igvEscena3D::moverHombroIzq(float angle) {
    return restriccion(angle, minHom, maxHom, movimientoHombroIzq);
}

float igvEscena3D::moverTorso(float angle) {
    return movimientoTorso = angle;
}

float igvEscena3D::moverPiernaDer(float angle) {
    return restriccion(angle, minPie, maxPie, movimientoPiernaDer);
}

float igvEscena3D::moverPiernaIzq(float angle) {
    return restriccion(angle, minPie, maxPie, movimientoPiernaIzq);
}

void igvEscena3D::paredExterior(int x, int z) {
    glTranslatef(x, 5, z);
    if (x == 0)
        glScalef(50, 4, 1); // expande el suelo
    else
        glScalef(1, 4, 50);
    c.cargarCubo(PARED, 50, 4); //crea el cubo para el suelo
}

void igvEscena3D::setPosicionCamara(igvPunto3D _posicion) {
    luz.setPosicion(_posicion);
    luz.encender();
    luz.aplicar();
}

void igvEscena3D::moverPuerta1(){
    if (Puerta1 < 9.5)
        Puerta1 += 0.1;
}

void igvEscena3D::moverPuerta2(){
    if (Puerta2 < 9.5)
        Puerta2 += 0.1;
}

void igvEscena3D::visualizar() {
    glPushMatrix(); // guarda la matriz de modelado
    luz.aplicar();
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix(); //Crea el techo
    glTranslatef(0, 10, 0);
    glScalef(50, 1, 50); // expande el techo
    c.cargarCubo(SUELO, 50, 50); //crea el cubo para el techo
    glPopMatrix();
    glPushMatrix(); //Crea el suelo
    glScalef(50, 1, 50); // expande el suelo
    c.cargarCubo(SUELO, 50, 50); //crea el cubo para el suelo
    glPopMatrix();

    glPushMatrix();//Crea las paredes exteriores
    paredExterior(0, -50);
    glPopMatrix();
    glPushMatrix();//Crea las paredes exteriores
    paredExterior(0, 50);
    glPopMatrix();
    glPushMatrix();//Crea las paredes exteriores
    paredExterior(50, 0);
    glPopMatrix();
    glPushMatrix();//Crea las paredes exteriores
    paredExterior(-50, 0);
    glPopMatrix();


    glPushMatrix();//Crea las paredes habitacion
    glTranslatef(25, 5, 30);
    glScalef(1, 4, 25);
    c.cargarCubo(PARED2, 50, 4);
    glPopMatrix();
    glPushMatrix();//Crea las paredes habitacion
    glTranslatef(-25, 5, 30);
    glScalef(1, 4, 25);
    c.cargarCubo(PARED2, 50, 4);
    glPopMatrix();
    glPushMatrix();//Crea las paredes habitacion
    glTranslatef(-25, 5, -30);
    glScalef(1, 4, 25);
    c.cargarCubo(PARED2, 50, 4);
    glPopMatrix();
    glPushMatrix();//Crea las paredes habitacion
    glTranslatef(25, 5, -30);
    glScalef(1, 4, 25);
    c.cargarCubo(PARED2, 50, 4);
    glPopMatrix();

   



    maniqui.dibujar();


    glPopMatrix(); // restaura la matriz de modelado

    glPushMatrix();
        visualizarPuertas();
    glPopMatrix();

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

