// Simple demo to step through and understand bytecode chunks
// Build: g++ -std=c++17 -g -o chunk_demo chunk_demo.cpp chunk.cpp value.cpp debug.cpp
// Debug: Set breakpoints and step through each line

#include "chunk.hpp"
#include "debug.hpp"
#include <cstdio>

int main() {
    // Step 1: Create an empty chunk
    Chunk chunk;
    // BREAKPOINT HERE - inspect chunk (empty vectors)

    // Step 2: Add a constant to the pool
    // This returns the INDEX where 1.2 is stored (index 0)
    int constantIndex = chunk.addConstant(1.2);
    printf("Added constant 1.2 at index %d\n", constantIndex);
    // BREAKPOINT HERE - inspect chunk.constants_ (now has 1.2)

    // Step 3: Write OP_CONSTANT instruction (2 bytes)
    // Byte 0: The opcode itself
    chunk.write(static_cast<uint8_t>(OpCode::OP_CONSTANT), 1);
    // BREAKPOINT HERE - inspect chunk.code_ (has 1 byte: 0x00)

    // Byte 1: The index into the constant pool
    chunk.write(static_cast<uint8_t>(constantIndex), 1);
    // BREAKPOINT HERE - inspect chunk.code_ (has 2 bytes: 0x00, 0x00)

    // Step 4: Write OP_RETURN instruction (1 byte)
    chunk.write(static_cast<uint8_t>(OpCode::OP_RETURN), 2);
    // BREAKPOINT HERE - inspect chunk.code_ (has 3 bytes: 0x00, 0x00, 0x01)

    // Step 5: Disassemble - step INTO this to see decoding
    printf("\n");
    disassembleChunk(chunk, "example");
    // STEP INTO disassembleChunk, then INTO disassembleInstruction
    // Watch how it reads code_[0], sees OP_CONSTANT, then reads code_[1]
    // to get the constant index, then looks up constants_[0]

    // Memory layout visualization:
    printf("\n--- Raw Memory Layout ---\n");
    printf("code_: ");
    for (size_t i = 0; i < chunk.count(); i++) {
        printf("[%zu]=0x%02X ", i, chunk.code(i));
    }
    printf("\n");

    printf("lines_: ");
    for (size_t i = 0; i < chunk.count(); i++) {
        printf("[%zu]=%d ", i, chunk.line(i));
    }
    printf("\n");

    printf("constants_: ");
    for (size_t i = 0; i < chunk.constants().size(); i++) {
        printf("[%zu]=", i);
        printValue(chunk.constant(i));
        printf(" ");
    }
    printf("\n");

    return 0;
}
