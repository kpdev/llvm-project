// RUN: %clang -S -emit-llvm %s 2>&1 -o - | FileCheck %s -check-prefix=CHECK-IR
// RUN: %clang %s -o %S/a.out && %S/a.out | FileCheck %s -check-prefix=CHECK-RT && rm %S/a.out

#include <stdio.h>

struct Circle { int c; };
struct Rect { int h, w; };
struct Trian { int a, b, c; };
struct Figure { int f; } < t0 : Circle;
                           t1 : Rect;
                           t2 : Trian >;

void PrintFigure<Figure* f>() {
    printf("PrintFigure<Figure* f> [Default]\n");
}

void PrintFigure<Figure<t0>* f>() {
    printf("PrintFigure<Figure<t0>* f> [Specialized]\n");
}

void PrintFigure<Figure<t1>* f>() {
    printf("PrintFigure<Figure<t1>* f> [Specialized]\n");
}

void foo()
{
// CHECK-IR: %__pp_head = getelementptr inbounds %struct.__pp_struct_Figure__t0, ptr %ttt, i32 0, i32 0
// CHECK-IR: %__pp_specialization_type = getelementptr inbounds %struct.Figure, ptr %__pp_head, i32 0, i32 1
// CHECK-IR: store i32 %0, ptr %__pp_specialization_type, align 4
    struct Figure<t0> ttt;
}

int main() {
    struct Figure<t0> t0_obj;
    struct Figure<t1> t1_obj;
    struct Figure<t2> t2_obj;

// CHECK-RT: PrintFigure<Figure<t0>* f> [Specialized]
    PrintFigure<&t0_obj>();

// CHECK-RT: PrintFigure<Figure<t1>* f> [Specialized]
    PrintFigure<&t1_obj>();

// CHECK-RT: PrintFigure<Figure* f> [Default]
    PrintFigure<&t2_obj>();
    return 0;
}
