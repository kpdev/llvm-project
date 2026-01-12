#include <stdio.h>

struct Figure{}<>;

struct S1{};
struct S2{};

struct Figure + <struct S1;>;
struct Figure + <struct S2;>;

void Print<struct Figure* f>()
{
    printf("Print default lib\n");
}

void Print<struct Figure.S1* f>()
{
    printf("Print S1 lib\n");
}

void mylib_show_glob(void) {
    printf("[Lib] Value: %d, Address: %p\n",
            __pp_tags_Figure, &__pp_tags_Figure);
}
