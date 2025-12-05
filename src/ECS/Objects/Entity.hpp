#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

struct Component;

class Entity {
public:
  Entity();
  Entity(std::string tag);
  virtual ~Entity();

  virtual void Start() {
  }
  virtual void update(float deltaTime) {
  }

  void addComponent(std::shared_ptr<Component> comp);
  template <typename T> std::shared_ptr<T> getComponent() {
    for (auto componentPtr : components) {
      if (componentPtr == nullptr)
        continue;

      if (auto casted = std::dynamic_pointer_cast<T>(componentPtr)) {
        return casted;
      }
    }
    return nullptr;
  }

  int getID() const;

  void setTag(std::string tag) {
    this->tag = tag;
  }
  std::string getTag() {
    return tag;
  }

private:
  std::vector<std::shared_ptr<Component>> components;
  int id;
  std::string tag;
};

#include "Entity.inl"
