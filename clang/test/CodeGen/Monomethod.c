// RUN: %clang %s -o %t.out && %t.out | FileCheck %s -check-prefix=CHECK-RT

// {workspace}/build/bin/clang {workspace}/clang/test/CodeGen/Monomethod.c -g -O0 -o {workspace}/clang/test/CodeGen/a1.out
// {workspace}/clang/test/CodeGen/a1.out

#include <stdio.h>

struct Circle { int r; };
struct Rectangle { int w, h; };
struct Figure { int color; } < struct Circle; struct Rectangle; >;


struct Triangle { int a, b, c; };
struct Figure + < struct Triangle; >;


void PrintFigure1<struct Figure* f>()
{
    printf(">>> [Default] PrintFigure1 color = %d\n", f->color);
}

void PrintFigure1<struct Figure.Circle *p>() {
    struct Figure.Circle c = *p;
    printf(">>> Circle: color = %d, r = %d\n", c.color, c.@r);
}

void PrintFigure1<struct Figure.Rectangle *p>() {
    struct Figure.Rectangle r = *p;
    printf(">>> Rectangle: color = %d, h = %d, w = %d\n",
            r.color, r.@h, r.@w);
}


int main()
{
    struct Figure.Circle fc;
    fc.color = 111;
    fc.@r = 100;

// CHECK-RT: >>> Circle: color = 111, r = 100
    PrintFigure1<&fc>();
    
    struct Figure.Rectangle fr;
    fr.color = 555;
    fr.@h = 300;
    fr.@w = 1000;
    
// CHECK-RT: >>> Rectangle: color = 555, h = 300, w = 1000
    PrintFigure1<&fr>();

    struct Figure.Triangle ft;
    ft.color = -1;

// CHECK-RT: >>> [Default] PrintFigure1 color = -1
    PrintFigure1<&ft>();
}
