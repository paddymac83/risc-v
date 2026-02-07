#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "common.hpp"
#include "value.hpp"
#include <vector>

// Operation codes for the virtual machine
enum class OpCode : uint8_t {
    OP_CONSTANT,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_RETURN,
};

// A chunk of bytecode - represents a sequence of instructions
class Chunk {
public:
    Chunk() = default;

    // Write a byte to the chunk
    void write(uint8_t byte, int line);

    // Add a constant to the constant pool, returns its index
    int addConstant(Value value);

    // Accessors
    const std::vector<uint8_t>& code() const { return code_; }
    const std::vector<int>& lines() const { return lines_; }
    const ValueArray& constants() const { return constants_; }

    // Access individual elements
    uint8_t code(size_t index) const { return code_[index]; }
    int line(size_t index) const { return lines_[index]; }
    Value constant(size_t index) const { return constants_[index]; }

    size_t count() const { return code_.size(); }

private:
    std::vector<uint8_t> code_;     // The bytecode
    std::vector<int> lines_;        // Line numbers for each byte
    ValueArray constants_;          // Constant pool
};

// Helper to convert OpCode to string
const char* opCodeName(OpCode code);

#endif // CHUNK_HPP
