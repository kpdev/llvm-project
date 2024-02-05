//==============================================================================
// shape-in.c - содержит процедуру ввода параметров
// и создания произвольной фигуры
//==============================================================================

#include <stdio.h>
#include "shape.h"

void InShape<struct shape *sh>(FILE* file) {};//= 0;
void OutShape<struct shape *sh>(FILE* file) {};//= 0;

//------------------------------------------------------------------------------
// Ввод параметров обобщенной фигуры из файла
shape* CreateAndInShape(FILE* ifst)
{
  shape *sp;
  struct shape<struct rectangle> sr;
  struct shape<struct triangle> st;
  int k;
  fscanf(ifst, "%d", &(k));
  switch(k) {
  case 1:
    sp = malloc(sizeof(struct shape<struct rectangle>));
    memcpy(sp, &sr, sizeof(struct shape<struct rectangle>));
    break;
  case 2:
    sp = malloc(sizeof(struct shape<struct triangle>));
    memcpy(sp, &st, sizeof(struct shape<struct triangle>));
    break;
  default:
    return 0;
  }
  InShape<sp>(ifst);
  return sp;
}
