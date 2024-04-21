//==============================================================================
// figures-input.c - функция содания ввода всех альтернативных фигур.
// Реализована как централизованная. Единственная, требующая модификации
// при вводе данных. Но можно тоже сделать эволюционно расширяемой.
//==============================================================================

#include <stdio.h>
#include "figure.h"
#include "figure-rectangle.h"
#include "figure-triangle.h"
#include "figure-circle.h"

void FigureIn<Figure *f>(FILE* file);

//------------------------------------------------------------------------------
// Ввод параметров одноф из фигур из файла
Figure* FigureCreateAndIn(FILE* ifst) {
  Figure *sp;
  int k;
  fscanf(ifst, "%d", &(k));
  switch(k) {
  case 1:
    // Создание и инициализация прямоугольника
    sp = create_spec<Figure<rect> >();
    break;
  case 2:
    // Создание и инициализация треугольника
    sp = create_spec<Figure<trian> >();
    break;
  case 3:
    // Создание и инициализация круга
    sp = create_spec<Figure<circ> >();
    break;
  default:
    return 0;
  }
  FigureIn<sp>(ifst);
  return sp;
}
