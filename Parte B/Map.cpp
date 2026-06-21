//
// Created by HP on 6/5/2026.
//


#include "Map.h"

Map::Map() {
    tamanio_lado = 40;
    mapa = nullptr;

    enemigos = nullptr;
    torres = nullptr;

    cantidad_enemigos = 0;
    cantidad_torres = 0;

    crearMapa();
    crearCamino();
}

Map::Map(int tamanio_lado) {
    this->tamanio_lado = tamanio_lado;
    mapa = nullptr;

    enemigos = nullptr;
    torres = nullptr;

    cantidad_enemigos = 0;
    cantidad_torres = 0;

    crearMapa();
    crearCamino();
}

Map::~Map() {
    for (int i = 0; i < tamanio_lado; i++) {
        delete[] mapa[i];
    }

    delete[] mapa;
    mapa = nullptr;

    // Solo eliminamos los arreglos de punteros.
    // No eliminamos los objetos Enemy ni Tower porque Map tiene agregacion con ellos.
    delete[] enemigos;
    enemigos = nullptr;

    delete[] torres;
    torres = nullptr;
}

int** Map::getMapa() const {
    return mapa;
}

int Map::getTamanioLado() const {
    return tamanio_lado;
}

void Map::crearMapa() {
    mapa = new int*[tamanio_lado];

    for (int i = 0; i < tamanio_lado; i++) {
        mapa[i] = new int[tamanio_lado];

        for (int j = 0; j < tamanio_lado; j++) {
            mapa[i][j] = 0;
        }
    }
}

void Map::crearCamino() {
    // Inicio del camino
    mapa[0][0] = 2;

    // Primer tramo: fila 1, columnas 2 hasta 4
    for (int j = 1; j <= 3; j++) {
        mapa[0][j] = 1;
    }

    // Segundo tramo: columna 4, filas 2 hasta 9
    for (int i = 1; i <= 8; i++) {
        mapa[i][3] = 1;
    }

    // Tercer tramo: fila 9, columnas 5 hasta 25
    for (int j = 4; j <= 24; j++) {
        mapa[8][j] = 1;
    }

    // Cuarto tramo: columna 25, filas 10 hasta 18
    for (int i = 9; i <= 17; i++) {
        mapa[i][24] = 1;
    }

    // Quinto tramo: fila 18, columnas 24 hasta 5
    for (int j = 23; j >= 4; j--) {
        mapa[17][j] = 1;
    }

    // Sexto tramo: columna 5, filas 19 hasta 27
    for (int i = 18; i <= 26; i++) {
        mapa[i][4] = 1;
    }

    // Septimo tramo: fila 27, columnas 6 hasta 37
    for (int j = 5; j <= 36; j++) {
        mapa[26][j] = 1;
    }

    // Octavo tramo: columna 37, filas 28 hasta 40
    for (int i = 27; i <= 39; i++) {
        mapa[i][36] = 1;
    }

    // Ultimo tramo: fila 40, columnas 38 y 39
    for (int j = 37; j <= 38; j++) {
        mapa[39][j] = 1;
    }

    // Base en la fila 40, columna 40
    mapa[39][39] = 3;
}

void Map::placeTower(int fila, int columna) {
}

void Map::spawnEnemies() {
}

void Map::moveEnemies() {
}

void Map::attackEnemies() {
}

void Map::verifyResult(bool& victoria, bool& derrota) {
}
