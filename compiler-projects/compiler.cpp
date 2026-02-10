#include "compiler.hpp"
#include "scanner.hpp"
#include "debug.hpp"
#include <cstdio>
#include <cstdlib>

// ---- Types ----

struct Parser {
    Token current;
    Token previous;
    bool hadError;
    bool panicMode;
};

enum class Precedence {
    PREC_NONE,
    PREC_ASSIGNMENT,  // =
    PREC_OR,          // or
    PREC_AND,         // and
    PREC_EQUALITY,    // == !=
    PREC_COMPARISON,  // < > <= >=
    PREC_TERM,        // + -
    PREC_FACTOR,      // * /
    PREC_UNARY,       // ! -
    PREC_CALL,        // . ()
    PREC_PRIMARY,
};

using ParseFn = void (*)();

struct ParseRule {
    ParseFn prefix;
    ParseFn infix;
    Precedence precedence;
};

// ---- State ----

static Parser parser;
static Scanner* currentScanner = nullptr;
static Chunk* compilingChunk = nullptr;

static Chunk* currentChunk() {
    return compilingChunk;
}

// ---- Error handling ----

static void errorAt(const Token& token, const char* message) {
    if (parser.panicMode) return;
    parser.panicMode = true;

    fprintf(stderr, "[line %d] Error", token.line);

    if (token.type == TokenType::END_OF_FILE) {
        fprintf(stderr, " at end");
    } else if (token.type != TokenType::ERROR) {
        fprintf(stderr, " at '%.*s'",
                static_cast<int>(token.lexeme.size()),
                token.lexeme.data());
    }

    fprintf(stderr, ": %s\n", message);
    parser.hadError = true;
}

static void error(const char* message) {
    errorAt(parser.previous, message);
}

static void errorAtCurrent(const char* message) {
    errorAt(parser.current, message);
}

// ---- Front end ----

static void advance() {
    parser.previous = parser.current;

    for (;;) {
        parser.current = currentScanner->scanToken();
        if (parser.current.type != TokenType::ERROR) break;

        errorAtCurrent(parser.current.lexeme.data());
    }
}

static void consume(TokenType type, const char* message) {
    if (parser.current.type == type) {
        advance();
        return;
    }

    errorAtCurrent(message);
}

// ---- Emitting bytecode ----

static void emitByte(uint8_t byte) {
    currentChunk()->write(byte, parser.previous.line);
}

static void emitBytes(uint8_t byte1, uint8_t byte2) {
    emitByte(byte1);
    emitByte(byte2);
}

static void emitReturn() {
    emitByte(static_cast<uint8_t>(OpCode::OP_RETURN));
}

static uint8_t makeConstant(Value value) {
    int constant = currentChunk()->addConstant(value);
    if (constant > UINT8_MAX) {
        error("Too many constants in one chunk.");
        return 0;
    }
    return static_cast<uint8_t>(constant);
}

static void emitConstant(Value value) {
    emitBytes(static_cast<uint8_t>(OpCode::OP_CONSTANT), makeConstant(value));
}

static void endCompiler() {
    emitReturn();
#ifdef DEBUG_PRINT_CODE
    if (!parser.hadError) {
        disassembleChunk(*currentChunk(), "code");
    }
#endif
}

// ---- Pratt parser ----

// Forward declarations
static void expression();
static ParseRule* getRule(TokenType type);
static void parsePrecedence(Precedence precedence);

static void number() {
    double value = strtod(parser.previous.lexeme.data(), nullptr);
    emitConstant(NUMBER_VAL(value));
}

static void literal() {
    switch (parser.previous.type) {
        case TokenType::FALSE: emitByte(static_cast<uint8_t>(OpCode::OP_FALSE)); break;
        case TokenType::NIL:   emitByte(static_cast<uint8_t>(OpCode::OP_NIL)); break;
        case TokenType::TRUE:  emitByte(static_cast<uint8_t>(OpCode::OP_TRUE)); break;
        default: return; // Unreachable.
    }
}

static void grouping() {
    expression();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
}

static void unary() {
    TokenType operatorType = parser.previous.type;

    // Compile the operand.
    parsePrecedence(Precedence::PREC_UNARY);

    // Emit the operator instruction.
    switch (operatorType) {
        case TokenType::BANG:
            emitByte(static_cast<uint8_t>(OpCode::OP_NOT));
            break;
        case TokenType::MINUS:
            emitByte(static_cast<uint8_t>(OpCode::OP_NEGATE));
            break;
        default: return; // Unreachable.
    }
}

static void binary() {
    TokenType operatorType = parser.previous.type;
    ParseRule* rule = getRule(operatorType);
    parsePrecedence(
        static_cast<Precedence>(static_cast<int>(rule->precedence) + 1));

    switch (operatorType) {
        case TokenType::BANG_EQUAL:
            emitBytes(static_cast<uint8_t>(OpCode::OP_EQUAL),
                      static_cast<uint8_t>(OpCode::OP_NOT)); break;
        case TokenType::EQUAL_EQUAL:
            emitByte(static_cast<uint8_t>(OpCode::OP_EQUAL)); break;
        case TokenType::GREATER:
            emitByte(static_cast<uint8_t>(OpCode::OP_GREATER)); break;
        case TokenType::GREATER_EQUAL:
            emitBytes(static_cast<uint8_t>(OpCode::OP_LESS),
                      static_cast<uint8_t>(OpCode::OP_NOT)); break;
        case TokenType::LESS:
            emitByte(static_cast<uint8_t>(OpCode::OP_LESS)); break;
        case TokenType::LESS_EQUAL:
            emitBytes(static_cast<uint8_t>(OpCode::OP_GREATER),
                      static_cast<uint8_t>(OpCode::OP_NOT)); break;
        case TokenType::PLUS:
            emitByte(static_cast<uint8_t>(OpCode::OP_ADD)); break;
        case TokenType::MINUS:
            emitByte(static_cast<uint8_t>(OpCode::OP_SUBTRACT)); break;
        case TokenType::STAR:
            emitByte(static_cast<uint8_t>(OpCode::OP_MULTIPLY)); break;
        case TokenType::SLASH:
            emitByte(static_cast<uint8_t>(OpCode::OP_DIVIDE)); break;
        default: return; // Unreachable.
    }
}

// Parse rules table — one entry per TokenType, in enum declaration order.
static ParseRule rules[] = {
    /* LEFT_PAREN    */ {grouping, nullptr, Precedence::PREC_NONE},
    /* RIGHT_PAREN   */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* LEFT_BRACE    */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* RIGHT_BRACE   */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* COMMA         */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* DOT           */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* MINUS         */ {unary,    binary,  Precedence::PREC_TERM},
    /* PLUS          */ {nullptr,  binary,  Precedence::PREC_TERM},
    /* SEMICOLON     */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* SLASH         */ {nullptr,  binary,  Precedence::PREC_FACTOR},
    /* STAR          */ {nullptr,  binary,  Precedence::PREC_FACTOR},
    /* BANG          */ {unary,    nullptr, Precedence::PREC_NONE},
    /* BANG_EQUAL    */ {nullptr,  binary,  Precedence::PREC_EQUALITY},
    /* EQUAL         */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* EQUAL_EQUAL   */ {nullptr,  binary,  Precedence::PREC_EQUALITY},
    /* GREATER       */ {nullptr,  binary,  Precedence::PREC_COMPARISON},
    /* GREATER_EQUAL */ {nullptr,  binary,  Precedence::PREC_COMPARISON},
    /* LESS          */ {nullptr,  binary,  Precedence::PREC_COMPARISON},
    /* LESS_EQUAL    */ {nullptr,  binary,  Precedence::PREC_COMPARISON},
    /* IDENTIFIER    */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* STRING        */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* NUMBER        */ {number,   nullptr, Precedence::PREC_NONE},
    /* AND           */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* CLASS         */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* ELSE          */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* FALSE         */ {literal,  nullptr, Precedence::PREC_NONE},
    /* FOR           */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* FUN           */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* IF            */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* NIL           */ {literal,  nullptr, Precedence::PREC_NONE},
    /* OR            */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* PRINT         */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* RETURN        */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* SUPER         */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* THIS          */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* TRUE          */ {literal,  nullptr, Precedence::PREC_NONE},
    /* VAR           */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* WHILE         */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* ERROR         */ {nullptr,  nullptr, Precedence::PREC_NONE},
    /* END_OF_FILE   */ {nullptr,  nullptr, Precedence::PREC_NONE},
};

static ParseRule* getRule(TokenType type) {
    return &rules[static_cast<int>(type)];
}

static void parsePrecedence(Precedence precedence) {
    advance();
    ParseFn prefixRule = getRule(parser.previous.type)->prefix;
    if (prefixRule == nullptr) {
        error("Expect expression.");
        return;
    }

    prefixRule();

    while (precedence <= getRule(parser.current.type)->precedence) {
        advance();
        ParseFn infixRule = getRule(parser.previous.type)->infix;
        infixRule();
    }
}

static void expression() {
    parsePrecedence(Precedence::PREC_ASSIGNMENT);
}

// ---- Public API ----

bool compile(std::string_view source, Chunk& chunk) {
    Scanner scanner(source);
    currentScanner = &scanner;
    compilingChunk = &chunk;

    parser.hadError = false;
    parser.panicMode = false;

    advance();
    expression();
    consume(TokenType::END_OF_FILE, "Expect end of expression.");
    endCompiler();

    currentScanner = nullptr;
    compilingChunk = nullptr;

    return !parser.hadError;
}
