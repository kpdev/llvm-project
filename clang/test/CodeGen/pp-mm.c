// RUN: %clang %s -o %S/a.out && %S/a.out | FileCheck %s -check-prefix=CHECK-RT && rm %S/a.out


typedef struct Circle { int r; } Circle;
typedef struct Rectangle { int w, h; } Rectangle;
struct Figure { unsigned color; } < struct Circle; struct Rectangle; >;


void PrintFigures<struct Figure* f1,
                  struct Figure* f2>()
{
    printf("default\n");
}


void PrintFigures<struct Figure.Circle *f1,
                  struct Figure.Circle *f2>()
{
    printf("circ + circ\n");
}

void PrintFigures<struct Figure.Rectangle *f1,
                  struct Figure.Rectangle *f2>()
{
    printf("rect + rect\n");
}

void PrintFigures<struct Figure.Circle *f1,
                  struct Figure.Rectangle *f2>()
{
    printf("circ + rect\n");
}

void PrintFigures<struct Figure.Rectangle *f1,
                  struct Figure.Circle *f2>()
{
    printf("rect + circ\n");
}

void MultimethodFirstRect<Figure* f2>(Figure.Rectangle* r1, int* ofst) {}

void MultimethodFirstRect<Figure.Rectangle* r2>(Figure.Rectangle* r1, int* ofst) {
  printf("Rectangle - Rectangle Combination\n");
}

void MultimethodFirstRect<Figure.Circle* t2>(Figure.Rectangle* r1, int* ofst) {
  printf("Rectangle - Circle Combination\n");
}

static
void StaticPrintFigure<struct Figure* f1>()
{
    printf("static default\n");
}


static
void StaticPrintFigure<struct Figure.Circle *f1>()
{
    printf("static circ\n");
}

int main() {
    struct Figure.Circle fc;
    struct Figure.Rectangle fr;
    // CHECK-RT: circ + circ
    PrintFigures<&fc, &fc>();
    // CHECK-RT: circ + rect
    PrintFigures<&fc, &fr>();
    // CHECK-RT: rect + circ
    PrintFigures<&fr, &fc>();
    // CHECK-RT: rect + rect
    PrintFigures<&fr, &fr>();

    struct Figure* fp = get_spec_ptr(Figure, 0);
    // CHECK-RT: default
    PrintFigures<fp, fp>();

    int dummy = 0;
    // CHECK-RT: Rectangle - Rectangle Combination
    MultimethodFirstRect<&fr>(&fr, &dummy);
    // CHECK-RT: Rectangle - Circle Combination
    MultimethodFirstRect<&fc>(&fr, &dummy);

    // CHECK-RT: static default
    StaticPrintFigure<&fr>();
    // CHECK-RT: static circ
    StaticPrintFigure<&fc>();
}
