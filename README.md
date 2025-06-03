
Проект компилятора языка С с поддержкой процедурно-параметрического расширения

Описание процедурно-параметрического подхода: https://www.mais-journal.ru/jour/article/view/1766

Проект с тестами сравнения производительности данного подхода с другими: https://gitverse.ru/kpdev/multimethod-benchmarks

Проект с описанием паттернов программирования для процедурно-параметрического подхода: https://github.com/kreofil/evo-situations/

-----------------------------------

# The LLVM Compiler Infrastructure

[![OpenSSF Scorecard](https://api.securityscorecards.dev/projects/github.com/llvm/llvm-project/badge)](https://securityscorecards.dev/viewer/?uri=github.com/llvm/llvm-project)
[![OpenSSF Best Practices](https://www.bestpractices.dev/projects/8273/badge)](https://www.bestpractices.dev/projects/8273)
[![libc++](https://github.com/llvm/llvm-project/actions/workflows/libcxx-build-and-test.yaml/badge.svg?branch=main&event=schedule)](https://github.com/llvm/llvm-project/actions/workflows/libcxx-build-and-test.yaml?query=event%3Aschedule)

Welcome to the LLVM project!

This repository contains the source code for LLVM, a toolkit for the
construction of highly optimized compilers, optimizers, and run-time
environments.

The LLVM project has multiple components. The core of the project is
itself called "LLVM". This contains all of the tools, libraries, and header
files needed to process intermediate representations and convert them into
object files. Tools include an assembler, disassembler, bitcode analyzer, and
bitcode optimizer.

C-like languages use the [Clang](https://clang.llvm.org/) frontend. This
component compiles C, C++, Objective-C, and Objective-C++ code into LLVM bitcode
-- and from there into object files, using LLVM.

Other components include:
the [libc++ C++ standard library](https://libcxx.llvm.org),
the [LLD linker](https://lld.llvm.org), and more.

## Getting the Source Code and Building LLVM

Consult the
[Getting Started with LLVM](https://llvm.org/docs/GettingStarted.html#getting-the-source-code-and-building-llvm)
page for information on building and running LLVM.

For information on how to contribute to the LLVM project, please take a look at
the [Contributing to LLVM](https://llvm.org/docs/Contributing.html) guide.

## Getting in touch

Join the [LLVM Discourse forums](https://discourse.llvm.org/), [Discord
chat](https://discord.gg/xS7Z362),
[LLVM Office Hours](https://llvm.org/docs/GettingInvolved.html#office-hours) or
[Regular sync-ups](https://llvm.org/docs/GettingInvolved.html#online-sync-ups).

The LLVM project has adopted a [code of conduct](https://llvm.org/docs/CodeOfConduct.html) for
participants to all modes of communication within the project.

## Build Procedural-Parametric Extension

It is not differs from mainstream llvm build.
But you can use the recommended command line for debug build
```
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DBUILD_SHARED_LIBS:STRING=ON "-DLLVM_TARGETS_TO_BUILD:STRING=X86" -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE "-DLLVM_ENABLE_PROJECTS:STRING=clang" -DLLVM_OPTIMIZED_TABLEGEN:STRING=ON -DLLVM_CCACHE_BUILD:STRING=ON -DCMAKE_C_COMPILER:FILEPATH=<path-to-c-compiler> -DCMAKE_CXX_COMPILER:FILEPATH=<path-to-cpp-compiler> -S<source-path> -B<build-path> -G Ninja
```
After that it is needed to build clang:
```
cmake --build <build-path> --config Debug --target all --
```
And check if it is actually works:
```
<build-path>/bin/llvm-lit <source-path>/clang/test/CodeGen/pp-linked.c
```
