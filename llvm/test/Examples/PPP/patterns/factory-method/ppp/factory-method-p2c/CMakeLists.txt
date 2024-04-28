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
    figure.h
    figure-container.h

    simple-creator.h

    #sources
    main.c

    simple-rectangle.c
    simple-triangle.c
    figure.c
    figure-container.c
    input-figures.c

    simple-creator.c

)

add_executable(evo-demo ${SOURCE_FILES})

