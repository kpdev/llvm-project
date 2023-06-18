#include "pp-linked-triangle.h"
#include <stdio.h>

void printTriangle()
{
    struct Figure<struct Triangle> ft;
    ft<a> = 1;
    ft<b> = 2;
    ft<c> = 3;
    ft.color = 0x00000001;

    printf("FigTriangle: %d %d %d %u\n", ft<a>, ft<b>, ft<c>, ft.color);
    printf("Triangle tags check: [%d]\n",
        (int)(ft.__pp_specialization_type == __pp_tag___pp_struct_Figure__Triangle));
}
