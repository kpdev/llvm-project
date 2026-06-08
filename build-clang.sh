#!/bin/bash
set -e

# Скрипт сборки Clang/LLVM с процедурно-параметрическим расширением
# Использование:
#   ./build-clang.sh
#
# Переменные окружения (опционально):
#   BUILD_DIR       - Директория сборки (по умолчанию: build)
#   SOURCE_DIR      - Директория исходников LLVM (по умолчанию: текущая)
#   BUILD_TYPE      - Тип сборки: Debug/Release (по умолчанию: Debug)
#   COMPILE_THREADS - Количество потоков компиляции (по умолчанию: 4)
#   CCACHE          - Использовать ccache: ON/OFF (по умолчанию: ON)
#
# После сборки:
#   cd $BUILD_DIR && ninja
#   ninja install
#   ./bin/clang --version
#
# Для запуска всех PP тестов:
#   $SOURCE_DIR/clang/test/CodeGen/check_all.py
# Для запуска отдельных тестов
#   $BUILD_DIR/bin/llvm-lit clang/test/CodeGen/pp-base.c

# Параметры сборки
BUILD_DIR="${BUILD_DIR:-build}"
SOURCE_DIR="${SOURCE_DIR:-.}"
BUILD_TYPE="${BUILD_TYPE:-Debug}"
COMPILE_THREADS="${COMPILE_THREADS:-4}"
CCACHE="${CCACHE:-ON}"

# Путь к cmake
CMAKE_CMD="cmake"

echo "=== Clang/LLVM build script ==="
echo "Source dir: ${SOURCE_DIR}"
echo "Build dir: ${BUILD_DIR}"
echo "Build type: ${BUILD_TYPE}"
echo "Compile threads: ${COMPILE_THREADS}"
echo "BUILD_SHARED_LIBS: ON"
echo "CCACHE: ${CCACHE}"
echo ""

# Преобразуем SOURCE_DIR в абсолютный путь, если он относительный
if [[ "${SOURCE_DIR}" != /* ]]; then
    SOURCE_DIR="$(cd "${SOURCE_DIR}" && pwd)"
fi

echo "Absolute source dir: ${SOURCE_DIR}"

# Полный путь к build dir
BUILD_DIR_ABS="${BUILD_DIR}"
if [[ "${BUILD_DIR}" != /* ]]; then
    BUILD_DIR_ABS="$(cd "${SOURCE_DIR}/.." && pwd)/${BUILD_DIR}"
fi
BUILD_DIR_ABS="${SOURCE_DIR}/../${BUILD_DIR}"
if [[ "${BUILD_DIR}" != /* ]]; then
    BUILD_DIR_ABS="$(pwd)/${BUILD_DIR}"
fi

# Создание директории сборки
mkdir -p "${BUILD_DIR_ABS}"

# Запуск cmake для LLVM/Clang
cd "${BUILD_DIR_ABS}"

${CMAKE_CMD} -G "Ninja" \
    -S "${SOURCE_DIR}/llvm" \
    -B "${BUILD_DIR_ABS}" \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
    -DBUILD_SHARED_LIBS=ON \
    -DLLVM_TARGETS_TO_BUILD="X86" \
    -DLLVM_ENABLE_PROJECTS="clang" \
    -DCMAKE_INSTALL_PREFIX="${BUILD_DIR_ABS}/install" \
    -DCMAKE_C_COMPILER=gcc \
    -DCMAKE_CXX_COMPILER=g++ \
    -DLLVM_ENABLE_ASSERTIONS=ON \
    -DLLVM_OPTIMIZED_TABLEGEN=ON \
    -DLLVM_PARALLEL_COMPILE_JOBS="${COMPILE_THREADS}" \
    -DLLVM_PARALLEL_LINK_JOBS=1 \
    -DLLVM_FORCE_VC_REPOSITORY=https://gitverse.ru/kpdev/llvm-project \
    -DLLVM_CCACHE_BUILD="${CCACHE}"

    # -DLLVM_ENABLE_ZLIB=ON \
    # -DLLVM_ENABLE_ZSTD=ON \
    # -DLLVM_ENABLE_FFI=ON \
    # -DLLVM_ENABLE_LIBXML2=ON \

echo ""
echo "=== CMake configuration complete ==="
echo "To build: cd ${BUILD_DIR_ABS} && ninja"
echo "To install: ninja install"
echo "To clean: ninja clean"
