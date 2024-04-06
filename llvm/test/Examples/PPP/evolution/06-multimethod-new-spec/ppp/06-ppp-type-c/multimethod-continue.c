// multimethod-continue.c - содержит функции, опрeделяющие реализацию
// мультиметода для добавленного круга
//==============================================================================

#include <stdio.h>
#include "figure.h"

//------------------------------------------------------------------------------
// Обобщающая функция, задающая абстрактный мультиметод
void Multimethod<Figure* f1, Figure* f2>(FILE* ofst) = 0;

//------------------------------------------------------------------------------
// Обработчик специализации для прямоугольника и круга
void Multimethod<Figure<Rectangle>* r1, Figure<Circle>* c2>(FILE* ofst) {
  fprintf(ofst, "Rectangle - Circle Combination\n");
}

//------------------------------------------------------------------------------
// Обработчик специализации для треугольника и круга
void Multimethod<Figure<Triangle>* r1, Figure<Circle>* c2>(FILE* ofst) {
  fprintf(ofst, "Triangle - Circle Combination\n");
}

//------------------------------------------------------------------------------
// Обработчик специализации для круга и прямоугольника
void Multimethod<Figure<Circle>* c1, Figure<Rectangle>* r2>(FILE* ofst) {
  fprintf(ofst, "Circle - Rectangle Combination\n");
}

//------------------------------------------------------------------------------
// Обработчик специализации для круга и треугольника
void Multimethod<Figure<Circle>* c1, Figure<Triangle>* t2>(FILE* ofst) {
  fprintf(ofst, "Circle - Triangle Combination\n");
}

//------------------------------------------------------------------------------
// Обработчик специализации для двух кругов
void Multimethod<Figure<Circle>* c1, Figure<Circle>* c2>(FILE* ofst) {
  fprintf(ofst, "Circle - Circle Combination\n");
}

