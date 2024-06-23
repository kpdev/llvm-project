// RUN: %clang -c %s -o %S/a.o
// RUN: %clang %S/a.o -o %S/a.out
// RUN: %S/a.out | FileCheck %s -check-prefix=CHECK-RT
// RUN: rm %S/a.out %S/a.o



#include <stdio.h>


typedef struct Circle { int r; } Circle;
struct Figure { int f; } < Circle*; >;

int main() {
    struct Circle c;
    c.r = 0;
    struct Figure<Circle*> fc;
    fc.@ = &c;
    fc.@->r = 5;

    // CHECK-RT: Field value: 5
    printf("Field value: %d\n", fc.@->r);
}