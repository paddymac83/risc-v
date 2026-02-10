#ifndef VALUE_HPP
#define VALUE_HPP

#include "common.hpp"
#include <vector>

// Tagged union value type (Chapter 18)
enum class ValueType {
    VAL_BOOL,
    VAL_NIL,
    VAL_NUMBER,
};

struct Value {
    ValueType type;
    union {
        bool boolean;
        double number;
    } as;

    // Default constructor (nil)
    Value() : type(ValueType::VAL_NIL) { as.number = 0; }

    // Named constructors
    static Value Bool(bool value) {
        Value v;
        v.type = ValueType::VAL_BOOL;
        v.as.boolean = value;
        return v;
    }

    static Value Nil() {
        Value v;
        v.type = ValueType::VAL_NIL;
        v.as.number = 0;
        return v;
    }

    static Value Number(double value) {
        Value v;
        v.type = ValueType::VAL_NUMBER;
        v.as.number = value;
        return v;
    }
};

// Type checking
inline bool IS_BOOL(Value value)   { return value.type == ValueType::VAL_BOOL; }
inline bool IS_NIL(Value value)    { return value.type == ValueType::VAL_NIL; }
inline bool IS_NUMBER(Value value) { return value.type == ValueType::VAL_NUMBER; }

// Value extraction
inline bool   AS_BOOL(Value value)   { return value.as.boolean; }
inline double AS_NUMBER(Value value) { return value.as.number; }

// Value creation (macro-style convenience)
inline Value BOOL_VAL(bool value)     { return Value::Bool(value); }
inline Value NIL_VAL()                { return Value::Nil(); }
inline Value NUMBER_VAL(double value) { return Value::Number(value); }

// Dynamic array of values (constant pool)
using ValueArray = std::vector<Value>;

// Utility functions
void printValue(Value value);
bool valuesEqual(Value a, Value b);

#endif // VALUE_HPP
