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

#define SUELO 1
#define PARED 2
#define PARED2 3
#define PUERTA 4
#define TORSO 5

namespace utils{

    /// <summary>
    /// Carga el modelo obj en los vectores
    /// </summary>
    /// <param name="path">path del archivo</param>
    /// <param name="vertices">vector de vertices</param>
    /// <param name="texture">vector de texturas</param>
    /// <param name="normals">vector de normales</param>
    /// <param name="triangle">vector de triangulos</param>
    /// <returns></returns>
    bool cargaOBJ(const char* path,
                  std::vector<float>& vertices,
                  std::vector<float>& texture,
                  std::vector<float>& normals,
                  std::vector<unsigned int>& triangle);

    /// <summary>
    /// Carga la textura
    /// </summary>
    /// <param name="tex">id de la textura</param>
    /// <param name="filename">path del archivo</param>
    /// <param name="width">numero de pixeles en ancho</param>
    /// <param name="height">numero de pixeles en alto</param>
    /// <returns>devuelve la textura cargada</returns>
    unsigned char* LoadTexture(GLuint tex, const char* filename, int width, int height);

}


#endif //OPENGLLINUXTEST_UTILS_H