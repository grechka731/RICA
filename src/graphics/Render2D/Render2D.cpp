#include "Render2D.hpp"
#include "../rica.hpp"
#include "Camera2D/Camera2D.hpp"
#include "raylib.h"
#include <iostream>

Render2DSystem& render2Dsystem = Render2DSystem::getInstance();

void Render2DSystem::init(int screenWidth, int screenHeight) {
  width = screenWidth;
  height = screenHeight;
  renderTexture = LoadRenderTexture(width, height);
  LOG_INFO("2D Render system initialized");
}

void Render2DSystem::update(const std::vector<std::shared_ptr<Entity>>& entities) {
  std::shared_ptr<Camera2DComponent> activeCamera = nullptr;
  for (auto entity : entities) {
    auto camera = entity->getComponent<Camera2DComponent>();
    if (camera && camera->isActiveCamera()) {
      activeCamera = camera;
      break;
    }
  }

  if (!activeCamera) {
    LOG_WARN("No active camera found for 2D rendering");
  }

  BeginTextureMode(renderTexture);
  if (activeCamera) {
    BeginMode2D(activeCamera->getCamera2D());
  }

  int spriteCount = 0;
  for (auto entity : entities) {
    auto sprite = entity->getComponent<SpriteComponent>();
    auto transform = entity->getComponent<TransformComponent>();

    if (!sprite || !transform)
      continue;

    spriteCount++;
    DrawTexturePro(sprite->getTexture(), sprite->getSource(),
                   transform->getDest(), transform->getOrigin(),
                   transform->getRotation(), sprite->getColor());
  }

  if (activeCamera) {
    EndMode2D();
  }

  EndTextureMode();
  LOG_DEBUG("2D Render updated");
}
