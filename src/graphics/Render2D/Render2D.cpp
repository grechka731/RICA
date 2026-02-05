#include "Render2D.hpp"
#include "../rica.hpp"
#include "Camera2D/Camera2D.hpp"
#include "raylib.h"
#include <iostream>

Render2DSystem& render2Dsystem = Render2DSystem::getInstance();

void Render2DSystem::init(int screenWidth, int screenHeight) {
width=screenWidth;
height=screenHeight;
renderTexture = LoadRenderTexture(width, height);
}

void Render2DSystem::Draw(const std::vector<RenderObject2D>& objects) {
  BeginTextureMode(renderTexture);
  ClearBackground(BLACK);

  for (const auto& obj : objects) {
    if (!obj.isLoaded)
      continue;

    DrawTexturePro(obj.texture, obj.source, obj.dest, obj.origin, obj.rotation,
                   obj.tint);
  }

  EndTextureMode();
}
