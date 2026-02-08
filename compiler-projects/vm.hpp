#ifndef VM_HPP
#define VM_HPP

#include "chunk.hpp"
#include "value.hpp"
#include <string_view>

constexpr int STACK_MAX = 256;

enum class InterpretResult {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
};

class VM {
public:
    VM();

    // Interpret source code (scanning on demand - Chapter 16)
    InterpretResult interpret(std::string_view source);

    // Interpret a pre-built chunk of bytecode (for direct bytecode tests)
    InterpretResult interpret(Chunk* chunk);

    // Stack operations (public for testing)
    void push(Value value);
    Value pop();

    // Stack inspection (for testing/debugging)
    Value stackTop() const { return stackTop_[-1]; }
    int stackSize() const { return static_cast<int>(stackTop_ - stack_); }

private:
    InterpretResult run();
    void resetStack();

    Chunk* chunk_;
    uint8_t* ip_;           // Instruction pointer
    Value stack_[STACK_MAX];
    Value* stackTop_;       // Points just past the top element
};

#endif // VM_HPP
