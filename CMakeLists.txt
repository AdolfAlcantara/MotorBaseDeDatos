cmake_minimum_required(VERSION 3.8)
project(DB_MOTOR)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        bloque.cpp
        bloque.h
        bloquecampo.cpp
        bloquecampo.h
        bloquemaestro.cpp
        bloquemaestro.h
        bloquetabla.cpp
        bloquetabla.h
        datafile.cpp
        datafile.h
        main.cpp
        manejadorbloques.cpp
        manejadorbloques.h
        manejadortablas.cpp
        manejadortablas.h
        tabla.cpp
        tabla.h
        campo.cpp
        campo.h
        Registro.cpp
        Registro.h
        bloqueregistro.cpp
        bloqueregistro.h
        jsonEstruct.cpp
        jsonEstruct.h
        json.hpp)

add_executable(DB_MOTOR ${SOURCE_FILES})