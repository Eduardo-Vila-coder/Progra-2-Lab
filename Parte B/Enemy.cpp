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
Enemy Enemy::operator-(int puntos) const {
  Enemy enemigo_resultado = *this;

  if (puntos >= enemigo_resultado.salud){  // Si el daño es mayor o igual a la salud que tiene el enemigo, la salud quedaria en cero
    enemigo_resultado.salud = 0;
    enemigo_resultado.activo = false;
  } else {
    enemigo_resultado.salud = enemigo_resultado.salud - puntos;
  }

  return enemigo_resultado;

}

// Esta funcion recibe el danio de la torre y usa la sobrecarga del operador -
void Enemy::enemigo_en_ataque(int danio_torre) {
  *this = *this - danio_torre;
}
