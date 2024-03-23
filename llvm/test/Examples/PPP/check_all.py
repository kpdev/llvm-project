#!/usr/bin/python3

import os

cur_dir = os.getcwd()
path_to_clang = cur_dir + "/build/bin/clang-15"

if not os.path.isfile(path_to_clang):
    print("[ERROR] Clang not found: " + path_to_clang)
    exit()

cd_to_evol_str = "cd ./llvm/test/Examples/PPP/evolution/"
run_tools_str = "/build && cmake "\
"-DCMAKE_C_COMPILER=" + path_to_clang + " "\
"--fresh -S ../ -B . "\
"&& make && ../bin/evo-demo ../data/input.txt ../data/output.txt"

command_list = [
    "./build/bin/llvm-lit "
        "clang/test/CodeGen/Figure.c "
        "-v"
    ,
    "./build/bin/llvm-lit "
        "clang/test/CodeGen/pp-linked.c "
        "-v"
    ,
    cd_to_evol_str
        + "00-start/ppp/00-ppp-type-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "01-new-spec/ppp/01-ppp-type-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "02-new-func/ppp/02-ppp-type-c"
        + run_tools_str
    ,
    cd_to_evol_str
        + "03-new-field/ppp/03-ppp-type-dyn-decorator-c"
        + run_tools_str
]

for cmd in command_list:
    print("\n===========")
    print("*** [TEST] Run command: ", cmd, " ***")
    retval = os.system(cmd)
    if retval != 0:
        print("*** [TEST] Error with: ", cmd)
        break
    else:
        print("*** [TEST] OK ***")
