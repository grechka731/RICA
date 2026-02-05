#pragma once

#include "raylib.h"
#include <memory>
#include <vector>

class Entity;
class Engine;
class Camera3DComponent;
class Transform3DComponent;
class MeshComponent; 
struct RenderObject3D {
  Model model;

  Vector3 position{0, 0, 0};
  Vector3 rotationAxis{0, 1, 0};
  float rotationAngle = 0.0f;
  Vector3 scale{1, 1, 1};

  Color tint = WHITE;
  bool isLoaded = false;
};
  class Render3DSystem {
public:
    Render3DSystem(const Render3DSystem&) = delete;
    Render3DSystem& operator=(const Render3DSystem&) = delete;
    Render3DSystem(Render3DSystem&&) = delete;
    Render3DSystem& operator=(Render3DSystem&&) = delete;

    static Render3DSystem& getInstance() {
        static Render3DSystem instance;
        return instance;
    }

    void init(int screenWidth, int screenHeight);
    //изменил декларацию
    void Draw(const std::vector<RenderObject3D>& objects,
           const std::vector<std::shared_ptr<Entity>>& entities);

    RenderTexture2D& getRenderTexture() { return renderTexture; }

    friend Engine;

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    Color getSkyColor() const {
        return skyColor;
    }

    void setSkyColor(Color color) {
        skyColor = color;
    }
    
private:
    Render3DSystem() = default;
    ~Render3DSystem() {
        if (renderTexture.id > 0) {
            UnloadRenderTexture(renderTexture);
        }
    }

    friend Engine;

protected:
    int width = 0;
    int height = 0;
    Color skyColor={0,0,0, 255};

    RenderTexture2D renderTexture = { 0 }; 
};

extern Render3DSystem& render3Dsystem;