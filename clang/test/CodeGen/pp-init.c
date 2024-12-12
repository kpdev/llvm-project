
// RUN: %clang %s -o %S/a.out && %S/a.out | FileCheck %s -check-prefix=CHECK-RT && rm %S/a.out

#include <stdio.h>

typedef struct Circle { int r; } Circle;
typedef struct Rectangle { int w, h; } Rectangle;
struct Figure {
    unsigned color;
    int additional_workload;
    double additional_workload2;
    char additional_workload3;
} < struct Circle; struct Rectangle; >;

typedef struct Triangle { int a, b, c; } Triangle;
Figure + < Triangle; >;

struct RectangleCover {
  struct Figure.Circle fc;       // Интерфей ввода-вывода для прямоугольника
  struct Figure.Triangle ft;     // Геометрический интефейс прямоугольника
  Rectangle r;                // Используемый прямоугольник
} <>;

struct RectangleCover g_rc;

int main() {
    // CHECK-RT: pf_empty tag = 0
    struct Figure* pf_empty = create_spec(Figure);
    printf("pf_empty tag = %d\n",
        pf_empty->__pp_specialization_type);

    // CHECK-RT: prc tag = 0
    struct RectangleCover* prc = create_spec(RectangleCover);
    printf("prc tag = %d\n",
        prc->__pp_specialization_type);

    // CHECK-RT: prc->fc tag = 1
    printf("prc->fc tag = %d\n",
        prc->fc.__pp_specialization_type);

    // CHECK-RT: prc->ft tag = 3
    printf("prc->ft tag = %d\n",
        prc->ft.__pp_specialization_type);


    // CHECK-RT: g_rc tag = 0
    printf("g_rc tag = %d\n",
        g_rc.__pp_specialization_type);

    // CHECK-RT: g_rc.fc tag = 1
    printf("g_rc.fc tag = %d\n",
        g_rc.fc.__pp_specialization_type);

    // CHECK-RT: g_rc.ft tag = 3
    printf("g_rc.ft tag = %d\n",
        g_rc.ft.__pp_specialization_type);

    // Just check compilation
    init_spec(Figure.Rectangle, &(g_rc.fc));
    // CHECK-RT: g_rc.fc tag = 2
    printf("g_rc.fc tag = %d\n",
        g_rc.fc.__pp_specialization_type);

    struct RectangleCover rc;
    // CHECK-RT: rc tag = 0
    printf("rc tag = %d\n",
        rc.__pp_specialization_type);

    // CHECK-RT: rc.fc tag = 1
    printf("rc.fc tag = %d\n",
        rc.fc.__pp_specialization_type);

    // CHECK-RT: rc.ft tag = 3
    printf("rc.ft tag = %d\n",
        rc.ft.__pp_specialization_type);
    return 0;
}
