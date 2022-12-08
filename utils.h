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

namespace utils{

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