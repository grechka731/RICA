#include "Input.hpp"
#include "../rica.hpp"

#ifdef EDITOR
#include "../editor/editor/editor.hpp"
bool isViewportFocused() {
  return editor.getViewport().getiswindowActive();
}
#endif

Input& input = Input::getInstance();
