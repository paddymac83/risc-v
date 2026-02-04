#!/bin/bash
set -e

WORKSPACE="$HOME/risc-v-compiler-learning"
LLVM_SRC="$WORKSPACE/tools/llvm"
LLVM_BUILD="$LLVM_SRC/build"
LLVM_INSTALL="$WORKSPACE/tools/llvm-install"

echo "Building LLVM..."
echo "This will take 1-3 hours depending on your machine..."
echo ""

# Create build directory
mkdir -p "$LLVM_BUILD"
cd "$LLVM_BUILD"

# Configure with CMake
cmake -G Ninja ../llvm \
    -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_ENABLE_PROJECTS="clang;lld" \
    -DLLVM_TARGETS_TO_BUILD="X86;RISCV" \
    -DCMAKE_INSTALL_PREFIX="$LLVM_INSTALL" \
    -DLLVM_ENABLE_ASSERTIONS=ON \
    -DLLVM_OPTIMIZED_TABLEGEN=ON

# Build (use all cores)
ninja -j$(nproc)

# Install
ninja install

echo ""
echo "LLVM built and installed successfully!"
echo "Location: $LLVM_INSTALL"
