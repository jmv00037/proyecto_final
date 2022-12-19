#include "cubo.h"


cubo::cubo(){
    texturaSuelo = utils::LoadTexture(SUELO, "01.bmp", 316, 316);
    texturaPared = utils::LoadTexture(PARED, "paredes.bmp", 128, 128);
    texturaPared2 = utils::LoadTexture(PARED2, "wall.bmp", 64, 64);
    puerta = utils::LoadTexture(PUERTA, "puerta.bmp", 64, 64);
    torso = utils::LoadTexture(TORSO, "torso.bmp", 185, 185);
}

cubo::~cubo(){
    free(texturaSuelo);
    free(texturaPared);
    free(texturaPared2);
    free(puerta);
    free(torso);
}

/// <summary>
/// crea un cubo
/// </summary>
void cubo::dibujar(float sx, float sy, float sz, unsigned int repetirX, unsigned int repetirY)
{
     
    int i, j;
    for (i = 0; i < 6; i++)
    {        
        glBegin(GL_QUADS);
        glNormal3f(normals[i][0], normals[i][1], normals[i][2]);
        for (j = 0; j < 4; j++)
        {
            glTexCoord2f(textures[i][j][0]*repetirX, textures[i][j][1]* repetirY); // SE MULTIPLICA POR repetir PARA REPETIR LA IMAGEN varias VECES EN EL CUBO
            glVertex3f(sx * cube[i][j][0], sy * cube[i][j][1], sz * cube[i][j][2]);
        }
        glEnd();
    }
}

/// <summary>
/// aplica texturas indicadas
/// </summary>
/// <param name="x">id textura</param>
void cubo::aplicarTexturas(unsigned int x){
    glBindTexture(GL_TEXTURE_2D, x);
    switch (x){
    case SUELO:
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 316, 316, GL_RGB, GL_UNSIGNED_BYTE, texturaSuelo);
        break;
    case PARED:
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 128, 128, GL_RGB, GL_UNSIGNED_BYTE, texturaPared);
        break;
    case PARED2:
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 64, 64, GL_RGB, GL_UNSIGNED_BYTE, texturaPared2);
        break;
    case PUERTA:
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 64, 64, GL_RGB, GL_UNSIGNED_BYTE, puerta);
        break;
    case TORSO:
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 185, 185, GL_RGB, GL_UNSIGNED_BYTE, torso);
        break;
    default:
        break;
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_COLOR);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

/// <summary>
/// Crea un cubo con textura
/// </summary>
void cubo::cargarCubo(unsigned int x, unsigned int repetirX, unsigned int repetirY){
    aplicarTexturas(x);
    dibujar(1, 1, 1,  repetirX,repetirY);
}

/// <summary>
/// Crea un cubo sin textura
/// </summary>
void cubo::sint(unsigned int x, unsigned int repetirX, unsigned int repetirY) {
    dibujar(1, 1, 1,  repetirX, repetirY);
}