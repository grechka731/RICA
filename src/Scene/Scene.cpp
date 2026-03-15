#include "Scene.hpp"
#include "../rica.hpp"

Scene::Scene() {
  LOG_DEBUG("Scene created");
}

Scene::~Scene() {
  LOG_DEBUG("Scene destroyed");
}

std::shared_ptr<Entity> Scene::createEntity(std::shared_ptr<Entity> entityPtr) {
  if (entityPtr != nullptr) {
    entities.push_back(entityPtr);
    LOG_DEBUG("Entity created in scene. Total entities updated");
  } else {
    LOG_WARN("Attempted to create null entity in scene");
  }
  return entityPtr;
}

std::optional<std::shared_ptr<Entity>> Scene::findById(int id) {
  for (auto entityPtr : entities) {
    if (entityPtr != nullptr && entityPtr->getID() == id) {
      LOG_DEBUG("Entity found by ID");
      return entityPtr;
    }
  }
  LOG_WARN("Entity not found by ID");
  return {};
}

std::vector<std::shared_ptr<Entity>> Scene::findByTag(const std::string& tag) {
  std::vector<std::shared_ptr<Entity>> resultVector;
  for (auto entityPtr : entities) {
    if (entityPtr != nullptr && entityPtr->getTag() == tag) {
      resultVector.push_back(entityPtr);
    }
  }
  LOG_DEBUG("Entities found by tag");
  return resultVector;
}

const std::vector<std::shared_ptr<Entity>>& Scene::getAllEntities() const {
  return entities;
}

void Scene::updateEntity() {
  LOG_DEBUG("Updating entities in scene");
  for (auto entityPtr : entities) {
    if (entityPtr != nullptr) {
      entityPtr->update(0.0f);
    }
  }
}
