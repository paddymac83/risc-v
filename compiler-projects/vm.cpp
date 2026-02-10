#include "vm.hpp"
#include "compiler.hpp"
#include "debug.hpp"
#include <cstdio>
#include <cstdarg>

VM::VM() : chunk_(nullptr), ip_(nullptr), stackTop_(nullptr) {
    resetStack();
}

void VM::resetStack() {
    stackTop_ = stack_;
}

void VM::push(Value value) {
    *stackTop_ = value;
    stackTop_++;
}

Value VM::pop() {
    stackTop_--;
    return *stackTop_;
}

void VM::runtimeError(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputs("\n", stderr);

    size_t instruction = ip_ - chunk_->code().data() - 1;
    int line = chunk_->line(instruction);
    fprintf(stderr, "[line %d] in script\n", line);
    resetStack();
}

bool VM::isFalsey(Value value) {
    return IS_NIL(value) || (IS_BOOL(value) && !AS_BOOL(value));
}

InterpretResult VM::interpret(std::string_view source) {
    Chunk chunk;
    if (!compile(source, chunk)) {
        return InterpretResult::INTERPRET_COMPILE_ERROR;
    }

    chunk_ = &chunk;
    ip_ = const_cast<uint8_t*>(chunk_->code().data());
    return run();
}

InterpretResult VM::interpret(Chunk* chunk) {
    chunk_ = chunk;
    ip_ = const_cast<uint8_t*>(chunk_->code().data());
    return run();
}

InterpretResult VM::run() {
#define READ_BYTE() (*ip_++)
#define READ_CONSTANT() (chunk_->constant(READ_BYTE()))
#define BINARY_OP(valueType, op) \
    do { \
        if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) { \
            runtimeError("Operands must be numbers."); \
            return InterpretResult::INTERPRET_RUNTIME_ERROR; \
        } \
        double b = AS_NUMBER(pop()); \
        double a = AS_NUMBER(pop()); \
        push(valueType(a op b)); \
    } while (false)

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        // Print stack contents
        printf("          ");
        for (Value* slot = stack_; slot < stackTop_; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
        disassembleInstruction(*chunk_,
            static_cast<int>(ip_ - chunk_->code().data()));
#endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case static_cast<uint8_t>(OpCode::OP_CONSTANT): {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case static_cast<uint8_t>(OpCode::OP_NIL):   push(NIL_VAL()); break;
            case static_cast<uint8_t>(OpCode::OP_TRUE):  push(BOOL_VAL(true)); break;
            case static_cast<uint8_t>(OpCode::OP_FALSE): push(BOOL_VAL(false)); break;
            case static_cast<uint8_t>(OpCode::OP_EQUAL): {
                Value b = pop();
                Value a = pop();
                push(BOOL_VAL(valuesEqual(a, b)));
                break;
            }
            case static_cast<uint8_t>(OpCode::OP_GREATER): BINARY_OP(BOOL_VAL, >); break;
            case static_cast<uint8_t>(OpCode::OP_LESS):    BINARY_OP(BOOL_VAL, <); break;
            case static_cast<uint8_t>(OpCode::OP_ADD):      BINARY_OP(NUMBER_VAL, +); break;
            case static_cast<uint8_t>(OpCode::OP_SUBTRACT): BINARY_OP(NUMBER_VAL, -); break;
            case static_cast<uint8_t>(OpCode::OP_MULTIPLY): BINARY_OP(NUMBER_VAL, *); break;
            case static_cast<uint8_t>(OpCode::OP_DIVIDE):   BINARY_OP(NUMBER_VAL, /); break;
            case static_cast<uint8_t>(OpCode::OP_NOT):
                push(BOOL_VAL(isFalsey(pop())));
                break;
            case static_cast<uint8_t>(OpCode::OP_NEGATE): {
                if (!IS_NUMBER(peek(0))) {
                    runtimeError("Operand must be a number.");
                    return InterpretResult::INTERPRET_RUNTIME_ERROR;
                }
                push(NUMBER_VAL(-AS_NUMBER(pop())));
                break;
            }
            case static_cast<uint8_t>(OpCode::OP_RETURN): {
                printValue(pop());
                printf("\n");
                return InterpretResult::INTERPRET_OK;
            }
        }
    }

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}
