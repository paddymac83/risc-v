#include "chunk.hpp"

void Chunk::write(uint8_t byte, int line) {
    code_.push_back(byte);
    lines_.push_back(line);
}

int Chunk::addConstant(Value value) {
    constants_.push_back(value);
    return static_cast<int>(constants_.size() - 1);
}

const char* opCodeName(OpCode code) {
    switch (code) {
        case OpCode::OP_CONSTANT: return "OP_CONSTANT";
        case OpCode::OP_NIL:      return "OP_NIL";
        case OpCode::OP_TRUE:     return "OP_TRUE";
        case OpCode::OP_FALSE:    return "OP_FALSE";
        case OpCode::OP_EQUAL:    return "OP_EQUAL";
        case OpCode::OP_GREATER:  return "OP_GREATER";
        case OpCode::OP_LESS:     return "OP_LESS";
        case OpCode::OP_ADD:      return "OP_ADD";
        case OpCode::OP_SUBTRACT: return "OP_SUBTRACT";
        case OpCode::OP_MULTIPLY: return "OP_MULTIPLY";
        case OpCode::OP_DIVIDE:   return "OP_DIVIDE";
        case OpCode::OP_NOT:      return "OP_NOT";
        case OpCode::OP_NEGATE:   return "OP_NEGATE";
        case OpCode::OP_RETURN:   return "OP_RETURN";
    }
    return "UNKNOWN";
}
