//==============================================================================
// shape-in.c - содержит процедуру ввода параметров
// и создания произвольной фигуры
//==============================================================================

#include <stdio.h>
#include <stdlib.h>
#include "shape.h"

//------------------------------------------------------------------------------
// Сигнатуры требуемых функций можно тоже подключить через
// заголовочный файл. Но, для простоты, можно и так описать.
void InRectangle(rectangle *r, FILE* ifst);
void InTriangle(triangle *t, FILE* ifst);

//------------------------------------------------------------------------------
// Ввод параметров обобщенной фигуры из файла
shape* InShape(FILE* ifst)
{
  shape *sp;
  int k;
  fscanf(ifst, "%d", &(k));
  switch(k) {
  case 1:
    sp = malloc(sizeof(shape));
    sp->k = RECTANGLE;
    InRectangle(&(sp->r), ifst);
    return sp;
  case 2:
    sp = malloc(sizeof(shape));
    sp->k = TRIANGLE;
    InTriangle(&(sp->t), ifst);
    return sp;
  default:
    return 0;
  }
}
