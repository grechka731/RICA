#include "Engine.hpp"

#include "../rica.hpp"
#include "Physic/Physic3D/Physic.hpp"
#include "Render2D/Render2D.hpp"
#include "Render3D/Render3D.hpp"
#include "Var/Var.hpp"
#include "raylib.h"

#include "fileLog.h"
#include "terminalLog.h"
#include <chrono>
#include <cstddef>
#include <fstream>
#include <rlImGui.h>
#include <string>
#include <thread>

#ifdef EDITOR
#include "editor/editor/editor.hpp"
#endif

Engine& engine = Engine::getInstance();

bool parseInitFile(rapidjson::Document& doc) {
  std::fstream initFile("initEngine.json");
  if (!initFile.is_open()) {
    LOG_ERROR("Failed to load initEngine.json");
    return false;
  }
  std::string initString((std::istreambuf_iterator<char>(initFile)),
                         std::istreambuf_iterator<char>());
  doc.Parse(initString.c_str());
  if (doc.HasParseError()) {
    LOG_ERROR("Failed to parse JSON for initEngine.json");
    return false;
  }
  LOG_INFO("initEngine.json loaded successfully");
  return true;
}

unsigned int GetFlagValue(const char* flagName) {
  if (strcmp(flagName, "FLAG_FULLSCREEN_MODE") == 0)
    return FLAG_FULLSCREEN_MODE;
  if (strcmp(flagName, "FLAG_WINDOW_RESIZABLE") == 0)
    return FLAG_WINDOW_RESIZABLE;
  if (strcmp(flagName, "FLAG_WINDOW_UNDECORATED") == 0)
    return FLAG_WINDOW_UNDECORATED;
  if (strcmp(flagName, "FLAG_WINDOW_HIDDEN") == 0)
    return FLAG_WINDOW_HIDDEN;
  if (strcmp(flagName, "FLAG_WINDOW_MINIMIZED") == 0)
    return FLAG_WINDOW_MINIMIZED;
  if (strcmp(flagName, "FLAG_WINDOW_MAXIMIZED") == 0)
    return FLAG_WINDOW_MAXIMIZED;
  if (strcmp(flagName, "FLAG_WINDOW_UNFOCUSED") == 0)
    return FLAG_WINDOW_UNFOCUSED;
  if (strcmp(flagName, "FLAG_WINDOW_TOPMOST") == 0)
    return FLAG_WINDOW_TOPMOST;
  if (strcmp(flagName, "FLAG_WINDOW_ALWAYS_RUN") == 0)
    return FLAG_WINDOW_ALWAYS_RUN;
  if (strcmp(flagName, "FLAG_WINDOW_TRANSPARENT") == 0)
    return FLAG_WINDOW_TRANSPARENT;

  if (strcmp(flagName, "FLAG_VSYNC_HINT") == 0)
    return FLAG_VSYNC_HINT;
  if (strcmp(flagName, "FLAG_MSAA_4X_HINT") == 0)
    return FLAG_MSAA_4X_HINT;
  if (strcmp(flagName, "FLAG_INTERLACED_HINT") == 0)
    return FLAG_INTERLACED_HINT;
  return 0;
}
struct RayLibVar {
  int width = 200;
  int height = 400;
  std::string title = "Default Game Title";
  int maxFPS = 60;
  unsigned int flag = 0;
};

std::optional<RayLibVar> parseInitFileForRayLib() {
  RayLibVar rayVar;
  rayVar.flag = 0;
  rapidjson::Document doc;

  if (!parseInitFile(doc)) {
    LOG_ERROR("Failed to parse init file for RayLib");
    return {};
  }

  if (!doc.HasMember("rayLib") || !doc["rayLib"].IsObject()) {
    LOG_ERROR("Missing 'rayLib' configuration in initEngine.json");
    return {};
  }

  const rapidjson::Value& config = doc["rayLib"];

  if (config.HasMember("windowTitle") && config["windowTitle"].IsString())
    rayVar.title = config["windowTitle"].GetString();
  if (config.HasMember("maxFPS") && config["maxFPS"].IsInt())
    rayVar.maxFPS = config["maxFPS"].GetInt();

  LOG_INFO("Window config loaded");

  if (config.HasMember("resolution") && config["resolution"].IsObject()) {
    const rapidjson::Value& resolution = config["resolution"];

    auto parseDimension = [&](const char* key, int& dimension) {
      if (!resolution.HasMember(key))
        return;
      const rapidjson::Value& value = resolution[key];
      if (value.IsInt()) {
        dimension = value.GetInt();
      } else if (value.IsString()) {
        std::string strValue = value.GetString();
      }
    };

    parseDimension("width", rayVar.width);
    parseDimension("height", rayVar.height);

    if (config.HasMember("configurationFlags") &&
        config["configurationFlags"].IsArray()) {
      const rapidjson::Value& flagsArray = config["configurationFlags"];
      for (rapidjson::SizeType i = 0; i < flagsArray.Size(); i++) {
        if (flagsArray[i].IsString()) {
          const char* flagString = flagsArray[i].GetString();
          rayVar.flag += GetFlagValue(flagString);
        }
      }
    }
  }

  SetConfigFlags(rayVar.flag);
  InitWindow(rayVar.width, rayVar.height, rayVar.title.c_str());
  SetExitKey(KEY_NULL);
  LOG_INFO("Window initialized");

  if (engine.is3Dmode()) {
    render3Dsystem.init(rayVar.width, rayVar.height);
    LOG_INFO("3D render system initialized");
  } else {
    render2Dsystem.init(rayVar.width, rayVar.height);
    LOG_INFO("2D render system initialized");
  }

  SetTargetFPS(rayVar.maxFPS);
  LOG_INFO("Target FPS set");

  return rayVar;
}

bool Engine::init() {

  LOG_INFO("Engine initialization started");

  SetTraceLogLevel(LOG_ALL);
  InitAudioDevice();
  LOG_INFO("Audio device initialized");

  isRunning = true;
  auto var = parseInitFileForRayLib();

  if (!var) {
    LOG_ERROR("Failed to initialize RayLib configuration");
    return false;
  }

#ifdef EDITOR
  rlImGuiSetup(true);
  LOG_INFO("ImGui setup completed");
  editor.init();
  LOG_INFO("Editor initialized");
  LOG_INFO("Engine initialization completed successfully");
#else 
  DisableCursor();
#endif

  return true;
}

void Engine::update() {
}

void Engine::deleteVectorSceneManager() {
  vectorSceneManager.clear();
}

void Engine::shutdown() {
  LOG_INFO("Engine shutdown started");
  CloseWindow();
  LOG_INFO("Window closed");
  engine.shader = {}; // deletes the shader, unloading it
  LOG_INFO("Shader unloaded");
  LOG_INFO("Engine shutdown completed");
}

std::vector<std::shared_ptr<Scene>> Engine::vectorSceneManager;
Engine::SceneManager Engine::sceneManager;

void Engine::updateCurrentScene() {
  unsigned int currentSceneId = sceneManager.getCurrentSceneID();
  if (currentSceneId < vectorSceneManager.size() &&
      vectorSceneManager[currentSceneId] != nullptr) {
    LOG_DEBUG("Updating current scene");
    vectorSceneManager[currentSceneId]->updateEntity();
  } else {
    LOG_WARN("Scene not found or is null");
  }
}

std::shared_ptr<Scene> Engine::SceneManager::newSceneByID(unsigned int ID) {
  if (ID >= Engine::vectorSceneManager.size()) {
    LOG_INFO("Resizing scene vector");
    Engine::vectorSceneManager.resize(ID + 1, nullptr);
  }
  if (Engine::vectorSceneManager[ID] != nullptr) {
    LOG_WARN("Scene already exists, replacing it");
    Engine::vectorSceneManager[ID] = nullptr;
  }
  auto scenePtr = std::make_shared<Scene>();
  Engine::vectorSceneManager[ID] = scenePtr;
  LOG_INFO("Scene created successfully");
  return scenePtr;
}

void Engine::SceneManager::setSceneByID(unsigned int ID) {
  if (ID >= vectorSceneManager.size()) {
    LOG_ERROR("Cannot set scene ID: out of bounds");
    return;
  }
  if (vectorSceneManager[ID] == nullptr) {
    LOG_ERROR("Cannot set scene ID: scene is null");
    return;
  }
  LOG_INFO("Scene switched");
  sceneCurrent = ID;
}

void Engine::SceneManager::setSceneLimit(unsigned int limit) {
  if (limit > Engine::vectorSceneManager.size()) {
    LOG_INFO("Expanding scene vector");
    Engine::vectorSceneManager.resize(limit, nullptr);
  } else if (limit < Engine::vectorSceneManager.size()) {
    LOG_INFO("Shrinking scene vector");
    for (int i = limit; i < (int)Engine::vectorSceneManager.size(); i++) {
      if (Engine::vectorSceneManager[i] != nullptr) {
        Engine::vectorSceneManager[i] = nullptr;
      }
    }
    Engine::vectorSceneManager.resize(limit);
  }
}

int main() {
  logger.addSystem(new terminalLog());
  logger.addSystem(new fileLog("engine.log"));

  LOG_INFO("=== RICA Engine Started ===");
  if (!gameStart()) {
    LOG_ERROR("Game initialization failed");
    return 1;
  }
  LOG_INFO("Game loop started");

  while (engine.getIsRunning() && !WindowShouldClose()) {
    engine.deltaTime = GetFrameTime();

    unsigned int currentSceneId = engine.sceneManager.getCurrentSceneID();
    auto currentScenePtr = Engine::vectorSceneManager[currentSceneId];

    currentScenePtr->OnUpdate(GetFrameTime());

    if (engine.is3Dmode()) {
#ifdef EDITOR
      render3Dsystem.setSelectedEntity(
          editor.getViewport().getSelectedEntity());
#endif
      render3Dsystem.update(currentScenePtr->getAllEntities());
      physic3DSystem.update(currentScenePtr->getAllEntities(),
                            engine.deltaTime);
    } else {
      collider2DSystem.update(currentScenePtr->getAllEntities());
      render2Dsystem.update(currentScenePtr->getAllEntities());
      audioSystem.update(currentScenePtr->getAllEntities());
    }

    BeginDrawing();
    ClearBackground(BLACK);

#ifdef EDITOR
    rlImGuiBegin();
    currentScenePtr->ImGuiDraw();
    editor.onUpdate();
    rlImGuiEnd();
#else
    RenderTexture2D& targetTexture = engine.is3Dmode()
                                         ? render3Dsystem.getRenderTexture()
                                         : render2Dsystem.getRenderTexture();
    int width = engine.is3Dmode() ? render3Dsystem.getWidth()
                                  : render2Dsystem.getWidth();
    int height = engine.is3Dmode() ? render3Dsystem.getHeight()
                                   : render2Dsystem.getHeight();
    if (targetTexture.id > 0) {
      BeginShaderMode(engine.shader->getRaylibShader());
      DrawTextureRec(targetTexture.texture,
                     (Rectangle){0, 0, (float)width, (float)-height},
                     (Vector2){0, 0}, WHITE);
      EndShaderMode();
    }
#endif

    DrawFPS(10, 10);
    EndDrawing();

    engine.update();
  }

  LOG_INFO("Game loop ended");
  engine.shutdown();
  LOG_INFO("=== RICA Engine Stopped ===");

  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  return 0;
}
