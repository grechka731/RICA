#pragma once

#include "../src/rica.hpp"
#include "raylib.h"
#include "../src/ECS/Components/Camera/Camera3D/Camera3D.hpp"
#include "../src/ECS/Components/Transform/Transform3D/Transform3D.hpp"

#include <memory>

class CameraController : public Entity {
private:
    float moveSpeed = 10.0f;
    float mouseSensitivity = 0.1f;

    std::shared_ptr<Camera3DComponent> camera;
    std::shared_ptr<Transform3DComponent> trans;

    float yaw = 0.0f;
    float pitch = 0.0f;

public:
    CameraController() {
        trans = std::make_shared<Transform3DComponent>();
        trans->setPosition({0.0f, 2.0f, 10.0f});
        this->addComponent(trans);

        camera = std::make_shared<Camera3DComponent>(Vector3{0.0f, 2.0f, 10.0f}, 90.0f, true);
        camera->setTarget({0.0f, 0.0f, 0.0f});
        this->addComponent(camera);
    
        var(moveSpeed, &moveSpeed);
        var(mouseSensitivity, &mouseSensitivity);
        var(yaw, &yaw);
        var(pitch, &pitch);
    }

    void update(float deltaTime) {
        Vector2 mouseDelta = GetMouseDelta();
        yaw -= mouseDelta.x * mouseSensitivity;
        pitch -= mouseDelta.y * mouseSensitivity;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        Vector3 forwardMove = { sinf(yaw * DEG2RAD), 0.0f, cosf(yaw * DEG2RAD) };
        Vector3 rightMove = { cosf(yaw * DEG2RAD), 0.0f, -sinf(yaw * DEG2RAD) };
        Vector3 up = {0.0f, 1.0f, 0.0f};

        Vector3 position = trans->getPosition();

        if (input.isKeyDown(KEY_W)) position = Vector3Add(position, Vector3Scale(forwardMove, moveSpeed * deltaTime));
        if (input.isKeyDown(KEY_S)) position = Vector3Add(position, Vector3Scale(forwardMove, -moveSpeed * deltaTime));
        if (input.isKeyDown(KEY_A)) position = Vector3Add(position, Vector3Scale(rightMove, moveSpeed * deltaTime));
        if (input.isKeyDown(KEY_D)) position = Vector3Add(position, Vector3Scale(rightMove, -moveSpeed * deltaTime));
        if (input.isKeyDown(KEY_SPACE)) position = Vector3Add(position, Vector3Scale(up, moveSpeed * deltaTime));
        if (input.isKeyDown(KEY_LEFT_CONTROL)) position = Vector3Add(position, Vector3Scale(up, -moveSpeed * deltaTime));

        trans->setPosition(position);
        trans->setRotation({pitch, yaw, 0.0f});

        Vector3 forwardLook = {
            sinf(yaw * DEG2RAD) * cosf(pitch * DEG2RAD),
            sinf(pitch * DEG2RAD),
            cosf(yaw * DEG2RAD) * cosf(pitch * DEG2RAD)
        };
        
        Vector3 target = Vector3Add(position, forwardLook);
        camera->setTarget(target);
        camera->setOffset(Vector3Subtract(position, target));
    }
};