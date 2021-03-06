/*
trabl:
действия в конце карты
задний фон сделать
+подпудрить код
+перс рисуеться в середине клетки когда надо рисоваться в ее начале но важно ли?
+перс стоит на 1 координату по x и по y меньше чем должен
+сращено с функцией рендеринга карты
 */

#ifndef MAP_H_
#define MAP_H_

#include <SDL/SDL.h>

///Сама карта, в последствии будет заменена на файл с таким же содержимым
static const char* mmap[] ={
  "6 14",
  "11111111111111",
  "11111111111111",
  "11111111111111",
  "11111111111111",
  "11111111111111",
  "10000000000001",
  "10000000000001",
  "10000001000001",
  "10000011100001",
  "11111111111111",
  "11111111111111",
  "11111111111111",
  "11111111111111",
  "11111111111111",
  "11111111111111",
  "11111111111111",
  "11111111111111",
  "11111111111111"
};
/**
@class map
Класс реализующий отрисовку и загрузку карты, и ее элементов
 */
class map
{
public:
  /**
     Коструктор по умолчанию
     @param screen - область для рисования карты
  */
  map(SDL_Surface* screen);
  ///Загрузка текстур карты
  void loadmap();
  void RenderingMap(int rsh,int rsw, int reh,int rew,int posx,int posy);
  bool endmap(int mx, int my);
  /**
     Перерисовка карты с заданным смещением и координатами
     @param mx - кооридната x на карте
     @param my - координата y на карте
     @param posx - смещение x на карте
     @param posy - смещение y на карте
  */
  void onmove(int mx,int my, int posx, int posy);
  ///@name Области для рамещения текстур карты
  ///@{
  SDL_Surface* map1, *bgmap, *gscreen;
  ///@}
  ///Размеры ячеек карты
  int gridx,gridy;

  
  ///Не нужно
  int mapx ,mapy;
  ///Не нужно
  int CountLeftMove, CountRightMove;
  ///@name Сколько показывать ячеек
  ///@{
  int ShowW,ShowH;
  ///@}
  ///@name Размеры карты в ячейках
  ///@{
  int MapH,MapW;
  ///@}
  ///@name Размеры ячеек карты
  ///@{
  int greedx,greedy;
  ///@}
};

#endif /* MAP_H_ */
