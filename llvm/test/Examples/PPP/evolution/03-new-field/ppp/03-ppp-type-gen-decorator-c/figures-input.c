//==============================================================================
// figures-input.c - функция содания ввода всех альтернативных фигур.
// Реализована как централизованная. Единственная, требующая модификации
// при вводе данных. Но можно тоже сделать эволюционно расширяемой.
// Реализация использует динамически подключаемый декоратор
//==============================================================================

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
        // sp = malloc(sizeof(Figure<Rectangle>));
        // Далее нужно сформировать признак. Наверное спец. функция...
        sp = create_spec<Figure<Decorator<Rectangle> > >();
        break;
    case 2:
        // sp = malloc(sizeof(Figure<Triangle>));
        // Далее нужно сформировать признак. Наверное спец. функция...
        sp = create_spec<Figure < Decorator < Triangle > > >();
        break;
    default:
        return 0;
    }
    FigureIn<sp>(ifst); // ввод декорированной фигуры
    return sp;
}
