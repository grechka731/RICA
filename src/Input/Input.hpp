#pragma once
#include "raylib.h"

#ifdef EDITOR
bool isViewportFocused();
#endif

class Input {
private:
  Input() = default;

public:
  Input(const Input&) = delete;
  Input& operator=(const Input&) = delete;

  static Input& getInstance() {
    static Input instance;
    return instance;
  }

  static bool isKeyPressed(int key) {
#ifdef EDITOR
    if (!isViewportFocused())
      return false;
#endif
    return IsKeyPressed(key);
  }

  static bool isKeyReleased(int key) {
#ifdef EDITOR
    if (!isViewportFocused())
      return false;
#endif
    return IsKeyReleased(key);
  }

  static bool isKeyDown(int key) {
#ifdef EDITOR
    if (!isViewportFocused())
      return false;
#endif
    return IsKeyDown(key);
  }

  static bool isKeyUp(int key) {
#ifdef EDITOR
    if (!isViewportFocused())
      return false;
#endif
    return IsKeyUp(key);
  }
};

extern Input& input;