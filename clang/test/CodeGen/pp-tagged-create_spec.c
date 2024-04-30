// RUN: %clang %s -o %S/a.out && %S/a.out | FileCheck %s -check-prefix=CHECK-RT && rm %S/a.out

struct Circle {};
typedef struct Figure {} < c : Circle > Figure;

struct Decorator {} < Figure; >;

Figure + <decor : Decorator;>;

int main() {

    struct Figure<decor<Figure>* f = create_spec<Figure<decor<Figure> > >();
    // CHECK-RT: Tags: 2 1
    printf("Tags: %d %d\n",
            f->__pp_specialization_type,
            f->@.__pp_specialization_type);
}
