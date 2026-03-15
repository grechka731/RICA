#pragma once

#include "raylib.h"
#include <memory>
#include <vector>

class Entity;
class Engine;

class Render2DSystem {
public:
    Render2DSystem(const Render2DSystem&) = delete;
    Render2DSystem& operator=(const Render2DSystem&) = delete;

    static Render2DSystem& getInstance() {
        static Render2DSystem instance;
        return instance;
    }

    void init(int screenWidth, int screenHeight);

    void update(const std::vector<std::shared_ptr<Entity>>& entities);

    RenderTexture2D& getRenderTexture() { return renderTexture; }

    friend Engine;

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }
    
private:
    Render2DSystem() = default;
    
    ~Render2DSystem() {
        if (renderTexture.id > 0) {
            UnloadRenderTexture(renderTexture);
        }
    }

protected:
    int width;
    int height;
    
    RenderTexture2D renderTexture = { 0 }; 
};

extern Render2DSystem& render2Dsystem;