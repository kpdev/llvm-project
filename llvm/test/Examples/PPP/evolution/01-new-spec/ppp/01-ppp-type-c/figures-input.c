//==============================================================================
// figures-input.c - функция содания ввода всех альтернативных фигур.
// Реализована как централизованная. Единственная, требующая модификации
// при вводе данных. Но можно тоже сделать эволюционно расширяемой.
//==============================================================================

#include <stdio.h>
#include "figure.h"
#include "rectangle.h"
#include "triangle.h"
#include "circle.h"

//------------------------------------------------------------------------------
// Ввод параметров одноф из фигур из файла
Figure* FigureCreateAndIn(FILE* ifst) {
  Figure *sp;
  int k;
  fscanf(ifst, "%d", &(k));
  switch(k) {
  case 1:
    // Создание и инициализация прямоугольника
    sp = create_spec(Figure<Rectangle>);
    break;
  case 2:
    // Создание и инициализация треугольника
    sp = create_spec(Figure<Triangle>);
    break;
  case 2:
    // Создание и инициализация круга
    sp = create_spec(Figure<Circle>);
    break;
  default:
    return 0;
  }
  FigureIn<sp>(ifst);
}
