
// RUN: %clang %s -o %t
// RUN: not %t 2>&1 | FileCheck %s

#include <stdio.h>
#include <stdlib.h>

typedef struct Circle { int r; } Circle;
typedef struct Rectangle { int w, h; } Rectangle;
typedef struct Triangle { int a, b, c; } Triangle;
struct Figure { unsigned color; } < Circle; Rectangle; Triangle; >;

void PrintFigure<Figure* f>() = 0;

void PrintFigure<Figure.Rectangle* f>() {
    printf("Rectangle\n");
}

void PrintFigure<Figure.Triangle* f>() {
    printf("Triangle\n");
}

int main() {
    struct Figure.Rectangle fr;
    // CHECK: Rectangle
    PrintFigure<&fr>();

    struct Figure.Circle fc;
    // CHECK: Error. Called default handler for method PrintFigure
    PrintFigure<&fc>();

    struct Figure.Triangle ft;
    // This code will not be executed
    //      because of error on previous PrintFigure call
    // CHECK-NOT: Triangle
    PrintFigure<&ft>();
}
