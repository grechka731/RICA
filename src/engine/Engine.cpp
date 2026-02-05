#include "Engine.hpp"

#include "../rica.hpp"
#include "Physic/Physic3D/Physic.hpp"
#include "Render2D/Render2D.hpp"
#include "Render3D/Render3D.hpp"
#include "Var/Var.hpp"
#include "raylib.h"

#include <cstddef>
#include <fstream>
#include <string> // Добавлен для std::stoi
#include <rlImGui.h>

#ifdef EDITOR
#include "editor/editor/editor.hpp"
#endif

// Глобальная переменная движка (Engine Singleton)
Engine& engine = Engine::getInstance();

bool parseInitFile(rapidjson::Document& doc) {
  std::fstream initFile("initEngine.json");
  if (!initFile.is_open()) {
    logger.addLog(LogLevel::ERROR, basePath, "Failed to load initEngine.json",
                  "logRica.txt");
    logger.addLog(LogLevel::ERROR, basePath, "Failed to load initEngine.json");

    return false;
  }
  std::string initString((std::istreambuf_iterator<char>(initFile)),
                         std::istreambuf_iterator<char>());
  doc.Parse(initString.c_str());
  if (doc.HasParseError()) {
    logger.addLog(LogLevel::ERROR, basePath,
                  "Failed to parse JSON for position" +
                      std::to_string(doc.GetErrorOffset()),
                  "logRica.txt");
    logger.addLog(LogLevel::ERROR, basePath,
                  "Failed to parse JSON for position" +
                      std::to_string(doc.GetErrorOffset()));

    return false;
  }
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

  if (!parseInitFile(doc))
    return {};

  // Ранний выход, если нет корневого объекта "rayLib"
  if (!doc.HasMember("rayLib") || !doc["rayLib"].IsObject())
    return {};

  const rapidjson::Value& config = doc["rayLib"];

  // 1. Парсинг заголовка и FPS
  if (config.HasMember("windowTitle") && config["windowTitle"].IsString())
    rayVar.title = config["windowTitle"].GetString();
  if (config.HasMember("maxFPS") && config["maxFPS"].IsInt())
    rayVar.maxFPS = config["maxFPS"].GetInt();

  // 2. Парсинг разрешения и флагов
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
  if (engine.is3Dmode())
    render3Dsystem.init(rayVar.width, rayVar.height);
  else
    render2Dsystem.init(rayVar.width, rayVar.height);

  SetTargetFPS(rayVar.maxFPS);

  return rayVar;
}

bool Engine::init() {
  SetTraceLogLevel(LOG_ALL);
  InitAudioDevice();

  isRunning = true;
  auto var = parseInitFileForRayLib();
  
  if (!var)
    return false;

  // Инициализируем ImGui для всех режимов, так как он нужен и в игре, и в редакторе
  rlImGuiSetup(true); 
  // БЛЯТЬ ПОЧЕМУ ТО НЕТУ ТУТ #ifdef EDITOR
  #ifdef EDITOR
  editor.init();
  #endif
  return true;
}

void Engine::update() {
}

void Engine::deleteVectorSceneManager() {
  vectorSceneManager.clear();
}

void Engine::shutdown() {
  CloseWindow();
  engine.shader = {}; // deletes the shader, unloading it
}

std::vector<std::shared_ptr<Scene>> Engine::vectorSceneManager;
Engine::SceneManager Engine::sceneManager;

void Engine::updateCurrentScene() {
  logger.addLog(LogLevel::DEBUG, basePath, __func__, "logRica.txt");
  unsigned int currentSceneId = sceneManager.getCurrentSceneID();
  if (currentSceneId < vectorSceneManager.size() &&
      vectorSceneManager[currentSceneId] != nullptr) {
    vectorSceneManager[currentSceneId]->updateEntity();
  }
}

std::shared_ptr<Scene> Engine::SceneManager::newSceneByID(unsigned int ID) {
  if (ID >= Engine::vectorSceneManager.size()) {

    logger.addLog(LogLevel::CRITICAL, basePath,
                  "World ID " + std::to_string(ID) +
                      " is out of bounds! Resizing vector.",
                  "logRica.txt");
    logger.addLog(LogLevel::CRITICAL, basePath,
                  "World ID " + std::to_string(ID) +
                      " is out of bounds! Resizing vector.");

    Engine::vectorSceneManager.resize(ID + 1, nullptr);
  }
  if (Engine::vectorSceneManager[ID] != nullptr) {
    Engine::vectorSceneManager[ID] = nullptr;
  }
  auto scenePtr = std::make_shared<Scene>();
  Engine::vectorSceneManager[ID] = scenePtr;
  return scenePtr;
}

void Engine::SceneManager::setSceneByID(unsigned int ID) {
  if (ID >= vectorSceneManager.size()) {
    logger.addLog(LogLevel::CRITICAL, basePath,
                  "Cannot set scene ID " + std::to_string(ID) +
                      ": out of bounds",
                  "logRica.txt");
    logger.addLog(LogLevel::CRITICAL, basePath,
                  "Cannot set scene ID " + std::to_string(ID) +
                      ": out of bounds");
    return;
  }
  if (vectorSceneManager[ID] == nullptr) {
    logger.addLog(LogLevel::CRITICAL, basePath,
                  "Cannot set scene ID " + std::to_string(ID) +
                      ": scene is null",
                  "logRica.txt");
    logger.addLog(LogLevel::CRITICAL, basePath,
                  "Cannot set scene ID " + std::to_string(ID) +
                      ": scene is null");

    return;
  }
  sceneCurrent = ID;
}

void Engine::SceneManager::setSceneLimit(unsigned int limit) {
  if (limit > Engine::vectorSceneManager.size()) {
    Engine::vectorSceneManager.resize(limit, nullptr);
  } else if (limit < Engine::vectorSceneManager.size()) {
    for (int i = limit; i < (int)Engine::vectorSceneManager.size(); i++) {
      if (Engine::vectorSceneManager[i] != nullptr) {
        Engine::vectorSceneManager[i] = nullptr;
      }
    }
    Engine::vectorSceneManager.resize(limit);
  }
}



// Функции для построения RenderObject3D и RenderObject2D из Entity
RenderObject3D BuildRenderObject(std::shared_ptr<Entity> entity) {

  RenderObject3D obj;

  auto model = entity->getComponent<MeshComponent>();
  auto transform = entity->getComponent<Transform3DComponent>();

  if (!model || !transform || !model->isLoaded())
    return obj;

  obj.model = model->getModel();
  // TODO : Add texture to the object 
  // obj.texture = model->getTexture();

  obj.position = transform->getPosition();
  obj.rotationAxis = transform->getRotationAxis();
  obj.rotationAngle = transform->getRotationAngle();
  obj.scale = transform->getScale();

  obj.tint = model->getColor();
  obj.isLoaded = true;

  return obj;
}
// Построение списка RenderObject3D из списка Entity
std::vector<RenderObject3D>
BuildRenderList(const std::vector<std::shared_ptr<Entity>>& entities) {
  std::vector<RenderObject3D> list;

  for (auto& entity : entities) {
    auto obj = BuildRenderObject(entity);
    if (obj.isLoaded)
      list.push_back(obj);
  }

  return list;
}
RenderObject2D BuildRenderObject2D(std::shared_ptr<Entity> entity) {
  RenderObject2D obj;

  auto sprite = entity->getComponent<SpriteComponent>();
  auto transform = entity->getComponent<TransformComponent>();

  if (!sprite || !transform)
    return obj;

  obj.texture = sprite->getTexture();
  obj.source = sprite->getSource();

  obj.dest = transform->getDest();
  obj.origin = transform->getOrigin();
  obj.rotation = transform->getRotation();

  obj.tint = sprite->getColor();

  obj.isLoaded = true;

  return obj;
}
std::vector<RenderObject2D>
BuildRenderList2D(const std::vector<std::shared_ptr<Entity>>& entities) {
  std::vector<RenderObject2D> list;

  for (auto& entity : entities) {
    auto obj = BuildRenderObject2D(entity);

    if (obj.isLoaded)
      list.push_back(obj);
  }

  return list;
}


int main() {
    logger.addLog(LogLevel::DEBUG, basePath, __func__, "logRica.txt");

    if (!gameStart())
        return 1;

    while (engine.getIsRunning() && !WindowShouldClose()) {
        engine.deltaTime = GetFrameTime();
        //if (IsKeyPressed(KEY_ESCAPE))
          //  engine.setIsRunning(false);

        unsigned int currentSceneId = engine.sceneManager.getCurrentSceneID();
        // Здесь должна быть ваша проверка на существование сцены
        auto currentScenePtr = Engine::vectorSceneManager[currentSceneId];

        // 1. ОБНОВЛЕНИЕ ЛОГИКИ СЦЕНЫ
        currentScenePtr->OnUpdate(GetFrameTime());

        // 2. OFF-SCREEN РЕНДЕРИНГ (Рендерим всё в текстуру)
        if (engine.is3Dmode()) {
          // Получаем все обьекты и переводим их в RenderObject3D( transform,моделька,текстура)
            auto entities = currentScenePtr->getAllEntities();
            auto renderList = BuildRenderList(entities);
            //скармливаем рендеру новый список обьектов
            render3Dsystem.Draw(renderList, entities);

            
            // физику не трогаю,там лучше оставить как есть(особенности екс)
            physic3DSystem.update(currentScenePtr->getAllEntities(), engine.deltaTime);
        } else {
            collider2DSystem.update(currentScenePtr->getAllEntities());
            auto entities = currentScenePtr->getAllEntities();

            auto renderList2D = BuildRenderList2D(entities);

            render2Dsystem.Draw(renderList2D);

            audioSystem.update(currentScenePtr->getAllEntities());
        }

        // 3. ВЫВОД НА ЭКРАН
        BeginDrawing();
        ClearBackground(BLACK);

        RenderTexture2D& targetTexture = engine.is3Dmode()
                                             ? render3Dsystem.getRenderTexture()
                                             : render2Dsystem.getRenderTexture();

        int width = engine.is3Dmode() ? render3Dsystem.getWidth() : render2Dsystem.getWidth();
        int height = engine.is3Dmode() ? render3Dsystem.getHeight() : render2Dsystem.getHeight();

#ifdef EDITOR
        // --- РЕЖИМ РЕДАКТОРА ---
        // Мы НЕ рисуем DrawTextureRec здесь. 
        // Вместо этого мы открываем ImGui, и Viewport внутри editor.onUpdate() 
        // сам заберет текстуру и отрисует её в окне.
        
        rlImGuiBegin();
        
        currentScenePtr->ImGuiDraw(); // Отрисовка UI текущей сцены
        editor.onUpdate();            // Отрисовка окон редактора (Viewport, Terminal и т.д.)
        
        rlImGuiEnd();
#else
        // --- РЕЖИМ ИГРЫ ---
        // Прямой вывод текстуры на весь экран
        if (targetTexture.id > 0) {
            BeginShaderMode(engine.shader->getRaylibShader());
          // msvc плохо воспринимает (Vector2),(Rectangle) и тп cause its C
          // style но с gcc норм
           DrawTextureRec(targetTexture.texture,
                           Rectangle{0, 0, (float)width, (float)-height},
                           Vector2{0, 0}, WHITE);

            
            EndShaderMode();
        }
#endif

        DrawFPS(10, 10);
        EndDrawing(); 

        logger.addLog(LogLevel::DEBUG, basePath, __func__, "logRica.txt");
        engine.update();
    }

    engine.shutdown();
    return 0;
}
