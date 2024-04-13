// RUN: %clang -S -emit-llvm %s 2>&1 -o - | FileCheck %s -check-prefix=CHECK-IR



struct Circle { int c; };
struct Figure { int f; } < t0 : Circle; >;

void foo()
{
// CHECK-IR: %__pp_head = getelementptr inbounds %struct.__pp_struct_Figure__t0, ptr %ttt, i32 0, i32 0
// CHECK-IR: %__pp_specialization_type = getelementptr inbounds %struct.Figure, ptr %__pp_head, i32 0, i32 1
// CHECK-IR: store i32 %0, ptr %__pp_specialization_type, align 4
    struct Figure<t0> ttt;
}
