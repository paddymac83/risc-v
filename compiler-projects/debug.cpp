#include "debug.hpp"
#include "value.hpp"
#include <cstdio>

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int constantInstruction(const char* name, const Chunk& chunk, int offset) {
    uint8_t constantIndex = chunk.code(offset + 1);
    printf("%-16s %4d '", name, constantIndex);
    printValue(chunk.constant(constantIndex));
    printf("'\n");
    return offset + 2;
}

void disassembleChunk(const Chunk& chunk, const char* name) {
    printf("== %s ==\n", name);

    for (int offset = 0; offset < static_cast<int>(chunk.count());) {
        offset = disassembleInstruction(chunk, offset);
    }
}

int disassembleInstruction(const Chunk& chunk, int offset) {
    printf("%04d ", offset);

    // Show line number or | if same as previous
    if (offset > 0 && chunk.line(offset) == chunk.line(offset - 1)) {
        printf("   | ");
    } else {
        printf("%4d ", chunk.line(offset));
    }

    uint8_t instruction = chunk.code(offset);
    switch (static_cast<OpCode>(instruction)) {
        case OpCode::OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OpCode::OP_ADD:
            return simpleInstruction("OP_ADD", offset);
        case OpCode::OP_SUBTRACT:
            return simpleInstruction("OP_SUBTRACT", offset);
        case OpCode::OP_MULTIPLY:
            return simpleInstruction("OP_MULTIPLY", offset);
        case OpCode::OP_DIVIDE:
            return simpleInstruction("OP_DIVIDE", offset);
        case OpCode::OP_NEGATE:
            return simpleInstruction("OP_NEGATE", offset);
        case OpCode::OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}
