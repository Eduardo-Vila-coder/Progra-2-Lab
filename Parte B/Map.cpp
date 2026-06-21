//
// Created by HP on 6/5/2026.
//

#include "Map.h"

Map::Map() {
tamanio_lado = 40;
mapa = nullptr;
inicializarMapa();
}

Map::Map(int tamanio_lado) {
this->tamanio_lado = tamanio_lado;
mapa = nullptr;
inicializarMapa();
}

Map::~Map() {
eliminarMapa();
}

int Map::getTamanioLado() const {
return tamanio_lado;
}

int** Map::getMapa() const {
return mapa;
}

void Map::inicializarMapa() {
// Creamos las filas del arreglo dinamico
mapa = new int*[tamanio_lado];


for (int i = 0; i < tamanio_lado; i++) {
    // Creamos las columnas de cada fila
    mapa[i] = new int[tamanio_lado];

    // Al inicio, todas las celdas son espacios vacios
    for (int j = 0; j < tamanio_lado; j++) {
        mapa[i][j] = 0;
    }
}

// Por ahora colocamos el inicio y la base.
// Cuando tengan definido el camino final de 40 x 40,
// aqui se agregaran las posiciones cuyo valor sera 1.
mapa[0][0] = 2; // I: inicio
mapa[tamanio_lado - 1][tamanio_lado - 1] = 3; // B: base


}

int Map::getCelda(int fila, int columna) const {
// Si la posicion esta fuera del mapa, devolvemos -1
if (fila < 0 || fila >= tamanio_lado || columna < 0 || columna >= tamanio_lado) {
return -1;
}


return mapa[fila][columna];


}

void Map::setCelda(int fila, int columna, int valor) {
// Solo modificamos la celda si existe dentro del mapa
if (fila >= 0 && fila < tamanio_lado && columna >= 0 && columna < tamanio_lado) {
mapa[fila][columna] = valor;
}
}

void Map::agregarEnemigo(Enemy* enemigo) {
enemigos.push_back(enemigo);
}

void Map::agregarTorre(Tower* torre) {
torres.push_back(torre);
}

vector<Enemy*>& Map::getEnemigos() {
return enemigos;
}

vector<Tower*>& Map::getTorres() {
return torres;
}

void Map::eliminarMapa() {
// Si no existe mapa, no hay nada que eliminar
if (mapa == nullptr) {
return;
}


// Eliminamos cada fila creada con new[]
for (int i = 0; i < tamanio_lado; i++) {
    delete[] mapa[i];
}

// Eliminamos el arreglo que contenia las filas
delete[] mapa;
mapa = nullptr;


}
