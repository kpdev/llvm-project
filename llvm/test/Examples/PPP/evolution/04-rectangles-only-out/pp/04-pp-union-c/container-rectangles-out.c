//==============================================================================
// container-rectangles-out.c - содержит функцию
// вывода из содержимого контейнера только прямоугольников
//==============================================================================

#include "container.h"
#include <stdio.h>

//------------------------------------------------------------------------------
// Сигнатуры требуемых функций можно тоже подключить через
// заголовочный файл. Но, для простоты, можно и так описать.
bool FigureRectangleOnlyOut(struct Figure* s, FILE* ofst);

//------------------------------------------------------------------------------
// Вывод только прямоугольников в указанный поток
void ContainerRectanglesOnlyOut(Container* c, FILE* ofst)
{
    int rectCount = 0;
    for (int i = 0; i < c->len; i++) {
        if(FigureRectangleOnlyOut(c->cont[i], ofst)) {
            ++rectCount;
        }
    }
    fprintf(ofst, "Container contains %d rectangles.\n", rectCount);
}
