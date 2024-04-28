#ifndef __figures_counter_builder__
#define __figures_counter_builder__

//------------------------------------------------------------------------------
// figures-counter-builder.h - строитель для подсчета фигур
//------------------------------------------------------------------------------

#include <fstream>
#include "builder.h"

//------------------------------------------------------------------------------
// Строитель из простых фигур
class CounterBuilder: public Builder {
  int rectanglesCounter;
  int trianglesCounter;
public:
  CounterBuilder();
  // Методы, используемые для строительства композиций
  virtual void BuildRectangle(double x, double y);
  virtual void BuildTriangle(double a, double b, double c);
  // Круга нет. Метод по умолчанию пустой
  // Результат строительства сохраняется в файле
  virtual void ResultOut(std::ofstream &ofst);
};

//------------------------------------------------------------------------------

#endif // __figures_counter_builder__