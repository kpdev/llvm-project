
// RUN: %clang %s -o %t
// RUN: %t 2>&1 | FileCheck %s

#include <stdio.h>
#include <stdlib.h>

typedef struct Circle { int r; } Circle;
typedef struct Rectangle { int w, h; } Rectangle;
typedef struct Triangle { int a, b, c; } Triangle;
typedef struct Figure { unsigned color; } < Circle; > Figure;

Figure + < Rectangle; >;
Figure + < Triangle; >;

void PrintFigure<Figure* f>() = 0;

void PrintFigure<Figure.Rectangle* f>() {
    printf("Rectangle w=%d h=%d\n", f->@w, f->@h);
}

void PrintFigure<Figure.Triangle* f>() {
    printf("Triangle a=%d b=%d c=%d\n", f->@a, f->@b, f->@c);
}

void PrintFigure<Figure.Circle* f>() {
    printf("Circle r=%d\n", f->@r);
}

Figure.Rectangle g_fr;

int main() {
    g_fr.color = 0xffffffff;
    g_fr.@w = 100; g_fr.@h = 200;
    // CHECK: Rectangle w=100 h=200
    PrintFigure<&g_fr>();

    Figure.Rectangle fr;
    fr.color = 0x00;
    fr.@w = 10; fr.@h = 20;
    // CHECK: Rectangle w=10 h=20
    PrintFigure<&fr>();

    Figure.Circle fc;
    fc.color = 0x01;
    fc.@r = 42;
    // CHECK: Circle r=42
    PrintFigure<&fc>();

    Figure.Triangle ft;
    ft.color = 0x02;
    ft.@a = 1; ft.@b = 2; ft.@c = 3;
    // CHECK: Triangle a=1 b=2 c=3
    PrintFigure<&ft>();

    Figure.Circle* pfc = create_spec(Figure.Circle);
    pfc->@r = 100;
    // CHECK: Circle r=100
    PrintFigure<pfc>();

    int count = get_spec_size(Figure);
    // CHECK: 4
    printf("%d\n", count);

    return 0;
}
