#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"
#include <iostream>
#include "igvInterfaz.h"
#include "igvCamara.h"

#define MAXIMA_DISTANCIA 100

// Metodos constructores 

igvEscena3D::igvEscena3D():luz(GL_LIGHT0, igvPunto3D(1.0, 1.0, 1.0), igvColor(0.0, 0.0, 0.0, 1.0), igvColor(1.0, 1.0, 1.0, 1.0), igvColor(1.0, 1.0, 1.0, 1.0), double(1.0), double(0.0), double(0.0)),
                            maniqui(igvPunto3D(-40,5,-40),&c,180), p1(0.0,1.0,0.0), p2(0.0,0.0,1.0), maniqui2(igvPunto3D(40, 5, 40), &c,0) {
    ejes = true;
    movimientoCabeza = 0; movimientoHombroDer = 0, movimientoHombroIzq = 0;
    //Se cargan del fichero los objetos y se guardan
    luz.encender();
    luz.aplicar();


    std::string ruta = "..\\modelos\\C96.obj";
    if (utils::cargaOBJ(&ruta[0], pistola.vertices, pistola.texturas, pistola.normales, pistola.triangulos))
        cargadoCorrectamente = true;
    else
        cargadoCorrectamente = false;
    
}

igvEscena3D::~igvEscena3D() {
}

///// Apartado B: M�todos para visualizar cada parte del modelo

void igvEscena3D::visualizarPartes(std::vector<float>& v, std::vector<float>& n, std::vector<unsigned int>& tri) {
    glFlush();

    glEnable(GL_TRIANGLES);
    glShadeModel(GL_SMOOTH);

    /* Apartado B: TODO */
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &v[0]);

    glDrawElements(GL_TRIANGLES, tri.size(), GL_UNSIGNED_INT, &tri[0]);
    glDisableClientState(GL_VERTEX_ARRAY);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, &n[0]);


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
}

void igvEscena3D::moverPuerta1(){
    if (Puerta1 < 9.5)
        Puerta1 += 0.1;
}

void igvEscena3D::moverPuerta2(){
    if (Puerta2 < 9.5)
        Puerta2 += 0.1;
}

void hitBox(std::vector<float> pos, robot& m) {
    cout << pos[0] << ", " << pos[1] << ", " << pos[2] << endl;
    cout << m.posicionRobot[X] << ", " << m.posicionRobot[Y] << ", " << m.posicionRobot[Z] << endl << endl;
    if (pos[0] <= m.posicionRobot[X] + 2 && pos[0] >= m.posicionRobot[X]-2 &&
        abs(pos[1]) <= abs(m.posicionRobot[Y]) + 1 && abs(pos[1]) >= abs(m.posicionRobot[Y]) - 1 &&
        abs(pos[2]) <= abs(m.posicionRobot[Z]) + 2 && abs(pos[2]) >= abs(m.posicionRobot[Z]) - 2) {
        m.morir();
    }
}

void igvEscena3D::visualizar() {
    glPushMatrix(); // guarda la matriz de modelado
    //luz.aplicar();
    
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

    // PISTOLA
    glPushMatrix();
        glTranslatef(x, 2.3, z);     // MUEVE LA POSTOLA AL LADO DE LA CAMARA
        glRotatef(-angX, 0, 1, 0);   // ROTA LA PISTOLA SEGÚN EL MOVIMIENTO DE RATON
        glTranslatef(-x, -2.3, -z ); //MUEVE LA PISTOLA AL ORIGEN
        glTranslatef(x+0.2, 2.3, z);
        glScalef(0.05,0.05,0.05);
        glRotatef(180, 0, 1, 0);
        visualizarPartes(pistola.vertices, pistola.normales, pistola.triangulos); // GENERA MODELO DE LA PISTOLA A PARTIR DEL FICHERO .OBJ
    glPopMatrix();
    
    for (int i = 0; i < balas.size(); i++) {
        std::vector<float> pos; // SE GUARDAN LAS POSICIONES DE LA BALA

        for (int j = 0; j < 3; j++) { //SE CALCULAN LAS POSICIONES SEGUN LA DIRECCION QUE RECORRE 
            if (direccion[i][j] < 0) {
                pos.push_back(balas[i].first[j] - direccion[i][j] * balas[i].second); 
                balas[i].first[j] = pos[j];
            }
            else if (direccion[i][j] == 0) {
                pos.push_back(balas[i].first[j]);
            }
            else if (direccion[i][j] > 0) {
                pos.push_back(balas[i].first[j] - direccion[i][j] * balas[i].second) ;
                balas[i].first[j] = pos[j];
            }
        }

        glPushMatrix(); 
            glTranslatef( pos[0], pos[1], pos[2]); // SE MUEVE LA BALA
            glutSolidSphere(0.1,100,2);
        glPopMatrix();
        
        //SE COMPRUEBA SI HA DADO AL ROBOT
        hitBox(pos,maniqui);
        hitBox(pos, maniqui2);

        //SE DESTRUYE LA BALA SI RECORRE CIERTA DISTANCIA
        if (++destruirBalas[i] == MAXIMA_DISTANCIA) {
            destruirBalas.erase(destruirBalas.begin());
            balas.erase(balas.begin());
            direccion.erase(direccion.begin());
        }

    }
    if (!maniqui.muerto()) {
        glPushMatrix();
            maniqui.dibujar();
        glPopMatrix();
    }
    if (!maniqui2.muerto()) {
        glPushMatrix();
            maniqui2.dibujar();
        glPopMatrix();
    }

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

