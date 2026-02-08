#include "compiler.hpp"
#include "vm.hpp"
#include "chunk.hpp"
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

// Redirect stdout to suppress compile() output during tests
static FILE* devnull = nullptr;
static FILE* real_stdout = nullptr;

static void suppress_output() {
    if (!devnull) devnull = fopen("/dev/null", "w");
    if (devnull) {
        real_stdout = stdout;
        stdout = devnull;
    }
}

static void restore_output() {
    if (real_stdout) {
        stdout = real_stdout;
        real_stdout = nullptr;
    }
}

// ---- Compiler tests ----

TEST(test_compile_empty_string) {
    suppress_output();
    bool result = compile("");
    restore_output();
    assert(result && "Empty source should compile successfully");
}

TEST(test_compile_single_token) {
    suppress_output();
    bool result = compile("42");
    restore_output();
    assert(result && "Single number should compile");
}

TEST(test_compile_operators) {
    suppress_output();
    bool result = compile("1 + 2 - 3 * 4 / 5");
    restore_output();
    assert(result && "Arithmetic operators should compile");
}

TEST(test_compile_comparison_operators) {
    suppress_output();
    bool result = compile("1 < 2 <= 3 > 4 >= 5 == 6 != 7");
    restore_output();
    assert(result && "Comparison operators should compile");
}

TEST(test_compile_all_keywords) {
    suppress_output();
    bool result = compile(
        "and class else false for fun if nil or "
        "print return super this true var while"
    );
    restore_output();
    assert(result && "All keywords should compile without error");
}

TEST(test_compile_string_literal) {
    suppress_output();
    bool result = compile("\"hello world\"");
    restore_output();
    assert(result && "String literal should compile");
}

TEST(test_compile_empty_string_literal) {
    suppress_output();
    bool result = compile("\"\"");
    restore_output();
    assert(result && "Empty string literal should compile");
}

TEST(test_compile_identifiers) {
    suppress_output();
    bool result = compile("foo bar _baz quux123");
    restore_output();
    assert(result && "Identifiers should compile");
}

TEST(test_compile_var_declaration) {
    suppress_output();
    bool result = compile("var x = 10;");
    restore_output();
    assert(result && "Variable declaration should compile");
}

TEST(test_compile_function_definition) {
    suppress_output();
    bool result = compile("fun add(a, b) { return a + b; }");
    restore_output();
    assert(result && "Function definition should compile");
}

TEST(test_compile_class_definition) {
    suppress_output();
    bool result = compile("class Point { init(x, y) { this.x = x; this.y = y; } }");
    restore_output();
    assert(result && "Class definition should compile");
}

TEST(test_compile_if_else) {
    suppress_output();
    bool result = compile("if (true) print 1; else print 2;");
    restore_output();
    assert(result && "If-else should compile");
}

TEST(test_compile_while_loop) {
    suppress_output();
    bool result = compile("while (true) { print 1; }");
    restore_output();
    assert(result && "While loop should compile");
}

TEST(test_compile_for_loop) {
    suppress_output();
    bool result = compile("for (var i = 0; i < 10; i = i + 1) print i;");
    restore_output();
    assert(result && "For loop should compile");
}

TEST(test_compile_multiline) {
    suppress_output();
    bool result = compile("var a = 1;\nvar b = 2;\nvar c = a + b;");
    restore_output();
    assert(result && "Multiline source should compile");
}

TEST(test_compile_comments_ignored) {
    suppress_output();
    bool result = compile("var x = 1; // comment\nvar y = 2;");
    restore_output();
    assert(result && "Source with comments should compile");
}

TEST(test_compile_nested_braces) {
    suppress_output();
    bool result = compile("{ { { } } }");
    restore_output();
    assert(result && "Nested braces should compile");
}

// ---- Error cases ----

TEST(test_compile_unterminated_string) {
    suppress_output();
    bool result = compile("\"oops");
    restore_output();
    assert(!result && "Unterminated string should fail");
}

TEST(test_compile_unexpected_character) {
    suppress_output();
    bool result = compile("@");
    restore_output();
    assert(!result && "Unexpected character should fail");
}

TEST(test_compile_multiple_errors) {
    suppress_output();
    bool result = compile("@ # $");
    restore_output();
    assert(!result && "Multiple unexpected characters should fail");
}

// ---- VM source-interpret integration tests ----

TEST(test_vm_interpret_source) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("var x = 42;");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_interpret_empty_source) {
    suppress_output();
    VM vm;
    InterpretResult result = vm.interpret("");
    restore_output();
    assert(result == InterpretResult::INTERPRET_OK);
}

TEST(test_vm_chunk_interpret_still_works) {
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
    printf("=== Compiler Unit Tests ===\n\n");

    // Compiler tests
    RUN_TEST(test_compile_empty_string);
    RUN_TEST(test_compile_single_token);
    RUN_TEST(test_compile_operators);
    RUN_TEST(test_compile_comparison_operators);
    RUN_TEST(test_compile_all_keywords);
    RUN_TEST(test_compile_string_literal);
    RUN_TEST(test_compile_empty_string_literal);
    RUN_TEST(test_compile_identifiers);
    RUN_TEST(test_compile_var_declaration);
    RUN_TEST(test_compile_function_definition);
    RUN_TEST(test_compile_class_definition);
    RUN_TEST(test_compile_if_else);
    RUN_TEST(test_compile_while_loop);
    RUN_TEST(test_compile_for_loop);
    RUN_TEST(test_compile_multiline);
    RUN_TEST(test_compile_comments_ignored);
    RUN_TEST(test_compile_nested_braces);

    // Error tests
    RUN_TEST(test_compile_unterminated_string);
    RUN_TEST(test_compile_unexpected_character);
    RUN_TEST(test_compile_multiple_errors);

    // VM integration tests
    RUN_TEST(test_vm_interpret_source);
    RUN_TEST(test_vm_interpret_empty_source);
    RUN_TEST(test_vm_chunk_interpret_still_works);

    printf("\n=== Results: %d/%d tests passed ===\n", tests_passed, tests_run);

    if (devnull) fclose(devnull);

    return tests_passed == tests_run ? 0 : 1;
}
