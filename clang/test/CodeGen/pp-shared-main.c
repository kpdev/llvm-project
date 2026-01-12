// RUN: %clang %S/Inputs/pp-shared-lib.c -shared -fPIC -o %S/libmylib.so
// RUN: %clang %s -o %S/a.out -L%S -lmylib -Wl,-rpath=%S
// RUN: %S/a.out | FileCheck %s -check-prefix=CHECK-RT
// RUN: rm %S/a.out %S/libmylib.so


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
