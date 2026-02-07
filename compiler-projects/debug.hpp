#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "chunk.hpp"

// Disassemble all instructions in a chunk
void disassembleChunk(const Chunk& chunk, const char* name);

// Disassemble a single instruction at the given offset
// Returns the offset of the next instruction
int disassembleInstruction(const Chunk& chunk, int offset);

#endif // DEBUG_HPP
