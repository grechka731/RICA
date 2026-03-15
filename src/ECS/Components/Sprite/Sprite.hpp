#pragma once

#include "../Component.hpp"
#include <raylib.h>

#include <string>

class SpriteComponent : public Component {
public:
  SpriteComponent(const std::string& path);
  
  SpriteComponent() {
    var(color, &color);
    var(source, &source);
  }

  const char* getComponentName() const override { return "Sprite"; }
  
  bool LoadTextureSprite(const char* path);

  void setColor(Color color) {
    this->color = color;
  }
  void setSource(float x, float y, float width, float height) {
    source = {x, y, width, height};
  }

  int getHeightSprite() {
    return texture.height;
  }
  int getWidthSprite() {
    return texture.width;
  }
  Color getColor() {
    return color;
  }
  Texture2D getTexture() {
    return texture;
  }
  Rectangle getSource() {
    return source;
  }

private:
  Texture2D texture{0};
  Color color = WHITE;
  Rectangle source{0, 0, 0, 0};
};
