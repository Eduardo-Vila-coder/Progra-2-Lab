//
// Created by HP on 6/5/2026.
//

#ifndef PARTE_B_MAP_H
#define PARTE_B_MAP_H

class Map {
private:
    int** gameMap;
    int length_side;

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
