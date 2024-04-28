//==============================================================================
// triangle-inout.c - содержит обработчики ввода-вывода
// параметров обобщенного треугольника
//==============================================================================

#include <stdio.h>
#include "triangle.h"

//------------------------------------------------------------------------------
// Прототипы основ специализаций
void SimpleTriangleIn(SimpleTriangle *t, FILE* ifst);
void SimpleTriangleOut(SimpleTriangle *t, FILE* ofst);
void CoordTriangleIn(CoordTriangle *t, FILE* ifst);
void CoordTriangleOut(CoordTriangle *t, FILE* ofst);

//------------------------------------------------------------------------------
// Обобщенная функция, ввода треугольников
void TriangleIn<Triangle *t>(FILE* ifst) = 0;
// Обобщенная функция, вывода треугольников
void TriangleOut<Triangle *t>(FILE* ofst) = 0;

//------------------------------------------------------------------------------
// Обработчик специализации, осуществляющий ввод простых треугольников
void TriangleIn<Triangle<SimpleTriangle> *t>(FILE* ifst) {
  SimpleTriangleIn(&(t->@), ifst);
}

//------------------------------------------------------------------------------
// Обработчик специализации, осуществляющий вывод простых треугольников
void TriangleOut<Triangle<SimpleTriangle> *t>(FILE* ofst) {
  SimpleTriangleOut(&(t->@), ofst);
}

//------------------------------------------------------------------------------
// Обработчик специализации, осуществляющий ввод треугольников,
// задаваемых координатами
void TriangleIn<Triangle<CoordTriangle> *t>(FILE* ifst) {
  CoordTriangleIn(&(t->@), ifst);
}

//------------------------------------------------------------------------------
// Обработчик специализации, осуществляющий вывод треугольников,
// задаваемых координатами
void TriangleOut<Triangle<CoordTriangle> *t>(FILE* ofst) {
  CoordTriangleOut(&(t->@), ofst);
}
