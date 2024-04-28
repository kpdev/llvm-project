//==============================================================================
// figure-container.c - содержит обработки контейнера
//==============================================================================

#include <stdlib.h>
#include "figure-container.h"

//------------------------------------------------------------------------------
// Инициализация контейнера
void FigureContainerInit(FigureContainer *c) {
  c->len = 0;
}

//------------------------------------------------------------------------------
// Очистка контейнера от элементов (освобождение памяти)
void FigureContainerClear(FigureContainer *c) {
  for(int i = 0; i < c->len; i++) {
    free(c->cont[i]);
  }
  FigureContainerInit(c);
}

//------------------------------------------------------------------------------
// Добавление в контейнер указанной фигуры
void FigureContainerAppend(FigureContainer* c, Figure * figure) {
  if(c->len < figure_max_len) {
    c->cont[c->len++] = figure;
  }
}

//------------------------------------------------------------------------------
// Вывод содержимого контейнера в указанный поток
void FigureContainerOut(FigureContainer *c, FILE* ofst) {
  fprintf(ofst, "Container contains %d elements.\n", c->len);
  for(int i = 0; i < c->len; i++) {
    fprintf(ofst, "%d: " , i);
    FigureOut<c->cont[i]>(ofst);
  }
}
