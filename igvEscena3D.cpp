#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;
    movimientoCabeza=0; movimientoHombroDer=0,movimientoHombroIzq=0;
    //Se cargan del fichero los objetos y se guardan


    std::string ruta = "..\\modelos\\";
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

void igvEscena3D::visualizarPartes(std::vector<float> &v, std::vector<float> &n, std::vector<unsigned int> &tri) {
    glFlush();

    glEnable(GL_TRIANGLES);
    glShadeModel(GL_SMOOTH);

    /* Apartado B: TODO */
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &v[0]);

    glDrawElements(GL_TRIANGLES, tri.size(), GL_UNSIGNED_INT, &tri[0]);
    glDisableClientState(GL_VERTEX_ARRAY);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT,0,&n[0]);
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

void igvEscena3D::visualizar() {
	// crear luces
	GLfloat luz0[4] = { 5.0,5.0,5.0,1 }; // luz puntual
	glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aqu� si permanece fija y no se mueve con la escena
	glEnable(GL_LIGHT0);

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

	// se pintan los ejes
	if (ejes) pintar_ejes();

	//glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aqu� si se mueve junto con la escena (tambi�n habr�a que desactivar la de arriba).



	///// Apartado B: aqui hay que añadir la visualizacion del arbol del modelo utilizando la pila de matrices de OpenGL
	/////             se recomienda crear una metodo auxiliar que encapsule todo el codigo para la visualizacion
	/////             del modelo, dejando aqui solo la llamada a ese metodo, asi como distintas funciones una para cada
	/////			  parte del modelo.



    if(cargadoCorrectamente){
        glPushMatrix();
            glRotated(movimientoTorso,0,1,0);
            visualizarPartes(torso.vertices,torso.normales,torso.triangulos);
            //CABEZA
            glPushMatrix();
                glRotated(movimientoCabeza,0,1,0);
                visualizarPartes(cabeza.vertices,cabeza.normales,cabeza.triangulos);
            glPopMatrix();
            //HOMBRO IZQUIERDO
            glPushMatrix();
                glTranslatef(-0.179,1.88,1.03);
                glRotated(movimientoHombroIzq,0,0,1);
                glTranslatef(0.179,-1.88,-1.03);
                visualizarPartes(hombroIzq.vertices,hombroIzq.normales,hombroIzq.triangulos);
                //BRAZO IZQUIERDO
                glPushMatrix();
                    visualizarPartes(brazoIzq.vertices,brazoIzq.normales,brazoIzq.triangulos);
                glPopMatrix();
            glPopMatrix();
            //HOMBRO DERECHO
            glPushMatrix();
                glTranslatef(-0.112,1.88,-1.25);
                glRotated(movimientoHombroDer,0,0,1);
                glTranslatef(0.112,-1.88,1.25);
                visualizarPartes(hombroDer.vertices,hombroDer.normales,hombroDer.triangulos);
                //BRAZO DERECHO
                glPushMatrix();
                    visualizarPartes(brazoDer.vertices,brazoDer.normales,brazoDer.triangulos);
                glPopMatrix();
            glPopMatrix();
            //PARTE SUPERIOR DE LA PIERNA DERECHA
            glPushMatrix();
                glTranslatef(-0.00468,-0.3,-0.544);
                glRotated(movimientoPiernaDer,0,0,1);
                glTranslatef(0.00468,0.3,0.544);
                visualizarPartes(piernaSupDer.vertices,piernaSupDer.normales,piernaSupDer.triangulos);
                //PIERNA DERECHA
                glPushMatrix();
                    visualizarPartes(piernaDer.vertices,piernaDer.normales,piernaDer.triangulos);
                glPopMatrix();
            glPopMatrix();
            //PARTE SUPERIOR DE LA PIERNA IZQUIERDA
            glPushMatrix();
                glTranslatef(-0.00468,-0.3,-0.544);
                glRotated(movimientoPiernaIzq,0,0,1);
                glTranslatef(0.00468,0.3,0.544);
                visualizarPartes(piernaSupIzq.vertices,piernaSupIzq.normales,piernaSupIzq.triangulos);
                //PIERNA IZQUIERDA
                glPushMatrix();
                    visualizarPartes(piernaIzq.vertices,piernaIzq.normales,piernaIzq.triangulos);
                glPopMatrix();
            glPopMatrix();

        glPopMatrix();
    }
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


