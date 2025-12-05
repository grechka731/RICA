#include "Entity.hpp"
#include "../../rica.hpp"
#include "../Components/Camera/Camera3D/Camera3D.hpp"
#include "../Components/Mesh/Mesh.hpp"
#include "../Components/Transform/Transform3D/Transform3D.hpp"
#include <iostream>

static int globalEntityId = 0;

Entity::Entity() : id(globalEntityId++) {
}

Entity::Entity(std::string tag) : id(globalEntityId++), tag(tag) {
}

Entity::~Entity() = default;

int Entity::getID() const {
  return id;
}

void Entity::addComponent(std::shared_ptr<Component> comp) {
  if (comp != nullptr) {
    components.push_back(comp);
  }
}