//==============================================================================
// shape-in.cpp - содержит процедуру ввода параметров
// и создания произвольной фигуры
//==============================================================================

#include <fstream>
#include "shape.h"

//------------------------------------------------------------------------------

// Сигнатуры требуемых функций можно тоже подключить через
// заголовочный файл. Но, для простоты, можно и так описать.
void In(rectangle &r, std::ifstream &ist);
void In(triangle  &t, std::ifstream &ist);

//------------------------------------------------------------------------------
// Ввод параметров обобщенной фигуры из файла
shape* In(std::ifstream &ifst)
{
  shape *sp;
  int k;
  ifst >> k;
  switch(k) {
  case 1:
    sp = new shape;
    sp->k = shape::RECTANGLE;
    // sp->k = sp->RECTANGLE;
    In(sp->r, ifst);
    return sp;
  case 2:
    sp = new shape;
    sp->k = shape::TRIANGLE;
    // sp->k = sp->TRIANGLE;
    In(sp->t, ifst);
    return sp;
  default:
    return 0;
  }
}
