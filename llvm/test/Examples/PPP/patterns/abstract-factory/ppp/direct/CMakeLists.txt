# set minimum cmake version
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(evo-demo)               # Название проекта
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type is Debug" FORCE)

set(BUILD_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/../bin")

# Установка переменной со списком исходников
set(SOURCE_FILES
    # headers
    simple-rectangle.h
    simple-triangle.h

    coord-point.h
    coord-rectangle.h
    coord-triangle.h

    rectangle.h
    triangle.h
    figure.h
    container.h

    figure-factory.h
    simple-figure-factory.h
    coord-figure-factory.h

    #sources
    main.c

    simple-rectangle-inout.c
    simple-triangle-inout.c

    coord-rectangle-inout.c
    coord-triangle-inout.c

    figure-in.c
    figure-out.c
    container-constr.c
    container-in.c
    container-out.c

    simple-figure-factory.cpp
    coord-figure-factory.cpp
)

add_executable(evo-demo ${SOURCE_FILES})

