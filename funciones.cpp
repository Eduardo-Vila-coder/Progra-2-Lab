#include "funciones.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include<ctime>
using namespace std;

void initGame(int**& gameMap, const int& length_side, int towersPosition[6][2], bool towersActivate[6]) {
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


    //Inicializamos la posicion de las torres con -1 , porque este numero esta sin uso en las posiciones del mapa.
    for (int i = 0; i < 6; i++) {
        towersPosition[i][0] = -1;
        towersPosition[i][1] = -1;
        towersActivate[i] = false;
    }

    cout<< "----------Mapa creado----------"<< endl;
        
    
}


void drawMap(int** gameMap,const int length_side, int towersPosition[6][2], int enemiesPosition[6][2], bool towersActivate[6], bool enemiesActivate[6]) {
    cout << setw(6) << " ";
    //Imprimimos el numero de cada columna
    for (int i = 0; i < length_side; i++) {
        cout << setw(4) << i+1;
    }
    cout <<"\n\n";

    //Imprimimos el numero de cada fila
    for (int i=0; i<length_side;i++) {
        if (i<=9)
            cout << setw(4) << i+1 << "  ";
        else {
            cout << setw(4) << i+1 << "  ";
        }
        //Imprimimos el inicio y el final
        for (int j=0; j<length_side;j++) {
            bool draw=false;

            if (gameMap[i][j]==2) {
                cout << setw(4) << "I";
                draw=true;
            }
            if (gameMap[i][j]==3) {
                cout << setw(4) << "B";
                draw=true;
            }

            //Verificamos si hay torre en alguna posicion para imprimirla
            for (int k=0; k<6; k++) {
                if (i==towersPosition[k][0] && j==towersPosition[k][1] && towersActivate[k]==true) {
                    draw=true;
                    cout << setw(4) << ("T" + to_string(k + 1));
                }
                //Verificamos si hay enemigos en alguna posicion para mostrarlo en consola
                else if (i==enemiesPosition[k][0] && j==enemiesPosition[k][1] && enemiesActivate[k]==true){
                    draw=true;
                    cout << setw(4) << "E";
                }
            }
            if (gameMap[i][j]==1 && draw==false) {
                cout << setw(4) << "*";
            }
            if (gameMap[i][j]==0 && draw==false) {
                cout << setw(4) << ".";
            }
        }


        cout << endl;
    }
}


void placeTower(int x, int y, int &money, int** gameMap, int towersPosition[6][2], bool towersActivate[6], int towerCost) {
    //Primero, debemos tener en cuenta que el usuario va a ingresar en los valores de x,y las filas y columnas empezando desde 1, pero los arreglos inician desde 0. Entonces haremos lo siguiente:
    int ind_fila = x - 1;    // Si ingresa fila = x = 5, el indice sera 4
    int ind_columna = y - 1; // Si ingresa columna = y =  10, el indice sera 9

    
    //Cuando el usuario haya ingresado la fila y columna donde va a colocar la torre, debemos validar que esa posicion este dentro del mapa
    if (ind_fila < 0 || ind_fila >= 20 || ind_columna < 0 || ind_columna >= 20) {
        cout << "La posicion que ingresaste esta fuera del mapa" << endl;
        return;
    }

    
    // En caso ingrese una posicion dentro del mapa, debemos verificar que esa posicion no sea el lugar I (2), el lugar B (3) y que no sea el lugar del camino (1)
     if (gameMap[ind_fila][ind_columna] == 2 || gameMap[ind_fila][ind_columna] == 3 || gameMap[ind_fila][ind_columna] == 1) {
        cout << "Error, no se puede colocar una torre en esa posicion" << endl;
        return;
    }

    
    // Ademas, debemos verificar que esa posicion no este ocupada por una torre (4)
    if (gameMap[ind_fila][ind_columna] == 4) {
        cout << "Ya existe una torre en esa posicion" << endl;
        return;
    }

    
    //Validaremos que la torre sea adyacente al camino, ya que las torres que coloquemos deben cumplir esa condicion
    bool adyacente = false;  //Si encontramos torre adyacente al camino, se cambia a true
    
    // Tramo 1: Tramo que baja por la columna 1 y pasa por las filas del 3 a 6 (indice columna = 0, indice filas: de 2 a 5)
    if (ind_columna == 0 && ind_fila >= 2 && ind_fila <= 5) adyacente = true;
    
    // Tramo 2: Tramo que esta debajo del camino en la fila 6 y va desde las columnas 2 al 11
    if (ind_fila == 5 && ind_columna >= 1 && ind_columna <= 10) adyacente = true;
    
    // Tramo 3: Tramo que baja por la columna 11 y pasa por las filas del 7 al 9
    if (ind_columna == 10 && ind_fila >= 6 && ind_fila <= 8) adyacente = true;
    
    // Tramo 4: Tramo que esta encima del camino en la fila 9 y va desde las columnas 2 al 10
    if (ind_fila == 8 && ind_columna >= 1 && ind_columna <= 9) adyacente = true;
    
    // Tramo 5: Tramo que baja por la columna 2 y pasa por las filas del 10 al 16
    if (ind_columna == 1 && ind_fila >= 9 && ind_fila <= 15) adyacente = true;

    // Tramo 6: Tramo que esta debajo del camino en la fila 16 y va desde las columnas 3 al 17
    if (ind_fila == 15 && ind_columna >= 2 && ind_columna <= 16) adyacente = true;

    // Tramo 7: Tramo que baja por la columna 17 y pasa por las filas del 17 al 20
    if (ind_columna == 16 && ind_fila >= 16 && ind_fila <= 19) adyacente = true;
    
    if (!adyacente) {
        cout << "La torre debe estar adyacente al camino"<< endl;
        return;
    }

    
    // Cuando ya validamos que la torre que colocaremos es adyacente al camino, entonces la colocaremos y gastaremos dinero en ello.
    if (money < towerCost) {    //Primero validamos si hay dinero
        cout << "No hay dinero suficiente para colocar una torre" << endl;
        return;
    }
    
    // Si tenemos dinero suficiente, entonces colocaremos la torre
    money -= towerCost;
    gameMap[ind_fila][ind_columna] = 4;     //(4 significa que estamos colocando una torre)
    //Como ya colocamos la torre, finalmente vamos a guardar la posicion de esta nueva torre
    for (int i = 0; i<6; i++) {
    if (towersPosition[i][0] == -1) {  //Si es verdadero, este espacio nunca fue usado
        towersPosition[i][0] = ind_fila;
        towersPosition[i][1] = ind_columna;
        towersActivate[i] = true;
        break;
        }
    }
    
    //Por ultimo, imprimimos que la torre fue colocada y el dinero actualizado
    cout << "Torre colocada"<< endl;
    cout << "Dinero: "<< money << endl;
}


void spawnEnemies(int enemiesPosition[6][2], bool enemiesActivate[6]) {
    srand(time(nullptr));

    //Creamos un arreglo local con las posiciones iniciales de todos los enemigos considerando el numero maximo
    int start_position[6][2]={{0, 1}, {0, 2}, {1, 2},
    {2, 2}, {3, 2}, {3, 3}
    };
    //Generamos un numero aleatorio de enemigos entre 3 y 6
    int n=(rand()%4)+3;

    for (int k=0; k<n; k++) {
        //Asignamos las coordenadas x e y usando los valores del arreglo creado anteriormente
        enemiesPosition[k][0] = start_position[k][0];
        enemiesPosition[k][1] = start_position[k][1];

        //Actualizamos el estado del enemigo para ejecutar las funciones drawMap y attackEnemies
        enemiesActivate[k]=true;
    }
}

void moveEnemies() {}
void attackEnemies(int** gameMap, int &money, int enemiesPosition[6][2], bool enemiesActivate[6], int towersPosition[6][2], bool towersActivate[6]) {
    // Vamos a crear un arreglo que guardara todo el camino en orden para luego usarlo cuando queramos detectar a un enemigo cerca de la base, pongo 105 para
    //tener suficiente espacio en el arreglo
    int camino_enemigo[105][2];
    int paso = 0;      //Este contador nos sirve para recorrer las posiciones dentro del arreglo

    //Posiciones iniciales
    camino_enemigo[paso][0] = 1;
    camino_enemigo[paso][1] = 0;
    paso++;

    // Segundo tramo
    for (int i = 1; i <= 3; i++) {
        camino_enemigo[paso][0] = i;
        camino_enemigo[paso][1] = 1;
        paso++;
    }

    // Tercer tramo
    for (int j = 1; j <= 11; j++) {
        camino_enemigo[paso][0] = 4;
        camino_enemigo[paso][1] = j;
        paso++;
    }

    // Cuarto tramo
    for (int i = 5; i <= 8; i++) {
        camino_enemigo[paso][0] = i;
        camino_enemigo[paso][1] = 11;
        paso++;
    }

    // Quinto tramo
    for (int j = 11; j >= 2; j--) {
        camino_enemigo[paso][0] = 9;
        camino_enemigo[paso][1] = j;
        paso++;
    }

    // Sexto tramo
    for (int i = 10; i <= 13; i++) {
        camino_enemigo[paso][0] = i;
        camino_enemigo[paso][1] = 2;
        paso++;
    }

    // Septimo tramo
    for (int j = 2; j <= 17; j++) {
        camino_enemigo[paso][0] = 14;
        camino_enemigo[paso][1] = j;
        paso++;
    }

    // Octavo tramo
    for (int i = 15; i <= 19; i++) {
        camino_enemigo[paso][0] = i;
        camino_enemigo[paso][1] = 17;
        paso++;
    }

    // Posiciones antes de la base
    camino_enemigo[paso][0] = 19;
    camino_enemigo[paso][1] = 18;
    paso++;

    camino_enemigo[paso][0] = 19;
    camino_enemigo[paso][1] = 19;
    paso++;

    // Guardamos el tamano total que tiene camino
    int camino_enemigo_Length = paso;


    //Ahora defininos el rango de ataque que tiene cada torre
    int rango_ataque[12][2] = {{ 0,-2},{ 0, 2},{-2, 0},{ 2, 0},{-1,-2},{ 1,-2},{-1, 2},{ 1, 2},{-2,-1},{ 2,-1},{-2, 1},{ 2, 1}};


    //Ahora revisamos cada torre
    for (int torre = 0; torre < 6; torre++) {

        // Si la torre ya disparo, lo vamos a ignorar
        if (towersActivate[torre] == false) {
            continue;
        }

        //Si la torre no existe, lo vamos a ignorar tambien
        if (towersPosition[torre][0] == -1) {
            continue;
        }

        

        // Aqui obtenemos la posicion de la torre
        int fila_torre = towersPosition[torre][0];
        int columna_torre = towersPosition[torre][1];

        // Estas variables nos seviran para guardar el enemigo mas cercano y asi poder eliminarlo
        int enemigo_cercano = -1;
        int paso_cercano = -1;


        //Ahora, vamos a revisar todos los enemigos
        for (int enemigo = 0; enemigo<6; enemigo++) {
            // Si el enemigo no existe lo vamos a ignorar
            if (enemiesActivate[enemigo] == false) {
                continue;
            }

            // Si el enemigo existe, entonces obtenemos la posicion del enemigo
            int fila_enemigo = enemiesPosition[enemigo][0];
            int columna_enemigo = enemiesPosition[enemigo][1];


            //Ahora revismaos las posiciones del rango para encontrar al enemigo mas cercano
            for (int r = 0; r<12; r++) {
                int fila_rango = fila_torre + rango_ataque[r][0];
                int columna_rango = columna_torre + rango_ataque[r][1];

                // Tenemos que validar que el enemigo este dentro del rango de ataque
                if (fila_rango == fila_enemigo && columna_rango == columna_enemigo) {
                    
                    // Buscamos en que paso del camino esta este enemigo mas cercano que hemos encontrado
                    for (int paso_en_busqueda = 0; paso_en_busqueda < camino_enemigo_Length; paso_en_busqueda++) {
                        
                        if (camino_enemigo[paso_en_busqueda][0] == fila_enemigo && camino_enemigo[paso_en_busqueda][1] == columna_enemigo) {
                            // Verificamos que es el enemigo mas cercano de todos los que hemos encontrado hasta ahora?
                            if (paso_en_busqueda > paso_cercano) {
                                paso_cercano = paso_en_busqueda;
                                enemigo_cercano = enemigo;
                            }
                            break;
                        }
                    }
                    
                    break;
                    
                }
            }
        }

        
        //Por ultimo, cuando encontremos al enemigo mas cercano, lo tenemos que eliminar 
        if (enemigo_cercano != -1) {
            // Guardamos la posicion del enemigo que vamos a eliminar
            int fila_enemigo_cercano    = enemiesPosition[enemigo_cercano][0];
            int columna_enemigo_cercano = enemiesPosition[enemigo_cercano][1];

            // Borramos al enemigo de nuestro mapa
            gameMap[fila_enemigo_cercano][columna_enemigo_cercano] = 1;

            // Luego tenemos que poner al enemigo como muerto
            enemiesActivate[enemigo_cercano] = false;

            // Como se elimino al enemigo, le damos dinero al jugador
            money += 50;

            // Desactivamos la torre permanentemente
            towersActivate[torre] = false;

            
    
        }

        
    }
} 
void verifyResult() {}
void gameStatus() {}

void deleteMap(int**& gameMap, const int& length_side) {
    for (int i = 0; i < length_side; i++) {
        delete[] gameMap[i];
    }

    delete[] gameMap;
    gameMap = nullptr;
}
