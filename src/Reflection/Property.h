#pragma once

enum PropType{
    INT,
    FLOAT,
    STRING,
    VEC3,
    VEC2,
    BOOL,
    COLOR,
    RECT,
    UNKNOWN
};

struct PropertyInfo{
    const char* name;
    void* ptr;
    PropType type;

    PropertyInfo(const char* n, void* p, PropType t) 
        : name(n), ptr(p), type(t) {}
};
