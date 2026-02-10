// Main entry point for the Lox interpreter
// Supports multiple modes:
//   ./clox                  - Interactive REPL
//   ./clox <file>           - Execute a .lox file
//   ./clox --demo           - Run demo: compile & execute a sample expression
//   ./clox --scan [file]    - Scan-only mode (print tokens without compiling)
//   ./clox --debug [file]   - Debug mode (verbose output through compiler)
//   ./clox --test           - Run built-in self-tests
//   ./clox --help           - Show usage

#include "common.hpp"
#include "compiler.hpp"
#include "scanner.hpp"
#include "vm.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

// ---- File reading ----

static std::string readFile(const char* path) {
    std::ifstream file(path);
    if (!file) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// ---- REPL ----

static void repl() {
    VM vm;
    std::string line;

    printf("clox REPL (Chapter 18 - Types of Values)\n");
    printf("Type an expression. Press Ctrl+D to exit.\n\n");

    for (;;) {
        printf("> ");

        if (!std::getline(std::cin, line)) {
            printf("\n");
            break;
        }

        vm.interpret(line);
    }
}

// ---- File execution ----

static void runFile(const char* path) {
    std::string source = readFile(path);

    VM vm;
    InterpretResult result = vm.interpret(std::string_view(source));

    if (result == InterpretResult::INTERPRET_COMPILE_ERROR) exit(65);
    if (result == InterpretResult::INTERPRET_RUNTIME_ERROR) exit(70);
}

// ---- Scan-only mode (original scanner behavior) ----

static void runScanner(std::string_view source) {
    Scanner scanner(source);

    int line = -1;
    for (;;) {
        Token token = scanner.scanToken();

        if (token.line != line) {
            std::cout << std::setw(4) << token.line << " ";
            line = token.line;
        } else {
            std::cout << "   | ";
        }

        std::cout << std::setw(16) << std::left << tokenTypeName(token.type)
                  << " '" << token.lexeme << "'" << std::endl;

        if (token.type == TokenType::END_OF_FILE) break;
    }
}

// ---- Demo mode ----

static const char* DEMO_SOURCE = "!(5 - 4 > 3 * 2 == !nil)";

static void runDemo() {
    printf("=== Compiler Demo (Chapter 18 - Types of Values) ===\n\n");
    printf("Expression: %s\n", DEMO_SOURCE);
    printf("Expected:   true\n\n");

    printf("Scanner output:\n");
    printf("------------------------------\n");
    runScanner(DEMO_SOURCE);
    printf("------------------------------\n\n");

    printf("Compilation + Execution:\n");
    printf("------------------------------\n");
    VM vm;
    InterpretResult result = vm.interpret(DEMO_SOURCE);
    printf("------------------------------\n");
    printf("Result: %s\n",
           result == InterpretResult::INTERPRET_OK ? "OK" : "ERROR");
}

// ---- Debug mode ----

static void runDebug(const char* path) {
    std::string source;
    if (path) {
        source = readFile(path);
    } else {
        source = DEMO_SOURCE;
    }

    printf("=== Debug Mode ===\n\n");
    printf("Source (%zu bytes):\n", source.size());
    printf("------------------------------\n");
    printf("%s\n", source.c_str());
    printf("------------------------------\n\n");

    printf("Step 1: Scanner tokens\n");
    printf("------------------------------\n");
    runScanner(source);
    printf("------------------------------\n\n");

    printf("Step 2: Compile + Execute\n");
    printf("------------------------------\n");
    VM vm;
    InterpretResult result = vm.interpret(std::string_view(source));
    printf("------------------------------\n");
    printf("Result: %s\n",
           result == InterpretResult::INTERPRET_OK ? "OK" :
           result == InterpretResult::INTERPRET_COMPILE_ERROR ? "COMPILE ERROR" :
           "RUNTIME ERROR");
}

// ---- Self-tests ----

static int tests_run = 0;
static int tests_passed = 0;
static FILE* devnull_ = nullptr;
static FILE* saved_stdout_ = nullptr;
static FILE* saved_stderr_ = nullptr;

static void suppress_output() {
    if (!devnull_) devnull_ = fopen("/dev/null", "w");
    if (devnull_) {
        saved_stdout_ = stdout;
        stdout = devnull_;
        saved_stderr_ = stderr;
        stderr = devnull_;
    }
}

static void restore_output() {
    if (saved_stdout_) {
        stdout = saved_stdout_;
        saved_stdout_ = nullptr;
    }
    if (saved_stderr_) {
        stderr = saved_stderr_;
        saved_stderr_ = nullptr;
    }
}

#define RUN_SELF_TEST(name) do { \
    FILE* out = saved_stdout_ ? saved_stdout_ : stdout; \
    fprintf(out, "  %-40s ", #name); \
    tests_run++; \
    if (name()) { \
        tests_passed++; \
        fprintf(out, "PASS\n"); \
    } else { \
        fprintf(out, "FAIL\n"); \
    } \
} while(0)

// Expression compilation tests
static bool test_compile_number() {
    Chunk chunk;
    return compile("42", chunk);
}

static bool test_compile_arithmetic() {
    Chunk chunk;
    return compile("1 + 2 * 3", chunk);
}

static bool test_compile_negation() {
    Chunk chunk;
    return compile("-42", chunk);
}

static bool test_compile_grouping() {
    Chunk chunk;
    return compile("(1 + 2) * 3", chunk);
}

static bool test_compile_complex() {
    Chunk chunk;
    return compile("(-1 + 2) * 3 - -4", chunk);
}

// Error tests
static bool test_compile_error_empty() {
    Chunk chunk;
    return !compile("", chunk);
}

static bool test_compile_error_unexpected_char() {
    Chunk chunk;
    return !compile("@", chunk);
}

static bool test_compile_error_missing_paren() {
    Chunk chunk;
    return !compile("(1 + 2", chunk);
}

// VM tests
static bool test_vm_interpret_expression() {
    VM vm;
    InterpretResult result = vm.interpret("1 + 2");
    return result == InterpretResult::INTERPRET_OK;
}

static bool test_vm_interpret_complex() {
    VM vm;
    InterpretResult result = vm.interpret("(-1 + 2) * 3 - -4");
    return result == InterpretResult::INTERPRET_OK;
}

static bool test_vm_interpret_chunk_still_works() {
    Chunk chunk;
    int c = chunk.addConstant(NUMBER_VAL(99.0));
    chunk.write(static_cast<uint8_t>(OpCode::OP_CONSTANT), 1);
    chunk.write(static_cast<uint8_t>(c), 1);
    chunk.write(static_cast<uint8_t>(OpCode::OP_RETURN), 1);

    VM vm;
    InterpretResult result = vm.interpret(&chunk);
    return result == InterpretResult::INTERPRET_OK;
}

static bool test_vm_error_on_bad_source() {
    VM vm;
    InterpretResult result = vm.interpret("@@@");
    return result == InterpretResult::INTERPRET_COMPILE_ERROR;
}

static void runTests() {
    printf("=== Compiler & VM Self-Tests (Chapter 18) ===\n\n");
    printf("Compiler tests:\n");

    suppress_output();

    RUN_SELF_TEST(test_compile_number);
    RUN_SELF_TEST(test_compile_arithmetic);
    RUN_SELF_TEST(test_compile_negation);
    RUN_SELF_TEST(test_compile_grouping);
    RUN_SELF_TEST(test_compile_complex);

    FILE* out = saved_stdout_ ? saved_stdout_ : stdout;
    fprintf(out, "\nError tests:\n");
    RUN_SELF_TEST(test_compile_error_empty);
    RUN_SELF_TEST(test_compile_error_unexpected_char);
    RUN_SELF_TEST(test_compile_error_missing_paren);

    fprintf(out, "\nVM tests:\n");
    RUN_SELF_TEST(test_vm_interpret_expression);
    RUN_SELF_TEST(test_vm_interpret_complex);
    RUN_SELF_TEST(test_vm_interpret_chunk_still_works);
    RUN_SELF_TEST(test_vm_error_on_bad_source);

    restore_output();

    if (devnull_) { fclose(devnull_); devnull_ = nullptr; }

    printf("\n=== Results: %d/%d tests passed ===\n", tests_passed, tests_run);

    if (tests_passed != tests_run) exit(1);
}

// ---- Usage ----

static void printUsage() {
    printf("Usage: clox [options] [file]\n\n");
    printf("Options:\n");
    printf("  <file>           Execute a .lox source file\n");
    printf("  --demo           Run demo with sample expression\n");
    printf("  --scan [file]    Scan-only mode (print named tokens)\n");
    printf("  --debug [file]   Debug mode (scanner + compiler verbose output)\n");
    printf("  --test           Run built-in self-tests\n");
    printf("  --help           Show this help message\n");
    printf("\n");
    printf("With no arguments, starts an interactive REPL.\n");
}

// ---- Main ----

int main(int argc, char* argv[]) {
    if (argc == 1) {
        repl();
    } else if (strcmp(argv[1], "--help") == 0) {
        printUsage();
    } else if (strcmp(argv[1], "--demo") == 0) {
        runDemo();
    } else if (strcmp(argv[1], "--test") == 0) {
        runTests();
    } else if (strcmp(argv[1], "--scan") == 0) {
        if (argc > 2) {
            std::string source = readFile(argv[2]);
            printf("Scanning %s:\n", argv[2]);
            runScanner(source);
        } else {
            printf("Scanning sample code:\n");
            runScanner(DEMO_SOURCE);
        }
    } else if (strcmp(argv[1], "--debug") == 0) {
        runDebug(argc > 2 ? argv[2] : nullptr);
    } else if (argv[1][0] == '-') {
        fprintf(stderr, "Unknown option: %s\n", argv[1]);
        printUsage();
        exit(64);
    } else {
        runFile(argv[1]);
    }

    return 0;
}
