
// RUN: %clang -c %S/Inputs/pp-linked-figure.c -o %S/f.o
// RUN: %clang -c %S/Inputs/pp-linked-triangle.c -o %S/t.o
// RUN: %clang -c %s -o %S/a.o
// RUN: %clang %S/f.o %S/t.o %S/a.o -o %S/a.out
// RUN: %S/a.out | FileCheck %s -check-prefix=CHECK-RT
// RUN: rm %S/a.out %S/f.o %S/t.o %S/a.o

#include "Inputs/pp-linked-figure.h"
#include "Inputs/pp-linked-triangle.h"

int main()
{
    // CHECK-RT: FigCircle: 42 4294967295
    printCircle();
    // CHECK-RT-NEXT: FigRect: 5 7 255
    printRectangle();
    // CHECK-RT-NEXT: FigTriangle: 1 2 3 1
    printTriangle();

    // TODO: Fix it
    // CHECK-RT-NOT: Figure tags: 3
    // CHECK-RT-NOT: Circle tag: 1
    // CHECK-RT-NOT: Rectangle tag: 2
    // CHECK-RT-NOT: Triangle tag: 3
    printf("Figure tags: %d\n", __pp_tags_Figure);
    printf("Circle tag: %d\n", __pp_tag___pp_struct_Figure__Circle);
    printf("Rectangle tag: %d\n", __pp_tag___pp_struct_Figure__Rectangle);
    printf("Triangle tag: %d\n", __pp_tag___pp_struct_Figure__Triangle);

    return 0;
}
