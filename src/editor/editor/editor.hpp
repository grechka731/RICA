#pragma once
#include "../panel/allPanels/terminal/terminal.hpp"
#include "../panel/allPanels/viewport/viewport.hpp"
#include "../panel/allPanels/details/details.hpp"
#include "../panel/panel.hpp"
#include "../../ECS/Objects/Entity.hpp"
#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"
#include <memory>

class Editor {
private:
  std::shared_ptr<Entity> selectedObj;
  Terminal terminal;
  Viewport viewport;
  Details details;

  Editor() = default; 

public:
    friend class Input;
    friend class Viewport;

    Editor(const Editor&) = delete;
    Editor& operator=(const Editor&) = delete;

    static Editor& getInstance() {
        static Editor instance;
        return instance;
    }

    Viewport& getViewport() {
        return viewport;
    }

    void init(){
    ImGuiIO& io = ImGui::GetIO(); 
    io.ConfigFlags |=ImGuiConfigFlags_DockingEnable; 
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    }

    void onUpdate() {
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        
        terminal.onUpdate();
        viewport.onUpdate();
        details.onUpdate();
    }

    PanelEditor & getPanel(std::string name) {
        if (name == "Terminal") {
            return terminal;
        } else if (name == "Viewport") {
            return viewport;
        } else if (name == "Details") {
            return details;
        } else {
        return terminal;
        }
    }
};

extern Editor& editor;