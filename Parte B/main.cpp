#include <iostream>
#include <string>
#include "Game.h"

using namespace std;

int main() {
    string command;

    do {
        cout << "$: ";
        cin >> command;
    } while (command != "init");

    Game* game = new Game();

    ifstream file("../savegame.txt");
    if (file.is_open()) {
        file.close();
        game->loadGame();
    } else {
        cout << "Welcome to the world of tower defense xyz" << endl;
        game->gameStatus();
        game->drawWindow();
    }

    int n, x, y;

    do {
        cout << "$: ";
        cin >> command;

        if (command == "map") {
            game->drawWindow();
        } else if (command == "up") {
            cin >> n;
            game->moveCamera(0, -n);        // Es -n en up porque el eje Y esta invertido
            game->drawWindow();
        } else if (command == "down") {
            cin >> n;
            game->moveCamera(0, n);         // Es +n en down porque el eje Y esta invertido
            game->drawWindow();
        } else if (command == "left") {
            cin >> n;
            game->moveCamera(-n, 0);
            game->drawWindow();
        } else if (command == "right") {
            cin >> n;
            game->moveCamera(n, 0);
            game->drawWindow();
        } else if (command == "status") {
            game->gameStatus();
        } else if (command == "place") {
            cin >> x >> y;
            game->placeTower(x, y);
            game->drawWindow();
        } else if (command == "wave") {
            game->spawnEnemies();
            game->gameStatus();
            game->drawWindow();
        } else if (command == "next") {
            game->moveEnemies();
            game->attackEnemies();
            game->verifyResult();
        } else if (command == "save") {
            game->saveGame();
            cout << "El juego ha finalizado" << endl;
            break;
        } else if (command == "load") {
            game->loadGame();
        } else if (command == "exit") {
            cout << "El juego ha finalizado" << endl;
            break;
        }else if (command == "help")
        {
            cout << "Comandos disponibles:" << endl;
            cout << "init : Inicia un juego nuevo con 300 de dinero" << endl;
            cout << "map : Muestra la ventana del mapa" << endl;
            cout << "up : Mueve la camara arriba n posiciones" << endl;
            cout << "down: Mueve la camara abajo n posiciones" << endl;
            cout << "left : Mueve la camara a la izquierda n posiciones" << endl;
            cout << "right : Mueve la camara a la derecha n posiciones" << endl;
            cout << "place x y : Coloca una torre en fila x, columna y (cuesta 100)" << endl;
            cout << "wave : Genera 6 enemigos en el inicio del camino" << endl;
            cout << "next : Avanza un turno: enemigos se mueven y torres atacan" << endl;
            cout << "status : Muestra dinero, cantidad de torres y enemigos vivos" << endl;
            cout << "save : Guarda la partida en savegame.txt" << endl;
            cout << "load : Carga la partida desde savegame.txt" << endl;
            cout << "exit : Cierra el juego" << endl;

        }
        else {
            cout << "Comando no reconocido" << endl;
        }
    } while (!game->isVictory() && !game->isDefeat());

    game->drawWindow();

    if (game->isVictory()) {
        cout << "GANASTE - Todos los enemigos fueron eliminados" << endl;
    } else if (game->isDefeat()) {
        cout << "GAME OVER - La base fue destruida" << endl;
    }

    delete game;

    return 0;
}
