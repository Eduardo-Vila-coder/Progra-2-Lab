//
// Created by HP on 6/5/2026.
//

#include "Enemy.h"

Enemy::Enemy(){
  salud = 1;
  activo = true;
  fila = 0;
  columna = 0;
}

Enemy::Enemy(int salud, int fila, int columna){
  this->salud = salud;
  this->activo = true;
  this->fila = fila;
  this->columna = columna;
}
int Enemy::getSalud() const {
  return salud;
}

bool Enemy::getActivo() const {
  return activo;
}

int Enemy::getFila() const {
  return fila;
}

int Enemy::getColumna() const {
  return columna;
}

void Enemy::setSalud(int salud){
  this->salud = salud;
}

void Enemy::setActivo(bool activo){
  this->activo = activo;
}

void Enemy::setPosicionEnemy(int fila, int columna) {
  this->fila = fila;
  this->columna = columna;
}

bool Enemy::operator==(const Enemy& otroEnemigo) const {
  if (this->fila == otroEnemigo.fila && this->columna == otroEnemigo.columna) {
    return true;
  }
  return false;
}
