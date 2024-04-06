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
void Multimethod<Figure<rect>* r1, Figure<circ>* c2>(FILE* ofst) {
  fprintf(ofst, "Rectangle - Circle Combination\n");
}

//------------------------------------------------------------------------------
// Обработчик специализации для треугольника и круга
void Multimethod<Figure<trian>* r1, Figure<circ>* c2>(FILE* ofst) {
  fprintf(ofst, "Triangle - Circle Combination\n");
}

//------------------------------------------------------------------------------
// Обработчик специализации для круга и прямоугольника
void Multimethod<Figure<circ>* c1, Figure<rect>* r2>(FILE* ofst) {
  fprintf(ofst, "Circle - Rectangle Combination\n");
}

//------------------------------------------------------------------------------
// Обработчик специализации для круга и треугольника
void Multimethod<Figure<circ>* c1, Figure<trian>* t2>(FILE* ofst) {
  fprintf(ofst, "Circle - Triangle Combination\n");
}

//------------------------------------------------------------------------------
// Обработчик специализации для двух кругов
void Multimethod<Figure<circ>* c1, Figure<circ>* c2>(FILE* ofst) {
  fprintf(ofst, "Circle - Circle Combination\n");
}

