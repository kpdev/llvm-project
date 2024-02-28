//==============================================================================
// container-rectangles-out.c - содержит функцию вывода только прямоугольников,
// находящихся в контейнере, используя обобщенную функцию, проверки
// на прямоугольник
//==============================================================================

#include <stdio.h>
#include "container.h"
#include "is-figure-rectangle.h"

//------------------------------------------------------------------------------
// Вывод прямоугольников из контейнера в указанный поток
void ContainerRectangleOnlyOut(Container *c, FILE* ofst) {
  int rectCount = 0;
  for(int i = 0; i < c->len; i++) {
    if(isFigureRectangle<c->cont[i]>()) {
      FigureOut<c->cont[i]>(ofst);
      ++rectCount;
    }
  }
  fprintf(ofst, "Container contains %d rectangles.\n", rectCount);
}
