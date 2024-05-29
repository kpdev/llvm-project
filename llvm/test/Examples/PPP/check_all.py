#!/usr/bin/python3

import os

cur_dir = os.getcwd()
bin_dir = "/build/bin/"
path_to_clang = cur_dir + bin_dir + "clang-15"
path_to_fcheck = cur_dir + bin_dir + "FileCheck"

if not os.path.isfile(path_to_clang):
    print("[ERROR] Clang not found: " + path_to_clang)
    exit()

# TODO: Refactoring tests run

cd_to_evol_str = "cd ./llvm/test/Examples/PPP/evolution/"
cd_to_pattenrs_str = "cd ./llvm/test/Examples/PPP/patterns/"
cd_to_misc_str = "cd ./llvm/test/Examples/PPP/misc/"

run_tools_str = "/build && cmake "\
"-DCMAKE_C_COMPILER=" + path_to_clang + " "\
"--fresh -S ../ -B . "\
"&& make && ../bin/evo-demo ../data/input.txt ../data/output.txt "\
"&& rm -rf ../build/* && rm -rf ../bin/*"

run_tools_patterns_str = "/build && cmake "\
"-DCMAKE_C_COMPILER=" + path_to_clang + " "\
"--fresh -S ../ -B . "\
"&& make && ../bin/factory-method ../data/input.txt ../data/output.txt "\
"&& rm -rf ../build/* && rm -rf ../bin/*"

run_container_str = "/build && cmake "\
"-DCMAKE_C_COMPILER=" + path_to_clang + " "\
"--fresh -S ../ -B . "\
"&& make && ../bin/container | "\
+ path_to_fcheck + " ../output_to_compare.txt "\
"&& rm -rf ../build/* && rm -rf ../bin/*"

command_list = [
    "./build/bin/llvm-lit "
        "clang/test/CodeGen/Figure.c "
        "-v"
    ,
    "./build/bin/llvm-lit "
        "clang/test/CodeGen/pp-linked.c "
        "-v"
    ,
    "./build/bin/llvm-lit "
        "clang/test/CodeGen/pp-tagged-generalization.c "
        "-v"
    ,
    "./build/bin/llvm-lit "
        "clang/test/CodeGen/pp-tagged-create_spec.c "
        "-v"
    ,
    "./build/bin/llvm-lit "
        "clang/test/CodeGen/pp-mm.c "
        "-v"
    ,
    "./build/bin/llvm-lit "
        "clang/test/CodeGen/pp-mm-tag.c "
        "-v"
    ,
    cd_to_evol_str
        + "00-start/ppp/00-ppp-type-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "00-start/ppp/00-ppp-tag-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "01-new-spec/ppp/01-ppp-type-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "01-new-spec/ppp/01-ppp-tag-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "02-new-func/ppp/02-ppp-type-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "02-new-func/ppp/02-ppp-tag-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "03-new-field/ppp/03-ppp-type-dyn-decorator-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "03-new-field/ppp/03-ppp-tag-dyn-decorator-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "03-new-field/ppp/03-ppp-type-gen-decorator-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "03-new-field/ppp/03-ppp-tag-gen-decorator-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "04-rectangles-only-out/ppp/04-ppp-type-rect-only-out-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "04-rectangles-only-out/ppp/04-ppp-tag-rect-only-out-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "04-rectangles-only-out/ppp/04-ppp-type-is-rect-only-out-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "04-rectangles-only-out/ppp/04-ppp-tag-is-rect-only-out-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "05-multimethod/ppp/05-ppp-type-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "05-multimethod/ppp/05-ppp-tag-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "06-multimethod-new-spec/ppp/06-ppp-type-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "06-multimethod-new-spec/ppp/06-ppp-tag-c"
        + run_tools_str
    ,
    cd_to_pattenrs_str
        + "factory-method-p2c"
        + run_tools_patterns_str
    ,
    cd_to_misc_str
        + "container-tag"
        + run_container_str
]

idx = 1
for cmd in command_list:
    print("\n===========")
    str_test = "[TEST][" + str(idx) + "]"
    idx = idx + 1
    print("***", str_test, "Run command: ", cmd, " ***")
    retval = os.system(cmd)
    if retval != 0:
        print("***", str_test, "Error with: ", cmd)
        break
    else:
        print("***", str_test, "OK ***")
