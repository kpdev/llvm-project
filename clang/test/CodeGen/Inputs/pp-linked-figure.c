#include "pp-linked-figure.h"
#include <stdio.h>

void printRectangle()
{
    struct Figure<Rectangle> fr;
    fr<w> = 5;
    fr<h> = 7;
    fr.color = 0x000000ff;

    printf("FigRect: %d %d %u\n", fr<w>, fr<h>, fr.color);
}

void printCircle()
{
    struct Figure<Circle> fc;
    fc<r> = 42;
    fc.color = 0xffffffff;

    printf("FigCircle: %d %u\n", fc<r>, fc.color);
}
