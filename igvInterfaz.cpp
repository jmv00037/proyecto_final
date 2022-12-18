#define FPS 60
#define STOP 1500

#include <cstdlib>
#include <iostream>
#include "igvInterfaz.h"

using namespace std;

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
// ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz() {
}

igvInterfaz::~igvInterfaz() {}


// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {
    interfaz.camara = igvCamara(alto_ventana, ancho_ventana, igvPunto3D(0, 4, 0), igvPunto3D(0, 0, 1), igvPunto3D(0, 1, 0));
}

void igvInterfaz::configura_entorno(int argc, char** argv,
    int _ancho_ventana, int _alto_ventana,
    int _pos_X, int _pos_Y,
    string _titulo) {
    // inicializaci�n de las variables de la interfaz																	
    ancho_ventana = _ancho_ventana;
    alto_ventana = _alto_ventana;

    // inicializaci�n de la ventana de visualizaci�n
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(_ancho_ventana, _alto_ventana);
    glutInitWindowPosition(_pos_X, _pos_Y);
    //glutCreateWindow(_titulo.c_str());

    char game_mode_string[64];
    snprintf(game_mode_string, sizeof(game_mode_string), "%dx%d@60", ancho_ventana, alto_ventana);
    glutGameModeString(game_mode_string);
    glutEnterGameMode();

    glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);

    glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
    glClearColor(1.0, 1.0, 1.0, 0.0); // establece el color de fondo de la ventana

    glEnable(GL_LIGHTING); // activa la iluminacion de la escena
    glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion

    crear_mundo(); // crea el mundo a visualizar en la ventana
}

void igvInterfaz::inicia_bucle_visualizacion() {
    glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void Timer(int iUnused) {
    glutPostRedisplay();
    glutTimerFunc(30, Timer, 0);
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
    int velocidad = 40;
    switch (key) {
    case 'a':
    case 'd':
    case 'w':
    case 's':
        interfaz.camara.onKeyBoard(key, interfaz.dt);
        interfaz.camara.aplicar();
        interfaz.escena.setPosicionCamara(interfaz.camara.r);
        interfaz.escena.luz.aplicar();
        
        break;
    case 27: // tecla de escape para SALIR
        exit(1);
        break;
    }
    glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
    // dimensiona el viewport al nuevo ancho y alto de la ventana
    // guardamos valores nuevos de la ventana de visualizacion
    interfaz.set_ancho_ventana(w);
    interfaz.set_alto_ventana(h);

    // establece los par�metros de la c�mara y de la proyecci�n
    interfaz.camara.aplicar();
}


void igvInterfaz::set_glutDisplayFunc() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer
    // se establece el viewport
    glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());


    // aplica las transformaciones en funci�n de los par�metros de la c�mara
    interfaz.camara.aplicar();
    // visualiza la escena
    interfaz.escena.visualizar();

    // refresca la ventana
    glutSwapBuffers();
}

void igvInterfaz::set_glutIdleFunc() {
    int velocidad = 1;

    if(interfaz.animacion) {
        if(interfaz.angCabeza==interfaz.escena.getMaxCabeza() || interfaz.angCabeza==interfaz.escena.getMinCabeza()){
            interfaz.cambiarCabeza = !interfaz.cambiarCabeza;
        }
        if(interfaz.cambiarCabeza) {
            interfaz.angCabeza += interfaz.deltaX;
            interfaz.angCabeza = interfaz.escena.moverCabeza(interfaz.angCabeza);
            interfaz.escena.moverPiernaDer(interfaz.angCabeza);
            interfaz.escena.moverPiernaIzq(-interfaz.angCabeza);
            interfaz.escena.moverHombroDer(interfaz.angCabeza-90);
            interfaz.escena.moverHombroIzq(-interfaz.angCabeza-90);
        }else{
            interfaz.angCabeza -= interfaz.deltaX;
            interfaz.angCabeza = interfaz.escena.moverCabeza(interfaz.angCabeza);
            interfaz.escena.moverPiernaDer(interfaz.angCabeza);
            interfaz.escena.moverPiernaIzq(-interfaz.angCabeza);
            interfaz.escena.moverHombroDer(interfaz.angCabeza-90);
            interfaz.escena.moverHombroIzq(-interfaz.angCabeza-90);
        }
    }
   
    

        if (interfaz.movimiento1 == false) {
            if (interfaz.escena.maniqui.get_rotacionHombro2X() < 40) {
                interfaz.escena.maniqui.set_rotacionHombro2X(interfaz.escena.maniqui.get_rotacionHombro2X() + velocidad);
            }
            if (interfaz.escena.maniqui.get_rotacionHombro1X() > -40) {
                interfaz.escena.maniqui.set_rotacionHombro1X(interfaz.escena.maniqui.get_rotacionHombro1X() - velocidad);
            }
            if (interfaz.escena.maniqui.get_rotacionPierna2() < 40) {
                interfaz.escena.maniqui.set_rotacionPierna2(interfaz.escena.maniqui.get_rotacionPierna2() + velocidad);
            }
            if (interfaz.escena.maniqui.get_rotacionPierna1() > -40) {
                interfaz.escena.maniqui.set_rotacionPierna1(interfaz.escena.maniqui.get_rotacionPierna1() - velocidad);
            }
            else {
                interfaz.movimiento1 = true;
            }

        }
        else {
            if (interfaz.escena.maniqui.get_rotacionHombro2X() > -40) {
                interfaz.escena.maniqui.set_rotacionHombro2X(interfaz.escena.maniqui.get_rotacionHombro2X() - velocidad);
            }
            if (interfaz.escena.maniqui.get_rotacionHombro1X() < 40) {
                interfaz.escena.maniqui.set_rotacionHombro1X(interfaz.escena.maniqui.get_rotacionHombro1X() + velocidad);
            }
            if (interfaz.escena.maniqui.get_rotacionPierna2() > -40) {
                interfaz.escena.maniqui.set_rotacionPierna2(interfaz.escena.maniqui.get_rotacionPierna2() - velocidad);
            }
            if (interfaz.escena.maniqui.get_rotacionPierna1() < 40) {
                interfaz.escena.maniqui.set_rotacionPierna1(interfaz.escena.maniqui.get_rotacionPierna1() + velocidad);
            }
            else {
                interfaz.movimiento1 = false;
            }
        }
        //MOVIMIENTO ROBOT
        
        cout << interfaz.movimientoRobot << endl;
        if (interfaz.movimientoRobot == STOP) {
            interfaz.atras = true;
            interfaz.escena.maniqui.girar();
        }
        if (interfaz.movimientoRobot == 0) {
            interfaz.atras = false;
            interfaz.escena.maniqui.girar();
        }

        if (interfaz.atras) {
            interfaz.movimientoRobot--;
            interfaz.escena.maniqui.moverAtras();
        }
        else {
            interfaz.movimientoRobot++;
            interfaz.escena.maniqui.moverAdelante();
        }


        glutPostRedisplay();
    
}

void igvInterfaz::passiveMouseCB(int x, int y) {

    double nuevox = (x - (interfaz.ancho_ventana / 2));
    double nuevoy = ((interfaz.alto_ventana / 2) - y);

    interfaz.camara.mirar(nuevox, nuevoy, interfaz.dt);

    interfaz.camara.aplicar();

    glutPostRedisplay();
}

void igvInterfaz::inicializa_callbacks() {
    glutPassiveMotionFunc(passiveMouseCB);
    glutKeyboardFunc(set_glutKeyboardFunc);
    glutReshapeFunc(set_glutReshapeFunc);
    glutDisplayFunc(set_glutDisplayFunc);
    glutIdleFunc(set_glutIdleFunc);
    glutTimerFunc(1000 / FPS, loop, 0);//espera un numero de milisegundos para que vaya fluido
}

void igvInterfaz::loop(int)
{
    glutWarpPointer(interfaz.ancho_ventana / 2, interfaz.alto_ventana / 2); //Mantiene el ranton en el centro
    int t = glutGet(GLUT_ELAPSED_TIME); //numero de milisegundos desde que se llamo a glutinit()
    interfaz.dt = (t - interfaz.tUltimoFotograma) / 1000.0;
    interfaz.tUltimoFotograma = t;
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, loop, 0);

}

