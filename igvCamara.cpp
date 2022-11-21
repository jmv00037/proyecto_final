
#include <math.h>
#include <stdio.h>

#include "igvCamara.h"
#include "utils.h"

// Metodos constructores

igvCamara::igvCamara() {
    P0 = igvPunto3D(0.0f, 0.0f, 0.0f);
    r = igvPunto3D(0.0f, 0.0f, 1.0f);
    v = igvPunto3D(0.0f, 1.0f, 3.0f);
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