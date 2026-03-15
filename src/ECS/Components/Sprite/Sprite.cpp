#include "Sprite.hpp"
#include "../../../rica.hpp"

bool SpriteComponent::LoadTextureSprite(const char* path) {
  if (texture.id != 0) {
    UnloadTexture(texture);
    LOG_DEBUG("Previous texture unloaded");
  }

  texture = LoadTexture(path);
  LOG_DEBUG("Loading texture");

  if (texture.id == 0) {
    LOG_ERROR("Failed to load texture");
    return false;
  }

  LOG_INFO("Texture loaded successfully");

  source = {0, 0, (float)texture.width, (float)texture.height};
  color = WHITE;

  return true;
}

SpriteComponent::SpriteComponent(const std::string& path) {
  LoadTextureSprite(path.c_str());
}
