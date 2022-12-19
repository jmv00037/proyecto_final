#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

#include "igvCamara.h"
#include <utility>


// Metodos constructores

igvCamara::igvCamara(int windowWith, int windowHeigh, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V): m_window_Width(windowWith), m_window_Height(windowHeigh) {
    P0 = _P0;
    r = _r;
    r.normalizar();
    v = _V;
    v.normalizar();



    angulo = 60.0;
    raspecto = 1.0;
    znear = 0.2;
    zfar = -1*3;

    tipo = IGV_PERSPECTIVA;
}

igvCamara::~igvCamara() {}

igvCamara::igvCamara(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V) {
    P0 = _P0;
    r = _r;
    v = _V;

	tipo = _tipo;
}


// Metodos publicos 
void igvCamara::set(igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V) {
    P0 = _P0;
    r = _r;
    v = _V;
}
void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
	double _xwmin, double _xwmax, double _ywmin, double _ywmax, double _znear, double _zfar) {
	tipo = _tipo;

    P0 = _P0;
    r = _r;
    v = _V;

	xwmin = _xwmin;
	xwmax = _xwmax;
	ywmin = _ywmin;
	ywmax = _ywmax;
	znear = _znear;
	zfar = _zfar;
}

void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
	double _angulo, double _raspecto, double _znear, double _zfar) {
	tipo = _tipo;

    P0 = _P0;
    r = _r;
    v = _V;

	angulo = _angulo;
	raspecto = _raspecto;
	znear = _znear;
	zfar = _zfar;
}

void igvCamara::aplicar(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (tipo == IGV_PARALELA) {
		glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}
	if (tipo == IGV_FRUSTUM) {
		glFrustum(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}
	if (tipo == IGV_PERSPECTIVA) {
		gluPerspective(angulo, raspecto, znear, zfar);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(P0[X], P0[Y], P0[Z], r[X], r[Y], r[Z], v[X], v[Y], v[Z]);
}

/// <summary>
/// Aplica zoom
/// </summary>
void igvCamara::zoom(){
    if (!hayZoom) {
        angulo /= 1 + 0.5;
        xwmin /= 1 + 0.5;
        ywmin /= 1 + 0.5;
        xwmax /= 1 + 0.5;
        ywmax /= 1 + 0.5;
        hayZoom = true;
    }
}

/// <summary>
/// Quita zoom aplicado
/// </summary>
void igvCamara::revZoom(){
    if (hayZoom) {
        angulo *= 1 + 0.5;
        xwmin *= 1 + 0.5;
        ywmin *= 1 + 0.5;
        xwmax *= 1 + 0.5;
        ywmax *= 1 + 0.5;
        hayZoom = false;
    }
}

void igvCamara::setPosition(float x, float y, float z) {
    P0.set(x, y, z);
}

/// <summary>
/// Mueve la camara según la tecla pulsada
/// </summary>
/// <param name="key">tecla pulsada</param>
/// <param name="dt">diferencia de tiempo respecto anterior fotograma</param>
/// <returns></returns>
float  igvCamara::onKeyBoard(unsigned char key, double dt) {
    double y1 = P0[Y];
    double y2 = r[Y];
    switch (key) {
        case 'w':
            {    
                igvPunto3D dir;
                dir = r - P0;
                dir.normalizar();
                P0 += dir * (m_speed * dt);
                r += dir * (m_speed * dt);
            break;
            }
        case 's':{
            igvPunto3D dir;
            dir = r - P0;
            dir.normalizar();
            P0 -= dir * (m_speed * dt);
            r -= dir * (m_speed * dt);
            break;
            }
        case 'a': {
            igvPunto3D dir = v.cross((r - P0));
            dir.normalizar();
            P0 += dir * (m_speed * dt);
            r += dir * (m_speed * dt);
            break;
            }
        case 'd': {
            igvPunto3D dir = (r - P0).cross(v);
            dir.normalizar();
            P0 += dir * (m_speed * dt);
            r += dir * (m_speed * dt);
            }
    }
    P0[Y] = y1;
    r[Y] = y2;

    return m_speed * dt;
}

/// <summary>
/// Rota la camara segun posicion del raton
/// </summary>
/// <param name="difX">Posicion X del cursor respecto a la pantalla</param>
/// <param name="difY">Posicion Y del cursor respecto a la pantalla</param>
/// <param name="dt">diferencia de tiempo respecto anterior fotograma</param>
/// <returns>devuelve el angulo que rota la camara</returns>
std::pair<float, float> igvCamara::mirar(double difX, double difY, double dt)
{
    rAnterior = r;
    alfa += difX * mouseSpeed * dt;
    beta += difY * mouseSpeed * dt;
    
    
    std::pair<float, float> ret(alfa,beta);

    double dist = sqrt((pow(r[X]-P0[X],2)  + pow(r[Z] - P0[Z], 2)));
    double alfaRad = alfa * M_PI / 180;
    double betaRad = beta * M_PI / 180;

    

    double rxz = dist * cos(betaRad);

    
        

    r[X] = P0[X] + sin(alfaRad) * rxz;
    r[Y] = P0[Y] + sin(betaRad) * dist;
    r[Z] = P0[Z] - cos(alfaRad) * rxz;

    if (abs(betaRad) > 0.5) { //bloqueo de camara en el eje Y
        beta -= difY * mouseSpeed * dt;
        alfa -= difX * mouseSpeed * dt;
        r = rAnterior;
        return ret;
    }

    
    return ret;
}
