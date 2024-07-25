// RUN: %clang -S -emit-llvm %s 2>&1 -o - | FileCheck %s -check-prefix=CHECK-IR
// RUN: %clang %s -o %S/a.out && %S/a.out | FileCheck %s -check-prefix=CHECK-RT && rm %S/a.out

#include <stdio.h>

struct WeekDay {} < Monday,
                    Tuesday,
                    Wednesday,
                    Thursday,
                    Friday,
                    Saturday,
                    Sunday
                    : void >;

struct Circle { int c; };
struct Rect { int h, w; };
struct Trian { int a, b, c; };

struct Figure { int f; } < t0 : Circle;
                           t1 : Rect;
                           t2, t3 : Trian >;

struct SameTypeTest {} < Circle1,
                         Circle2,
                         Circle3
                         : Circle>;

//-------
void PrintFigure<Figure* f>() {
    printf("PrintFigure<Figure* f> [Default]\n");
}

void PrintFigure<Figure.t0* f>() {
    printf("PrintFigure<Figure<t0>* f> [Specialized]\n");
}

void PrintFigure<Figure.t1* f>() {
    printf("PrintFigure<Figure<t1>* f> [Specialized]\n");
}

void PrintFigure<Figure.t3* f>() {
    printf("PrintFigure<Figure<t3>* f> [Specialized]\n");
}

//--------
void PrintSameType<SameTypeTest* f>() {
    printf("PrintSameType<SameTypeTest* f> [Default]\n");
}

void PrintSameType<SameTypeTest.Circle1* f>() {
    printf("PrintSameType<SameTypeTest<Circle1>* f> [Specialized]\n");
}

void PrintSameType<SameTypeTest.Circle3* f>() {
    printf("PrintSameType<SameTypeTest<Circle3>* f> [Specialized]\n");
}


//--------
void PrintWeekday<WeekDay* d>() {
    printf("PrintFigure<WeekDay* d> [Default]\n");
}

void PrintWeekday<WeekDay.Monday* d>() {
    printf("PrintFigure<WeekDay<Monday>* d> [Specialized]\n");
}

void PrintWeekday<WeekDay.Tuesday* d>() {
    printf("PrintFigure<WeekDay<Tuesday>* d> [Specialized]\n");
}

void foo()
{
// CHECK-IR: %__pp_head = getelementptr inbounds %struct.__pp_struct_Figure__t0, ptr %ttt, i32 0, i32 0
// CHECK-IR: %__pp_specialization_type = getelementptr inbounds %struct.Figure, ptr %__pp_head, i32 0, i32 1
// CHECK-IR: store i32 %0, ptr %__pp_specialization_type, align 4
    struct Figure.t0 ttt;
}

int main() {
    struct Figure.t0 t0_obj;
    struct Figure.t1 t1_obj;
    struct Figure.t2 t2_obj;
    struct Figure.t3 t3_obj;

// CHECK-RT: PrintFigure<Figure<t0>* f> [Specialized]
    PrintFigure<&t0_obj>();

// CHECK-RT: PrintFigure<Figure<t1>* f> [Specialized]
    PrintFigure<&t1_obj>();

// CHECK-RT: PrintFigure<Figure* f> [Default]
    PrintFigure<&t2_obj>();

// CHECK-RT: PrintFigure<Figure<t3>* f> [Specialized]
    PrintFigure<&t3_obj>();

    struct WeekDay.Monday monday;
    struct WeekDay.Tuesday tuesday;
    struct WeekDay.Friday friday;

// CHECK-RT: PrintFigure<WeekDay<Monday>* d> [Specialized]
    PrintWeekday<&monday>();

// CHECK-RT: PrintFigure<WeekDay<Tuesday>* d> [Specialized]
    PrintWeekday<&tuesday>();

// CHECK-RT: PrintFigure<WeekDay* d> [Default]
    PrintWeekday<&friday>();


    struct SameTypeTest.Circle1 c1;
    struct SameTypeTest.Circle2 c2;
    struct SameTypeTest.Circle3 c3;

// CHECK-RT: PrintSameType<SameTypeTest<Circle1>* f> [Specialized]
    PrintSameType<&c1>();
// CHECK-RT: PrintSameType<SameTypeTest* f> [Default]
    PrintSameType<&c2>();
// CHECK-RT: PrintSameType<SameTypeTest<Circle3>* f> [Specialized]
    PrintSameType<&c3>();
    return 0;
}
