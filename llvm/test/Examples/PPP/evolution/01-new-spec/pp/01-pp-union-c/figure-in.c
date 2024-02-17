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
void InRectangle(Rectangle *r, FILE* ifst);
void InTriangle(Triangle *t, FILE* ifst);
void InCircle(Circle *c, FILE* ifst);

//------------------------------------------------------------------------------
// Ввод параметров обобщенной фигуры из файла
Figure* InFigure(FILE* ifst)
{
  Figure *pf;
  int k;
  fscanf(ifst, "%d", &(k));
  switch(k) {
  case 1:
    pf = malloc(sizeof(Figure));
    pf->k = RECTANGLE;
    InRectangle(&(pf->r), ifst);
    return pf;
  case 2:
    pf = malloc(sizeof(Figure));
    pf->k = TRIANGLE;
    InTriangle(&(pf->t), ifst);
    return pf;
  case 3:
    pf = malloc(sizeof(Figure));
    pf->k = CIRCLE;
    InCircle(&(pf->c), ifst);
    return pf;
  default:
    return 0;
  }
}
