// RUN: %clang -c %s -o %S/a.o
// RUN: %clang %S/a.o -o %S/a.out
// RUN: %S/a.out | FileCheck %s -check-prefix=CHECK-RT
// RUN: rm %S/a.out %S/a.o



#include <stdio.h>


struct Figure { int f; } < int; >;

typedef struct FigureTag { }
    < tag_c : int; > FigureTag;
FigureTag + < fourth_tag : int; >;

int main() {
    struct Figure<int> fc;
    fc.@ = 5;

    // CHECK-RT: Field value: 5
    printf("Field value: %d\n", fc.@);

    struct FigureTag<tag_c> tfc;
    tfc.@ = 7;

    // CHECK-RT: Field value: 7
    printf("Field value: %d\n", tfc.@);

    struct FigureTag<fourth_tag> tfc2;
    tfc2.@ = 42;

    // CHECK-RT: Field value: 42
    printf("Field value: %d\n", tfc2.@);
}
