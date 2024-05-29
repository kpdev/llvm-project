# set minimum cmake version
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(ring-list)               # Название проекта
SET(CMAKE_C_COMPILER ppclang)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type is Debug" FORCE)

set(BUILD_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/../bin")

# Установка переменной со списком исходников
set(SOURCE_FILES
    # headers
    value.h
    ring-list.h

    #sources
    main.c

    value.c
    ring-list.c
)

add_executable(ring-list ${SOURCE_FILES})

