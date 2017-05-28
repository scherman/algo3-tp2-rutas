cmake_minimum_required(VERSION 3.7)
project(algo3_tp2_rutas)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES_EJ1 problema1.cpp listaAdyacencia.hpp stringTokenizer.hpp)
set(SOURCE_FILES_EJ2 Eje.h problema2.cpp listaAdyacencia.hpp stringTokenizer.hpp)
set(SOURCE_FILES_EJ3 Eje.h problema3.cpp GrafoListaIncidencias.h DisjointSet.h)

add_executable(ej1 ${SOURCE_FILES_EJ3})
add_executable(ej2 ${SOURCE_FILES_EJ3})
add_executable(ej3 ${SOURCE_FILES_EJ3})
