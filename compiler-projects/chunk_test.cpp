#include "chunk.hpp"
#include "debug.hpp"
#include <cassert>
#include <cstdio>
#include <string>

// Simple test framework
static int tests_run = 0;
static int tests_passed = 0;

#define TEST(name) void name()
#define RUN_TEST(name) do { \
    printf("Running %s... ", #name); \
    tests_run++; \
    name(); \
    tests_passed++; \
    printf("PASSED\n"); \
} while(0)

TEST(test_empty_chunk) {
    Chunk chunk;
    assert(chunk.count() == 0);
    assert(chunk.code().empty());
    assert(chunk.lines().empty());
    assert(chunk.constants().empty());
}

TEST(test_write_byte) {
    Chunk chunk;
    chunk.write(static_cast<uint8_t>(OpCode::OP_RETURN), 1);

    assert(chunk.count() == 1);
    assert(chunk.code(0) == static_cast<uint8_t>(OpCode::OP_RETURN));
    assert(chunk.line(0) == 1);
}

TEST(test_add_constant) {
    Chunk chunk;
    int index = chunk.addConstant(1.2);

    assert(index == 0);
    assert(chunk.constants().size() == 1);
    assert(chunk.constant(0) == 1.2);
}

TEST(test_multiple_constants) {
    Chunk chunk;
    int idx0 = chunk.addConstant(1.0);
    int idx1 = chunk.addConstant(2.0);
    int idx2 = chunk.addConstant(3.0);

    assert(idx0 == 0);
    assert(idx1 == 1);
    assert(idx2 == 2);
    assert(chunk.constant(0) == 1.0);
    assert(chunk.constant(1) == 2.0);
    assert(chunk.constant(2) == 3.0);
}

TEST(test_write_constant_instruction) {
    Chunk chunk;
    int constantIdx = chunk.addConstant(42.0);

    chunk.write(static_cast<uint8_t>(OpCode::OP_CONSTANT), 1);
    chunk.write(static_cast<uint8_t>(constantIdx), 1);
    chunk.write(static_cast<uint8_t>(OpCode::OP_RETURN), 1);

    assert(chunk.count() == 3);
    assert(chunk.code(0) == static_cast<uint8_t>(OpCode::OP_CONSTANT));
    assert(chunk.code(1) == 0); // constant index
    assert(chunk.code(2) == static_cast<uint8_t>(OpCode::OP_RETURN));
}

TEST(test_line_tracking) {
    Chunk chunk;
    chunk.write(static_cast<uint8_t>(OpCode::OP_RETURN), 1);
    chunk.write(static_cast<uint8_t>(OpCode::OP_RETURN), 2);
    chunk.write(static_cast<uint8_t>(OpCode::OP_RETURN), 2);
    chunk.write(static_cast<uint8_t>(OpCode::OP_RETURN), 3);

    assert(chunk.line(0) == 1);
    assert(chunk.line(1) == 2);
    assert(chunk.line(2) == 2);
    assert(chunk.line(3) == 3);
}

TEST(test_opcode_names) {
    assert(std::string(opCodeName(OpCode::OP_CONSTANT)) == "OP_CONSTANT");
    assert(std::string(opCodeName(OpCode::OP_RETURN)) == "OP_RETURN");
}

TEST(test_disassemble) {
    Chunk chunk;
    int constantIdx = chunk.addConstant(1.2);
    chunk.write(static_cast<uint8_t>(OpCode::OP_CONSTANT), 123);
    chunk.write(static_cast<uint8_t>(constantIdx), 123);
    chunk.write(static_cast<uint8_t>(OpCode::OP_RETURN), 123);

    printf("\n--- Disassembly output ---\n");
    disassembleChunk(chunk, "test chunk");
    printf("--- End disassembly ---\n");

    // If we get here without crashing, the test passes
}

int main() {
    printf("=== Chunk Unit Tests ===\n\n");

    RUN_TEST(test_empty_chunk);
    RUN_TEST(test_write_byte);
    RUN_TEST(test_add_constant);
    RUN_TEST(test_multiple_constants);
    RUN_TEST(test_write_constant_instruction);
    RUN_TEST(test_line_tracking);
    RUN_TEST(test_opcode_names);
    RUN_TEST(test_disassemble);

    printf("\n=== Results: %d/%d tests passed ===\n", tests_passed, tests_run);

    return tests_passed == tests_run ? 0 : 1;
}
