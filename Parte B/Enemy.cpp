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

// Devuelve la salud actual del enemigo
int Enemy::getSalud() const {
  return salud;
}

// Devuelve el estado actual del enemigo
bool Enemy::getActivo() const {
  return activo;
}

// Devuelve la fila actual del enemigo
int Enemy::getFila() const {
  return fila;
}

// Devuelve la columna actual del enemigo
int Enemy::getColumna() const {
  return columna;
}

// Cambia la salud del enemigo
void Enemy::setSalud(int salud){
  this->salud = salud;
}

// Cambia el estado del enemigo
void Enemy::setActivo(bool activo){
  this->activo = activo;
}

// Cambia la posicion del enemigo
void Enemy::setPosicionEnemy(int fila, int columna) {
  this->fila = fila;
  this->columna = columna;
}

// En esta parte, esta la sobrecarga del operador, que permite restar puntos de salud a un enemigo usando el operador -
void Enemy::operator-=(int puntos) {
  if (puntos >= salud) {
    salud = 0;
    activo = false;
  } else {
    salud = salud - puntos;
  }

}

// Esta funcion recibe el danio de la torre y usa la sobrecarga del operador -
void Enemy::enemigo_en_ataque(int danio_torre) {
  *this -= danio_torre;
}
