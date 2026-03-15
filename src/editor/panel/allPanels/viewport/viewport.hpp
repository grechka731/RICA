#pragma once
#include "../../panel.hpp"
#include "ECS/Objects/Entity.hpp"
#include <memory>
#include <imgui.h>

class Viewport : public PanelEditor {
private:
    bool isWindowActive = false;
    std::shared_ptr<Entity> selectedEntity;
    ImVec2 viewportSize;
    ImVec2 viewportPos;
public:
    Viewport() : PanelEditor("Viewport") {}
    void onUpdate() override;

    bool getiswindowActive() const;
    bool isRightMousePressed() const { return IsMouseButtonDown(MOUSE_BUTTON_RIGHT); }
    std::shared_ptr<Entity> getSelectedEntity() const { return selectedEntity; }
    void setSelectedEntity(std::shared_ptr<Entity> entity) { selectedEntity = entity; }
};