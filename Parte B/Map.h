//
// Created by HP on 6/5/2026.
//

#ifndef PARTE_B_MAP_H
#define PARTE_B_MAP_H

#include "Enemy.h"
#include "Tower.h"

class Map {
private:
    int** mapa;
    int tamanio_lado;

    // Utilizaremos arreglo dinamico de punteros
    // Map va a agregar enemigos y torres pero no necesariamente va a ser quien los destruye
    Enemy** enemigos;
    Tower** torres;

    int cantidad_enemigos;
    int cantidad_torres;

public:
    Map();
    Map(int tamanio_lado);
    ~Map();

    int** getMapa() const;
    int getTamanioLado() const;

    void crearMapa();
    void crearCamino();

    // Estos metodos se completaran despues usando Enemy y Tower
    void placeTower(int fila, int columna);
    void spawnEnemies();
    void moveEnemies();
    void attackEnemies();
    void verifyResult(bool& victoria, bool& derrota);
};

#endif //PARTE_B_MAP_H
