cmake_minimum_required(VERSION 3.19)
project(busquedaSecuencia)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-g)

add_subdirectory(test)
include_directories("./include")

add_test(testSecuencia test/testSecuencia.cpp src/secuenciaEnteros.cpp)
add_test(testVariable test/testVariable.cpp src/variable.cpp)
add_test(testMatriz test/testMatriz.cpp src/matriz.cpp src/secuenciaEnteros.cpp)
add_test(testDiagrama test/testDiagrama.cpp src/lector.cpp src/diagrama.cpp src/secuenciaEnteros.cpp
        src/variable.cpp src/matriz.cpp src/utilidades.cpp)
add_test(testLector test/testLector.cpp src/lector.cpp src/diagrama.cpp src/secuenciaEnteros.cpp
        src/variable.cpp src/matriz.cpp src/utilidades.cpp)
add_executable(principal src/principal.cpp src/diagrama.cpp src/matriz.cpp src/lector.cpp
               src/aStarSearch.cpp src/colaPrioridad.cpp src/estado.cpp
               src/secuenciaEnteros.cpp src/secuenciaOperaciones.cpp src/utilidades.cpp
               src/variable.cpp
               include/diagrama.h include/matriz.h include/lector.h include/aStarSearch.h
               include/colaPrioridad.h
               include/secuenciaEnteros.h include/secuenciaOperaciones.h include/utilidades.h
               include/variable.h)
