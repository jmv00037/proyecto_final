#ifndef __IGVINTERFAZ
#define __IGVINTERFAZ

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <iostream>
#include "igvEscena3D.h"
#include "igvCamara.h"

using namespace std;

class igvInterfaz {
protected:
	// Atributos
	int ancho_ventana; // ancho inicial de la ventana de visualizacion
	int alto_ventana;  // alto inicial de la ventana de visualizacion

	igvEscena3D escena; // escena que se visualiza en la ventana definida por igvInterfaz
	igvCamara camara; // c�mara que se utiliza para visualizar la escena
    igvCamara* actual = nullptr;

    //movimientos con teclas
    float incrementoMov=5,hombroDer=0,hombroIzq=0,cabeza=0,torso=0,piernaDer=0,piernaIzq=0;
    //animacion
    float deltaX=1,angCabeza=0,angPierna=0,angBrazos=0;
    bool animacion=false,cambiarCabeza=false,cambiarPiernas=false,cambiarBrazos=false;

    ///PRUEBA
    double dt;
    double tUltimoFotograma;

	//CAMARA STUFF
	bool bloqueoCamara = false;
	double anteriorX, anteriorY;

public:
	// Constructores por defecto y destructor
	igvInterfaz();
	~igvInterfaz();

	// Metodos est�ticos
	// callbacks de eventos
    static void passiveMouseCB(int x, int  y); //Raton
	static void set_glutKeyboardFunc(unsigned char key, int x, int y); // metodo para control de eventos del teclado
	static void set_glutReshapeFunc(int w, int h); // metodo que define la camara de vision y el viewport
												   // se llama autom�ticamente cuano se camba el tama�o de la ventana
	static void set_glutDisplayFunc(); // metodo para visualizar la escena
	static void set_glutIdleFunc(); // metodo para animar la escena

	// Metodos
	// crea el mundo que se visualiza en la ventana
	void crear_mundo(void);

	// inicializa todos los par�metros para crear una ventana de visualizaci�n
	void configura_entorno(int argc, char** argv, // parametros del main
		int _ancho_ventana, int _alto_ventana, // ancho y alto de la ventana de visualizaci�n
		int _pos_X, int _pos_Y, // posicion inicial de la ventana de visualizaci�n
		string _titulo // t�tulo de la ventan de visualizaci�n
	);
	void inicializa_callbacks(); // inicializa todas los callbacks
	void inicia_bucle_visualizacion(); // visualiza la escena y espera a eventos sobre la interfaz

	// m�todos get_ y set_ de acceso a los atributos
	int get_ancho_ventana() { return ancho_ventana; };
	int get_alto_ventana() { return alto_ventana; };

	void set_ancho_ventana(int _ancho_ventana) { ancho_ventana = _ancho_ventana; };
	void set_alto_ventana(int _alto_ventana) { alto_ventana = _alto_ventana; };

    static void loop(int);
};

#endif
