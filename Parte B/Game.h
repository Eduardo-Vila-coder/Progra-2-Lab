#ifndef PARTE_B_GAME_H
#define PARTE_B_GAME_H

#include "Map.h"
#include "Camera.h"
#include "Enemy.h"
#include "Tower.h"

class Game {
private:
    Map* mapa; //Puntero al mapa 40x40
    Camera* camara; // Puntero a la camara 20 x 20

    Enemy** enemies; //(max.6) Arreglo de punteros a los enemigos
    Tower** towers;                              //max6
    int* enemyPathIndex;     // en q paso del camino va cada enemigo, se guarda

    int** caminoPath; //es donde se guardan las coordenadas
    int pathLength;

    int money;  // el dinero q tenemos para comprar torres
    int numEnemies;
    int numTowers;
    bool waveSpawned; //true si ya mandamos la oleada de enemigos y sino false
    bool victory; // se pone True cuando matamos a tdos los enemys(osea ganamos)
    bool defeat; // se pone True cuando un enemy llega a la meta B(osea perdemos)

    static const int MAX_ENEMIES = 6;
    static const int MAX_TOWERS = 6;
    static const int TOWER_COST = 100; //precio de cada torre
    static const int ENEMY_REWARD = 50; // dinero que nos dan por matar a un enemy

    void buildPath(); //la funcion se encarga de llenar caminoPath
    //                      con las coordenada desde I hasta B

public:
    Game(); // se crea el mpa, camara , camino y ponemos el dinero en 300
    ~Game();//aqui se libera td la memoria que eliminamos con "delete"

    void drawWindow();
    void gameStatus(); //muestra tipo como un resumen: dinero-torres-enemigos
    void placeTower(int x, int y);
    void spawnEnemies();//crea kis 6 enemigis y los pone al inicio del camino
    void moveEnemies();//mueve al enemigo una casilla adelnte
    void attackEnemies();
    void verifyResult();
    void saveGame(); //guarda td el estado del juego 
    void loadGame();    //si el archivo no existe, muestra error
    void moveCamera(int dx, int dy); //le dice a ka camara que se mueva segun las coordenadas q lleguen

    bool isVictory() const; //devuelve true si ganamos
    bool isDefeat() const;//devuelve true si perdemos
};

#endif //PARTE_B_GAME_H
