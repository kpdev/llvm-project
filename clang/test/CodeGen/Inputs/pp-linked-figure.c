#include "pp-linked-figure.h"
#include <stdio.h>

void printCircle()
{
    struct Figure<struct Circle> fc;
    fc<r> = 42;
    fc.color = 0xffffffff;

    printf("FigCircle: %d %u\n", fc<r>, fc.color);
    printf("Circle tags check: [%d]\n",
        (int)(fc.__pp_specialization_type == __pp_tag___pp_struct_Figure__Circle));
}

void printRectangle()
{
    struct Figure<struct Rectangle> fr;
    fr<w> = 5;
    fr<h> = 7;
    fr.color = 0x000000ff;

    printf("FigRect: %d %d %u\n", fr<w>, fr<h>, fr.color);
    printf("Rectangle tags check: [%d]\n",
        (int)(fr.__pp_specialization_type == __pp_tag___pp_struct_Figure__Rectangle));
}
