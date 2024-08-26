// RUN: %clang %s -o %S/a.out && %S/a.out | FileCheck %s -check-prefix=CHECK-RT && rm %S/a.out

#include <stdio.h>
#include <stdlib.h>

typedef struct SimpleRectangle {
  double x, y; // ширина, высота
} SimpleRectangle;

typedef struct SimpleTriangle {
  double a, b, c; // стороны треугольника
} SimpleTriangle;

typedef struct SimpleFigure {}<> SimpleFigure;
SimpleFigure + <rect: SimpleRectangle;>;
SimpleFigure + <trian: SimpleTriangle;>;

typedef struct Point {
  double x, y; // точка
} Point;

typedef struct CoordRectangle {
  Point top_left, down_right; // координаты верхнего и нижнего углов
} CoordRectangle;

typedef struct CoordTriangle {
  Point a, b, c; // вершины треугольника
} CoordTriangle;

typedef struct CoordFigure {}<> CoordFigure;
CoordFigure + <rect: CoordRectangle;>;
CoordFigure + <trian: CoordTriangle;>;

typedef struct Figure { }<> Figure;
Figure + <simple: SimpleFigure;>;
Figure + <coord: CoordFigure;>;

int main()
{
    struct Figure* pf = create_spec(Figure.simple.trian);
    // CHECK-RT: Figure tag = 1
    printf("Figure tag = %d\n", pf->__pp_specialization_type);

    struct Figure.simple.trian* pfst = pf;
    // CHECK-RT-NEXT: Figure tag = 1
    printf("Figure tag = %d\n",
        pfst->__pp_specialization_type);

    struct SimpleFigure* ps_pfst = &(pfst->@);
    // CHECK-RT-NEXT: Simple tag = 2
    printf("Simple tag = %d\n",
        ps_pfst->__pp_specialization_type);

    struct Figure.simple* pfs = pf;
    // CHECK-RT-NEXT: Figure tag = 1
    printf("Figure tag = %d\n",
        pfs->__pp_specialization_type);

    struct SimpleFigure* ps_pfs  = &(pfs->@);
    // CHECK-RT-NEXT: Simple tag = 2
    printf("Simple tag = %d\n",
        ps_pfs->__pp_specialization_type);

    return 0;
}
