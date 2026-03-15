#include "../src/ECS/Components/Camera/Camera3D/Camera3D.hpp"
#include "../src/engine/Engine.hpp"
#include "../src/rica.hpp"
#include "camera_controller.hpp"
#include "player.hpp"
#include "raylib.h"
#include <imgui.h>
#include <iostream>
#include <memory>

const int screenWidth = 1920;
const int screenHeight = 1080;

class GameScene : public Scene {
private:
  std::shared_ptr<Player> player;
  std::shared_ptr<CameraController> cameraEntity;
  std::shared_ptr<Entity> shaderEntity;

  int timeLoc;
  int resolutionLoc;
  std::array<float, 2> resolution;

public:
  GameScene() {
    cameraEntity = std::make_shared<CameraController>();
    this->createEntity(cameraEntity);
    player = std::make_shared<Player>();
    this->createEntity(player);

    auto& engineShader = engine.getShader();

    engineShader = EngineShader({}, "raymarching.fs");

    timeLoc = engineShader->getShaderLocation("time");
    resolutionLoc = engineShader->getShaderLocation("resolution");

    resolution[0] = (float)screenWidth;
    resolution[1] = (float)screenHeight;

    engineShader->setShaderValue(resolutionLoc, resolution);
  }

  ~GameScene() {
  }

  void OnUpdate(float dt) override {
    auto& engineShader = engine.getShader();
    float time = (float)GetTime();
    engineShader->setShaderValue(timeLoc, time);
    if (cameraEntity)
      cameraEntity->update(dt);
    if (player)
      player->update(dt);
  }

};

bool gameStart() {
  engine.set3Dmode(true);
  if (!engine.init())
    return false;

  engine.sceneManager.setSceneLimit(10);
  engine.sceneManager.CreateScene<GameScene>(1);

  render3Dsystem.setSkyColor({100, 100, 100, 100});

  return true;
}
