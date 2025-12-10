<h1 align="center">🎮 RICA Game Engine — Полная Документация</h1>

📝 1. Введение

RICA — лёгкий игровой движок на основе Raylib с архитектурой ECS (Entity Component System).

Он предназначен для создания 2D и 3D игр, имеет систему сцен, поддерживает работу со звуком, коллизиями, 3D моделями и различными компонентами.

Данная документация описывает всю логику движка, API, структуру и стандартные компоненты.

📂 2. Структура проекта

<p align="left">

Базовая структура проекта:

/project
  /src        — исходный код движка
  /game       — игровая логика проекта
  /assets     — ресурсы
  /lib        — внешние зависимости (Raylib)


Основные подпапки движка (/src):

src/ECS/components   — компоненты

src/ECS/systems      — системы

src/graphics         — рендер 2D/3D

src/engine           — жизненный цикл движка

src/Scene            — система сцен

src/Audio            — аудио и пространственный звук

src/Collider         — коллизии 2D

</p>

✨ 3. Архитектура ECS

<p align="left">

Entity (Сущность)

Сущность хранит компоненты и обеспечивает доступ к ним.

Методы Entity:

addComponent

getComponent

hasComponent

removeComponent

setTag / getTag

getID

isEnabled / setEnabled

Component (Компонент)

Компоненты — структуры данных без логики.

System (Система)

Система обрабатывает сущности, содержащие определённый набор компонентов.

Все системы имеют основной метод обработки:

update(std::vector<std::shared_ptr<Entity>>& entities, float dt)


</p>

🛠️ 4. Компоненты & 5. Системы

<p align="left">

TransformComponent (2D/3D)

2D Методы: setPosition, setRotation, setScale, getRect.

3D Методы: setPosition, setRotation, getTransformMatrix.

Rendering & Media

SpriteComponent: LoadTextureSprite, setColor, getTexture.

MeshComponent: loadMesh, setColor, unload.

AudioComponent: addSound(tag, path), play(tag), setVolumeAll.

Cameras

Camera2DComponent: setTarget, setOffset, setZoom, setRotation.

Camera3DComponent: setTarget, setOffset, setFovy.

Systems Overview

Render2DSystem / Render3DSystem: Управление рендерингом и камерами.

AudioSystem: Пространственный звук.

Collider2DSystem: Обновление коллизий, isColliding.

Physic2D: Гравитация, перемещение.

</p>

⚙️ 6. Scene API & 7. Engine API

<p align="left">

Scene API (Система сцен)

Методы: createEntity, Create(), findById, OnLoad, OnUpdate, OnUnload.

Пример реализации сцены:

class MyScene : public Scene {
  void OnLoad() override {
    auto e = std::make_shared<Entity>();
    e->addComponent(std::make_shared<TransformComponent>());
    createEntity(e);
  }
};


Engine API

Engine Методы: init, update, shutdown, set3Dmode, getIsRunning, getDeltaTime.

SceneManager Методы: CreateScene, setSceneByID, getCurrentScene.

</p>

💡 8. Примеры использования

<p align="left">

Создание сущности:

auto e = std::make_shared<Entity>();
auto t = std::make_shared<TransformComponent>();
t->setPosition(100, 200);
e->addComponent(t);
scene->createEntity(e);


Создание 3D объекта:

auto t = std::make_shared<Transform3DComponent>();
auto m = std::make_shared<MeshComponent>();
m->loadMesh("one.glb");
entity->addComponent(t);
entity->addComponent(m);


Включение 3D режима:

engine.set3Dmode(true);


</p>

🔄 9. Основной цикл (Game Loop)

<p align="center">

while (engine.getIsRunning() && !WindowShouldClose()) {
  engine.deltaTime = GetFrameTime();
  currentScene->OnUpdate(engine.deltaTime); 

  BeginDrawing();
  ClearBackground(BLACK);

  if (engine.is3Dmode()) {
    render3Dsystem.update(...);
  } else {
    collider2DSystem.update(...);
    render2Dsystem.update(...);
    audioSystem.update(...);
  }

  EndDrawing();
}


</p>

<h3 align="center">✅ 10. Завершение</h3>

<p align="center">
RICA предоставляет простой, модульный и расширяемый базис для разработки игр.
</p>
