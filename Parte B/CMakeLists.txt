cmake_minimum_required(VERSION 4.2)
project(Parte_B)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Parte_B
        Camera.cpp
        Camera.h
        Enemy.cpp
        Enemy.h
        Game.cpp
        Game.h
        main.cpp
        Map.cpp
        Map.h
        Tower.cpp
        Tower.h)
