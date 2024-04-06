# set minimum cmake version
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(evo-demo)               # Название проекта
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type is Debug" FORCE)

set(BUILD_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/../bin")

# Установка переменной со списком исходников
set(SOURCE_FILES
    # headers
    rectangle.h
    triangle.h
    figure.h
    container.h

    #sources
    main.c
    rectangle-in.c
    rectangle-out.c
    triangle-in.c
    triangle-out.c
    figure-in.c
    figure-out.c
    container-constr.c
    container-in.c
    container-out.c
    multimethod.c
    container-mm-out.c
)

add_executable(evo-demo ${SOURCE_FILES})

