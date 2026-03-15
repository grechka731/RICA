#include "viewport.hpp"
#include "../../../engine/Engine.hpp"
#include "../../../graphics/Render2D/Render2D.hpp"
#include "../../../graphics/Render3D/Render3D.hpp"
#include "../../../Scene/Scene.hpp"
#include "editor.hpp"
#include <imgui.h>
#include <rlImGui.h>
#include "raylib.h"

void Viewport::onUpdate() {
  if (ImGui::Begin("Viewport")) {
    ImGui::Text("Viewport");
    isWindowActive = ImGui::IsWindowHovered();
    bool isRightMousePressed = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);

    viewportPos = ImGui::GetCursorScreenPos();
    viewportSize = ImGui::GetContentRegionAvail();

    std::shared_ptr<Scene> scene = engine.getActiveScene();
    if (scene) {
      RenderTexture2D& targetTexture = engine.is3Dmode()
                                           ? render3Dsystem.getRenderTexture()
                                           : render2Dsystem.getRenderTexture();
      rlImGuiImageRenderTextureFit(&targetTexture, false);

      if (ImGui::IsItemClicked(0) && isWindowActive) {
        ImVec2 mousePos = ImGui::GetMousePos();
        
        auto entities = scene->getAllEntities();
        for (auto& entity : entities) {
          if (auto mesh = entity->getComponent<MeshComponent>()) {
            selectedEntity = entity;
            break;
          }
        }
      }
    }

    if (isWindowActive && IsKeyPressed(KEY_ESCAPE)) {
      isWindowActive = false;
    }
  }
  ImGui::End();

  bool shouldControlCamera = isWindowActive && !IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
  
  if (shouldControlCamera) {
    HideCursor();
  } else {
    ShowCursor();
  }
}

bool Viewport::getiswindowActive() const {
  return isWindowActive;
}
