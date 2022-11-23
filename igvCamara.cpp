
#include <math.h>
#include <stdio.h>

#include "igvCamara.h"

static int MARGIN = 10;

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
    init();
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

void igvCamara::setPosition(float x, float y, float z) {
    P0.set(x, y, z);
}

void igvCamara::onKeyBoard(unsigned char key, double dt) {
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
        case '+':
            m_speed += 0.1;
            break;
        case '-':
            m_speed -= 0.1;
            if(m_speed < 0.1f) m_speed = 0.1f;
            break;
    }
}

void igvCamara::onMouse(int x, int y) {

    int deltaX = x - m_mousePos.x;
    int deltaY = y - m_mousePos.y;

    m_mousePos.x = x;
    m_mousePos.y = y;

    float camVert = deltaY*1.5;

    if (camVert > 90)
        camVert = 90;
    else if (camVert < -90)
        camVert = -90;

    float camHor = deltaX*0.5;

    float rads = (camHor+deltaX)*M_PI / 180;
    P0[X] -= sin(rads)*deltaY;
    P0[Z] -= cos(rads)*deltaY;

    //m_angle_H += (float)deltaX / 20.0f;
    //m_angle_V += (float)deltaY / 50.0f;
/*
    update();
*/
}

void igvCamara::init() {
    igvPunto3D HTarget(r.c[X], 0.0, r.c[Z]);
    HTarget.normalizar();

    float angle = ToDegree(asin(abs(HTarget.c[Z])));

    if(HTarget.c[Z] >= 0.0f){
        if(HTarget.c[X] >= 0.0f)
            m_angle_H = 360.0f - angle;
        else
            m_angle_H = 180.0f - angle;
    }else{
        if(HTarget.c[X] >= 0.0f)
            m_angle_H = angle;
        else
            m_angle_H = 180.0f - angle;
    }

    m_angle_V = -ToDegree(asin(r.c[Y]));

    m_mousePos.x = m_window_Height/2;
    m_mousePos.y = m_window_Width/2;

}

void igvCamara::update() {
    igvPunto3D Yaxis(0.0f, 1.0f, 0.0f);

    igvPunto3D View(1.0f, 0.0f, 0.0f);
    View.Rotate(m_angle_H, Yaxis);
    View.normalizar();

    igvPunto3D U = Yaxis.cross(View);
    U.normalizar();
    View.Rotate(m_angle_V, U);

    r = View;
    r.normalizar();

    v = r.cross(U);
    v.normalizar();

}


void igvCamara::mirar(double incAlfa, double incBeta)
{
    beta += incBeta * 0.1;
    alfa += incAlfa * 0.1;
    if (beta > 89.0) {
        beta = 89.0;
    }
    else if (beta < -89.0) {
        beta = -89.0;
    }
    double dist = sqrt((pow(r[X]-P0[X],2)  + pow(r[Z] - P0[Z], 2)));
    double alfaRad = alfa * M_PI / 180;
    double betaRad = beta * M_PI / 180;
    double rxz = dist * cos(betaRad);

    r[X] = P0[X] + sin(alfaRad) * rxz;
    //r[Y] = P0[Y] + sin(betaRad) * dist;
    r[Z] = P0[Z] - cos(alfaRad) * rxz;

}
