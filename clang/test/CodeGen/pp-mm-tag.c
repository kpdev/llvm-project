// RUN: %clang %s -o %S/a.out && %S/a.out | FileCheck %s -check-prefix=CHECK-RT && rm %S/a.out


struct Circle { int c; };
struct Rect { int h, w; };
struct Trian { int a, b, c; };

struct Figure { int f; } < t0 : Circle;
                           t1 : Rect;
                           t2, t3 : Trian >;

void PrintFigures<struct Figure* f1,
                  struct Figure* f2>()
{
    printf("default\n");
}


void PrintFigures<struct Figure.t0 *f1,
                  struct Figure.t0 *f2>()
{
    printf("t0 + t0\n");
}

void PrintFigures<struct Figure.t0 *f1,
                  struct Figure.t1 *f2>()
{
    printf("t0 + t1\n");
}

void PrintFigures<struct Figure.t1 *f1,
                  struct Figure.t2 *f2>()
{
    printf("t1 + t2\n");
}

void PrintFigures<struct Figure.t2 *f1,
                  struct Figure.t3 *f2>()
{
    printf("t2 + t3\n");
}

void PrintFigures<struct Figure.t3 *f1,
                  struct Figure.t0 *f2>()
{
    printf("t3 + t0\n");
}

int main() {
    struct Figure.t0 t0_obj;
    struct Figure.t1 t1_obj;
    struct Figure.t2 t2_obj;
    struct Figure.t3 t3_obj;

    // CHECK-RT: t0 + t0
    PrintFigures<&t0_obj, &t0_obj>();
    // CHECK-RT: default
    PrintFigures<&t1_obj, &t1_obj>();
    // CHECK-RT: t0 + t1
    PrintFigures<&t0_obj, &t1_obj>();
    // CHECK-RT: t1 + t2
    PrintFigures<&t1_obj, &t2_obj>();
    // CHECK-RT: t2 + t3
    PrintFigures<&t2_obj, &t3_obj>();
    // CHECK-RT: t3 + t0
    PrintFigures<&t3_obj, &t0_obj>();
}
