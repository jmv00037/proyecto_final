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
    modo = IGV_VISUALIZAR;
    objeto_seleccionado = -1;
    boton_retenido = false;
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
    case 'e':
        interfaz.escena.moverPuerta1();
        break;
    case 'r':
        interfaz.escena.moverPuerta2();
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
    //interfaz.camara.aplicar();
    // visualiza la escena
    //interfaz.escena.visualizar();

    // refresca la ventana
    //glutSwapBuffers();
    // Apartado A: antes de aplicar las transformaciones de cámara y proyección hay que comprobar el modo para sólo visualizar o seleccionar:
    if (interfaz.modo == IGV_SELECCIONAR) {
        // Apartado A: Para que funcione habrá que dibujar la escena sin efectos, sin iluminación, sin texturas ...
        glDisable(GL_LIGHTING); // desactiva la iluminacion de la escena
        glDisable(GL_DITHER);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_CULL_FACE);

        // Apartado A: Reestablece los colores como no seleccionado
        if (interfaz.objeto_seleccionado != -1)
        {
            //Puerta 1
            if (interfaz.escena.getPuerta1().getColorByte()[0] == 255 && interfaz.escena.getPuerta1().getColorByte()[1] == 255 && interfaz.escena.getPuerta1().getColorByte()[2] == 0) {

                interfaz.escena.getPuerta1().setColorByte((float)interfaz.colorPixelGuardado[0] / 255, (float)interfaz.colorPixelGuardado[1] / 255, (float)interfaz.colorPixelGuardado[2] / 255);
                interfaz.objeto_seleccionado = 1;
            }
            //Puerta 2
            if (interfaz.escena.getPuerta2().getColorByte()[0] == 255 && interfaz.escena.getPuerta2().getColorByte()[1] == 255 && interfaz.escena.getPuerta2().getColorByte()[2] == 0) {

                interfaz.escena.getPuerta2().setColorByte((float)interfaz.colorPixelGuardado[0] / 255, (float)interfaz.colorPixelGuardado[1] / 255, (float)interfaz.colorPixelGuardado[2] / 255);
                interfaz.objeto_seleccionado = 1;
            }


            interfaz.objeto_seleccionado = -1;
        }


        // Apartado A: aplica la cámara
        interfaz.camara.aplicar();

        // Apartado A: visualiza los BV cada uno de un color
        interfaz.escena.visualizarVB();

        // Apartado A: Obtener el color del pixel seleccionado
        GLubyte colorPixel[3];
        glReadPixels(interfaz.cursorX, interfaz.cursorY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, colorPixel);
       
        // Apartado A: Comprobar el color del objeto que hay en el cursor mirando en la tabla de colores y asigna otro color al objeto seleccionado


        //cout << interfaz.escena.getCajas().size() << "je\n";

        if (colorPixel[0] == 0 && colorPixel[1] != 0  && 0 == colorPixel[2]) {
            interfaz.colorPixelGuardado[0] = colorPixel[0];
            interfaz.colorPixelGuardado[1] = colorPixel[1];
            interfaz.colorPixelGuardado[2] = colorPixel[2];
            interfaz.escena.getPuerta2().setColorByte(255 / 255, 255 / 255, 0 / 255);
            interfaz.objeto_seleccionado = 1;
        }

        if (colorPixel[0] != 0 && colorPixel[1] != 0 && 0 != colorPixel[2]) {
            interfaz.colorPixelGuardado[0] = colorPixel[0];
            interfaz.colorPixelGuardado[1] = colorPixel[1];
            interfaz.colorPixelGuardado[2] = colorPixel[2];
            interfaz.escena.getPuerta1().setColorByte(255 / 255, 255 / 255, 0 / 255);
            interfaz.objeto_seleccionado = 1;
        }

        glutPostRedisplay();
        // Apartado A: Cambiar a modo de visualización de la escena
        interfaz.modo = IGV_VISUALIZAR;
        
        // Apartado A: Habilitar de nuevo la iluminación
        glEnable(GL_LIGHTING);
    }
    else {
        // aplica las transformaciones en función de los parámetros de la cámara
        interfaz.camara.aplicar();
        // visualiza la escena
        interfaz.escena.visualizar();

        // refresca la ventana
        glutSwapBuffers();
    }
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
        
        //cout << interfaz.movimientoRobot << endl;
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
    glutMouseFunc(set_glutMouseFunc);
    glutMotionFunc(set_glutMotionFunc);
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

void igvInterfaz::set_glutMouseFunc(GLint boton, GLint estado, GLint x, GLint y){
    // Apartado A: comprobar que se ha pulsado el botón izquierdo 


    if (boton == GLUT_LEFT_BUTTON)
    {
        if (estado == GLUT_DOWN) {
            interfaz.cursorX = x;
            interfaz.cursorY = interfaz.alto_ventana - y;
            interfaz.modo = IGV_SELECCIONAR;
        }


    }
    // Apartado A: guardar que el boton se ha presionado o se ha soltado, si se ha pulsado hay que
    // pasar a modo IGV_SELECCIONAR

    // Apartado A: guardar el pixel pulsado

    // Apartado A: renovar el contenido de la ventana de vision 
//interfaz.modo = IGV_VISUALIZAR;
    glutPostRedisplay();
}

void igvInterfaz::set_glutMotionFunc(GLint x, GLint y){
    // Apartado B: si el botón está retenido y hay algún objeto seleccionado,
 // comprobar el objeto seleccionado y la posición del ratón y rotar
 // el objeto seleccionado utilziando el desplazamiento entre la posición 
 //inicial y final del ratón

 //cout << "antres " << interfaz.objeto_seleccionado << "\n";
 //cout << "antres 2" << interfaz.boton_retenido << "\n";

    if (interfaz.boton_retenido == false && interfaz.objeto_seleccionado == 1)
    {
        //glRotatef(45, 0, 1, 0);

        
            if (interfaz.escena.getPuerta1().getColorByte()[0] == 255 && interfaz.escena.getPuerta1().getColorByte()[1] == 255 && interfaz.escena.getPuerta1().getColorByte()[2] == 0) {
                interfaz.escena.moverPuerta1();
            }
            //Puerta 2
            if (interfaz.escena.getPuerta2().getColorByte()[0] == 255 && interfaz.escena.getPuerta2().getColorByte()[1] == 255 && interfaz.escena.getPuerta2().getColorByte()[2] == 0) {
                interfaz.escena.moverPuerta2();
            }

        
    }
    // Apartado B: guardar la nueva posición del ratón 

    // Apartado B: renovar el contenido de la ventana de vision 
    glutPostRedisplay();
}

