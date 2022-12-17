#include <vector>
#include <cstdio>
#include <cstring>
#include "utils.h"
#pragma warning(disable:4996)


using namespace utils;

bool utils::cargaOBJ(const char* path,std::vector<float> &vertices, std::vector<float> &texture,std::vector<float> &normals, std::vector<unsigned int> &triangle){

    FILE* file = fopen(path, "r");

    //COMPRUEBA SI LA LECTURA DEL FICHERO SE REALIZA DE FORMA CORRECTA
    if( file == nullptr ){
        printf("No se puede abrir el fichero, comprueba la ruta\n");
        getchar();
        return false;
    }

    //LECTURA DEL FICHERO
    char lineHeader[200];
    int res = fscanf(file,"%s",lineHeader);
    while(res != EOF){
        if( strcmp(lineHeader,"v") == 0 ){ //CASO DE QUE SEA VERTICE
            float x,y,z;
            fscanf(file, "%f %f %f\n", &x, &y, &z );
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }else if( strcmp(lineHeader,"vt") == 0 ){ //CASO DE QUE SEA TEXTURA
            float x,y;
            fscanf(file, "% f %f\n", &x, &y);
            y = -y;
            texture.push_back(y);
            texture.push_back(y);
        }else if( strcmp( lineHeader, "vn" ) == 0 ){ //CASO DE QUE SEA NORMAL
            float x,y,z;
            fscanf(file, "%f %f %f\n", &x, &y, &z );
            normals.push_back(x);
            normals.push_back(y);
            normals.push_back(z);
        }else if( strcmp( lineHeader, "f" ) == 0 ){ //CASO DE QUE SEA TRIANGULO
            unsigned int x,y,z,nada;
            fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &x, &nada, &nada, &y, &nada,
                   &nada, &z, &nada, &nada);
            triangle.push_back(x-1);
            triangle.push_back(y-1);
            triangle.push_back(z-1);
        }else{
            // Probablemente un comentario
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }

        res = fscanf(file,"%s",lineHeader);
    }

    fclose(file);
    return true;
}


unsigned char* utils::LoadTexture(GLuint tex, const char* filename, int width, int height)
{
    // bmp 24 bit
    unsigned char* data;
    unsigned char R, G, B;
    FILE* file;

    file = fopen(filename, "rb");

    if (file == NULL)return 0;
    data = (unsigned char*)malloc(width * height * 3);
    fseek(file, 128, 0);
    fread(data, width * height * 3, 1, file);
    fclose(file);

    
    int index;
    for (int i = 0; i < width * height; ++i)
    {
        index = i * 3;
        B = data[index]; G = data[index + 1]; R = data[index + 2];
        data[index] = R; data[index + 1] = G; data[index + 2] = B;
    }

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    return data;
}
