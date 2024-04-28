//------------------------------------------------------------------------------
// figures-counter-builder.cpp - реализация методов подсчета фигур
//------------------------------------------------------------------------------

#include "figures-counter-builder.h"
#include "simple-rectangle.h"
#include "simple-triangle.h"

// Конструктор, подключающий массив для хранения аппликации
CounterBuilder::CounterBuilder():
    rectanglesCounter{0}, trianglesCounter{0}
{}

// Методы, используемые для строительства композиций
void CounterBuilder::BuildRectangle(double x, double y) {
  ++rectanglesCounter;
}
void CounterBuilder::BuildTriangle(double a, double b, double c) {
  ++trianglesCounter;
}

// Результат строительства сохраняется в файле
void CounterBuilder::ResultOut(std::ofstream &ofst) {
  ofst << "Result of figures counting:\n";
  ofst << "    number of rectangles: " << rectanglesCounter << "\n";
  ofst << "    number of triangles:  " << trianglesCounter << "\n";
}
