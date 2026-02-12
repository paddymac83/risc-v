#include "value.hpp"
#include "object.hpp"
#include <cstdio>
#include <cstring>

void printValue(Value value) {
    switch (value.type) {
        case ValueType::VAL_BOOL:
            printf(AS_BOOL(value) ? "true" : "false");
            break;
        case ValueType::VAL_NIL:
            printf("nil");
            break;
        case ValueType::VAL_NUMBER:
            printf("%g", AS_NUMBER(value));
            break;
        case ValueType::VAL_OBJ:
            printObject(value);
            break;
    }
}

bool valuesEqual(Value a, Value b) {
    if (a.type != b.type) return false;
    switch (a.type) {
        case ValueType::VAL_BOOL:   return AS_BOOL(a) == AS_BOOL(b);
        case ValueType::VAL_NIL:    return true;
        case ValueType::VAL_NUMBER: return AS_NUMBER(a) == AS_NUMBER(b);
        case ValueType::VAL_OBJ: {
            ObjString* aString = AS_STRING(a);
            ObjString* bString = AS_STRING(b);
            return aString->length == bString->length &&
                memcmp(aString->chars, bString->chars,
                       aString->length) == 0;
        }
        default:                    return false; // Unreachable.
    }
}
