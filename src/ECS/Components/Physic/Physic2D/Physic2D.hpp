#pragma once
#include "../../Component.hpp"
#include "../../../../lib/raylib/src/raymath.h"

class Physic2DComponent : public Component {
public:
  Physic2DComponent() {
    // ✅ Регистрируем поля для Details панели
    var(isStatic, &isStatic);
    var(mass, &mass);
    var(centerOfMassOffset, &centerOfMassOffset);
    var(gravityScale, &gravityScale);
    var(gravityActive, &gravityActive);
    var(restitution, &restitution);
    var(friction, &friction);
    var(force, &force);
    var(temperature, &temperature);
  }

  const char* getComponentName() const override { return "Physic2D"; }

  friend class Physic2DComponent;

private:
  bool isStatic = false;
  float mass = 1;
  Vector2 centerOfMassOffset = {0, 0};
  float gravityScale = 1.0f;
  bool gravityActive = true;
  float restitution = 1;
  float friction = 1;
  float force = 0;
  float temperature = 0;
};
