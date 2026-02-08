#include "vm.hpp"
#include "compiler.hpp"
#include "debug.hpp"
#include <cstdio>

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

InterpretResult VM::interpret(std::string_view source) {
    if (!compile(source)) {
        return InterpretResult::INTERPRET_COMPILE_ERROR;
    }
    return InterpretResult::INTERPRET_OK;
}

InterpretResult VM::interpret(Chunk* chunk) {
    chunk_ = chunk;
    ip_ = const_cast<uint8_t*>(chunk_->code().data());
    return run();
}

InterpretResult VM::run() {
#define READ_BYTE() (*ip_++)
#define READ_CONSTANT() (chunk_->constant(READ_BYTE()))
#define BINARY_OP(op) \
    do { \
        double b = pop(); \
        double a = pop(); \
        push(a op b); \
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
            case static_cast<uint8_t>(OpCode::OP_ADD):      BINARY_OP(+); break;
            case static_cast<uint8_t>(OpCode::OP_SUBTRACT): BINARY_OP(-); break;
            case static_cast<uint8_t>(OpCode::OP_MULTIPLY): BINARY_OP(*); break;
            case static_cast<uint8_t>(OpCode::OP_DIVIDE):   BINARY_OP(/); break;
            case static_cast<uint8_t>(OpCode::OP_NEGATE): {
                push(-pop());
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
