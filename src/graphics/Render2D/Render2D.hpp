#pragma once

#include "raylib.h"
#include <memory>
#include <vector>

// ... (остальные forward declarations)
class Entity;
class Engine;
struct RenderObject2D {
  Texture2D texture;

  Rectangle source;
  Rectangle dest;

  Vector2 origin{0, 0};
  float rotation = 0.0f;

  Color tint = WHITE;

  bool isLoaded = false;
};

class Render2DSystem {
public:
    Render2DSystem(const Render2DSystem&) = delete;
    Render2DSystem& operator=(const Render2DSystem&) = delete;

    static Render2DSystem& getInstance() {
        static Render2DSystem instance;
        return instance;
    }

    void init(int screenWidth, int screenHeight);

    void Draw(const std::vector<RenderObject2D>& objects);

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