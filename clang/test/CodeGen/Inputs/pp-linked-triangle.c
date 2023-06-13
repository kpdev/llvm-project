#include "pp-linked-triangle.h"
#include <stdio.h>

void printTriangle()
{
    struct Figure<Triangle> ft;
    ft<a> = 1;
    ft<b> = 2;
    ft<c> = 3;
    ft.color = 0x00000001;

    // CHECK-RT: FigTriangle: 1 2 3 1
    printf("FigTriangle: %d %d %d %u\n", ft<a>, ft<b>, ft<c>, ft.color);
}
