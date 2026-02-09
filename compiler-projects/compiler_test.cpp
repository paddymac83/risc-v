#include "compiler.hpp"
#include "vm.hpp"
#include "chunk.hpp"
#include <cassert>
#include <cstdio>

// Test framework matching the project's existing style
static int tests_run = 0;
static int tests_passed = 0;

#define TEST(name) static void name()
#define RUN_TEST(name) do { \
    printf("Running %s... ", #name); \
    tests_run++; \
    name(); \
    tests_passed++; \
    printf("PASSED\n"); \
} while(0)

// Redirect stdout and stderr to suppress compile()/VM output during tests
static FILE* devnull = nullptr;
static FILE* real_stdout = nullptr;
static FILE* real_stderr = nullptr;

static void suppress_output() {
    if (!devnull) devnull = fopen("/dev/null", "w");
    if (devnull) {
        real_stdout = stdout;
        stdout = devnull;
        real_stderr = stderr;
        stderr = devnull;
    }
}

static void restore_output() {
    if (real_stdout) {
        stdout = real_stdout;
        real_stdout = nullptr;
    }
    if (real_stderr) {
        stderr = real_stderr;
        real_stderr = nullptr;
    }
}

// ---- Expression compilation tests (should succeed) ----

TEST(test_compile_number) {
    Chunk chunk;
    suppress_output();
    bool result = compile("42", chunk);
    restore_output();
    assert(result && "Single number should compile");
}

TEST(test_compile_decimal) {
    Chunk chunk;
    suppress_output();
    bool result = compile("3.14", chunk);
    restore_output();
    assert(result && "Decimal number should compile");
}

TEST(test_compile_addition) {
    Chunk chunk;
    suppress_output();
    bool result = compile("1 + 2", chunk);
    restore_output();
    assert(result && "Addition should compile");
}

TEST(test_compile_subtraction) {
    Chunk chunk;
    suppress_output();
    bool result = compile("5 - 3", chunk);
    restore_output();
    assert(result && "Subtraction should compile");
}

TEST(test_compile_multiplication) {
    Chunk chunk;
    suppress_output();
    bool result = compile("2 * 3", chunk);
    restore_output();
    assert(result && "Multiplication should compile");
}

TEST(test_compile_division) {
    Chunk chunk;
    suppress_output();
    bool result = compile("10 / 2", chunk);
    restore_output();
    assert(result && "Division should compile");
}

TEST(test_compile_negate) {
    Chunk chunk;
    suppress_output();
    bool result = compile("-5", chunk);
    restore_output();
    assert(result && "Unary negation should compile");
}

TEST(test_compile_grouping) {
    Chunk chunk;
    suppress_output();
    bool result = compile("(1 + 2)", chunk);
    restore_output();
    assert(result && "Grouped expression should compile");
}

TEST(test_compile_nested_grouping) {
    Chunk chunk;
    suppress_output();
    bool result = compile("(((42)))", chunk);
    restore_output();
    assert(result && "Nested grouping should compile");
}

TEST(test_compile_precedence) {
    Chunk chunk;
    suppress_output();
    bool result = compile("2 + 3 * 4", chunk);
    restore_output();
    assert(result && "Precedence expression should compile");
}

TEST(test_compile_complex) {
    Chunk chunk;
    suppress_output();
    bool result = compile("(-1 + 2) * 3 - -4", chunk);
    restore_output();
    assert(result && "Complex expression should compile");
}

// ---- Bytecode verification tests ----

TEST(test_bytecode_number) {
    // "42" -> OP_CONSTANT 0, OP_RETURN
    Chunk chunk;
    suppress_output();
    bool result = compile("42", chunk);
    restore_output();
    assert(result);
    assert(chunk.count() == 3); // OP_CONSTANT, index, OP_RETURN
    assert(chunk.code(0) == static_cast<uint8_t>(OpCode::OP_CONSTANT));
    assert(chunk.code(1) == 0);
    assert(chunk.constant(0) == 42.0);
    assert(chunk.code(2) == static_cast<uint8_t>(OpCode::OP_RETURN));
}

TEST(test_bytecode_binary) {
    // "1 + 2" -> OP_CONSTANT 0, OP_CONSTANT 1, OP_ADD, OP_RETURN
    Chunk chunk;
    suppress_output();
    bool result = compile("1 + 2", chunk);
    restore_output();
    assert(result);
    assert(chunk.count() == 6); // 2 constants (2 bytes each) + ADD + RETURN
    assert(chunk.code(0) == static_cast<uint8_t>(OpCode::OP_CONSTANT));
    assert(chunk.constant(static_cast<size_t>(chunk.code(1))) == 1.0);
    assert(chunk.code(2) == static_cast<uint8_t>(OpCode::OP_CONSTANT));
    assert(chunk.constant(static_cast<size_t>(chunk.code(3))) == 2.0);
    assert(chunk.code(4) == static_cast<uint8_t>(OpCode::OP_ADD));
    assert(chunk.code(5) == static_cast<uint8_t>(OpCode::OP_RETURN));
}

TEST(test_bytecode_negate) {
    // "-5" -> OP_CONSTANT 0, OP_NEGATE, OP_RETURN
    Chunk chunk;
    suppress_output();
    bool result = compile("-5", chunk);
    restore_output();
    assert(result);
    assert(chunk.count() == 4);
    assert(chunk.code(0) == static_cast<uint8_t>(OpCode::OP_CONSTANT));
    assert(chunk.constant(0) == 5.0);
    assert(chunk.code(2) == static_cast<uint8_t>(OpCode::OP_NEGATE));
    assert(chunk.code(3) == static_cast<uint8_t>(OpCode::OP_RETURN));
}

TEST(test_bytecode_precedence) {
    // "2 + 3 * 4" should compile as 2, 3, 4, *, + (not 2, 3, +, 4, *)
    Chunk chunk;
    suppress_output();
    bool result = compile("2 + 3 * 4", chunk);
    restore_output();
    assert(result);
    // OP_CONSTANT 0(2), OP_CONSTANT 1(3), OP_CONSTANT 2(4),
    // OP_MULTIPLY, OP_ADD, OP_RETURN
    assert(chunk.count() == 9);
    assert(chunk.code(6) == static_cast<uint8_t>(OpCode::OP_MULTIPLY));
    assert(chunk.code(7) == static_cast<uint8_t>(OpCode::OP_ADD));
}

// ---- Error tests (should fail) ----

TEST(test_compile_error_empty) {
    Chunk chunk;
    suppress_output();
    bool result = compile("", chunk);
    restore_output();
    assert(!result && "Empty source should fail (no expression)");
}

TEST(test_compile_error_unexpected_token) {
    Chunk chunk;
    suppress_output();
    bool result = compile("var", chunk);
    restore_output();
    assert(!result && "Keyword alone should fail");
}

TEST(test_compile_error_missing_paren) {
    Chunk chunk;
    suppress_output();
    bool result = compile("(1 + 2", chunk);
    restore_output();
    assert(!result && "Missing closing paren should fail");
}

TEST(test_compile_error_unexpected_char) {
    Chunk chunk;
    suppress_output();
    bool result = compile("@", chunk);
    restore_output();
    assert(!result && "Unexpected character should fail");
}

TEST(test_compile_error_unterminated_string) {
    Chunk chunk;
    suppress_output();
    bool result = compile("\"oops", chunk);
    restore_output();
    assert(!result && "Unterminated string should fail");
}

// ---- VM integration tests ----

TEST(test_vm_compile_and_run) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("1 + 2");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_complex_expression) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("(-1 + 2) * 3 - -4");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_error_on_bad_source) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("@@@");
    restore_output();
    assert(result == InterpretResult::INTERPRET_COMPILE_ERROR);
}

TEST(test_vm_chunk_still_works) {
    // The old Chunk*-based interpret path should still function
    Chunk chunk;
    int c = chunk.addConstant(42.0);
    chunk.write(static_cast<uint8_t>(OpCode::OP_CONSTANT), 1);
    chunk.write(static_cast<uint8_t>(c), 1);
    chunk.write(static_cast<uint8_t>(OpCode::OP_RETURN), 1);

    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret(&chunk);
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

int main() {
    printf("=== Compiler Unit Tests (Chapter 17 - Compiling Expressions) ===\n\n");

    // Expression compilation
    RUN_TEST(test_compile_number);
    RUN_TEST(test_compile_decimal);
    RUN_TEST(test_compile_addition);
    RUN_TEST(test_compile_subtraction);
    RUN_TEST(test_compile_multiplication);
    RUN_TEST(test_compile_division);
    RUN_TEST(test_compile_negate);
    RUN_TEST(test_compile_grouping);
    RUN_TEST(test_compile_nested_grouping);
    RUN_TEST(test_compile_precedence);
    RUN_TEST(test_compile_complex);

    // Bytecode verification
    RUN_TEST(test_bytecode_number);
    RUN_TEST(test_bytecode_binary);
    RUN_TEST(test_bytecode_negate);
    RUN_TEST(test_bytecode_precedence);

    // Error cases
    RUN_TEST(test_compile_error_empty);
    RUN_TEST(test_compile_error_unexpected_token);
    RUN_TEST(test_compile_error_missing_paren);
    RUN_TEST(test_compile_error_unexpected_char);
    RUN_TEST(test_compile_error_unterminated_string);

    // VM integration
    RUN_TEST(test_vm_compile_and_run);
    RUN_TEST(test_vm_complex_expression);
    RUN_TEST(test_vm_error_on_bad_source);
    RUN_TEST(test_vm_chunk_still_works);

    printf("\n=== Results: %d/%d tests passed ===\n", tests_passed, tests_run);

    if (devnull) fclose(devnull);

    return tests_passed == tests_run ? 0 : 1;
}
