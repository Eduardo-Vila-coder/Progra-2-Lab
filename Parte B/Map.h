#ifndef PARTE_B_MAP_H
#define PARTE_B_MAP_H
#include <vector>
#include "Enemy.h"
#include "Tower.h"

class Map {
private:
    int** gameMap;
    int length_side;

    // Agregacion: Lo que va a hacer Map es guardar punteros a enemigos y torres
    vector <Enemy*> enemigos;
    vector <Tower*> torres;
    

public:
    Map();
    Map(int length_side);
    ~Map();

    void crearMapa();
    void crearCamino();

    int** getGameMap() const;
    int getLengthSide() const;
};

#endif //PARTE_B_MAP_H
