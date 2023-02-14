// RUN: %clang -S -emit-llvm %s -o - | FileCheck %s -check-prefix=CHECK-DEFAULT
// RUN: %clang -S -emit-llvm %s 2>&1 -o - | FileCheck %s -check-prefix=CHECK-LL
// CHECK-DEFAULT: [PPMC] Parse extension
// CHECK-DEFAULT:   Token -> Kind: [identifier], Name:[Base1]
// CHECK-DEFAULT:   Token -> Kind: [comma]
// CHECK-DEFAULT:   Token -> Kind: [identifier], Name:[Base2]
// CHECK-DEFAULT: [PPMC] Finish parse extension

// CHECK-LL: struct Generalization definition
// CHECK-LL: load 'double'
// CHECK-LL: __pp_specialization_type 'int'
// CHECK-LL: %struct.Generalization = type { double, i32 }
// CHECK-LL: %struct.__pp_struct_Generalization__Base1 = type { i32 }
// CHECK-LL: %struct.__pp_struct_Generalization__Base2 = type { i32 }

struct Base1 { int i; };
struct Base2 { int j; };
struct Generalization { double load; } [ Base1, Base2 ];

double foo (struct Generalization g) { return g.load; }

int bar1 (struct __pp_struct_Generalization__Base1 b) { return b.m_some_inner_field; }
int bar2 (struct __pp_struct_Generalization__Base2 b) { return b.m_some_inner_field; }