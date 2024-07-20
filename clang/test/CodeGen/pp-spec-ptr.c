// RUN: %clang -c %s -o %S/a.o
// RUN: %clang %S/a.o -o %S/a.out
// RUN: %S/a.out | FileCheck %s -check-prefix=CHECK-RT
// RUN: rm %S/a.out %S/a.o



#include <stdio.h>


typedef struct Circle { int r; } Circle;
struct Figure { int f; } < Circle*; >;
struct FigureTag { } < tag_c : Circle*; >;

typedef struct Rect { int w, h; } Rect;
Figure + <Rect*;>;
FigureTag + <r_tag: Rect*;>;

void Print1<struct FigureTag* f>(){
    printf("Print1 default version\n");
}

void Print1<struct FigureTag<tag_c>* f>() {
    printf("Print1 tagged version\n");
}

void Print1<struct FigureTag<r_tag>* f>() {
    printf("Print1 r_tag version\n");
}

void SimpleFun(struct FigureTag<tag_c>* f) {
    printf("SimpleFun: %d %d\n",
        f->__pp_specialization_type,
        f->@->r);
}

void PrintWithoutTag<struct Figure* f>() = 0;

void PrintWithoutTag<struct Figure<Rect*>* f>(){
    printf("PrintWithoutTag Rect* [%d %d]\n",
        f->@->w, f->@->h);
}

void SimpleFunR(struct FigureTag<r_tag>* f) {
    printf("SimpleFunR: %d %d %d\n",
        f->__pp_specialization_type,
        f->@->w,
        f->@->h);
}

int main() {
    struct Circle c;
    c.r = 0;
    struct Figure<Circle*> fc;
    fc.@ = &c;
    fc.@->r = 5;

    // CHECK-RT: Field value: 5
    printf("Field value: %d\n", fc.@->r);

    struct FigureTag<tag_c> tfc;
    tfc.@ = &c;
    tfc.@->r = 7;

    // CHECK-RT: Field value: 7 == 7
    printf("Field value: %d == %d\n",
            tfc.@->r, c.r);

    // CHECK-RT: Print1 tagged version
    Print1<&tfc>();

    // CHECK-RT: SimpleFun: 1 7
    SimpleFun(&tfc);

    Rect r;
    r.w = 1;
    r.h = 2;
    struct FigureTag<r_tag> tfr;
    tfr.@ = &r;
    tfr.@->w = 3;

    // CHECK-RT: Print1 r_tag version
    Print1<&tfr>();

    // CHECK-RT: SimpleFunR: 2 3 2
    SimpleFunR(&tfr);

    struct Figure<Rect*> fr;
    fr.@ = &r;
    fr.@->w = 42;

    // CHECK-RT: PrintWithoutTag Rect* [42 2]
    PrintWithoutTag<&fr>();

    // CHECK-RT-NOT: PrintWithoutTag
    PrintWithoutTag<&fc>();
}
