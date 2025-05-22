// RUN: %clang -c %s -o %S/a.o
// RUN: %clang %S/a.o -o %S/a.out
// RUN: %S/a.out | FileCheck %s -check-prefix=CHECK-RT
// RUN: rm %S/a.out %S/a.o



#include <stdio.h>


struct Figure { int f; } < int; >;

typedef struct FigureTag { }
    < tag_c : int; > FigureTag;
FigureTag + < fourth_tag : int; >;
FigureTag + < void_tag : void; >;

struct FigureD { } < double; >;
struct FigureF { } < float; >;
struct FigureC { } < char; >;
struct FigureD2 { } < tag: double; >;
struct FigureF2 { } < tag: float; >;
struct FigureC2 { } < tag: char; >;

struct FigureFull { } < char; int; double; float; >;
FigureFull + < tag1 : char; >;
FigureFull + < tag2 : int; >;
FigureFull + < tag3 : double; >;
FigureFull + < tag4 : float; >;

void PrintFF<struct FigureFull* f>(){
    printf("PrintFF default version\n");
}

void PrintFF<struct FigureFull.tag1* f>() {
    printf("PrintFF tag1 version\n");
}

void PrintFF<struct FigureFull.tag2* f>() {
    printf("PrintFF tag2 version\n");
}

void Print1<struct FigureTag* f>(){
    printf("Print1 default version\n");
}

void Print1<struct FigureTag.tag_c* f>() {
    printf("Print1 tagged version\n");
}

void Print1<struct FigureTag.void_tag* f>() {
    printf("Print1 void_tag version\n");
}

int main() {
    struct Figure.int fc;
    fc.@ = 5;

    // CHECK-RT: Field value: 5
    printf("Field value: %d\n", fc.@);

    struct FigureTag.tag_c tfc;
    tfc.@ = 7;

    // CHECK-RT: Field value: 7
    printf("Field value: %d\n", tfc.@);

    struct FigureTag.fourth_tag tfc2;
    tfc2.@ = 42;

    // CHECK-RT: Field value: 42
    printf("Field value: %d\n", tfc2.@);

    // CHECK-RT: Print1 tagged version
    Print1<&tfc>();

    // CHECK-RT: Print1 default version
    Print1<&tfc2>();

    struct FigureTag.void_tag tfv;

    // CHECK-RT: Print1 void_tag version
    Print1<&tfv>();

    struct FigureD.double fd1;
    struct FigureF.float ff1;
    struct FigureC.char fc1;

    fd1.@ = 1.0;
    ff1.@ = 1.0f;
    fc1.@ = 'A';

    struct FigureD2.tag fd2;
    struct FigureF2.tag ff2;
    struct FigureC2.tag fc2;

    fd2.@ = 1.0;
    ff2.@ = 1.0f;
    fc2.@ = 'A';

    struct FigureFull.int ffi;
    struct FigureFull.char ffc;
    struct FigureFull.double ffd;
    struct FigureFull.float fff;
    ffi.@ = 1;
    ffc.@ = 'A';
    ffd.@ = 1.0;
    fff.@ = 1.0f;

    struct FigureFull.tag1 fft1;
    struct FigureFull.tag2 fft2;
    struct FigureFull.tag3 fft3;
    struct FigureFull.tag4 fft4;

    fft1.@ = ffc.@;
    fft2.@ = ffi.@;
    fft3.@ = ffd.@;
    fft4.@ = fff.@;

    // CHECK-RT: PrintFF tag1 version
    PrintFF<&fft1>();
    // CHECK-RT: PrintFF tag2 version
    PrintFF<&fft2>();
    // CHECK-RT: PrintFF default version
    PrintFF<&fft3>();
    // CHECK-RT: PrintFF default version
    PrintFF<&fft4>();
    // CHECK-RT: PrintFF default version
    PrintFF<&ffi>();
}
