
// RUN: %clang %s -o %S/a.out && %S/a.out | FileCheck %s -check-prefix=CHECK-RT && rm %S/a.out

#include <stdio.h>

typedef struct Circle { int r; } Circle;
typedef struct Rectangle { int w, h; } Rectangle;
struct Figure { unsigned color; } < struct Circle; struct Rectangle; >;

typedef struct Triangle { int a, b, c; } Triangle;
Figure + < Triangle; >;

struct RectangleCover {
  struct Figure.Circle fc;       // Интерфей ввода-вывода для прямоугольника
  struct Figure.Triangle ft;     // Геометрический интефейс прямоугольника
  Rectangle r;                // Используемый прямоугольник
} <>;

struct RectangleCover g_rc;

int main() {
    struct RectangleCover rc;
    // CHECK-RT: rc tag = 0
    printf("rc tag = %d\n",
        rc.__pp_specialization_type);
    return 0;
}