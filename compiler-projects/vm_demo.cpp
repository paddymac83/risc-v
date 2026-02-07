// VM demo to step through bytecode execution
// Build: g++ -std=c++17 -g -o vm_demo vm_demo.cpp vm.cpp chunk.cpp value.cpp debug.cpp
// Debug: Set breakpoints and step through the VM dispatch loop
//
// This computes: -((1.2 + 3.4) / 5.6) = -0.821429

#include "chunk.hpp"
#include "debug.hpp"
#include "vm.hpp"
#include <cstdio>

int main() {
    // Step 1: Build the bytecode for -((1.2 + 3.4) / 5.6)
    Chunk chunk;

    // Push 1.2 onto the stack
    int c1 = chunk.addConstant(1.2);
    chunk.write(static_cast<uint8_t>(OpCode::OP_CONSTANT), 1);
    chunk.write(static_cast<uint8_t>(c1), 1);
    // BREAKPOINT HERE - constant pool has 1.2

    // Push 3.4 onto the stack
    int c2 = chunk.addConstant(3.4);
    chunk.write(static_cast<uint8_t>(OpCode::OP_CONSTANT), 1);
    chunk.write(static_cast<uint8_t>(c2), 1);
    // BREAKPOINT HERE - constant pool has 1.2, 3.4

    // Add: pops 3.4 and 1.2, pushes 4.6
    chunk.write(static_cast<uint8_t>(OpCode::OP_ADD), 1);

    // Push 5.6 onto the stack
    int c3 = chunk.addConstant(5.6);
    chunk.write(static_cast<uint8_t>(OpCode::OP_CONSTANT), 1);
    chunk.write(static_cast<uint8_t>(c3), 1);

    // Divide: pops 5.6 and 4.6, pushes 4.6/5.6 = 0.821429
    chunk.write(static_cast<uint8_t>(OpCode::OP_DIVIDE), 1);

    // Negate: pops 0.821429, pushes -0.821429
    chunk.write(static_cast<uint8_t>(OpCode::OP_NEGATE), 1);

    // Return: pops and prints the result
    chunk.write(static_cast<uint8_t>(OpCode::OP_RETURN), 1);

    // Step 2: Disassemble the bytecode
    printf("=== Disassembly ===\n");
    disassembleChunk(chunk, "-((1.2 + 3.4) / 5.6)");

    // Step 3: Execute it through the VM
    // BREAKPOINT in VM::run() to watch the dispatch loop
    printf("\n=== Execution ===\n");
    VM vm;
    InterpretResult result = vm.interpret(&chunk);

    printf("\nResult status: %s\n",
        result == InterpretResult::INTERPRET_OK ? "OK" :
        result == InterpretResult::INTERPRET_COMPILE_ERROR ? "COMPILE_ERROR" :
        "RUNTIME_ERROR");

    return 0;
}
