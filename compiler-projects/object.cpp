#include "object.hpp"
#include <cstdio>
#include <cstring>

// Global pointer to the active VM's object list head.
// Set by the VM before compilation/execution via setObjectList().
static Obj** objectsHead = nullptr;

void setObjectList(Obj** listHead) {
    objectsHead = listHead;
}

// Allocate a raw Obj and link it into the VM's object list.
static Obj* allocateObject(size_t size, ObjType type) {
    // Use operator new for raw memory (mirrors C's reallocate(NULL, 0, size))
    Obj* object = reinterpret_cast<Obj*>(::operator new(size));
    object->type = type;

    // Link into the VM's object list for GC tracking
    if (objectsHead) {
        object->next = *objectsHead;
        *objectsHead = object;
    } else {
        object->next = nullptr;
    }

    return object;
}

static ObjString* allocateString(char* chars, int length) {
    ObjString* string = reinterpret_cast<ObjString*>(
        allocateObject(sizeof(ObjString), ObjType::OBJ_STRING));
    string->length = length;
    string->chars = chars;
    return string;
}

ObjString* copyString(const char* chars, int length) {
    char* heapChars = new char[length + 1];
    memcpy(heapChars, chars, length);
    heapChars[length] = '\0';
    return allocateString(heapChars, length);
}

ObjString* takeString(char* chars, int length) {
    return allocateString(chars, length);
}

void printObject(Value value) {
    switch (OBJ_TYPE(value)) {
        case ObjType::OBJ_STRING:
            printf("%s", AS_CSTRING(value));
            break;
    }
}

void freeObject(Obj* object) {
    switch (object->type) {
        case ObjType::OBJ_STRING: {
            ObjString* string = reinterpret_cast<ObjString*>(object);
            delete[] string->chars;
            ::operator delete(object);
            break;
        }
    }
}

void freeObjects(Obj* objects) {
    Obj* object = objects;
    while (object != nullptr) {
        Obj* next = object->next;
        freeObject(object);
        object = next;
    }
}
