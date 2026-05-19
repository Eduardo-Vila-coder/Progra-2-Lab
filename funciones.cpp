#include "funciones.h"
#include <iostream>
using namespace std;

void initGame(int**& gameMap, const int& length_side) {
    //Paso_1: Como primer paso, creamos las 20 filas y las 20 columnas
    gameMap = new int*[length_side];
        
    for (int i = 0; i<length_side; i++) {
        gameMap[i] = new int[length_side];
    }

    //Paso_2: Como el numero 0 representa espacios vacios, llenamos todo el mapa con ceros
    for (int i = 0; i < length_side; i++) {
        for (int j = 0; j < length_side; j++) {
            gameMap[i][j] = 0;
        }
    }

    //Paso_3: Colocamos el inicio y el final del camino
    gameMap[0][0] = 2; // El numero 2 representa el "I"
    gameMap[19][19] = 3; // El numero 3 representa la "B"

    //Dibujamos el camino por donde pasaran los enemigos. Lo voy a dividir en tramos. El numero 1 representa un espacio negro o lleno
    gameMap[1][0] = 1;
    for (int i = 1; i <= 3; i++) gameMap[i][1] = 1;   //  Primer tramo
    for (int j = 1; j <= 11; j++) gameMap[4][j] = 1;  //  Segundo tramo
    for (int i = 5; i <= 8; i++) gameMap[i][11] = 1;  //  Tercer tramo
    for (int j = 2; j <= 11; j++) gameMap[9][j] = 1;  //  Cuarto tramo
    for (int i = 10; i <= 13; i++) gameMap[i][2] = 1; //  Quinto tramo
    for (int j = 2; j <= 17; j++) gameMap[14][j] = 1; //  Sexto tramo
    for (int i = 15; i <= 19; i++) gameMap[i][17] = 1; // Septimo tramo
    gameMap[19][18] = 1;    

    cout << "----------Mapa creado----------" << endl;
        
    
}

void drawMap(int** gameMap,const int length_side, int towersPosition[6][2], int enemiesPosition[6][2], bool towersActivate[6], bool enemiesActivate[6]) {
    cout<<"column   ";
    //Imprimimos el numero de cada columna
    for (int i = 0; i < length_side; i++) {
        if (i<=9)
            cout<<i<<"  ";
        else {
            cout<<i<<" ";
        }
    }
    cout <<"\n\n";

    //Imprimimos el numero de cada fila
    for (int i=0; i<length_side;i++) {
        if (i<=9)
            cout<<"row "<<i<<"    ";
        else {
            cout<<"row "<<i<<"   ";
        }
        //Imprimimos el inicio y el final
        for (int j=0; j<length_side;j++) {
            //Creamos una variable booleana para evitar colocar varios elementos en una misma posicion
            bool draw=false;

            if (gameMap[i][j]==2)
                cout<<" I ";
            if (gameMap[i][j]==3)
                cout<<" B ";
            //Verificamos si hay torre en alguna posicion para imprimirla
            for (int k=0; k<6; k++) {
                if (i==towersPosition[k][0] && j==towersPosition[k][1] && towersActivate[k]==true) {
                    draw=true;
                    cout<<" T"<<k<<" ";
                }

                //Verificamos si hay enemigos en alguna posicion para mostrarlo en consola
                else if (i==enemiesPosition[k][0] && j==enemiesPosition[k][1] && enemiesActivate[k]==true) {
                    draw=true;
                    cout<<" E ";
                }
            }

            //Mostramos el camino con "*"
            if (gameMap[i][j]==1 && draw==false) {}
                cout<<" * ";
            //Rellenamos los vacios
            if (gameMap[i][j]==0 && draw==false) {}
                cout<<"  ";
        }
        cout << endl;
    }
}

void placeTower(int x, int y) {
    
}
void spawnEnemies(int enemiesPosition[6][2], bool enemiesActivate[6]) {

    //Creamos un arreglo local con las posiciones iniciales de todos los enemigos considerando el numero maximo
    int star_position[6][2]={{0, 1}, {0, 1}, {1, 2},
    {2, 2}, {3, 2}, {3, 3}
    };
    //Generamos un numero aleatorio de enemigos entre 3 y 6
    int n=(rand()%4)+3;

    for (int k=0; k<n; k++) {
        //Asignamos las coordenadas x e y usando los valores del arreglo creado anteriormente
        enemiesPosition[k][0] = star_position[k][0];
        enemiesPosition[k][1] = star_position[k][1];

        //Actualizamos el estado del enemigo para ejecutar las funciones drawMap y attackEnemies
        enemiesActivate[k]=true;
    }
}

void moveEnemies() {}
void attackEnemies() {}
void verifyResult() {}
void gameStatus() {}

void deleteMap(int**& gameMap, const int& length_side) {
    for (int i = 0; i < length_side; i++) {
        delete[] gameMap[i];
    }

    delete[] gameMap;
    gameMap = nullptr;
}
