#ifndef VM_HPP
#define VM_HPP

#include "chunk.hpp"
#include "value.hpp"
#include <string_view>

// Forward declaration
struct Obj;

constexpr int STACK_MAX = 256;

enum class InterpretResult {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
};

class VM {
public:
    VM();
    ~VM();

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

    // Peek at a value on the stack without popping
    Value peek(int distance) const { return stackTop_[-1 - distance]; }

private:
    InterpretResult run();
    void resetStack();
    void runtimeError(const char* format, ...);
    bool isFalsey(Value value);
    void concatenate();

    Chunk* chunk_;
    uint8_t* ip_;           // Instruction pointer
    Value stack_[STACK_MAX];
    Value* stackTop_;       // Points just past the top element
    Obj* objects_;          // Head of linked list of all heap objects
};

#endif // VM_HPP
