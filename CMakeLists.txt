cmake_minimum_required(VERSION 3.10) # common to every CLion project
project(proyecto_final) # project name

set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

################################################

add_executable(proyecto_final main.cpp igvInterfaz.h igvInterfaz.cpp igvEscena3D.cpp igvEscena3D.h igvCamara.h igvCamara.cpp igvPunto3D.cpp igvPunto3D.h utils.cpp utils.h) #common to all clion project

target_link_libraries(proyecto_final ${OpenGlLinkers}) # linking opengl libraries to the project
