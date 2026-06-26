#include "Camera.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

Camera::Camera(int ancho_Visor, int alto_Visor, int anchoMap, int altoMap) {
    ancho = ancho_Visor;
    alto = alto_Visor;
    limiteAncho = anchoMap;
    limiteAlto = altoMap;
    x = 0;
    y = 0;
}

Camera::~Camera() {
}

void Camera::fijarPosicion(int nuevoX, int nuevoY) {
    x = nuevoX;
    y = nuevoY;

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > limiteAncho - ancho) x = limiteAncho - ancho;
    if (y > limiteAlto - alto) y = limiteAlto - alto;
}

void Camera::mover(int movX, int movY) {
    fijarPosicion(x + movX, y + movY);
}

int Camera::obtenX() const { return x; }
int Camera::obtenY() const { return y; }
int Camera::obtenAncho() const { return ancho; }
int Camera::obtenAlto() const { return alto; }

void Camera::drawWindow(int** mapa, vector<Tower*>& torres, vector<Enemy*> enemigos) const {
    if (mapa == nullptr) return;

    cout << setw(6) << " ";
    for (int j = x; j < x + ancho; j++) {
        cout << setw(4) << j + 1;
    }
    cout << "\n\n";

    for (int i = y; i < y + alto; i++) {
        cout << setw(4) << i + 1 << "  ";

        for (int j = x; j < x + ancho; j++) {
            bool dibujado = false;

            for (int k = 0; k < 6; k++) {
                if (i == torres.at(k)->getRow() && j == torres.at(k)->getCol() && torres.at(k)->getTowersActivate()) {
                    dibujado = true;
                    cout << setw(4) << ("T" + to_string(k + 1));
                    break;
                }
                else if (i == enemigos.at(k)->getFila() && j == enemigos.at(k)->getColumna() && enemigos.at(k)->getActivo()) {
                    dibujado = true;
                    cout << setw(4) << "E";
                    break;
                }
            }

            if (!dibujado && mapa[i][j] == 2) {
                cout << setw(4) << "I";
                dibujado = true;
            }
            if (!dibujado && mapa[i][j] == 3) {
                cout << setw(4) << "B";
                dibujado = true;
            }
            if (!dibujado && mapa[i][j] == 1) {
                cout << setw(4) << "*";
            }
            if (!dibujado && mapa[i][j] == 0) {
                cout << setw(4) << ".";
            }
        }
        cout << endl;
    }
}

void Camera::operator()(int nuev_X, int nuev_Y) {
    fijarPosicion(nuev_X, nuev_Y);
}
