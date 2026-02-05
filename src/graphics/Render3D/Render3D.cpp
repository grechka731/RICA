#include "Render3D.hpp"
#include "../rica.hpp"
#include "Camera3D/Camera3D.hpp"
#include "Transform3D/Transform3D.hpp"
#include "raylib.h"
#include <iostream>

Render3DSystem& render3Dsystem = Render3DSystem::getInstance();

void Render3DSystem::init(int screenWidth, int screenHeight) {
width=screenWidth;
height = screenHeight; 
renderTexture = LoadRenderTexture(width, height);
SetTextureFilter(renderTexture.texture, TEXTURE_FILTER_BILINEAR);
}

void Render3DSystem::Draw(
    const std::vector<RenderObject3D>& objects,
    const std::vector<std::shared_ptr<Entity>>& entities)
    /*почему же камера 
    будет проходить как ecs компонент?
    та емае так и делают
    */ {
  std::shared_ptr<Camera3DComponent> activeCamera = nullptr;

  // Камеру из ЕКС берем
  for (auto& entity : entities) {
    auto camera = entity->getComponent<Camera3DComponent>();

    if (camera && camera->isActiveCamera()) {
      activeCamera = camera;
      break;
    }
  }

  BeginTextureMode(renderTexture);
  ClearBackground(skyColor);

  if (activeCamera)
    BeginMode3D(activeCamera->getCamera3D());

  // рендер с нашей структурой(правильный подход,при смене ecs нам надо будет
  // переписать ecs-struct билдер а не рендер) та и просто правильнее так
  for (const auto& obj : objects) {
    if (!obj.isLoaded)
      continue;

    DrawModelEx(obj.model, obj.position, obj.rotationAxis, obj.rotationAngle,
                obj.scale, obj.tint);
  }

  if (activeCamera)
    EndMode3D();

  EndTextureMode();

}
