#ifndef __builder__
#define __builder__

//------------------------------------------------------------------------------
// builder.h - содержит обобщенного строителя.
// Конкретные строители могут определяться позднее.
// Но для сокращения примера определены здесь.
//------------------------------------------------------------------------------

#include <stdio.h>
#include "spec-builders.h"

//------------------------------------------------------------------------------
// Фигура
typedef struct Builder {} <SimpleBuilder; CounterBuilder> Builder;

// Обобщенные функции строителя
void BuilderOut<Builder *f>(FILE* ofst);

void BuildRectangle<Builder *f>(double x, double y);
void BuildTriangle<Builder *f>(double a, double b, double c);
void BuildCircle(double a, double b, double c); // Вдруг будет?
// Результат строительства сохраняется в файле
void ResultOut<Builder *f>(FILE* ofst);

#endif // __builder__