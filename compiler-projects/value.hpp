#ifndef VALUE_HPP
#define VALUE_HPP

#include "common.hpp"
#include <vector>

// For now, Value is just a double (as in Chapter 14)
// This will be expanded to a tagged union in later chapters
using Value = double;

// Dynamic array of values (constant pool)
using ValueArray = std::vector<Value>;

// Utility function to print a value
void printValue(Value value);

#endif // VALUE_HPP
