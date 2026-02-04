#!/bin/bash
set -e

WORKSPACE="$HOME/risc-v-compiler-learning"
TVM_SRC="$WORKSPACE/tools/tvm"
TVM_BUILD="$TVM_SRC/build"
LLVM_INSTALL="$WORKSPACE/tools/llvm-install"

echo "Building TVM..."
echo ""

# Create build directory
mkdir -p "$TVM_BUILD"
cd "$TVM_BUILD"

# Copy config template
cp ../cmake/config.cmake .

# Modify config to enable LLVM
sed -i "s|# set(USE_LLVM.*|set(USE_LLVM $LLVM_INSTALL/bin/llvm-config)|g" config.cmake

# Configure with CMake
cmake -G Ninja ..

# Build
ninja -j$(nproc)

# Install Python package
cd "$TVM_SRC/python"
pip3 install --user -e .

echo ""
echo "TVM built successfully!"
echo "Testing installation..."
python3 -c "import tvm; print(f'TVM version: {tvm.__version__}')"
