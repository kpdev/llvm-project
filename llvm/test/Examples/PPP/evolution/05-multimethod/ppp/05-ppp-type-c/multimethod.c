//==============================================================================
// multimethod.c - содержит функции, опрделяющие реализацию мультиметода
// для чистого процедурного подхода с использованием для фигуры объединения
//==============================================================================

#include <stdio.h>
#include "figure-rectangle.h"
#include "figure-triangle.h"

//------------------------------------------------------------------------------
// Обобщающая функция, задающая абстрактный мультиметод
void Multimethod<Figure* f1, Figure* f2>(FILE* ofst) {}// = 0;

//------------------------------------------------------------------------------
// Обработчик специализации для двух прямоугольников
void Multimethod<Figure<Rectangle>* r1, Figure<Rectangle>* r2>(FILE* ofst) {
  fprintf(ofst, "Rectangle - Rectangle Combination\n");
}

//------------------------------------------------------------------------------
// Обработчик специализации для прямоугольника и треугольника
void Multimethod<Figure<Rectangle>* r1, Figure<Triangle>* t2>(FILE* ofst) {
  fprintf(ofst, "Rectangle - Triangle Combination\n");
}

//------------------------------------------------------------------------------
// Обработчик специализации для треугольника и прямоугольника
void Multimethod<Figure<Triangle>* t1, Figure<Rectangle>* r2>(FILE* ofst) {
  fprintf(ofst, "Triangle - Rectangle Combination\n");
}

//------------------------------------------------------------------------------
// Обработчик специализации для двух треугольников
void Multimethod<Figure<Triangle>* t1, Figure<Triangle>* t2>(FILE* ofst) {
  fprintf(ofst, "Triangle - Triangle Combination\n");
}

