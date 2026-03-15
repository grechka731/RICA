#pragma once
#include "../../Component.hpp"
#include <cmath>

class TransformComponent : public Component {
public:
  TransformComponent()
    : position({0.0f, 0.0f}), rotation(0.0f), scale(1.0f), width(0.0f), height(0.0f) {
    // ✅ Регистрируем поля для Details панели
    var(position, &position);
    var(rotation, &rotation);
    var(scale, &scale);
    var(width, &width);
    var(height, &height);
  }

  const char* getComponentName() const override { return "Transform2D"; }

  void set(Vector2 position, float rotation, float scale, float width,
           float height) {
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    this->width = width;  
    this->height = height; 
  }

  const Vector2& getPosition() const {
    return position;
  }

  float getRotation() const {
    return rotation;
  }

  float getScale() const {
    return scale;
  }
  
  float getWidth() const {
    return width;
  }

  float getHeight() const {
    return height;
  }

  float getScaledWidth() const {
      return width * scale;
  }
  
  float getScaledHeight() const {
      return height * scale;
  }

  Rectangle getDest() const {
    float scaledWidth = getScaledWidth();
    float scaledHeight = getScaledHeight();

    return {position.x - scaledWidth / 2.0f, position.y - scaledHeight / 2.0f,
            scaledWidth, scaledHeight};
  }

  Vector2 getOrigin() const {
    return {
        getScaledWidth() / 2.0f, 
        getScaledHeight() / 2.0f 
    };
  }



  void setPosition(const Vector2& pos) {
    this->position = pos;
  }
  
  void setPosition(float x, float y) {
    this->position.x = x;
    this->position.y = y;
  }

  void setRotation(float rotation) {
    this->rotation = rotation;
  }

  void setScale(float scale) {
    this->scale = scale;
  }

  void setWidth(float width) {
    this->width = width;
  }

  void setHeight(float height) {
    this->height = height;
  }

private:
  Vector2 position;
  float rotation;
  float scale;
  float width;
  float height;
};
