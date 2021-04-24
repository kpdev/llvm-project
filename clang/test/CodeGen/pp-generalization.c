// RUN: %clang -S -emit-llvm -o - %s | FileCheck %s
// CHECK: [PPMC] Parse extension
// CHECK:   Token -> Kind: [identifier], Name:[Base1]
// CHECK:   Token -> Kind: [comma]
// CHECK:   Token -> Kind: [identifier], Name:[Base2]
// CHECK: [PPMC] Finish parse extension

struct Base1 { int i; };
struct Base2 { int j; };
struct Generalization {} [ Base1, Base2 ];
