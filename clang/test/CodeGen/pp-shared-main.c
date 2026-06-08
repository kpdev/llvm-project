// RUN: %clang %S/Inputs/pp-shared-lib.c -shared -fPIC -o %T/libmylib.so
// RUN: %clang %s -o %t.out -L%T -lmylib -Wl,-rpath=%T
// RUN: %t.out | FileCheck %s -check-prefix=CHECK-RT


#include <stdio.h>

extern void mylib_show_glob(void);

struct Figure{}<>;
struct S3{};
struct Figure + <struct S3;>;

void main_show_glob(void) {
    printf("[Main] Value: %d, Address: %p\n",
            __pp_tags_Figure, &__pp_tags_Figure);
}

int main(void) {
    // CHECK-RT: [Lib] Value: 3, Address: [[ADDR:0x[0-9a-f]+]]
    mylib_show_glob();
    // Value and Address are the same for lib and main:
    // CHECK-RT: [Main] Value: 3, Address: [[ADDR]]
    main_show_glob();
    return 0;
}
