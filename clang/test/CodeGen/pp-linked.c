
// RUN: %clang -c %S/Inputs/pp-linked-figure.c -o %S/f.o
// RUN: %clang -c %S/Inputs/pp-linked-triangle.c -o %S/t.o
// RUN: %clang -c %s -o %S/a.o
// RUN~: %clang %S/f.o %S/t.o %S/a.o -o %S/a.out
// RUN~: %S/a.out | FileCheck %s -check-prefix=CHECK-RT
// RUN~: rm %S/a.out %S/f.o %S/t.o %S/a.o

#include "Inputs/pp-linked-figure.h"
#include "Inputs/pp-linked-triangle.h"

int main()
{
    printCircle();
    printRectangle();
    printTriangle();
    return 0;
}
