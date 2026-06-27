#ifndef PARTE_B_CAMERA_H
#define PARTE_B_CAMERA_H

// Estaria bien incluir estos archivos sin relacionarlos?
#include <vector>
#include "Tower.h"
#include "Enemy.h"
using namespace std;

class Camera {
private:
    int x,y;
    int ancho, alto;
    int limiteAncho;
    int limiteAlto;

public:
    Camera(int ancho_Visor, int alto_Visor, int ancho_Map, int alto_Map);
    ~Camera();

    void mover(int movX, int movY);
    int obtenX() const;
    int obtenY() const;
    int obtenAncho() const;
    int obtenAlto() const;

    void drawWindow(int** mapa, vector<Tower*>& torres, vector<Enemy*> enemigos) const;

    void operator()(int nuevoX, int nuevoY);
};

#endif //PARTE_B_CAMERA_H
