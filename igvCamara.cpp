
#include <math.h>
#include <stdio.h>

#include "igvCamara.h"
#include "utils.h"

// Metodos constructores

igvCamara::igvCamara() {
    m_pos = igvPunto3D(0.0f, 0.0f, 0.0f);
    m_target = igvPunto3D(0.0f, 0.0f, 1.0f);
    m_up = igvPunto3D(0.0f, 1.0f, 0.0f);
}

igvCamara::~igvCamara() {}

igvCamara::igvCamara(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V) {
    m_pos = _P0;
    m_target = _r;
    m_up = _V;

	tipo = _tipo;
}


// Metodos publicos 
void igvCamara::set(igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V) {
    m_pos = _P0;
    m_target = _r;
    m_up = _V;
}
void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
	double _xwmin, double _xwmax, double _ywmin, double _ywmax, double _znear, double _zfar) {
	tipo = _tipo;

    m_pos = _P0;
    m_target = _r;
    m_up = _V;

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

    m_pos = _P0;
    m_target = _r;
    m_up = _V;

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
	gluLookAt(m_pos[X], m_pos[Y], m_pos[Z], m_target[X], m_target[Y], m_target[Z], m_up[X], m_up[Y], m_up[Z]);
}

void igvCamara::setPosition(float x, float y, float z) {
    m_pos.set(x,y,z);
}

void igvCamara::onKeyBoard(unsigned char key) {
    switch (key) {
        case 'w':
            {
            igvPunto3D dir;
            dir = m_target - m_pos;
            dir.normalizar();
            m_pos += dir *= m_speed ;
            m_target += dir *= m_speed;
            break;
            }
        case 's':
            m_pos -= (m_target * m_up);
            break;
        case 'a': {
            igvPunto3D izq = m_target.cross(m_up);
            izq.normalizar();
            izq *= m_speed;
            m_pos += izq;
            break;
            }
        case 'd': {
            igvPunto3D der = m_up.cross(m_target);
            der.normalizar();
            der *= m_speed;
            m_pos += der;
            break;
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