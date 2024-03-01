//==============================================================================
// figures-input.c - функция содания ввода всех альтернативных фигур.
// Реализована как централизованная. Единственная, требующая модификации
// при вводе данных. Но можно тоже сделать эволюционно расширяемой.
// Реализация использует динамически подключаемый декоратор
//==============================================================================

// #include "decorator.h"
#include "figure.h"
#include "figure-decorator.h"
#include "figure-rectangle.h"
#include "figure-triangle.h"
#include <stdio.h>

void FigureIn<Figure *f>(FILE* file);
//------------------------------------------------------------------------------
// Ввод параметров одной из фигур из файла, включая ее цвет
Figure* FigureCreateAndIn(FILE* ifst)
{
    Figure* sp;
    int k;
    fscanf(ifst, "%d", &(k));
    switch (k) {
    case 1:
        // Далее нужно сформировать признак. Наверное спец. функция...
        sp = create_spec<struct Figure<struct Rectangle> >(); // Создание и инициализация
        break;
    case 2:
        // Далее нужно сформировать признак. Наверное спец. функция...
        sp = create_spec<struct Figure<struct Triangle> >(); // Создание и инициализация
        break;
    default:
        return 0;
    }
    // Создание декоратора
    struct Figure<Decorator>* sd = create_spec<struct Figure<struct Decorator> >();
    (sd->@).f = sp; // связывание с фигурой
    FigureIn<sd>(ifst); // ввод декорированной фигуры
    return (Figure*)sd;
}
