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
