#pragma once

#include "Property.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include "rica.hpp"

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
  template <typename T> std::shared_ptr<T> getComponent();

  int getID() const;

  void setTag(std::string tag) {
    this->tag = tag;
  }
  std::string getTag() {
    return tag;
  }

  void addPropertyDetails(const char* name, void* ptr, PropType type){
    PropertyDetails.push_back({name, ptr, type});
  }

  const std::vector<PropertyInfo>& getPropertyDetails() const {
    return PropertyDetails;
  }

  const std::vector<std::shared_ptr<Component>>& getComponents() const {
    return components;
  }

private:
  std::vector<std::shared_ptr<Component>> components;
  int id;
  std::string tag;

  std::vector<PropertyInfo> PropertyDetails;
};

#include "Entity.inl"
