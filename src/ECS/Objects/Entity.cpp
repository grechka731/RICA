#include "Entity.hpp"
#include "../../rica.hpp"
#include <iostream>
#include "../Components/Camera/Camera3D/Camera3D.hpp"
#include "../Components/Mesh/Mesh.hpp"
#include "../Components/Transform/Transform3D/Transform3D.hpp"
#include "../Components/Physic/Physic3D/Physic3D.hpp"

static int globalEntityId = 0;

Entity::Entity() : id(globalEntityId++) {
  var(id, &id);
  var(tag, &tag);
  LOG_DEBUG("Entity created");
}

Entity::Entity(std::string tag) : id(globalEntityId++), tag(tag) {
  var(id, &id);
  var(tag, &tag);
  LOG_DEBUG("Entity created with tag");
}

Entity::~Entity() {
  LOG_DEBUG("Entity destroyed");
}

int Entity::getID() const {
  return id;
}

void Entity::addComponent(std::shared_ptr<Component> comp) {
  if (comp != nullptr) {
    components.push_back(comp);
    LOG_DEBUG("Component added to entity");
  } else {
    LOG_WARN("Attempted to add null component to entity");
  }
}

template <typename T> std::shared_ptr<T> Entity::getComponent() {
  for (auto componentPtr : components) {
    if (componentPtr == nullptr)
      continue;

    if (auto casted = std::dynamic_pointer_cast<T>(componentPtr)) {
      return casted;
    }
  }
  return nullptr;
}

template std::shared_ptr<SpriteComponent>
Entity::getComponent<SpriteComponent>();
template std::shared_ptr<TransformComponent>
Entity::getComponent<TransformComponent>();
template std::shared_ptr<Collider2DComponent>
Entity::getComponent<Collider2DComponent>();
template std::shared_ptr<AudioComponent> Entity::getComponent<AudioComponent>();
template std::shared_ptr<Camera2DComponent>
Entity::getComponent<Camera2DComponent>();

template std::shared_ptr<Camera3DComponent>
Entity::getComponent<Camera3DComponent>();
template std::shared_ptr<MeshComponent>
Entity::getComponent<MeshComponent>();
template std::shared_ptr<Transform3DComponent>
Entity::getComponent<Transform3DComponent>();
template std::shared_ptr<Physic3DComponent>
Entity::getComponent<Physic3DComponent>();
