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
