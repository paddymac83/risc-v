#include "vm.hpp"
#include "chunk.hpp"
#include "debug.hpp"
#include "object.hpp"
#include <cassert>
#include <cstdio>
#include <cstring>
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
    int idx = chunk.addConstant(NUMBER_VAL(value));
    chunk.write(static_cast<uint8_t>(OpCode::OP_CONSTANT), line);
    chunk.write(static_cast<uint8_t>(idx), line);
}

static void emitOp(Chunk& chunk, OpCode op, int line) {
    chunk.write(static_cast<uint8_t>(op), line);
}

TEST(test_vm_push_pop) {
    VM vm;
    vm.push(NUMBER_VAL(1.0));
    vm.push(NUMBER_VAL(2.0));
    vm.push(NUMBER_VAL(3.0));

    assert(vm.stackSize() == 3);
    assert(AS_NUMBER(vm.pop()) == 3.0);
    assert(AS_NUMBER(vm.pop()) == 2.0);
    assert(AS_NUMBER(vm.pop()) == 1.0);
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

// ---- Chapter 18: New value type tests ----

TEST(test_vm_nil_literal) {
    // OP_NIL, OP_RETURN -> prints "nil"
    Chunk chunk;
    emitOp(chunk, OpCode::OP_NIL, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_bool_literals) {
    // OP_TRUE, OP_RETURN -> prints "true"
    Chunk chunk;
    emitOp(chunk, OpCode::OP_TRUE, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_not) {
    // OP_TRUE, OP_NOT, OP_RETURN -> prints "false"
    Chunk chunk;
    emitOp(chunk, OpCode::OP_TRUE, 1);
    emitOp(chunk, OpCode::OP_NOT, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_equal) {
    // push 1.0, push 1.0, OP_EQUAL, OP_RETURN -> prints "true"
    Chunk chunk;
    emitConstant(chunk, 1.0, 1);
    emitConstant(chunk, 1.0, 1);
    emitOp(chunk, OpCode::OP_EQUAL, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_greater) {
    // push 3.0, push 1.0, OP_GREATER, OP_RETURN -> prints "true"
    Chunk chunk;
    emitConstant(chunk, 3.0, 1);
    emitConstant(chunk, 1.0, 1);
    emitOp(chunk, OpCode::OP_GREATER, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_less) {
    // push 1.0, push 3.0, OP_LESS, OP_RETURN -> prints "true"
    Chunk chunk;
    emitConstant(chunk, 1.0, 1);
    emitConstant(chunk, 3.0, 1);
    emitOp(chunk, OpCode::OP_LESS, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_negate_non_number_error) {
    // OP_TRUE, OP_NEGATE should produce a runtime error
    Chunk chunk;
    emitOp(chunk, OpCode::OP_TRUE, 1);
    emitOp(chunk, OpCode::OP_NEGATE, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_RUNTIME_ERROR);
}

TEST(test_vm_add_type_error) {
    // OP_TRUE, push 1.0, OP_ADD should produce a runtime error
    Chunk chunk;
    emitOp(chunk, OpCode::OP_TRUE, 1);
    emitConstant(chunk, 1.0, 1);
    emitOp(chunk, OpCode::OP_ADD, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_RUNTIME_ERROR);
}

// ---- Chapter 19: String tests (direct bytecode) ----

// Helper: emit a string constant instruction
static void emitStringConstant(Chunk& chunk, const char* str, int line) {
    ObjString* objStr = copyString(str, static_cast<int>(strlen(str)));
    int idx = chunk.addConstant(OBJ_VAL(reinterpret_cast<Obj*>(objStr)));
    chunk.write(static_cast<uint8_t>(OpCode::OP_CONSTANT), line);
    chunk.write(static_cast<uint8_t>(idx), line);
}

TEST(test_vm_string_constant) {
    // Push a string constant and return it
    // Build chunk with string constants, then let VM execute
    Obj* objects = nullptr;
    setObjectList(&objects);

    Chunk chunk;
    emitStringConstant(chunk, "hello", 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
    freeObjects(objects);
    setObjectList(nullptr);
}

TEST(test_vm_string_concat_bytecode) {
    // Push two strings, add (concatenate), return
    Obj* objects = nullptr;
    setObjectList(&objects);

    Chunk chunk;
    emitStringConstant(chunk, "foo", 1);
    emitStringConstant(chunk, "bar", 1);
    emitOp(chunk, OpCode::OP_ADD, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
    freeObjects(objects);
    setObjectList(nullptr);
}

TEST(test_vm_string_equal_bytecode) {
    // Two identical strings should be equal
    Obj* objects = nullptr;
    setObjectList(&objects);

    Chunk chunk;
    emitStringConstant(chunk, "same", 1);
    emitStringConstant(chunk, "same", 1);
    emitOp(chunk, OpCode::OP_EQUAL, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
    freeObjects(objects);
    setObjectList(nullptr);
}

TEST(test_vm_string_not_equal_bytecode) {
    // Two different strings should not be equal
    Obj* objects = nullptr;
    setObjectList(&objects);

    Chunk chunk;
    emitStringConstant(chunk, "abc", 1);
    emitStringConstant(chunk, "xyz", 1);
    emitOp(chunk, OpCode::OP_EQUAL, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_OK);
    freeObjects(objects);
    setObjectList(nullptr);
}

TEST(test_vm_string_number_add_error) {
    // String + number should be a runtime error
    Obj* objects = nullptr;
    setObjectList(&objects);

    Chunk chunk;
    emitStringConstant(chunk, "hello", 1);
    emitConstant(chunk, 42.0, 1);
    emitOp(chunk, OpCode::OP_ADD, 1);
    emitOp(chunk, OpCode::OP_RETURN, 1);

    VM vm;
    printf("\n");
    InterpretResult result = vm.interpret(&chunk);
    assert(result == InterpretResult::INTERPRET_RUNTIME_ERROR);
    freeObjects(objects);
    setObjectList(nullptr);
}

int main() {
    printf("=== VM Unit Tests (Chapter 19 - Strings) ===\n\n");

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

    // Chapter 18 tests
    RUN_TEST(test_vm_nil_literal);
    RUN_TEST(test_vm_bool_literals);
    RUN_TEST(test_vm_not);
    RUN_TEST(test_vm_equal);
    RUN_TEST(test_vm_greater);
    RUN_TEST(test_vm_less);
    RUN_TEST(test_vm_negate_non_number_error);
    RUN_TEST(test_vm_add_type_error);

    // Chapter 19 tests
    printf("\n--- Chapter 19: Strings ---\n");
    RUN_TEST(test_vm_string_constant);
    RUN_TEST(test_vm_string_concat_bytecode);
    RUN_TEST(test_vm_string_equal_bytecode);
    RUN_TEST(test_vm_string_not_equal_bytecode);
    RUN_TEST(test_vm_string_number_add_error);

    printf("\n=== Results: %d/%d tests passed ===\n", tests_passed, tests_run);

    return tests_passed == tests_run ? 0 : 1;
}
