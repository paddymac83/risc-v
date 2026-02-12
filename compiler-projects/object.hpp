#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "common.hpp"
#include "value.hpp"

// Object types (Chapter 19)
enum class ObjType {
    OBJ_STRING,
};

// Base object struct — every heap-allocated Lox object starts with this.
// Objects form an intrusive linked list via `next` for GC tracking.
struct Obj {
    ObjType type;
    Obj* next;
};

// String object — owns a heap-allocated char array.
struct ObjString {
    Obj obj;        // "Inherits" from Obj (C-style struct embedding)
    int length;
    char* chars;
};

// Type checking helpers
inline ObjType OBJ_TYPE(Value value) { return AS_OBJ(value)->type; }

inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

inline bool IS_STRING(Value value) {
    return isObjType(value, ObjType::OBJ_STRING);
}

// Value extraction for strings
inline ObjString* AS_STRING(Value value) {
    return reinterpret_cast<ObjString*>(AS_OBJ(value));
}

inline const char* AS_CSTRING(Value value) {
    return (reinterpret_cast<ObjString*>(AS_OBJ(value)))->chars;
}

// Set the global pointer to the active VM's object list head.
// The VM calls this before compilation/execution so that
// allocateObject() can link new objects into the VM's list.
void setObjectList(Obj** listHead);

// Allocate a new ObjString that copies `length` bytes from `chars`.
ObjString* copyString(const char* chars, int length);

// Allocate a new ObjString that takes ownership of `chars`
// (caller must have allocated chars with new[]).
ObjString* takeString(char* chars, int length);

// Print an Obj-typed Value.
void printObject(Value value);

// Free a single object.
void freeObject(Obj* object);

// Free all objects in the linked list starting from `objects`.
void freeObjects(Obj* objects);

#endif // OBJECT_HPP
