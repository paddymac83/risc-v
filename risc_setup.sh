#!/bin/bash
# RISC-V Compiler Learning Environment Setup Script
# This script sets up the complete development environment for learning AI compiler engineering

set -e  # Exit on error

echo "=========================================="
echo "RISC-V Compiler Learning Environment Setup"
echo "=========================================="
echo ""

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Workspace directory
WORKSPACE="$HOME/risc-v-compiler-learning"

# Function to print colored output
print_status() {
    echo -e "${GREEN}[✓]${NC} $1"
}

print_error() {
    echo -e "${RED}[✗]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[!]${NC} $1"
}

# Check if running on Linux
if [[ "$OSTYPE" != "linux-gnu"* ]]; then
    print_error "This script is designed for Linux (Ubuntu/Debian). Please adapt for your OS."
    exit 1
fi

# echo "Step 1: System Updates and Basic Tools"
# echo "========================================"
# sudo apt update
# sudo apt upgrade -y
# print_status "System updated"

# echo ""
# echo "Step 2: Installing Build Essentials"
# echo "====================================="
# sudo apt install -y \
#     build-essential \
#     git \
#     cmake \
#     ninja-build \
#     python3 \
#     python3-pip \
#     python3-dev \
#     python3-setuptools \
#     wget \
#     curl \
#     vim \
#     htop \
#     tmux \
#     tree

# print_status "Build tools installed"

# echo ""
# echo "Step 3: Installing LLVM 18"
# echo "=========================="
# # Download LLVM install script
# wget -O llvm-install.sh https://apt.llvm.org/llvm.sh
# chmod +x llvm-install.sh

# # Install LLVM 18
# sudo ./llvm-install.sh 18

# # Install LLVM development packages
# sudo apt install -y \
#     llvm-18 \
#     llvm-18-dev \
#     llvm-18-tools \
#     libllvm18 \
#     clang-18 \
#     clang-tools-18 \
#     libclang-18-dev \
#     lld-18

# # Set up alternatives
# sudo update-alternatives --install /usr/bin/llvm-config llvm-config /usr/bin/llvm-config-18 100
# sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-18 100
# sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-18 100

# print_status "LLVM 18 installed"

# echo ""
# echo "Step 4: Installing RISC-V Toolchain"
# echo "===================================="
# sudo apt install -y \
#     gcc-riscv64-linux-gnu \
#     g++-riscv64-linux-gnu \
#     binutils-riscv64-linux-gnu

# print_status "RISC-V toolchain installed"

# echo ""
# echo "Step 5: Installing QEMU"
# echo "======================="
# sudo apt install -y \
#     qemu-user \
#     qemu-system-misc \
#     qemu-utils \
#     qemu-system-riscv64

# print_status "QEMU installed"

# echo ""
# echo "Step 6: Installing Python Packages"
# echo "==================================="
# pip3 install --user --upgrade pip
# pip3 install --user \
#     numpy \
#     scipy \
#     matplotlib \
#     tornado \
#     psutil \
#     decorator \
#     attrs \
#     pytest \
#     jupyter \
#     notebook

# print_status "Python packages installed"

echo ""
echo "Step 7: Creating Workspace Structure"
echo "====================================="
mkdir -p "$WORKSPACE"
cd "$WORKSPACE"

mkdir -p compiler-projects
mkdir -p llvm-passes
mkdir -p risc-v-asm
mkdir -p tvm-work
mkdir -p benchmarks
mkdir -p blog-posts
mkdir -p notes
mkdir -p tools/{llvm,tvm,riscv-gnu-toolchain}
mkdir -p hardware/{visionfive2,qemu}
mkdir -p models/{onnx,pytorch,tensorflow}

print_status "Workspace structure created at $WORKSPACE"

echo ""
echo "Step 8: Cloning LLVM"
echo "===================="
echo "This will take some time (LLVM is ~3GB)..."

cd "$WORKSPACE/tools"
if [ ! -d "llvm" ]; then
    git clone --depth 1 --branch release/18.x https://github.com/llvm/llvm-project.git llvm
    print_status "LLVM cloned"
else
    print_warning "LLVM already exists, skipping clone"
fi

echo ""
echo "Step 9: Cloning TVM"
echo "==================="
cd "$WORKSPACE/tools"
if [ ! -d "tvm" ]; then
    git clone --recursive https://github.com/apache/tvm.git tvm
    print_status "TVM cloned"
else
    print_warning "TVM already exists, skipping clone"
fi

echo ""
echo "Step 10: Setting up Environment Variables"
echo "=========================================="

# Create environment setup script
cat > "$WORKSPACE/setup-env.sh" << 'EOF'
#!/bin/bash
# Source this file to set up your environment

export RISCV_WORKSPACE="$HOME/risc-v-compiler-learning"
export LLVM_DIR="$RISCV_WORKSPACE/tools/llvm-install"
export TVM_HOME="$RISCV_WORKSPACE/tools/tvm"
export PYTHONPATH="$TVM_HOME/python:${PYTHONPATH}"

# Add LLVM to PATH if installed
if [ -d "$LLVM_DIR/bin" ]; then
    export PATH="$LLVM_DIR/bin:$PATH"
fi

# Helper aliases
alias llvm-build="cd $RISCV_WORKSPACE/tools/llvm/build && ninja"
alias tvm-build="cd $RISCV_WORKSPACE/tools/tvm/build && ninja"
alias goto-workspace="cd $RISCV_WORKSPACE"
alias goto-llvm="cd $RISCV_WORKSPACE/tools/llvm"
alias goto-tvm="cd $RISCV_WORKSPACE/tools/tvm"

echo "RISC-V Compiler Learning Environment loaded!"
echo "Workspace: $RISCV_WORKSPACE"
EOF

chmod +x "$WORKSPACE/setup-env.sh"

# Add to .bashrc
if ! grep -q "risc-v-compiler-learning/setup-env.sh" "$HOME/.bashrc"; then
    echo "" >> "$HOME/.bashrc"
    echo "# RISC-V Compiler Learning Environment" >> "$HOME/.bashrc"
    echo "source $WORKSPACE/setup-env.sh" >> "$HOME/.bashrc"
fi

print_status "Environment setup script created"

echo ""
echo "Step 11: Creating Helper Scripts"
echo "================================="

# Script to build LLVM
cat > "$WORKSPACE/build-llvm.sh" << 'EOF'
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
EOF

chmod +x "$WORKSPACE/build-llvm.sh"

# Script to build TVM
cat > "$WORKSPACE/build-tvm.sh" << 'EOF'
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
EOF

chmod +x "$WORKSPACE/build-tvm.sh"

# Script to create new LLVM pass
cat > "$WORKSPACE/new-llvm-pass.sh" << 'EOF'
#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: ./new-llvm-pass.sh PassName"
    exit 1
fi

PASS_NAME=$1
WORKSPACE="$HOME/risc-v-compiler-learning"
PASS_DIR="$WORKSPACE/llvm-passes/$PASS_NAME"

mkdir -p "$PASS_DIR"
cd "$PASS_DIR"

# Create pass source
cat > "${PASS_NAME}.cpp" << PASS_EOF
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {

struct ${PASS_NAME} : public PassInfoMixin<${PASS_NAME}> {
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
        errs() << "Running ${PASS_NAME} on function: " << F.getName() << "\n";
        
        // TODO: Implement your pass logic here
        
        return PreservedAnalyses::all();
    }
    
    static bool isRequired() { return true; }
};

} // end anonymous namespace

// Plugin registration
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION, "${PASS_NAME}", LLVM_VERSION_STRING,
        [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "${PASS_NAME}") {
                        FPM.addPass(${PASS_NAME}());
                        return true;
                    }
                    return false;
                });
        }
    };
}
PASS_EOF

# Create CMakeLists.txt
cat > CMakeLists.txt << CMAKE_EOF
cmake_minimum_required(VERSION 3.13)
project(${PASS_NAME})

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM \${LLVM_PACKAGE_VERSION}")

include_directories(\${LLVM_INCLUDE_DIRS})
add_definitions(\${LLVM_DEFINITIONS})

add_library(${PASS_NAME} MODULE ${PASS_NAME}.cpp)

target_compile_features(${PASS_NAME} PRIVATE cxx_std_17)
CMAKE_EOF

# Create build script
cat > build.sh << BUILD_EOF
#!/bin/bash
mkdir -p build
cd build
cmake -DLLVM_DIR=$HOME/risc-v-compiler-learning/tools/llvm-install/lib/cmake/llvm ..
make
echo ""
echo "Pass built successfully!"
echo "Run with: opt -load-pass-plugin=./build/lib${PASS_NAME}.so -passes=${PASS_NAME} test.ll"
BUILD_EOF

chmod +x build.sh

echo "Created new LLVM pass: $PASS_NAME"
echo "Location: $PASS_DIR"
echo "Edit ${PASS_NAME}.cpp and run ./build.sh to compile"
EOF

chmod +x "$WORKSPACE/new-llvm-pass.sh"

print_status "Helper scripts created"

echo ""
echo "Step 12: Creating Project Templates"
echo "===================================="

# Simple C++ compiler template
cat > "$WORKSPACE/compiler-projects/template.cpp" << 'EOF'
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Token types
enum TokenType {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_EOF
};

// Token structure
struct Token {
    TokenType type;
    std::string value;
};

// Simple lexer
class Lexer {
    std::string input;
    size_t pos = 0;
    
public:
    Lexer(const std::string& input) : input(input) {}
    
    Token nextToken() {
        // Skip whitespace
        while (pos < input.length() && isspace(input[pos])) pos++;
        
        if (pos >= input.length()) {
            return {TOKEN_EOF, ""};
        }
        
        // Number
        if (isdigit(input[pos])) {
            std::string num;
            while (pos < input.length() && isdigit(input[pos])) {
                num += input[pos++];
            }
            return {TOKEN_NUMBER, num};
        }
        
        // Operators
        char c = input[pos++];
        if (c == '+') return {TOKEN_PLUS, "+"};
        if (c == '-') return {TOKEN_MINUS, "-"};
        
        throw std::runtime_error("Unknown character");
    }
};

int main() {
    std::string input = "10 + 20 - 5";
    Lexer lexer(input);
    
    Token tok;
    while ((tok = lexer.nextToken()).type != TOKEN_EOF) {
        std::cout << "Token: " << tok.value << "\n";
    }
    
    return 0;
}
EOF

# RISC-V assembly template
cat > "$WORKSPACE/risc-v-asm/template.s" << 'EOF'
# RISC-V Assembly Template
# Simple function that adds two numbers

.text
.globl add_numbers

add_numbers:
    # Arguments in a0 and a1
    # Return value in a0
    add a0, a0, a1
    ret

.globl _start
_start:
    # Load values
    li a0, 10
    li a1, 20
    
    # Call function
    call add_numbers
    
    # Exit
    li a7, 93      # exit syscall
    ecall
EOF

print_status "Project templates created"

echo ""
echo "=========================================="
echo "Setup Complete!"
echo "=========================================="
echo ""
echo -e "${GREEN}Next steps:${NC}"
echo "1. Close and reopen your terminal (or run: source ~/.bashrc)"
echo "2. Navigate to workspace: cd $WORKSPACE"
echo "3. Build LLVM (1-3 hours): ./build-llvm.sh"
echo "4. Build TVM (30 min): ./build-tvm.sh"
echo "5. Start learning!"
echo ""
echo -e "${YELLOW}Quick commands:${NC}"
echo "  goto-workspace   - Go to main workspace"
echo "  goto-llvm        - Go to LLVM directory"
echo "  goto-tvm         - Go to TVM directory"
echo ""
echo -e "${GREEN}Happy learning! 🚀${NC}"
echo ""
