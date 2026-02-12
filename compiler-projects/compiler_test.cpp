#include "compiler.hpp"
#include "vm.hpp"
#include "chunk.hpp"
#include "object.hpp"
#include <cassert>
#include <cstdio>
#include <cstring>

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
    assert(AS_NUMBER(chunk.constant(0)) == 42.0);
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
    assert(AS_NUMBER(chunk.constant(static_cast<size_t>(chunk.code(1)))) == 1.0);
    assert(chunk.code(2) == static_cast<uint8_t>(OpCode::OP_CONSTANT));
    assert(AS_NUMBER(chunk.constant(static_cast<size_t>(chunk.code(3)))) == 2.0);
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
    assert(AS_NUMBER(chunk.constant(0)) == 5.0);
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
    int c = chunk.addConstant(NUMBER_VAL(42.0));
    chunk.write(static_cast<uint8_t>(OpCode::OP_CONSTANT), 1);
    chunk.write(static_cast<uint8_t>(c), 1);
    chunk.write(static_cast<uint8_t>(OpCode::OP_RETURN), 1);

    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret(&chunk);
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

// ---- Chapter 18: Types of Values tests ----

TEST(test_compile_true) {
    Chunk chunk;
    suppress_output();
    bool result = compile("true", chunk);
    restore_output();
    assert(result && "true literal should compile");
    // Should be OP_TRUE, OP_RETURN
    assert(chunk.count() == 2);
    assert(chunk.code(0) == static_cast<uint8_t>(OpCode::OP_TRUE));
    assert(chunk.code(1) == static_cast<uint8_t>(OpCode::OP_RETURN));
}

TEST(test_compile_false) {
    Chunk chunk;
    suppress_output();
    bool result = compile("false", chunk);
    restore_output();
    assert(result && "false literal should compile");
    assert(chunk.count() == 2);
    assert(chunk.code(0) == static_cast<uint8_t>(OpCode::OP_FALSE));
    assert(chunk.code(1) == static_cast<uint8_t>(OpCode::OP_RETURN));
}

TEST(test_compile_nil) {
    Chunk chunk;
    suppress_output();
    bool result = compile("nil", chunk);
    restore_output();
    assert(result && "nil literal should compile");
    assert(chunk.count() == 2);
    assert(chunk.code(0) == static_cast<uint8_t>(OpCode::OP_NIL));
    assert(chunk.code(1) == static_cast<uint8_t>(OpCode::OP_RETURN));
}

TEST(test_compile_not) {
    Chunk chunk;
    suppress_output();
    bool result = compile("!true", chunk);
    restore_output();
    assert(result && "!true should compile");
    // OP_TRUE, OP_NOT, OP_RETURN
    assert(chunk.count() == 3);
    assert(chunk.code(0) == static_cast<uint8_t>(OpCode::OP_TRUE));
    assert(chunk.code(1) == static_cast<uint8_t>(OpCode::OP_NOT));
    assert(chunk.code(2) == static_cast<uint8_t>(OpCode::OP_RETURN));
}

TEST(test_compile_equality) {
    Chunk chunk;
    suppress_output();
    bool result = compile("1 == 2", chunk);
    restore_output();
    assert(result && "Equality should compile");
}

TEST(test_compile_inequality) {
    Chunk chunk;
    suppress_output();
    bool result = compile("1 != 2", chunk);
    restore_output();
    assert(result && "Inequality should compile");
    // Should emit OP_EQUAL then OP_NOT
}

TEST(test_compile_less) {
    Chunk chunk;
    suppress_output();
    bool result = compile("1 < 2", chunk);
    restore_output();
    assert(result && "Less-than should compile");
}

TEST(test_compile_greater) {
    Chunk chunk;
    suppress_output();
    bool result = compile("1 > 2", chunk);
    restore_output();
    assert(result && "Greater-than should compile");
}

TEST(test_compile_less_equal) {
    Chunk chunk;
    suppress_output();
    bool result = compile("1 <= 2", chunk);
    restore_output();
    assert(result && "Less-or-equal should compile");
    // Should emit OP_GREATER then OP_NOT
}

TEST(test_compile_greater_equal) {
    Chunk chunk;
    suppress_output();
    bool result = compile("1 >= 2", chunk);
    restore_output();
    assert(result && "Greater-or-equal should compile");
    // Should emit OP_LESS then OP_NOT
}

TEST(test_vm_true_literal) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("true");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_nil_literal) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("nil");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_not_false) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("!false");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_comparison) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("1 < 2");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_equality) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("1 == 1");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_negate_bool_error) {
    // -true should produce a runtime error
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("-true");
    restore_output();
    assert(result == InterpretResult::INTERPRET_RUNTIME_ERROR);
}

TEST(test_vm_add_bool_error) {
    // true + false should produce a runtime error
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("true + false");
    restore_output();
    assert(result == InterpretResult::INTERPRET_RUNTIME_ERROR);
}

// ---- Chapter 19: Strings tests ----

TEST(test_compile_string) {
    Chunk chunk;
    Obj* objects = nullptr;
    setObjectList(&objects);
    suppress_output();
    bool result = compile("\"hello\"", chunk);
    restore_output();
    assert(result && "String literal should compile");
    freeObjects(objects);
    setObjectList(nullptr);
}

TEST(test_compile_empty_string) {
    Chunk chunk;
    Obj* objects = nullptr;
    setObjectList(&objects);
    suppress_output();
    bool result = compile("\"\"", chunk);
    restore_output();
    assert(result && "Empty string should compile");
    freeObjects(objects);
    setObjectList(nullptr);
}

TEST(test_compile_string_concat) {
    Chunk chunk;
    Obj* objects = nullptr;
    setObjectList(&objects);
    suppress_output();
    bool result = compile("\"foo\" + \"bar\"", chunk);
    restore_output();
    assert(result && "String concatenation should compile");
    freeObjects(objects);
    setObjectList(nullptr);
}

TEST(test_bytecode_string) {
    // "hello" -> OP_CONSTANT 0, OP_RETURN
    Chunk chunk;
    Obj* objects = nullptr;
    setObjectList(&objects);
    suppress_output();
    bool result = compile("\"hello\"", chunk);
    restore_output();
    assert(result);
    assert(chunk.count() == 3); // OP_CONSTANT, index, OP_RETURN
    assert(chunk.code(0) == static_cast<uint8_t>(OpCode::OP_CONSTANT));
    assert(IS_OBJ(chunk.constant(0)));
    assert(IS_STRING(chunk.constant(0)));
    assert(strcmp(AS_CSTRING(chunk.constant(0)), "hello") == 0);
    assert(chunk.code(2) == static_cast<uint8_t>(OpCode::OP_RETURN));
    freeObjects(objects);
    setObjectList(nullptr);
}

TEST(test_bytecode_string_concat) {
    // "a" + "b" -> OP_CONSTANT 0, OP_CONSTANT 1, OP_ADD, OP_RETURN
    Chunk chunk;
    Obj* objects = nullptr;
    setObjectList(&objects);
    suppress_output();
    bool result = compile("\"a\" + \"b\"", chunk);
    restore_output();
    assert(result);
    assert(chunk.count() == 6);
    assert(chunk.code(0) == static_cast<uint8_t>(OpCode::OP_CONSTANT));
    assert(strcmp(AS_CSTRING(chunk.constant(0)), "a") == 0);
    assert(chunk.code(2) == static_cast<uint8_t>(OpCode::OP_CONSTANT));
    assert(strcmp(AS_CSTRING(chunk.constant(1)), "b") == 0);
    assert(chunk.code(4) == static_cast<uint8_t>(OpCode::OP_ADD));
    assert(chunk.code(5) == static_cast<uint8_t>(OpCode::OP_RETURN));
    freeObjects(objects);
    setObjectList(nullptr);
}

TEST(test_vm_string_literal) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("\"hello\"");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_string_concatenation) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("\"hello\" + \" world\"");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_string_equality_true) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("\"abc\" == \"abc\"");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_string_equality_false) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("\"abc\" == \"def\"");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_string_not_equal_number) {
    suppress_output();
    VM vm;
    // Strings and numbers are never equal (different types)
    InterpretResult result = vm.interpret("\"1\" == 1");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_string_plus_number_error) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("\"hello\" + 1");
    restore_output();
    assert(result == InterpretResult::INTERPRET_RUNTIME_ERROR);
}

TEST(test_vm_multi_concat) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("\"a\" + \"b\" + \"c\"");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_empty_string) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("\"\"");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_empty_string_concat) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("\"\" + \"hello\"");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

int main() {
    printf("=== Compiler Unit Tests (Chapter 19 - Strings) ===\n\n");

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

    // VM integration (Chapter 17)
    RUN_TEST(test_vm_compile_and_run);
    RUN_TEST(test_vm_complex_expression);
    RUN_TEST(test_vm_error_on_bad_source);
    RUN_TEST(test_vm_chunk_still_works);

    // Chapter 18: Types of Values
    printf("\n--- Chapter 18: Types of Values ---\n");
    RUN_TEST(test_compile_true);
    RUN_TEST(test_compile_false);
    RUN_TEST(test_compile_nil);
    RUN_TEST(test_compile_not);
    RUN_TEST(test_compile_equality);
    RUN_TEST(test_compile_inequality);
    RUN_TEST(test_compile_less);
    RUN_TEST(test_compile_greater);
    RUN_TEST(test_compile_less_equal);
    RUN_TEST(test_compile_greater_equal);
    RUN_TEST(test_vm_true_literal);
    RUN_TEST(test_vm_nil_literal);
    RUN_TEST(test_vm_not_false);
    RUN_TEST(test_vm_comparison);
    RUN_TEST(test_vm_equality);
    RUN_TEST(test_vm_negate_bool_error);
    RUN_TEST(test_vm_add_bool_error);

    // Chapter 19: Strings
    printf("\n--- Chapter 19: Strings ---\n");
    RUN_TEST(test_compile_string);
    RUN_TEST(test_compile_empty_string);
    RUN_TEST(test_compile_string_concat);
    RUN_TEST(test_bytecode_string);
    RUN_TEST(test_bytecode_string_concat);
    RUN_TEST(test_vm_string_literal);
    RUN_TEST(test_vm_string_concatenation);
    RUN_TEST(test_vm_string_equality_true);
    RUN_TEST(test_vm_string_equality_false);
    RUN_TEST(test_vm_string_not_equal_number);
    RUN_TEST(test_vm_string_plus_number_error);
    RUN_TEST(test_vm_multi_concat);
    RUN_TEST(test_vm_empty_string);
    RUN_TEST(test_vm_empty_string_concat);

    printf("\n=== Results: %d/%d tests passed ===\n", tests_passed, tests_run);

    if (devnull) fclose(devnull);

    return tests_passed == tests_run ? 0 : 1;
}
