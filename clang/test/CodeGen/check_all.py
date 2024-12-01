#!/usr/bin/python3

import os

cur_dir = os.getcwd()
bin_dir = "/build/bin/"
path_to_clang = cur_dir + bin_dir + "clang-15"

if not os.path.isfile(path_to_clang):
    print("[ERROR] Clang not found: " + path_to_clang)
    exit()

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
    "./build/bin/llvm-lit "
        "clang/test/CodeGen/pp-spec-ptr.c "
        "-v"
    ,
    "./build/bin/llvm-lit "
        "clang/test/CodeGen/pp-spec-base-types.c "
        "-v"
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
