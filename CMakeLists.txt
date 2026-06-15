cmake_minimum_required(VERSION 4.1)
project(Proyecto2_lab)

set(CMAKE_CXX_STANDARD 14)

include_directories("Parte A")
include_directories("Parte B")

add_executable(Proyecto2_lab
        "Parte A/funciones.cpp"
        "Parte A/funciones.h"
        "Parte A/main.cpp"
        "Parte B/Camera.cpp"
        "Parte B/Camera.h"
        "Parte B/Enemy.cpp"
        "Parte B/Enemy.h"
        "Parte B/Game.cpp"
        "Parte B/Game.h"
        "Parte B/main.cpp"
        "Parte B/Map.cpp"
        "Parte B/Map.h"
        "Parte B/Tower.cpp"
        "Parte B/Tower.h")
