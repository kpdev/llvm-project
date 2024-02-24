//==============================================================================
// figure-out.c - содержит процедуру вывода параметров
// для произвольной геометрической фигуры
//==============================================================================

#include <stdio.h>
#include "figure.h"

//------------------------------------------------------------------------------
// Сигнатуры требуемых функций можно тоже подключить через
// заголовочный файл. Но, для простоты, можно и так описать.
void RectangleOut(Rectangle *r, FILE* ofst);
void TriangleOut(Triangle *t, FILE *ofst);
void ColorOut(Figure *f, FILE *ofst);

//------------------------------------------------------------------------------
// Вывод параметров текущей фигуры в поток
void FigureOut(Figure *f, FILE* ofst)
{
  switch(f->k) {
    case RECTANGLE:
      RectangleOut(&(f->r), ofst);
      ColorOut(f, ofst);
      break;
    case TRIANGLE:
      TriangleOut(&(f->t), ofst);
      ColorOut(f, ofst);
      break;
    default:
      fprintf(ofst, "Incorrect figure!\n");
    }
}
