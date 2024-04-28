//==============================================================================
// rectangle-inout.c - содержит обработчики ввода-вывода
// параметров обобщенного прямоугольника
//==============================================================================

#include <stdio.h>
#include "rectangle.h"

//------------------------------------------------------------------------------
// Прототипы основ специализаций
void SimpleRectangleIn(SimpleRectangle *r, FILE* ifst);
void SimpleRectangleOut(SimpleRectangle *r, FILE* ofst);
void CoordRectangleIn(CoordRectangle *r, FILE* ifst);
void CoordRectangleOut(CoordRectangle *r, FILE* ofst);

//------------------------------------------------------------------------------
// Обобщенная функция ввода прямоугольников
void RectangleIn<Rectangle *r>(FILE* ifst) = 0;
// Обобщенная функция вывода прямоугольников
void RectangleOut<Rectangle *r>(FILE* ofst) = 0;

//------------------------------------------------------------------------------
// Обработчик специализации, осуществляющий ввод простых прямоугольников
void RectangleIn<Rectangle<SimpleRectangle> *r>(FILE* ifst) {
  SimpleRectangleIn(&(r->@), ifst);
}

//------------------------------------------------------------------------------
// Обработчик специализации, осуществляющий вывод простых прямоугольников
void RectangleOut<Rectangle<SimpleRectangle> *r>(FILE* ofst) {
  SimpleRectangleOut(&(r->@), ofst);
}

//------------------------------------------------------------------------------
// Обработчик специализации, осуществляющий ввод прямоугольников,
// задаваемых координатами
void RectangleIn<Rectangle<CoordRectangle> *r>(FILE* ifst) {
  CoordRectangleIn(&(r->@), ifst);
}

//------------------------------------------------------------------------------
// Обработчик специализации, осуществляющий вывод прямоугольников,
// задаваемых координатами
void RectangleOut<Rectangle<CoordRectangle> *r>(FILE* ofst) {
  CoordRectangleOut(&(r->@), ofst);
}
