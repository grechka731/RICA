#include "details.hpp"
#include "../../../engine/Engine.hpp"
#include "../../../graphics/Render2D/Render2D.hpp"
#include "../../../graphics/Render3D/Render3D.hpp"
#include "../../../editor/editor/editor.hpp"
#include "../../../Reflection/Property.h"
#include <imgui.h>
#include <rlImGui.h>

static void DisplayPropertyValue(const PropertyInfo& prop) {
  ImGui::PushID(prop.name);
  
  switch (prop.type) {
    case PropType::INT: {
      int* val = static_cast<int*>(prop.ptr);
      ImGui::InputInt(prop.name, val);
      break;
    }
    case PropType::FLOAT: {
      float* val = static_cast<float*>(prop.ptr);
      ImGui::InputFloat(prop.name, val);
      break;
    }
    case PropType::VEC3: {
      Vector3* val = static_cast<Vector3*>(prop.ptr);
      ImGui::Text("%s", prop.name);
      
      float inputWidth = 120.0f;
      float spacing = 4.0f;
      
      // X - зеленый
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.7f, 0.4f, 1.0f));
      ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.8f, 0.5f, 1.0f));
      ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.9f, 0.6f, 1.0f));
      ImGui::Button("##XColor", ImVec2(14, 18));
      ImGui::PopStyleColor(3);
      ImGui::SameLine(0, spacing);
      ImGui::SetNextItemWidth(inputWidth);
      ImGui::InputFloat("##X", &val->x, 0.1f);
      
      // Y - красный
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.4f, 0.4f, 1.0f));
      ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.5f, 0.5f, 1.0f));
      ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.9f, 0.6f, 0.6f, 1.0f));
      ImGui::Button("##YColor", ImVec2(14, 18));
      ImGui::PopStyleColor(3);
      ImGui::SameLine(0, spacing);
      ImGui::SetNextItemWidth(inputWidth);
      ImGui::InputFloat("##Y", &val->y, 0.1f);
      
      // Z - синий
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.4f, 0.7f, 1.0f));
      ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.5f, 0.8f, 1.0f));
      ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.6f, 0.9f, 1.0f));
      ImGui::Button("##ZColor", ImVec2(14, 18));
      ImGui::PopStyleColor(3);
      ImGui::SameLine(0, spacing);
      ImGui::SetNextItemWidth(inputWidth);
      ImGui::InputFloat("##Z", &val->z, 0.1f);
      
      break;
    }
    case PropType::VEC2: {
      Vector2* val = static_cast<Vector2*>(prop.ptr);
      float arr[2] = {val->x, val->y};
      if (ImGui::DragFloat2(prop.name, arr, 0.1f)) {
        val->x = arr[0];
        val->y = arr[1];
      }
      break;
    }
    case PropType::BOOL: {
      bool* val = static_cast<bool*>(prop.ptr);
      ImGui::Checkbox(prop.name, val);
      break;
    }
    case PropType::STRING: {
      ImGui::Text("%s: (string)", prop.name);
      break;
    }
    case PropType::COLOR: {
      Color* val = static_cast<Color*>(prop.ptr);
      float col[4] = {
        val->r / 255.0f,
        val->g / 255.0f,
        val->b / 255.0f,
        val->a / 255.0f
      };
      if (ImGui::ColorEdit4(prop.name, col)) {
        val->r = static_cast<unsigned char>(col[0] * 255.0f + 0.5f);
        val->g = static_cast<unsigned char>(col[1] * 255.0f + 0.5f);
        val->b = static_cast<unsigned char>(col[2] * 255.0f + 0.5f);
        val->a = static_cast<unsigned char>(col[3] * 255.0f + 0.5f);
      }
      break;
    }
    case PropType::RECT: {
      Rectangle* val = static_cast<Rectangle*>(prop.ptr);
      float rect[4] = { val->x, val->y, val->width, val->height };
      if (ImGui::InputFloat4(prop.name, rect)) {
        val->x = rect[0];
        val->y = rect[1];
        val->width = rect[2];
        val->height = rect[3];
      }
      break;
    }
    default:
      ImGui::Text("%s: (unknown)", prop.name);
  }
  
  ImGui::PopID();
}

void Details::onUpdate() {
  if (ImGui::Begin("Details")) {
    auto selectedEntity = editor.getViewport().getSelectedEntity();
    
    if (selectedEntity) {
      ImGui::Text("Entity ID: %d", selectedEntity->getID());
      ImGui::Text("Tag: %s", selectedEntity->getTag().c_str());
      
      ImGui::Separator();
      if (ImGui::CollapsingHeader("Entity Properties", ImGuiTreeNodeFlags_DefaultOpen)) {
        const auto& props = selectedEntity->getPropertyDetails();
        for (const auto& prop : props) {
          DisplayPropertyValue(prop);
        }
      }
      
      ImGui::Separator();
      if (ImGui::CollapsingHeader("Components", ImGuiTreeNodeFlags_DefaultOpen)) {
        const auto& components = selectedEntity->getComponents();
        for (const auto& comp : components) {
          if (!comp) continue;
          
          const char* compName = comp->getComponentName();
          if (ImGui::CollapsingHeader(compName)) {
            const auto& compProps = comp->getPropertyDetails();
            for (const auto& prop : compProps) {
              DisplayPropertyValue(prop);
            }
            if (compProps.empty()) {
              ImGui::Text("No properties");
            }
          }
        }
      }
      
    } else {
      ImGui::Text("No entity selected");
    }
  }
  ImGui::End();
}

bool Details::getiswindowActive() const {
  return isWindowActive;
}
