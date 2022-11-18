#include <stdio.h>
#include <math.h>

#include "igvPunto3D.h"

// Constructores
igvPunto3D::igvPunto3D() {
	c[X] = c[Y] = c[Z] = 0.0;
}

igvPunto3D::igvPunto3D (const double& x, const double& y, const double& z ) {
	c[X] = x;
	c[Y] = y;
	c[Z] = z;	
}

// Constructor de copia
igvPunto3D::igvPunto3D (const igvPunto3D& p ) {
	c[X] = p.c[X];
	c[Y] = p.c[Y];
	c[Z] = p.c[Z];
}

// Operador de asignación
igvPunto3D& igvPunto3D::operator = (const igvPunto3D& p) {
	c[X] = p.c[X];
	c[Y] = p.c[Y];
	c[Z] = p.c[Z];
	return(*this);
}

int igvPunto3D::operator == (const igvPunto3D& p) {
	return ((fabs(c[X]-p[X])<IGV_EPSILON) && (fabs(c[Y]-p[Y])<IGV_EPSILON) && (fabs(c[Z]-p[Z])<IGV_EPSILON));
}

int igvPunto3D::operator != (const igvPunto3D& p) {
	return ((fabs(c[X]-p[X])>=IGV_EPSILON) || (fabs(c[Y]-p[Y])>=IGV_EPSILON) || (fabs(c[Z]-p[Z])>=IGV_EPSILON));
}

// Destructor
igvPunto3D::~igvPunto3D() {
}

// Operadores

void igvPunto3D::set( const double& x, const double& y, const double& z) {
	c[X] = x;
	c[Y] = y;
	c[Z] = z;
}

igvPunto3D& igvPunto3D::operator+(const igvPunto3D& p)
{
    igvPunto3D res(c[0] + p.c[0], c[1] + p.c[1], c[2] + p.c[2]);
    return res;
}

igvPunto3D& igvPunto3D::operator-(const igvPunto3D& p)
{
    igvPunto3D* res = new igvPunto3D(c[0] - p.c[0], c[1] - p.c[1], c[2] - p.c[2]);
    return *res;
}

igvPunto3D& igvPunto3D::operator-=(const igvPunto3D& p) {
    c[X] -= p.c[X];
    c[Y] -= p.c[Y];
    c[Z] -= p.c[Z];
    return *this;
}

igvPunto3D& igvPunto3D::operator+=(const igvPunto3D& p) {
    c[X] += p.c[X];
    c[Y] += p.c[Y];
    c[Z] += p.c[Z];
    return *this;
}

igvPunto3D &igvPunto3D::operator*=(float f) {
    this->c[X] *= f;
    this->c[Y] *= f;
    this->c[Z] *= f;

    return *this;
}

igvPunto3D &igvPunto3D::operator*(const igvPunto3D &p) {
    igvPunto3D r;

    r[X] = this->c[X] * p[X];
    r[Y] = this->c[Y] * p[Y];
    r[Z] = this->c[Z] * p[Z];

    return r;
}

igvPunto3D igvPunto3D::cross(const igvPunto3D& v) const
{
    const float _x = this->c[Y] * v[Z] - this->c[Z] * v[Y];
    const float _y = this->c[Z] * v[X] - this->c[X] * v[Z];
    const float _z = this->c[X] * v[Y] - this->c[Y] * v[X];

    return igvPunto3D(_x, _y, _z);
}

void igvPunto3D::normalizar() {
    double mod = sqrt(pow(c[X],2) + pow(c[Y] , 2) + pow(c[Z],2));
    c[X] /= mod;
    c[Y] /= mod;
    c[Z] /= mod;
}
