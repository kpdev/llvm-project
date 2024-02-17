//==============================================================================
// figure-in.c - содержит процедуру ввода параметров
// и создания произвольной фигуры
//==============================================================================

#include <stdio.h>
#include <stdlib.h>
#include "figure.h"

//------------------------------------------------------------------------------
// Сигнатуры требуемых функций можно тоже подключить через
// заголовочный файл. Но, для простоты, можно и так описать.
void RectangleIn(Rectangle *r, FILE* ifst);
void TriangleIn(Triangle *t, FILE* ifst);

//------------------------------------------------------------------------------
// Ввод параметров обобщенной фигуры из файла
Figure* FigureIn(FILE* ifst)
{
  Figure *pf;
  int k;
  fscanf(ifst, "%d", &(k));
  switch(k) {
  case 1:
    pf = malloc(sizeof(Figure));
    pf->k = RECTANGLE;
    RectangleIn(&(pf->r), ifst);
    return pf;
  case 2:
    pf = malloc(sizeof(Figure));
    pf->k = TRIANGLE;
    TriangleIn(&(pf->t), ifst);
    return pf;
  default:
    return 0;
  }
}
