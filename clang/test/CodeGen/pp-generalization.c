// RUN: %clang -S -emit-llvm %s -o - | FileCheck %s -check-prefix=CHECK-DEFAULT
// RUN: %clang -S -Xclang -ast-dump -emit-llvm %s -o - | FileCheck %s -check-prefix=CHECK-AST
// RUN: %clang -S -emit-llvm %s 2>&1 -o - | FileCheck %s -check-prefix=CHECK-LL

// CHECK-DEFAULT: [PPMC] Parse extension
// CHECK-DEFAULT:   Token -> Kind: [identifier], Name:[Base1]
// CHECK-DEFAULT:   Token -> Kind: [comma]
// CHECK-DEFAULT:   Token -> Kind: [identifier], Name:[Base2]
// CHECK-DEFAULT: [PPMC] Finish parse extension

// CHECK-LL: struct Generalization definition
// CHECK-LL: load 'double'
// CHECK-LL: __pp_specialization_type 'int'
// CHECK-LL: %struct.__pp_struct_Generalization__Base1 = type { %struct.Generalization, %struct.Base1 }
// CHECK-LL: %struct.Generalization = type { double, i32 }
// CHECK-LL: %struct.Base1 = type { i32 }
// CHECK-LL: %struct.__pp_struct_Generalization__Base2 = type { %struct.Generalization, %struct.Base2 }
// CHECK-LL: %struct.Base2 = type { i32 }
// CHECK-LL: double @check_gen(ptr noundef byval(%struct.__pp_struct_Generalization__Base1) align 8 %gb)

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

struct Base1 { int i; };
struct Base2 { int j; };
struct Generalization { double load; } < Base1, Base2 >;

double check_gen (struct Generalization<Base1> gb) { return gb.__pp_head.load; }
double foo (struct Generalization g) { return g.load; }

int get_tag1 (struct __pp_struct_Generalization__Base1 b)
    { return b.__pp_head.__pp_specialization_type; }
int get_tag2 (struct __pp_struct_Generalization__Base2 b)
    { return b.__pp_head.__pp_specialization_type; }
struct Generalization get_gen1 (struct __pp_struct_Generalization__Base1 b) { return b.__pp_head; }
struct Generalization get_gen2 (struct __pp_struct_Generalization__Base2 b) { return b.__pp_head; }

struct Base1 get_b1 (struct __pp_struct_Generalization__Base1 b) { return b.__pp_tail; }
struct Base2 get_b2 (struct __pp_struct_Generalization__Base2 b) { return b.__pp_tail; }
