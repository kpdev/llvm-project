# set minimum cmake version
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(container)               # Название проекта
SET(CMAKE_C_COMPILER ppclang)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type is Debug" FORCE)

set(BUILD_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/../bin")

# Установка переменной со списком исходников
set(SOURCE_FILES
    # headers
    value.h
    array.h
    ring-list.h
    container.h

    #sources
    main.c

    value.c
    array.c
    ring-list.c
    container.c
    container-array.c
    container-ring-list.c
)

add_executable(container ${SOURCE_FILES})

