#pragma once
#include "../../Component.hpp"
#include "raylib.h"
#include <vector>

class Physic3DComponent : public Component {
public:
    Physic3DComponent() {
        // ✅ Регистрируем поля для Details панели
        var(velocity, &velocity);
        var(isStatic, &isStatic);
        var(gravityActive, &gravityActive);
        var(mass, &mass);
        var(gravityScale, &gravityScale);
        var(damping, &damping);
    }

    const char* getComponentName() const override { return "Physic3D"; }

    void addForce(Vector3 f) { forces.push_back(f); }
    const std::vector<Vector3>& getForces() const { return forces; }
    void clearForces() { forces.clear(); }

    bool getIsStatic() const { return isStatic; }
    void setIsStatic(bool value) { isStatic = value; }

    float getMass() const { return mass; }
    void setMass(float value) { mass = value > 0 ? value : 0.0001f; }

    bool isGravityActive() const { return gravityActive; }
    void setGravityActive(bool value) { gravityActive = value; }

    float getGravityScale() const { return gravityScale; }
    void setGravityScale(float value) { gravityScale = value; }
    
    Vector3 getVelocity() const { return velocity; }
    void setVelocity(Vector3 v) { velocity = v; }

    float getDamping() const { return damping; }

private:
    std::vector<Vector3> forces;
    Vector3 velocity = { 0, 0, 0 };
    
    bool isStatic = false;
    bool gravityActive = true;
    
    float mass = 1.0f;
    float gravityScale = 1.0f;
    float damping = 0.98f; 
};
