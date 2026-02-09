#ifndef COMPILER_HPP
#define COMPILER_HPP

#include "chunk.hpp"
#include <string_view>

// Compile a single expression from source code into bytecode.
// Returns true if compilation succeeded (no errors), false otherwise.
bool compile(std::string_view source, Chunk& chunk);

#endif // COMPILER_HPP
