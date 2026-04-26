// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -emit-llvm -o - %s | FileCheck %s

// Test that __pp_gvinit__ functions have LinkOnceODRLinkage when using PP-EXT global variable initialization

// Define a generalized structure
struct Container {} < Int, Float, Double : void >;

// Define global variables that are specializations
struct Container.Int global_int;
struct Container.Float global_float;
struct Container.Double global_double;

// CHECK: define {{.*}}linkonce_odr{{.*}} @__pp_gvinit__global_int()
// CHECK: define {{.*}}linkonce_odr{{.*}} @__pp_gvinit__global_float()
// CHECK: define {{.*}}linkonce_odr{{.*}} @__pp_gvinit__global_double()