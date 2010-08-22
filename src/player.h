/*
баг столкновения
 */

///Константа направления движения
enum mpointer { MV_UP, MV_DOWN, MV_LEFT, MV_RIGHT };

#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdio.h>
#include <SDL/SDL.h>
#include "map.h"

/**
@class player
Класс игрока реализующий основные его параметры
 */
class player
{
 public:
  ///Конструткор по умолчанию
  ///@param coordmapx - Координата игрока на карте по x
  ///@param coorgmapy - Координата игрока на карте по y
  ///@param screen - Область отрисовки
  player(int coordmapx, int coordmapy, SDL_Surface* screen);
  ///Проверка столкновения игрока с картой
  ///@param mpointer - направление движения игрока
  bool CheckCollision(mpointer direction, int posx, int posy);
  ///Метод перемещения игрока
  ///@param direction - Направление движения
  ///@param speed - Скорость движения в пикселях
  void moveplayer(mpointer direction, int speed);
  ///Интерфейс класса карты
  map *mymap;
  ///@name Координаты на карте
  ///@{
  int mapx, mapy;
  ///@}
  ///@name Смещение относительно координат
  ///@{
  int posx, posy;
  ///@}
};

#endif /* PLAYER_H_ */
