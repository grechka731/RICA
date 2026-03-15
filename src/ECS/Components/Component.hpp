#pragma once

#include <vector>
#include "Property.h"
#include "Reflector.h"

struct Component {
  virtual ~Component() = default;

  void addPropertyDetails(const char* name, void* ptr, PropType type){
    PropertyDetails.push_back({name, ptr, type});
  }

  const std::vector<PropertyInfo>& getPropertyDetails() const {
    return PropertyDetails;
  }

  virtual const char* getComponentName() const {
    return "Component";
  }

private:
    std::vector<PropertyInfo> PropertyDetails;
};
