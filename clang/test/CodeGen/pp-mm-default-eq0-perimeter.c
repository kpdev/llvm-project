
// RUN: %clang %s -o %S/a.out
// RUN: not %S/a.out 2>&1 | FileCheck %s
// RUN: rm %S/a.out

#include <stdio.h>
#include <stdlib.h>

typedef struct Circle { int r; } Circle;
typedef struct Rectangle { int w, h; } Rectangle;
typedef struct Triangle { int a, b, c; } Triangle;
struct Figure { unsigned color; } < Circle; Rectangle; Triangle; >;

double CalculatePerimeter<Figure* f>() = 0;

double CalculatePerimeter<Figure.Rectangle* f>() {
    printf("Rectangle\n");
    return 2 * (f->@w + f->@h);
}

double CalculatePerimeter<Figure.Triangle* f>() {
    printf("Triangle");
    return f->@a + f->@b + f->@c;  
}

int main() {
    struct Figure.Rectangle fr;
    // CHECK: Rectangle
    double pr = CalculatePerimeter<&fr>();

    struct Figure.Circle fc;
    // CHECK: Error. Called default handler for method CalculatePerimeter
    double pc = CalculatePerimeter<&fc>();

    struct Figure.Triangle ft;
    // This code will not be executed
    //      because of error on previous CalculatePerimeter call
    // CHECK-NOT: Triangle
    double pt = CalculatePerimeter<&ft>();

    // CHECK-NOT: Perimeters
    printf("Perimeters: %f %f %f\n", pr, pc, pt);
}
