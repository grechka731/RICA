#pragma once
#include "../../Component.hpp"
#include <raymath.h>

class Collider2DComponent : public Component {
public:
  Collider2DComponent(Vector2 position, int width, int height, bool isTrigger) {
    // ✅ Регистрируем поля для Details панели
    this->isTrigger = isTrigger;
    this->position.x = position.x;
    this->position.y = position.y;
    this->width = width;
    this->height = height;
    var(isTrigger, &this->isTrigger);
    var(position, &this->position);
    var(width, &this->width);
    var(height, &this->height);
  }

  Collider2DComponent() {
    // ✅ Регистрируем поля для Details панели
    var(isTrigger, &isTrigger);
    var(position, &position);
    var(width, &width);
    var(height, &height);
  }

  const char* getComponentName() const override { return "Collider2D"; }

  void setTrigger(bool isTrigger) {
    this->isTrigger = isTrigger;
  }
  void setWidth(int width) {
    this->width = width;
  }
  void setHeight(int height) {
    this->height = height;
  }

  bool getTrigger() {
    return isTrigger;
  }
  Vector2 getPosition() {
    return position;
  }
  int getWidth() {
    return width;
  }
  int getHeight() {
    return height;
  }

  friend class Collider2DSystem;

private:
  bool isTrigger = false;
  Vector2 position;
  int width, height;

  void setX(int x) {
    position.x = x;
  }
  void setY(int y) {
    position.y = y;
  }
};
