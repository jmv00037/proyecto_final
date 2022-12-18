#include <cstdlib>

#include "igvInterfaz.h"
#include <windows.h>
#include <mmsystem.h>
#include <GL\freeglut.h>

// Objetos globales
// objeto que contiene la configuraci�n y la interacci�n con la ventana de visualizaci�n
igvInterfaz interfaz;

int main(int argc, char** argv) {
	// inicializa la ventana de visualizaci�n
	interfaz.configura_entorno(argc, argv,
		1920, 1080, // tama�o de la ventana
		100, 100, // posicion de la ventana
		"Informatica Grafica y Visualizacion. Practica 3B." // titulo de la ventana
	);


	
	PlaySound(TEXT("1-06. DOOM.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	// establece las funciones callbacks para la gesti�n de los eventos
	interfaz.inicializa_callbacks();

	// inicia el bucle de visualizaci�n de OpenGL
	interfaz.inicia_bucle_visualizacion();

	return(0);
}
