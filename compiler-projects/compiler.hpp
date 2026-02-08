#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <string_view>

// Compile source code. At this stage (Chapter 16 - Scanning on Demand),
// the compiler scans tokens and prints them. In later chapters, this will
// produce bytecode in a Chunk.
//
// Returns true if compilation succeeded (no errors), false otherwise.
bool compile(std::string_view source);

#endif // COMPILER_HPP
