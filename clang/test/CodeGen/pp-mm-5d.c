// RUN: %clang %s -o %S/a.out && %S/a.out | FileCheck %s -check-prefix=CHECK-RT && rm %S/a.out


struct Circle {};
struct Rectangle {};
struct Figure {
} < struct Circle; struct Rectangle; >;

struct RGB{};
struct Format {
} < struct RGB; >;

struct Builder{};
struct Officer{};
struct Doctor{};
struct Worker {
} < struct Builder;
    struct Officer;
    struct Doctor; >;

void Multimethod5<struct Figure* f1,
                  struct Format* f2,
                  struct Worker* f3,
                  struct Format* f4,
                  struct Worker* f5>()
{
    printf("Def_5\n");
}

void Multimethod5<struct Figure.Circle* f1,
                  struct Format.RGB* f2,
                  struct Worker.Doctor* f3,
                  struct Format.RGB* f4,
                  struct Worker.Builder* f5>()
{
    printf("C-R-D-R-B\n");
}

int main() {
    struct Figure.Circle fcircle;
    struct Format.RGB frgb;
    struct Worker.Doctor wdoctor;
    struct Worker.Builder wbuilder;

    // CHECK-RT: Def_5
    Multimethod5<&fcircle, &frgb, &wdoctor, &frgb, &wdoctor>();
    // CHECK-RT: C-R-D-R-B
    Multimethod5<&fcircle, &frgb, &wdoctor, &frgb, &wbuilder>();
}
