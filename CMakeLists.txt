cmake_minimum_required(VERSION 3.7)
project(algo3_tp2_rutas)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Eje.h problema3.cpp GrafoListaIncidencias.h DisjointSet.h)
add_executable(algo3_tp2_rutas ${SOURCE_FILES})