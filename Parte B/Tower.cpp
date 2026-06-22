#include "Tower.h"

Tower::Tower() {
    this->damage=1;
    this->shots=1;
    this->towerActivate=true;
}

Tower::Tower(int row, int col, int damage, int shots) {
    this->damage=damage;
    this->row=row;
    this->col=col;
    this->shots=shots;
    this->towerActivate = true;
}

Tower::~Tower() {

};

//getters and setters
int Tower::getRow() {
    return this->row;
};
int Tower::getCol() {
    return this->col;
};
int Tower::getDamage() {
    return this->damage;
};
bool Tower::getTowersActivate() {
    return this->towerActivate;
};
int Tower::getShots() {
    return this->shots;
};
void Tower::setTowersActivate(bool towersActivate) {
    this->towerActivate=towersActivate;
};
void Tower::setShots(int shots) {
    this->shots=shots;
};
void Tower::setRow(int row) {
    this->row=row;
};
void Tower::setCol(int col) {
    this->col=col;
};
void Tower::setDamage(int damage) {
    this->damage=damage;
};

//funciones:
//#1 restar la cantidad de disparos y desactivar la torre cuando ya no tenga disparos disponibles
void Tower:: newShots() {
   if (shots>0)
       *this - 1;
   if (shots==0)
       towerActivate=false;
};

//usamos una sobrecarga del operador -
void Tower :: operator-(int disp) {
    shots -= disp;
};

int Tower::getFilaRango(int posicion) {
    return attackRange[posicion][0];
}

int Tower::getColumnaRango(int posicion) {
    return attackRange[posicion][1];
}
