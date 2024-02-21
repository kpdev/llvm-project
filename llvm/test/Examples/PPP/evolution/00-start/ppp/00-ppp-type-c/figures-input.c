//==============================================================================
// figures-input.c - функция содания ввода всех альтернативных фигур.
// Реализована как централизованная. Единственная, требующая модификации
// при вводе данных. Но можно тоже сделать эволюционно расширяемой.
//==============================================================================

#include <stdio.h>
#include "figure.h"
#include "figure-rectangle.h"
#include "figure-triangle.h"

void FigureIn<struct Figure *f>(FILE* file);

//------------------------------------------------------------------------------
// Ввод параметров одноф из фигур из файла
struct Figure* FigureCreateAndIn(FILE* ifst) {
  struct Figure *sp;
  int k;
  fscanf(ifst, "%d", &(k));
  switch(k) {
  case 1:
    // sp = malloc(sizeof(Figure<Rectangle>));
    // Далее нужно сформировать признак. Наверное спец. функция...
    sp = create_spec<struct Figure<struct Rectangle> >(); // Создание и инициализация
    break;
  case 2:
    // sp = malloc(sizeof(Figure<Triangle>));
    // Далее нужно сформировать признак. Наверное спец. функция...
    sp = create_spec<struct Figure<struct Triangle> >(); // Создание и инициализация
    break;
  default:
    return 0;
  }
  FigureIn<sp>(ifst);
  return sp;
}
