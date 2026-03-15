#pragma once

#include "Property.h"
#include "raylib.h"
#include <string>

inline PropType GetPropType(int)         { return PropType::INT; }
inline PropType GetPropType(float)       { return PropType::FLOAT; }
inline PropType GetPropType(Vector3)     { return PropType::VEC3; }
inline PropType GetPropType(Vector2)     { return PropType::VEC2; }
inline PropType GetPropType(bool)        { return PropType::BOOL; }
inline PropType GetPropType(std::string) { return PropType::STRING; }
inline PropType GetPropType(Color)       { return PropType::COLOR; }
inline PropType GetPropType(Rectangle)   { return PropType::RECT; }

inline PropType GetPropTypeFromPtr(int*)         { return PropType::INT; }
inline PropType GetPropTypeFromPtr(float*)       { return PropType::FLOAT; }
inline PropType GetPropTypeFromPtr(Vector3*)     { return PropType::VEC3; }
inline PropType GetPropTypeFromPtr(Vector2*)     { return PropType::VEC2; }
inline PropType GetPropTypeFromPtr(bool*)        { return PropType::BOOL; }
inline PropType GetPropTypeFromPtr(std::string*) { return PropType::STRING; }
inline PropType GetPropTypeFromPtr(Color*)       { return PropType::COLOR; }
inline PropType GetPropTypeFromPtr(Rectangle*)   { return PropType::RECT; }

#define VAR(name, value) \
    auto name = value; \
    this->addPropertyDetails(#name, &name, GetPropType(name))

#define var(name, ptr) this->addPropertyDetails(#name, (void*)(ptr), GetPropTypeFromPtr(ptr))
