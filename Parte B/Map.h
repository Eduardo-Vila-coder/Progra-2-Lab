#ifndef PARTE_B_MAP_H
#define PARTE_B_MAP_H
#include <vector>
#include <cstdlib>
#include<ctime>
#include "Enemy.h"
#include "Tower.h"
using namespace std;

class Map {
private:
    int** gameMap;
    int length_side;

    //Creamos un arreglo local con las posiciones iniciales de todos los enemigos considerando el numero maximo de ellos que puede aparecer
    int start_position[6][2]={{0, 1}, {0, 2}, {0, 3},{0, 4}, {1, 4}, {2, 4}};

    // Composicion: Lo que va a hacer Map es guardar punteros a enemigos y torres
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

    void placeTower(int fila, int columna, int danio, int disparos, int& dinero);
    void spawnEnemies();
    void moveEnemies();
    void attackEnemies(int &dinero);
    void verifyResult(bool& victory, bool& defeat);

    vector<Enemy*>& getEnemigos();
    vector<Tower*>& getTorres();
};

#endif //PARTE_B_MAP_H
