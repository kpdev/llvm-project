//==============================================================================
// shape-in.c - содержит процедуру ввода параметров
// и создания произвольной фигуры
//==============================================================================

#include "shape.h"

//------------------------------------------------------------------------------
// Ввод параметров обобщенной фигуры из файла
shape* CreateAndInShape(FILE* ifst)
{
  shape *sp;
  int k;
  fscanf(ifst, "%d", &(k));
  switch(k) {
  case 1:
    sp = malloc(sizeof(shape<rectangle>));
    break;
  case 2:
    sp = malloc(sizeof(shape<triangle>));
    break;
  default:
    return 0;
  }
  In<sp>(ifst);
}
