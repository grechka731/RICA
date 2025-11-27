#include "../src/rica.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>

class GameScene : public Scene {
private:
public:
  void OnLoad() override {}
  void OnUpdate(float deltaTime) override {}
};

class World;
class RenderSystem;
class Log;
enum LogLevel;
void gameStart() {
  engine.init();
  engine.sceneManager.setSceneLimit(10);
  engine.sceneManager.CreateScene<GameScene>(1);
}
