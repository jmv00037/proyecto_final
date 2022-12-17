#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"
#include <iostream>


// Metodos constructores 

igvEscena3D::igvEscena3D(){
	ejes = true;
    movimientoCabeza=0; movimientoHombroDer=0,movimientoHombroIzq=0;
    //Se cargan del fichero los objetos y se guardan

    std::string ruta = "..\\modelos\\";
    std::string pMundo = ruta + "Dungeon.obj";
    utils::cargaOBJ(&pMundo[0], mundo.vertices, mundo.texturas, mundo.normales, mundo.triangulos);
    
    std::string pCabeza = ruta + "cabeza.obj";
    std::string pTorso = ruta +"untitled.obj";
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

void igvEscena3D::paredExterior(int x,int z) {
    glTranslatef(x, 5, z);
    if(x==0)
        glScalef(50, 4, 1); // expande el suelo
    else
        glScalef(1, 4, 50);
    c.cargarCubo(PARED, 50, 4); //crea el cubo para el suelo
}

void igvEscena3D::visualizar() {
	// crear luces
	

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

	// se pintan los ejes
	//if (ejes) pintar_ejes();

	//glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aqu� si se mueve junto con la escena (tambi�n habr�a que desactivar la de arriba).
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    glPushMatrix(); //Crea el techo
        glTranslatef(0, 10, 0);
        glScalef(50, 1, 50); // expande el suelo
        c.cargarCubo(SUELO, 50, 50); //crea el cubo para el suelo
    glPopMatrix();
    glPushMatrix(); //Crea el suelo
        glScalef(50,1,50); // expande el suelo
        c.cargarCubo(SUELO, 50,50); //crea el cubo para el suelo
    glPopMatrix();
        
    glPushMatrix();//Crea las paredes exteriores
        paredExterior(0,-50);
    glPopMatrix();
    glPushMatrix();//Crea las paredes exteriores
        paredExterior(0,50);
    glPopMatrix();
    glPushMatrix();//Crea las paredes exteriores
        paredExterior(50, 0);
    glPopMatrix();
    glPushMatrix();//Crea las paredes exteriores
        paredExterior(-50, 0);
    glPopMatrix();
    

    glPushMatrix();//Crea las paredes habitacion
        glTranslatef(25, 5,30);
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

    glPushMatrix();//Crea puerta
        glTranslatef(-25, 5, 0);
        glScalef(1, 4, 5);
        c.cargarCubo(PUERTA, 1, 1);
    glPopMatrix();

    glPushMatrix();//Crea puerta
        glTranslatef(25, 5, 0);
        glScalef(1, 4, 5);
        c.cargarCubo(PUERTA, 1, 1);
    glPopMatrix();


    /*
    if(cargadoCorrectamente){
        glPushMatrix();
            glRotated(movimientoTorso,0,1,0);
            visualizarPartes(torso.vertices,torso.normales,torso.triangulos,torso.texturas);
            //CABEZA
            glPushMatrix();
                glRotated(movimientoCabeza,0,1,0);
                visualizarPartes(cabeza.vertices,cabeza.normales,cabeza.triangulos,cabeza.texturas);
            glPopMatrix();
            //HOMBRO IZQUIERDO
            glPushMatrix();
                glTranslatef(-0.179,1.88,1.03);
                glRotated(movimientoHombroIzq,0,0,1);
                glTranslatef(0.179,-1.88,-1.03);
                visualizarPartes(hombroIzq.vertices,hombroIzq.normales,hombroIzq.triangulos,hombroIzq.texturas);
                //BRAZO IZQUIERDO
                glPushMatrix();
                    visualizarPartes(brazoIzq.vertices,brazoIzq.normales,brazoIzq.triangulos,brazoIzq.texturas);
                glPopMatrix();
            glPopMatrix();
            //HOMBRO DERECHO
            glPushMatrix();
                glTranslatef(-0.112,1.88,-1.25);
                glRotated(movimientoHombroDer,0,0,1);
                glTranslatef(0.112,-1.88,1.25);
                visualizarPartes(hombroDer.vertices,hombroDer.normales,hombroDer.triangulos,hombroDer.texturas);
                //BRAZO DERECHO
                glPushMatrix();
                    visualizarPartes(brazoDer.vertices,brazoDer.normales,brazoDer.triangulos,brazoDer.texturas);
                glPopMatrix();
            glPopMatrix();
            //PARTE SUPERIOR DE LA PIERNA DERECHA
            glPushMatrix();
                glTranslatef(-0.00468,-0.3,-0.544);
                glRotated(movimientoPiernaDer,0,0,1);
                glTranslatef(0.00468,0.3,0.544);
                visualizarPartes(piernaSupDer.vertices,piernaSupDer.normales,piernaSupDer.triangulos,piernaSupDer.texturas);
                //PIERNA DERECHA
                glPushMatrix();
                    visualizarPartes(piernaDer.vertices,piernaDer.normales,piernaDer.triangulos,piernaDer.texturas);
                glPopMatrix();
            glPopMatrix();
            //PARTE SUPERIOR DE LA PIERNA IZQUIERDA
            glPushMatrix();
                glTranslatef(-0.00468,-0.3,-0.544);
                glRotated(movimientoPiernaIzq,0,0,1);
                glTranslatef(0.00468,0.3,0.544);
                visualizarPartes(piernaSupIzq.vertices,piernaSupIzq.normales,piernaSupIzq.triangulos,piernaSupIzq.texturas);
                //PIERNA IZQUIERDA
                glPushMatrix();
                    visualizarPartes(piernaIzq.vertices,piernaIzq.normales,piernaIzq.triangulos,piernaIzq.texturas);
                glPopMatrix();
            glPopMatrix();

        glPopMatrix();
    }*/
	glPopMatrix(); // restaura la matriz de modelado

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


