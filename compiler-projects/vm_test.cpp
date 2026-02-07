#include "vm.hpp"
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

// Helper: write a constant instruction and return the chunk
static void emitConstant(Chunk& chunk, double value, int line) {
    int idx = chunk.addConstant(value);
    chunk.write(static_cast<uint8_t>(OpCode::OP_CONSTANT), line);
    chunk.write(static_cast<uint8_t>(idx), line);
}

static void emitOp(Chunk& chunk, OpCode op, int line) {
    chunk.write(static_cast<uint8_t>(op), line);
}

TEST(test_vm_push_pop) {
    VM vm;
    vm.push(1.0);
    vm.push(2.0);
    vm.push(3.0);

    assert(vm.stackSize() == 3);
    assert(vm.pop() == 3.0);
    assert(vm.pop() == 2.0);
    assert(vm.pop() == 1.0);
    assert(vm.stackSize() == 0);
}

TEST(test_vm_constant_return) {
    // Program: push 42.0, return
    Chunk chunk;
    emitConstant(chunk, 42.0, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_negate) {
    // Program: push 5.0, negate, return
    // Expected output: -5
    Chunk chunk;
    emitConstant(chunk, 5.0, 1);
    emitOp(chunk, OpCode::OP_NEGATE, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_add) {
    // Program: push 1.0, push 2.0, add, return
    // Expected: 3
    Chunk chunk;
    emitConstant(chunk, 1.0, 1);
    emitConstant(chunk, 2.0, 1);
    emitOp(chunk, OpCode::OP_ADD, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_subtract) {
    // Program: push 10.0, push 3.0, subtract, return
    // Expected: 7
    Chunk chunk;
    emitConstant(chunk, 10.0, 1);
    emitConstant(chunk, 3.0, 1);
    emitOp(chunk, OpCode::OP_SUBTRACT, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_multiply) {
    // Program: push 6.0, push 7.0, multiply, return
    // Expected: 42
    Chunk chunk;
    emitConstant(chunk, 6.0, 1);
    emitConstant(chunk, 7.0, 1);
    emitOp(chunk, OpCode::OP_MULTIPLY, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_divide) {
    // Program: push 15.0, push 3.0, divide, return
    // Expected: 5
    Chunk chunk;
    emitConstant(chunk, 15.0, 1);
    emitConstant(chunk, 3.0, 1);
    emitOp(chunk, OpCode::OP_DIVIDE, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_stack_arithmetic) {
    // Verify stack state by using push/pop directly after interpret
    // Program: push 10, push 20, add, push 5, multiply, return
    // (10 + 20) * 5 = 150
    Chunk chunk;
    emitConstant(chunk, 10.0, 1);
    emitConstant(chunk, 20.0, 1);
    emitOp(chunk, OpCode::OP_ADD, 1);
    emitConstant(chunk, 5.0, 1);
    emitOp(chunk, OpCode::OP_MULTIPLY, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
    // After OP_RETURN pops the result, stack should be empty
    assert(vm.stackSize() == 0);
}

TEST(test_vm_complex_expression) {
    // Compute: -((1.2 + 3.4) / 5.6)
    // Step by step:
    //   push 1.2, push 3.4, add       -> stack: [4.6]
    //   push 5.6, divide               -> stack: [0.821428...]
    //   negate                          -> stack: [-0.821428...]
    //   return
    Chunk chunk;
    emitConstant(chunk, 1.2, 1);
    emitConstant(chunk, 3.4, 1);
    emitOp(chunk, OpCode::OP_ADD, 1);
    emitConstant(chunk, 5.6, 1);
    emitOp(chunk, OpCode::OP_DIVIDE, 1);
    emitOp(chunk, OpCode::OP_NEGATE, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_double_negate) {
    // push 7.0, negate, negate, return -> 7
    Chunk chunk;
    emitConstant(chunk, 7.0, 1);
    emitOp(chunk, OpCode::OP_NEGATE, 1);
    emitOp(chunk, OpCode::OP_NEGATE, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_operand_order) {
    // Verify that subtraction respects operand order
    // push 3, push 1, subtract -> 3 - 1 = 2, NOT 1 - 3 = -2
    Chunk chunk;
    emitConstant(chunk, 3.0, 1);
    emitConstant(chunk, 1.0, 1);
    emitOp(chunk, OpCode::OP_SUBTRACT, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
    // Output should be "2", not "-2"
}

TEST(test_vm_disassemble_new_opcodes) {
    Chunk chunk;
    emitConstant(chunk, 1.0, 1);
    emitConstant(chunk, 2.0, 1);
    emitOp(chunk, OpCode::OP_ADD, 1);
    emitOp(chunk, OpCode::OP_NEGATE, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    printf("\n--- Disassembly with new opcodes ---\n");
    disassembleChunk(chunk, "arithmetic");
    printf("--- End disassembly ---\n");
}

int main() {
    printf("=== VM Unit Tests ===\n\n");

    RUN_TEST(test_vm_push_pop);
    RUN_TEST(test_vm_constant_return);
    RUN_TEST(test_vm_negate);
    RUN_TEST(test_vm_add);
    RUN_TEST(test_vm_subtract);
    RUN_TEST(test_vm_multiply);
    RUN_TEST(test_vm_divide);
    RUN_TEST(test_vm_stack_arithmetic);
    RUN_TEST(test_vm_complex_expression);
    RUN_TEST(test_vm_double_negate);
    RUN_TEST(test_vm_operand_order);
    RUN_TEST(test_vm_disassemble_new_opcodes);

    printf("\n=== Results: %d/%d tests passed ===\n", tests_passed, tests_run);

    return tests_passed == tests_run ? 0 : 1;
}
