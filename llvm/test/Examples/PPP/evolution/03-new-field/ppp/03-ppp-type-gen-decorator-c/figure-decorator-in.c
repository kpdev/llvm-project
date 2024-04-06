//==============================================================================
// figure-decorator-in.c - Обработчик специализации, осуществляющий
// ввод содержимого фигуры, подключенной к декоратору и декоратора (цвета).
//==============================================================================

#include "figure-decorator.h"
#include <stdio.h>

//------------------------------------------------------------------------------
// Прототип функции ввода декоратора
void RectangleIn(Decorator* r, FILE* ifst);
// Прототип обобщеннай функции ввода фигуры
void FigureIn<Figure * f>(FILE* file);

void DecoratorIn<Decorator * d>(FILE* file) {}

void DecoratorIn<Decorator<Figure> * d>(FILE* ifst) {
    FigureIn<&(d->@)>(ifst);
    // TODO: Fix it
    // fscanf(ifst, "%x", &(d->color));
    unsigned color;
    fscanf(ifst, "%x", &color);
}

//------------------------------------------------------------------------------
// Ввод фигуры совместно с содержимым декоратора
void FigureIn<Figure<Decorator> * d>(FILE* ifst)
{
    DecoratorIn<&(d->@)>(ifst);
}
