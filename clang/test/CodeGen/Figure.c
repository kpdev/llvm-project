// RUN: %clang -S -emit-llvm %s -o - | FileCheck %s -check-prefix=CHECK-LOGS
// RUN: %clang -S -emit-llvm %s 2>&1 -o - | FileCheck %s -check-prefix=CHECK-MM
// RUN~: %clang -S -Xclang -ast-dump -emit-llvm %s -o - | FileCheck %s -check-prefix=CHECK-AST
// RUN: %clang -S -emit-llvm %s 2>&1 -o - | FileCheck %s -check-prefix=CHECK-IR
// RUN: %clang %s -o %S/a.out && %S/a.out | FileCheck %s -check-prefix=CHECK-RT && rm %S/a.out

// CHECK-LOGS:      [PPMC] Parse extension
// CHECK-LOGS-NEXT:   Token -> Kind: [struct]
// CHECK-LOGS-NEXT:   Token -> Kind: [identifier], Name:[Circle]
// CHECK-LOGS-NEXT:   Token -> Kind: [semi]
// CHECK-LOGS-NEXT:   Token -> Kind: [struct]
// CHECK-LOGS-NEXT:   Token -> Kind: [identifier], Name:[Rectangle]
// CHECK-LOGS-NEXT:   Token -> Kind: [semi]
// CHECK-LOGS-NEXT: [PPMC] Finish parse extension

// CHECK-LL: struct Generalization definition
// CHECK-LL: load 'double'
// CHECK-LL: __pp_specialization_type 'int'

// CHECK-LL: %struct.Base1 = type { i32 }
// CHECK-LL: %struct.Base2 = type { i32 }
// CHECK-LL: %struct.Generalization = type { double, i32 }
// CHECK-LL: %struct.__pp_struct_Generalization__Base1 = type { %struct.Generalization, %struct.Base1 }
// CHECK-LL: %struct.__pp_struct_Generalization__Base2 = type { %struct.Generalization, %struct.Base2 }

// CHECK-LL: @__pp_tags_Figure = dso_local global i32 0, align 4
// CHECK-LL: @__pp_tag___pp_struct_Figure__Circle = dso_local global i32 0, align 4
// CHECK-LL: @__pp_tag___pp_struct_Figure__Rectangle = dso_local global i32 0, align 4
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
// CHECK-AST-NEXT:|-FunctionDecl {{.*}} __pp_ctor__pp_struct_Generalization__Base1 'void ()'
// CHECK-AST-NEXT:| `-CompoundStmt {{.*}}
// CHECK-AST-NEXT:|-RecordDecl {{.*}} struct __pp_struct_Generalization__Base2 definition
// CHECK-AST-NEXT:| |-FieldDecl {{.*}} referenced __pp_head 'struct Generalization':'struct Generalization'
// CHECK-AST-NEXT:| `-FieldDecl {{.*}} referenced __pp_tail 'struct Base2':'struct Base2'
// CHECK-AST-NEXT:|-FunctionDecl {{.*}} __pp_ctor__pp_struct_Generalization__Base2 'void ()'
// CHECK-AST-NEXT:| `-CompoundStmt {{.*}}


//---------------------------------------

// typedef void(*ftype)(int);
// ftype* my_ptr;

#include <stdio.h>

struct Circle { int r; };
struct Rectangle { int w, h; };
struct Figure { unsigned color; } < struct Circle; struct Rectangle; >;

struct Triangle { int a, b, c; };
struct Figure + < struct Triangle; >;

struct BaseObject { int a; }<>;
struct NewObject { int b; };
struct BaseObject + < struct NewObject; >;

// CHECK-MM: TypedefDecl {{.*}} __pp_mmtype__pp_mm_PrintFigure 'void (*)(struct Figure *)'
void PrintFigure<struct Figure* f>();
// CHECK-MM: TypedefDecl {{.*}} __pp_mmtype__pp_mm_PrintFigureWithArg 'void (*)(struct Figure *, unsigned int)'
void PrintFigureWithArg<struct Figure* f>(unsigned i);
// CHECK-MM: TypedefDecl {{.*}} __pp_mmtype__pp_mm_MultiMethod 'void (*)(struct Figure *, struct Figure *)'
void MultiMethod<struct Figure* f1, struct Figure* f2>();
// CHECK-MM: TypedefDecl {{.*}} __pp_mmtype__pp_mm_MultiMethodWithArgs 'void (*)(struct Figure *, struct Figure *, unsigned int, unsigned int)'
void MultiMethodWithArgs<struct Figure* f1, struct Figure* f2>(unsigned c1, unsigned c2);

// CHECK-IR:      @__pp_mminitarr__pp_mm_PrintFigure = linkonce_odr dso_local global ptr null, align 8
// CHECK-IR-NEXT: @__pp_mminitarr__pp_mm_PrintFigureWithArg = linkonce_odr dso_local global ptr null, align 8
// CHECK-IR-NEXT: @__pp_mminitarr__pp_mm_MultiMethod = linkonce_odr dso_local global ptr null, align 8
// CHECK-IR-NEXT: @__pp_mminitarr__pp_mm_MultiMethodWithArgs = linkonce_odr dso_local global ptr null, align 8

// CHECK-IR: @llvm.global_ctors =
// CHECK-IR: { i32 102, ptr @__pp_alloc__pp_mm_PrintFigure, ptr null },
// CHECK-IR: { i32 102, ptr @__pp_alloc__pp_mm_PrintFigureWithArg, ptr null },
// CHECK-IR: { i32 102, ptr @__pp_alloc__pp_mm_MultiMethod, ptr null },
// CHECK-IR: { i32 102, ptr @__pp_alloc__pp_mm_MultiMethodWithArgs, ptr null }

// Allocate arrays and generate default handlers
// CHECK-IR:      define void @__pp_alloc__pp_mm_PrintFigure(ptr %0) {
// CHECK-IR-NEXT: entry:
// CHECK-IR-NEXT:   %1 = load i32, ptr @__pp_tags_Figure, align 4
// CHECK-IR-NEXT:   %2 = sext i32 %1 to i64
// CHECK-IR-NEXT:   %3 = mul i64 8, %2
// CHECK-IR-NEXT:   %call_malloc = call ptr @malloc(i64 noundef %3) #2
// CHECK-IR-NEXT:   store ptr %call_malloc, ptr @__pp_mminitarr__pp_mm_PrintFigure, align 8
// CHECK-IR-NEXT:   ret void
// CHECK-IR-NEXT: }

// CHECK-IR: @__pp_default__pp_mm_PrintFigure
// CHECK-IR: @__pp_default__pp_mm_PrintFigureWithArg

// CHECK-IR:      define void @__pp_alloc__pp_mm_MultiMethod(ptr %0, ptr %1) {
// CHECK-IR-NEXT: entry:
// CHECK-IR-NEXT:   %2 = load i32, ptr @__pp_tags_Figure, align 4
// CHECK-IR-NEXT:   %3 = sext i32 %2 to i64
// CHECK-IR-NEXT:   %4 = mul i64 8, %3
// CHECK-IR-NEXT:   %5 = load i32, ptr @__pp_tags_Figure, align 4
// CHECK-IR-NEXT:   %6 = sext i32 %5 to i64
// CHECK-IR-NEXT:   %7 = mul i64 %4, %6
// CHECK-IR-NEXT:   %call_malloc = call ptr @malloc(i64 noundef %7) #2
// CHECK-IR-NEXT:   store ptr %call_malloc, ptr @__pp_mminitarr__pp_mm_MultiMethod, align 8
// CHECK-IR-NEXT:   ret void
// CHECK-IR-NEXT: }

// CHECK-IR: @__pp_default__pp_mm_MultiMethod
// CHECK-IR: @__pp_default__pp_mm_MultiMethodWithArgs
void test_type_tag(struct Figure* f)
{
    printf("[foo_test] f->__pp_specialization_type = %d\n", f->__pp_specialization_type);
}

int main() {
    struct Figure<struct Circle> fc;
    fc<r> = 42;
    fc.color = 0xffffffff;

    // CHECK-RT:      [foo_test] f->__pp_specialization_type = 1
    test_type_tag(&fc);

    struct Figure<struct Rectangle> fr;
    fr<w> = 5;
    fr<h> = 7;
    fr.color = 0x000000ff;

    // CHECK-RT:      [foo_test] f->__pp_specialization_type = 2
    test_type_tag(&fr);

    struct Figure<struct Triangle> ft;
    ft<a> = 1;
    ft<b> = 2;
    ft<c> = 3;
    ft.color = 0x00000001;

    // CHECK-RT:      FigCircle: 42 4294967295
    // CHECK-RT-NEXT: FigRect: 5 7 255
    // CHECK-RT-NEXT: FigTriangle: 1 2 3 1
    printf("FigCircle: %d %u\n", fc<r>, fc.color);
    printf("FigRect: %d %d %u\n", fr<w>, fr<h>, fr.color);
    printf("FigTriangle: %d %d %d %u\n", ft<a>, ft<b>, ft<c>, ft.color);

    // CHECK-IR:       call void @__pp_mm_PrintFigure(ptr noundef %fc)
    // CHECK-IR-NEXT:  call void @__pp_mm_PrintFigureWithArg(ptr noundef %fc, i32 noundef 42)
    // CHECK-IR-NEXT:  call void @__pp_mm_MultiMethod(ptr noundef %fc, ptr noundef %fr)
    // CHECK-IR-NEXT:  call void @__pp_mm_MultiMethodWithArgs(ptr noundef %fc, ptr noundef %fr, i32 noundef 7, i32 noundef 8)
    PrintFigure<&fc>();
    PrintFigureWithArg<&fc>(42);
    MultiMethod<&fc, &fr>();
    MultiMethodWithArgs<&fc, &fr>(7, 8);

    // CHECK-RT-NEXT: Figure tags: 3
    // CHECK-RT-NEXT: Circle tag: 1
    // CHECK-RT-NEXT: Rectangle tag: 2
    // CHECK-RT-NEXT: Triangle tag: 3
    printf("Figure tags: %d\n", __pp_tags_Figure);
    printf("Circle tag: %d\n", __pp_tag___pp_struct_Figure__Circle);
    printf("Rectangle tag: %d\n", __pp_tag___pp_struct_Figure__Rectangle);
    printf("Triangle tag: %d\n", __pp_tag___pp_struct_Figure__Triangle);

    // CHECK-RT-NEXT: fc.__pp_specialization_type = 1
    // CHECK-RT-NEXT: fr.__pp_specialization_type = 2
    // CHECK-RT-NEXT: ft.__pp_specialization_type = 3
    printf("fc.__pp_specialization_type = %d\n", fc.__pp_specialization_type);
    printf("fr.__pp_specialization_type = %d\n", fr.__pp_specialization_type);
    printf("ft.__pp_specialization_type = %d\n", ft.__pp_specialization_type);

    struct Figure<struct Circle> fc2;
    struct Figure<struct Rectangle> fr2;
    struct Figure<struct Triangle> ft2;

    // CHECK-RT-NEXT: fc2.__pp_specialization_type = 1
    // CHECK-RT-NEXT: fr2.__pp_specialization_type = 2
    // CHECK-RT-NEXT: ft2.__pp_specialization_type = 3
    printf("fc2.__pp_specialization_type = %d\n", fc2.__pp_specialization_type);
    printf("fr2.__pp_specialization_type = %d\n", fr2.__pp_specialization_type);
    printf("ft2.__pp_specialization_type = %d\n", ft2.__pp_specialization_type);

    struct BaseObject<struct NewObject> obj;
    obj.a = 101;
    obj<b> = 102;
    // CHECK-RT-NEXT: BaseObject<NewObject>: 101 102
    printf("BaseObject<NewObject>: %d %d\n", obj.a, obj<b>);
}
