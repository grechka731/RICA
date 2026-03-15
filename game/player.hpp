#pragma once

#include "../src/rica.hpp"
#include "raylib.h"
#include "../src/ECS/Components/Mesh/Mesh.hpp"
#include "../src/ECS/Components/Transform/Transform3D/Transform3D.hpp"

#include <iostream>
#include <memory>


class Player : public Entity {
private:
    float speed = 5.0f;
    float rotationSpeed = 90.0f;

    std::shared_ptr<MeshComponent> mesh;
    std::shared_ptr<Transform3DComponent> trans;
public:
    Player() {
        trans = std::make_shared<Transform3DComponent>();
        trans->setPosition({0.0f, 0.0f, 0.0f});
        trans->setScale({0.1, 0.1, 0.1});

        this->addComponent(trans);

        mesh = std::make_shared<MeshComponent>();
        mesh->loadMesh("one.glb");
        this->addComponent(mesh);
        
        var(speed, &speed);
        var(rotationSpeed, &rotationSpeed);
    }


    void update(float deltaTime) {
        Vector3 position = trans->getPosition();
        float rotationY = trans->getRotationAngles().y;

        if (input.isKeyDown(KEY_LEFT)) {
            rotationY -= rotationSpeed * deltaTime;
        }
        if (input.isKeyDown(KEY_RIGHT)) {
            rotationY += rotationSpeed * deltaTime;
        }

        Vector3 forward = {
            sinf(rotationY * DEG2RAD),
            0.0f,
            cosf(rotationY * DEG2RAD)
        };

        if (input.isKeyDown(KEY_UP)) {
            position = Vector3Add(position, Vector3Scale(forward, speed * deltaTime));
        }
        if (input.isKeyDown(KEY_DOWN)) {
            position = Vector3Add(position, Vector3Scale(forward, -speed * deltaTime));
        }

        trans->setPosition(position);
        trans->setRotation({0.0f, rotationY, 0.0f});
    }

};