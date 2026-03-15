#pragma once
#include "../../Component.hpp"
#include <raylib.h>
#include <raymath.h>

class Camera3DComponent : public Component {
public:
  Camera3DComponent() {
    // ✅ Регистрируем поля для Details панели
    var(target, &target);
    var(offset, &offset);
    var(rotation, &rotation);
    var(fovy, &fovy);
    var(isActive, &isActive);
  }

  const char* getComponentName() const override { return "Camera3D"; }

  Camera3DComponent(Vector3 offset, float fovy = 1.0f, bool isActive = true)
      : offset(offset), fovy(fovy), isActive(isActive) {
    // ✅ Регистрируем поля для Details панели
    var(target, &target);
    var(offset, &offset);
    var(rotation, &rotation);
    var(fovy, &fovy);
    var(isActive, &isActive);
  }

  Camera3D getCamera3D() const {
    Camera3D cam;
    cam.position=Vector3Add(target, offset);
    cam.fovy=fovy;
    cam.target=target;
    cam.projection=CAMERA_PERSPECTIVE;
    cam.up=Vector3{0.0f, 1.0f, 0.0f};

    return cam;
  }

  void followTarget(Vector3 position) {
    target = position;
  }

  void smoothFollow(Vector3 position, float speed) {
    target.x += (position.x - target.x) * speed;
    target.y += (position.y - target.y) * speed;
  }

  void setTarget(Vector3 target) {
    this->target = target;
  }
  void setOffset(Vector3 offset) {
    this->offset = offset;
  }
  void setRotation(float rotation) {
    this->rotation = rotation;
  }
  void setFovy(float fovy) {
    this->fovy = fovy;
  }
  void setActive(bool isActive) {
    this->isActive = isActive;
  }

  Vector3 getTarget() const {
    return target;
  }
  Vector3 getOffset() const {
    return offset;
  }
  float getRotation() const {
    return rotation;
  }
  float getFovy() const {
    return fovy;
  }
  bool isActiveCamera() const {
    return isActive;
  }

private:
Vector3 target{0.0f, 0.0f, 0.0f};
  Vector3 offset{0.0f, 5.0f, 5.0f}; 
  float rotation = 0.0f; 
  float fovy = 75.0f;
  bool isActive = false;
};
