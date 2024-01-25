
// RUN: %clang -c %S/Inputs/Figure.c -o %S/f.o
// RUN: %clang -c %S/Inputs/Triangle.c -o %S/t.o
// RUN: %clang -c %s -o %S/a.o
// RUN: %clang %S/f.o %S/t.o %S/a.o -o %S/a.out
// RUN: %S/a.out | FileCheck %s -check-prefix=CHECK-RT
// RUN: rm %S/a.out %S/f.o %S/t.o %S/a.o

#include "Inputs/pp-linked-figure.h"
#include "Inputs/pp-linked-triangle.h"
#include <stdio.h>

struct Rhombus { int a, b; };
struct Figure + <struct Rhombus; >;

void PrintFigure<struct Figure<struct Rhombus> *p>() {
    struct Figure<struct Rhombus> r = *p;
    printf(">>> Rhombus: color = %d, a = %d, b = %d\n",
            r.color, r<a>, r<b>);
}

int main()
{
    // CHECK-RT: FigCircle: 42 4294967295
    // CHECK-RT-NEXT: Circle tags check: [1]
    printCircle();
    // CHECK-RT-NEXT: FigRect: 5 7 255
    // CHECK-RT-NEXT: Rectangle tags check: [1]
    printRectangle();
    // CHECK-RT-NEXT: FigTriangle: 1 2 3 1
    // CHECK-RT-NEXT: Triangle tags check: [1]
    printTriangle();

    // CHECK-RT: Figure tags: 4
    // CHECK-RT: Circle tag: 1
    // CHECK-RT: Rectangle tag: 2
    // CHECK-RT: Triangle tag: 3
    // CHECK-RT: Rhombus tag: 4
    printf("Figure tags: %d\n", __pp_tags_Figure);
    printf("Circle tag: %d\n", __pp_tag___pp_struct_Figure__Circle);
    printf("Rectangle tag: %d\n", __pp_tag___pp_struct_Figure__Rectangle);
    printf("Triangle tag: %d\n", __pp_tag___pp_struct_Figure__Triangle);
    printf("Rhombus tag: %d\n", __pp_tag___pp_struct_Figure__Rhombus);

    struct Figure<struct Circle> fc;
    fc.color = 111;
    fc<r> = 100;

    // CHECK-RT: PrintFigure Default body
    PrintFigure<&fc>();

    // CHECK-RT: >>> Triangle: color = 555, a = 10, b = 20, c = 30
    struct Figure<struct Triangle> ft;
    ft.color = 555;
    ft<a> = 10;
    ft<b> = 20;
    ft<c> = 30;
    PrintFigure<&ft>();


    // CHECK-RT: >>> Rectangle: color = 333, w = 22, h = 11
    struct Figure<struct Rectangle> fr;
    fr.color = 333;
    fr<w> = 22;
    fr<h> = 11;
    PrintFigure<&fr>();

    // CHECK-RT: >>> Rhombus: color = 999, a = 10000, b = 20000
    struct Figure<struct Rhombus> frh;
    frh.color = 999;
    frh<a> = 10000;
    frh<b> = 20000;
    PrintFigure<&frh>();

    return 0;
}
