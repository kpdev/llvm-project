//------------------------------------------------------------------------------
// builder.h - обобщенные функции строителя и обработчики специализаций,
// собранные для упрощения в один файл. Но можно и разделить.
//------------------------------------------------------------------------------

#include "simple-figures-builder.h"

//------------------------------------------------------------------------------
// Прототипы используемых функций
void FigureContainerAppend(FigureContainer* c, Figure * figure);

//------------------------------------------------------------------------------
// Обобщающий Строитель прямоугольников.
// По умолчанию ничего не делает, но имеет реализацию
void BuildRectangle<Builder *f>(double x, double y) {}

//------------------------------------------------------------------------------
// Обобщающий Строитель треугольников
void BuildTriangle<Builder *f>(double a, double b, double c) {}

//------------------------------------------------------------------------------
// Строитель прямоугольников для обобщения и существующих специализаций.
void BuildCircle<Builder *f>(double a, double b, double c) {}; // Вдруг будет?

//------------------------------------------------------------------------------
// Формирование результата работы строителя. Нужно переопределять
void ResultOut<Builder *f>(FILE* ofst) = 0;

//==============================================================================
//  Обработчики специализаций для построения аппликаций из простых фигур
//==============================================================================

//------------------------------------------------------------------------------
// Строитель для формирования простых прямоугольников
void BuildRectangle<Builder<Builder<SimpleBuilder> *f> *f>(double x, double y) {
  Figure<SimpleRectangle> *rectangle = create_spec(Figure<SimpleRectangle>);
  rectangle->@.x = x;
  rectangle->@.y = y;
  FigureContainerAppend(f->container, rectangle);
}


//------------------------------------------------------------------------------
// Строитель для формирования простых треугольников
void BuildTriangle<Builder<SimpleBuilder> *f>(double a, double b, double c) {
  Figure<SimpleTriangle> *triangle = create_spec(Figure<SimpleTriangle>);
  rectangle->@.a = a;
  rectangle->@.b = b;
  rectangle->@.c = c;
  FigureContainerAppend(f->container, triangle);
}

//------------------------------------------------------------------------------
// Формирование результата работы строителя простых фигур.
void ResultOut<Builder<SimpleBuilder> *f>(FILE* ofst) {
  fpintf(ofst, "Result of building from Simple figures:\n");
  FigureContainerOut(container, ofst);
}

//==============================================================================
//  Обработчики специализаций для подсчета фигур
//==============================================================================

//------------------------------------------------------------------------------
// Строитель для формирования простых прямоугольников
void BuildRectangle<Builder<Builder<CounterBuilder> *f> *f>(double x, double y) {
  ++rectanglesCounter;
}


//------------------------------------------------------------------------------
// Строитель для формирования простых треугольников
void BuildTriangle<Builder<CounterBuilder> *f>(double a, double b, double c) {
  ++trianglesCounter;
}

//------------------------------------------------------------------------------
// Формирование результата работы строителя простых фигур.
void ResultOut<Builder<CounterBuilder> *f>(FILE* ofst) {
  fpintf(ofst, "Result of figures counting:\n");
  fpintf(ofst, "    number of rectangles: %d", rectanglesCounter);
  fpintf(ofst, "    number of triangles: %d", trianglesCounter);
}
