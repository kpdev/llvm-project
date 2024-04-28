//==============================================================================
// coord-rectangle-inout.c - содержит функции ввода-вывода параметров
// прямоугольника, задаваемого координатами
//==============================================================================

#include <stdio.h>
#include "coord-rectangle.h"

//------------------------------------------------------------------------------
// Ввод параметров прямоугольника из файла
void CoordRectangleIn(CoordRectangle *r, FILE* ifst) {
  fscanf(ifst, "%lf", &(r->top_left.x));
  fscanf(ifst, "%lf", &(r->top_left.y));
  fscanf(ifst, "%lf", &(r->down_right.x));
  fscanf(ifst, "%lf", &(r->down_right.y));
}

//------------------------------------------------------------------------------
// Вывод параметров прямоугольника в форматируемый поток
void CoordRectangleOut(CoordRectangle *r, FILE* ofst) {
  fprintf(ofst,
          "It is Coord Rectangle: top left = (%.3lf,%.3lf),"
          " down right = (%.3lf,%.3lf)\n",
          r->top_left.x, r->top_left.y, r->down_right.x, r->down_right.y);
}
