// RUN: %clang %s -o %S/a.out && %S/a.out | FileCheck %s -check-prefix=CHECK-RT && rm %S/a.out

typedef struct Circle { int r; } Circle;
struct Figure1D { unsigned color; } < struct Circle; >;

typedef struct Rectangle { int w, h; } Rectangle;
struct Figure2D { unsigned color; } < struct Circle; struct Rectangle; >;

typedef struct Triangle { int a, b, c; } Triangle;
struct Figure3D { unsigned color; } < struct Circle; struct Rectangle; struct Triangle; >;


void PrintFigures<struct Figure1D* f1,
                  struct Figure2D* f2,
                  struct Figure3D* f3>()
{
    printf("default\n");
}

void PrintFigures<struct Figure1D.Circle    *f1,
                  struct Figure2D.Rectangle *f2,
                  struct Figure3D.Triangle  *f3>()
{
    printf("circ + rect + trian\n");
}

void PrintFigures<struct Figure1D.Circle *f1,
                  struct Figure2D.Circle *f2,
                  struct Figure3D.Circle *f3>()
{
    printf("circ + circ + circ\n");
}


int main() {
    struct Figure1D.Circle f1c;

    struct Figure2D.Circle    f2c;
    struct Figure2D.Rectangle f2r;

    struct Figure3D.Circle   f3c;
    struct Figure3D.Triangle f3t;

    // CHECK-RT: default
    PrintFigures<&f1c, &f2c, &f3t>();
    // CHECK-RT: circ + circ + circ
    PrintFigures<&f1c, &f2c, &f3c>();
    // CHECK-RT: circ + rect + trian
    PrintFigures<&f1c, &f2r, &f3t>();

    return 0;
}