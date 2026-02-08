// Main entry point for the Lox interpreter
// Supports multiple modes:
//   ./clox                  - Interactive REPL
//   ./clox <file>           - Execute a .lox file
//   ./clox --demo           - Run demo with sample Lox code through the compiler
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

    printf("clox REPL (Chapter 16 - Scanning on Demand)\n");
    printf("Type Lox code. Press Ctrl+D to exit.\n\n");

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

static const char* DEMO_SOURCE = R"(
// Variable declarations
var x = 10;
var name = "hello";

// Function
fun add(a, b) {
    return a + b;
}

// Control flow
if (x >= 5) {
    print x;
} else {
    print "small";
}

// Loop
while (x > 0) {
    x = x - 1;
}

// Class
class Point {
    init(x, y) {
        this.x = x;
        this.y = y;
    }
}
)";

static void runDemo() {
    printf("=== Compiler Demo (Chapter 16 - Scanning on Demand) ===\n\n");
    printf("Source code:\n");
    printf("------------------------------\n");
    printf("%s", DEMO_SOURCE);
    printf("------------------------------\n\n");

    printf("Compiler output (token type ID + lexeme):\n");
    printf("------------------------------\n");
    compile(DEMO_SOURCE);
    printf("------------------------------\n\n");

    printf("Scanner output (token type name + lexeme):\n");
    printf("------------------------------\n");
    runScanner(DEMO_SOURCE);
    printf("------------------------------\n");
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

    printf("Step 2: Compiler pass\n");
    printf("------------------------------\n");
    bool ok = compile(source);
    printf("------------------------------\n");
    printf("Compilation %s\n\n", ok ? "succeeded" : "FAILED (had errors)");
}

// ---- Self-tests ----

static int tests_run = 0;
static int tests_passed = 0;
static FILE* devnull_ = nullptr;
static FILE* saved_stdout_ = nullptr;

static void suppress_output() {
    if (!devnull_) devnull_ = fopen("/dev/null", "w");
    if (devnull_) {
        saved_stdout_ = stdout;
        stdout = devnull_;
    }
}

static void restore_output() {
    if (saved_stdout_) {
        stdout = saved_stdout_;
        saved_stdout_ = nullptr;
    }
}

#define RUN_SELF_TEST(name) do { \
    fprintf(saved_stdout_ ? saved_stdout_ : stdout, \
            "  %-40s ", #name); \
    tests_run++; \
    if (name()) { \
        tests_passed++; \
        fprintf(saved_stdout_ ? saved_stdout_ : stdout, "PASS\n"); \
    } else { \
        fprintf(saved_stdout_ ? saved_stdout_ : stdout, "FAIL\n"); \
    } \
} while(0)

static bool test_compile_empty() {
    return compile("");
}

static bool test_compile_simple_expression() {
    return compile("1 + 2;");
}

static bool test_compile_keywords() {
    return compile("var x = true; if (x) print x; while (false) nil;");
}

static bool test_compile_string_literal() {
    return compile("\"hello world\"");
}

static bool test_compile_error_unterminated_string() {
    return !compile("\"oops");
}

static bool test_compile_error_unexpected_char() {
    return !compile("@");
}

static bool test_compile_multiline() {
    return compile("var a = 1;\nvar b = 2;\nprint a + b;");
}

static bool test_compile_comments() {
    return compile("var x = 1; // this is a comment\nvar y = 2;");
}

static bool test_compile_class_definition() {
    return compile("class Foo { init() { this.x = 0; } }");
}

static bool test_compile_function_definition() {
    return compile("fun greet(name) { print name; return nil; }");
}

static bool test_vm_interpret_source() {
    VM vm;
    InterpretResult result = vm.interpret("var x = 42;");
    return result == InterpretResult::INTERPRET_OK;
}

static bool test_vm_interpret_chunk_still_works() {
    Chunk chunk;
    int c = chunk.addConstant(99.0);
    chunk.write(static_cast<uint8_t>(OpCode::OP_CONSTANT), 1);
    chunk.write(static_cast<uint8_t>(c), 1);
    chunk.write(static_cast<uint8_t>(OpCode::OP_RETURN), 1);

    VM vm;
    InterpretResult result = vm.interpret(&chunk);
    return result == InterpretResult::INTERPRET_OK;
}

static void runTests() {
    printf("=== Compiler & VM Self-Tests ===\n\n");
    printf("Compiler tests:\n");

    // Suppress compile() token output, but keep test names visible
    suppress_output();

    RUN_SELF_TEST(test_compile_empty);
    RUN_SELF_TEST(test_compile_simple_expression);
    RUN_SELF_TEST(test_compile_keywords);
    RUN_SELF_TEST(test_compile_string_literal);
    RUN_SELF_TEST(test_compile_error_unterminated_string);
    RUN_SELF_TEST(test_compile_error_unexpected_char);
    RUN_SELF_TEST(test_compile_multiline);
    RUN_SELF_TEST(test_compile_comments);
    RUN_SELF_TEST(test_compile_class_definition);
    RUN_SELF_TEST(test_compile_function_definition);

    fprintf(saved_stdout_ ? saved_stdout_ : stdout,
            "\nVM source-interpret tests:\n");
    RUN_SELF_TEST(test_vm_interpret_source);
    RUN_SELF_TEST(test_vm_interpret_chunk_still_works);

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
    printf("  --demo           Run demo with sample Lox code\n");
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
