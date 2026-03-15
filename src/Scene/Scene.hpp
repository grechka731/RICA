#pragma once
#include <memory>
#include <optional>
#include <string>
#include <vector>

class Entity;

class Scene {
public:
  Scene();
  virtual ~Scene();

  virtual void OnLoad() {
  }
  virtual void OnUpdate(float deltaTime) {
  }
  virtual void OnUnload() {
  }
  virtual void ImGuiDraw() {
  }

  std::shared_ptr<Entity> createEntity(std::shared_ptr<Entity> entity);

  template <typename T, typename... Args>
  std::shared_ptr<T> Create(Args&&... args);

  std::optional<std::shared_ptr<Entity>> findById(int id);
  std::vector<std::shared_ptr<Entity>> findByTag(const std::string& tag);
  const std::vector<std::shared_ptr<Entity>>& getAllEntities() const;

  void updateEntity();

private:
  std::vector<std::shared_ptr<Entity>> entities;
};

#include "Scene.inl"
