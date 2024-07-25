// RUN: %clang -c %s -o %S/a.o
// RUN: %clang %S/a.o -o %S/a.out
// RUN: %S/a.out | FileCheck %s -check-prefix=CHECK-RT
// RUN: rm %S/a.out %S/a.o



#include <stdio.h>


struct Figure { int f; } < int; >;

typedef struct FigureTag { }
    < tag_c : int; > FigureTag;
FigureTag + < fourth_tag : int; >;
FigureTag + < void_tag : void; >;

void Print1<struct FigureTag* f>(){
    printf("Print1 default version\n");
}

void Print1<struct FigureTag.tag_c* f>() {
    printf("Print1 tagged version\n");
}

void Print1<struct FigureTag.void_tag* f>() {
    printf("Print1 void_tag version\n");
}

int main() {
    struct Figure.int fc;
    fc.@ = 5;

    // CHECK-RT: Field value: 5
    printf("Field value: %d\n", fc.@);

    struct FigureTag.tag_c tfc;
    tfc.@ = 7;

    // CHECK-RT: Field value: 7
    printf("Field value: %d\n", tfc.@);

    struct FigureTag.fourth_tag tfc2;
    tfc2.@ = 42;

    // CHECK-RT: Field value: 42
    printf("Field value: %d\n", tfc2.@);

    // CHECK-RT: Print1 tagged version
    Print1<&tfc>();

    // CHECK-RT: Print1 default version
    Print1<&tfc2>();

    struct FigureTag.void_tag tfv;

    // CHECK-RT: Print1 void_tag version
    Print1<&tfv>();
}
