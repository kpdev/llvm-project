#!/bin/bash

docker run --rm -it \
    -v /home/as/projects/llvm-project:/src:ro \
    -v /home/as/projects/llvm-build:/build \
    -v /home/as/projects/llvm-install:/install \
    --name llvm-build \
    --entrypoint bash \
    llvm-builder
