// RUN: %clang -S -emit-llvm %s -o - | FileCheck %s -check-prefix=CHECK-DEFAULT
// RUN: %clang -S -emit-llvm %s 2>&1 -o - | FileCheck %s -check-prefix=CHECK-LL
// CHECK-DEFAULT: [PPMC] Parse extension
// CHECK-DEFAULT:   Token -> Kind: [identifier], Name:[Base1]
// CHECK-DEFAULT:   Token -> Kind: [comma]
// CHECK-DEFAULT:   Token -> Kind: [identifier], Name:[Base2]
// CHECK-DEFAULT: [PPMC] Finish parse extension

// CHECK-LL: struct Generalization definition
// CHECK-LL: k 'int'
// CHECK-LL: pp_tmp_field_0 'int'
// CHECK-LL: %struct.Generalization = type { i32, i32 }

struct Base1 { int i; };
struct Base2 { int j; };
struct Generalization { int k; } [ Base1, Base2 ];

int foo (struct Generalization g) { return g.k; }
