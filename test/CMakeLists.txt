cmake_minimum_required(VERSION 3.19)
project(inicio_julio_2021_cmake)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-g)

include_directories("../include")

add_executable(testSecuencia testSecuencia.cpp ../src/secuenciaEnteros.cpp ../include/opcionInversion.h)
add_executable(testVariable testVariable.cpp ../src/variable.cpp)
add_executable(testMatriz testMatriz.cpp ../src/matriz.cpp ../src/secuenciaEnteros.cpp)
add_executable(testDiagrama testDiagrama.cpp ../src/diagrama.cpp ../src/matriz.cpp
               ../src/variable.cpp ../src/secuenciaEnteros.cpp ../src/utilidades.cpp
               ../src/secuenciaOperaciones.cpp ../src/lector.cpp
               ../include/opcionInversion.h ../include/operacion.h
               ../include/secuenciaOperaciones.h)
add_executable(testLector testLector.cpp ../src/lector.cpp ../src/diagrama.cpp
               ../src/secuenciaEnteros.cpp ../src/variable.cpp ../src/matriz.cpp
               ../src/utilidades.cpp ../include/opcionInversion.h
               ../src/secuenciaOperaciones.cpp)
