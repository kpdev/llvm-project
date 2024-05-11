#ifndef __figure_container__
#define __figure_container__

//==============================================================================
// figure-container.h - содержит тип данных, представляющий простейший контейнер
//==============================================================================

#include <stdlib.h>
#include "figure.h"

enum {figure_max_len = 100}; // максимальная длина

//------------------------------------------------------------------------------
// Простейший контейнер на основе одномерного массива
typedef struct FigureContainer {
  int len; // текущая длина
  struct Figure *cont[figure_max_len];
} FigureContainer;

//------------------------------------------------------------------------------
// Инициализация контейнера
void FigureContainerInit(FigureContainer *c);
// Очистка контейнера от элементов (освобождение памяти)
void FigureContainerClear(FigureContainer *c);
// Добавление в контейнер указанной фигуры
void FigureContainerAppend(FigureContainer* c, Figure * figure);
// Вывод содержимого контейнера в указанный поток
void FigureContainerOut(FigureContainer *c, FILE* ofst);

#endif // __figure_container__