// RUN: %clang -S -emit-llvm %s -o - | FileCheck %s -check-prefix=CHECK-DEFAULT
// RUN: %clang -S -Xclang -ast-dump -emit-llvm %s -o - | FileCheck %s -check-prefix=CHECK-AST
// RUN: %clang -S -emit-llvm %s 2>&1 -o - | FileCheck %s -check-prefix=CHECK-LL
// RUN: %clang %s -o %S/a.out && %S/a.out | FileCheck %s -check-prefix=CHECK-RT && rm %S/a.out

// CHECK-DEFAULT: [PPMC] Parse extension
// CHECK-DEFAULT:   Token -> Kind: [identifier], Name:[Base1]
// CHECK-DEFAULT:   Token -> Kind: [comma]
// CHECK-DEFAULT:   Token -> Kind: [identifier], Name:[Base2]
// CHECK-DEFAULT: [PPMC] Finish parse extension

// CHECK-LL: struct Generalization definition
// CHECK-LL: load 'double'
// CHECK-LL: __pp_specialization_type 'int'

// CHECK-LL: %struct.Base1 = type { i32 }
// CHECK-LL: %struct.Base2 = type { i32 }
// CHECK-LL: %struct.Generalization = type { double, i32 }
// CHECK-LL: %struct.__pp_struct_Generalization__Base1 = type { %struct.Generalization, %struct.Base1 }
// CHECK-LL: %struct.__pp_struct_Generalization__Base2 = type { %struct.Generalization, %struct.Base2 }

// CHECK-LL: @__pp_tags_Figure = dso_local global i32 0, align 4
// CHECK-LL: @__pp_tag__pp_struct_Figure__Circle = dso_local global i32 0, align 4
// CHECK-LL: @__pp_tag__pp_struct_Figure__Rectangle = dso_local global i32 0, align 4
// CHECK-LL: @llvm.global_ctors = appending global [2 x { i32, ptr, ptr }] [{ i32, ptr, ptr } { i32 101, ptr @__pp_tag__pp_struct_Figure__Circle, ptr null }, { i32, ptr, ptr } { i32 101, ptr @__pp_tag__pp_struct_Figure__Rectangle, ptr null }]

// CHECK-LL: double @check_gen_b1(ptr noundef byval(%struct.__pp_struct_Generalization__Base1) align 8 %gb)
// CHECK-LL: double @check_gen_b2(ptr noundef byval(%struct.__pp_struct_Generalization__Base2) align 8 %gb)

// CHECK-LL: ; Function Attrs: noinline nounwind optnone uwtable
// CHECK-LL: define dso_local void @__pp_tag__pp_struct_Figure__Circle() #0 {
// CHECK-LL: entry:
// CHECK-LL:   %0 = load i32, ptr @__pp_tags_Figure, align 4
// CHECK-LL:   %inc = add nsw i32 %0, 1
// CHECK-LL:   store i32 %inc, ptr @__pp_tags_Figure, align 4
// CHECK-LL:   %1 = load i32, ptr @__pp_tags_Figure, align 4
// CHECK-LL:   store i32 %1, ptr @__pp_tag__pp_struct_Figure__Circle, align 4
// CHECK-LL:   ret void
// CHECK-LL: }

// CHECK-LL: ; Function Attrs: noinline nounwind optnone uwtable
// CHECK-LL: define dso_local void @__pp_tag__pp_struct_Figure__Rectangle() #0 {
// CHECK-LL: entry:
// CHECK-LL:   %0 = load i32, ptr @__pp_tags_Figure, align 4
// CHECK-LL:   %inc = add nsw i32 %0, 1
// CHECK-LL:   store i32 %inc, ptr @__pp_tags_Figure, align 4
// CHECK-LL:   %1 = load i32, ptr @__pp_tags_Figure, align 4
// CHECK-LL:   store i32 %1, ptr @__pp_tag__pp_struct_Figure__Rectangle, align 4
// CHECK-LL:   ret void
// CHECK-LL: }

// CHECK-AST:     |-RecordDecl {{.*}} struct Base1 definition
// CHECK-AST-NEXT:| `-FieldDecl {{.*}} i 'int'
// CHECK-AST-NEXT:|-RecordDecl {{.*}} struct Base2 definition
// CHECK-AST-NEXT:| `-FieldDecl {{.*}} j 'int'
// CHECK-AST-NEXT:|-RecordDecl {{.*}} struct Generalization definition
// CHECK-AST-NEXT:| |-FieldDecl {{.*}} referenced load 'double'
// CHECK-AST-NEXT:| `-FieldDecl {{.*}} referenced __pp_specialization_type 'int'
// CHECK-AST-NEXT:|-RecordDecl {{.*}} struct __pp_struct_Generalization__Base1 definition
// CHECK-AST-NEXT:| |-FieldDecl {{.*}} referenced __pp_head 'struct Generalization':'struct Generalization'
// CHECK-AST-NEXT:| `-FieldDecl {{.*}} referenced __pp_tail 'struct Base1':'struct Base1'
// CHECK-AST-NEXT:|-RecordDecl {{.*}} struct __pp_struct_Generalization__Base2 definition
// CHECK-AST-NEXT:| |-FieldDecl {{.*}} referenced __pp_head 'struct Generalization':'struct Generalization'
// CHECK-AST-NEXT:| `-FieldDecl {{.*}} referenced __pp_tail 'struct Base2':'struct Base2'

//---------------------------------------

#include <stdio.h>

struct Circle { int r; };
struct Rectangle { int w, h; };
struct Figure { unsigned color; } < struct Circle, struct Rectangle >;

int main() {
    struct Figure<Circle> fc;
    fc<r> = 42;
    fc.color = 0xffffffff;

    struct Figure<Rectangle> fr;
    fr<w> = 5;
    fr<h> = 7;
    fr.color = 0x000000ff;


    // CHECK-RT:      FigCircle: 42 4294967295
    // CHECK-RT-NEXT: FigRect: 5 7 255
    printf("FigCircle: %d %u\n", fc<r>, fc.color);
    printf("FigRect: %d %d %u\n", fr<w>, fr<h>, fr.color);
}

//----------------------------------------

struct Base1 { int i; };
struct Base2 { int j; };
struct Generalization { double load; } < Base1, Base2 >;

int get_b1_field(struct Base1 b) { return b.i; }
int get_b2_field(struct Base2 b) { return b.j; }
double foo (struct Generalization g) { return g.load; }

int get_tag1 (struct __pp_struct_Generalization__Base1 b)
    { return b.__pp_specialization_type; }
int get_tag2 (struct __pp_struct_Generalization__Base2 b)
    { return b.__pp_specialization_type; }

void test_field_access() {
    struct Generalization<Base1> gb;
    gb<i> = 42;
    gb.load = 3.0;
}

// struct Generalization get_gen1 (struct __pp_struct_Generalization__Base1 b) { return b.__pp_head; }
// struct Generalization get_gen2 (struct __pp_struct_Generalization__Base2 b) { return b.__pp_head; }

struct Base1 get_b1 (struct Generalization<Base1> b) { return b<>; }
struct Base2 get_b2 (struct Generalization<Base2> b) { return b<>; }

double check_gen_b1 (struct Generalization<Base1> gb) { return gb.load; }
double check_gen_b2 (struct Generalization<Base2> gb) { return gb.load; }

int get_spec_field1 (struct Generalization<Base1> gb) { return gb<i>; }
int get_spec_field2 (struct Generalization<Base2> gb) { return gb<j>; }

int test_vars() {
    struct Generalization<Base1> gb1;
    gb1<i> = 3;
    struct Generalization<Base2> gb2;
    gb2<j> = 5;
    return get_spec_field1(gb1) + get_spec_field2(gb2);
}

struct Base_gen1 { struct Generalization<Base1> b; };
struct Base_gen2 { struct Generalization<Base2> b; };
// struct Generalization_nested { double additional_field; } < Generalization<Base1>, Generalization<Base2> >;
struct Generalization_extended { double other_field; } < Base_gen1, Base_gen2 >;

void test_nested_vars() {
    // struct Generalization_nested<Generalization<Base1>> gn1;
    // gn1<><i> = 4;
    struct Generalization_extended<Base_gen1> ge1;
    ge1<b><i> = 5;
}
