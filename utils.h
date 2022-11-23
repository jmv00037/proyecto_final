//
// Created by jesus on 3/11/22.
//

#ifndef OPENGLLINUXTEST_UTILS_H
#define OPENGLLINUXTEST_UTILS_H

#include <GL/glut.h>
#include "igvPunto3D.h"
#include "vector"
#include "cmath"
#include "string"

#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))

namespace utils{
    //CLASES UTILES
    struct Vector2i
    {
        int x;
        int y;
    };

    struct Quaternion
    {
        float x, y, z, w;

        Quaternion(float Angle, const igvPunto3D& V);

        Quaternion(float _x, float _y, float _z, float _w);

        void Normalize();

        Quaternion Conjugate() const;

        igvPunto3D   ToDegrees();

        Quaternion operator*( const Quaternion& r);

        Quaternion operator*( const igvPunto3D& v);

    };


    //FUNCIONES UTILES
    /**
     * CARGA UN OBJETO DE UN FICHERO .obj
     * @param path RUTA DEL FICHERO
     * @param vertices VECTOR CON LOS VERTICES DEL OBJETO
     * @param texture VECTOR CON LOS VERTICES DE TEXTURAS
     * @param normals VECTOR CON LAS NORMALES
     * @param triangle VECTOR CON LOS TRIANGULOS
     * @return FALSO SI NO ABRE EL FICHERO, TRUE SI CARGA EL OBJETO COMPLETO
     */
    bool cargaOBJ(const char* path,
                  std::vector<float>& vertices,
                  std::vector<float>& texture,
                  std::vector<float>& normals,
                  std::vector<unsigned int>& triangle);

}


#endif //OPENGLLINUXTEST_UTILS_H