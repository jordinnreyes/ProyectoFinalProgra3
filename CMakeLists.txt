cmake_minimum_required(VERSION 3.28.1)
project(ProyectoFinalProgra3)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProyectoFinalProgra3 main.cpp
        classPelicula/pelicula.cpp
        classPelicula/pelicula.h
        classPelicula/procesarCsv.cpp
        classUsuario/usuario.h
        nodoYarbol/nodo.cpp
        nodoYarbol/nodo.h
        nodoYarbol/arbolPeliculas.cpp
        nodoYarbol/arbolPeliculas.h
        classBusqueda/busqueda.cpp
        classBusqueda/busqueda.h
        classPelicula/procesarCsv.h
)
