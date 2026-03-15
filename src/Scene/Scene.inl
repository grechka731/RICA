#pragma once
#include "../ECS/Objects/Entity.hpp"
#include "Scene.hpp"

template <typename T, typename... Args>
std::shared_ptr<T> Scene::Create(Args&&... args) {
  std::shared_ptr<T> ptr = std::make_shared<T>(std::forward<Args>(args)...);
  createEntity(ptr);
  ptr->Start();
  return ptr;
}
