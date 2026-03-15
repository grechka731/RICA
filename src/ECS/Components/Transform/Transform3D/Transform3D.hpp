#pragma once
#include "../../../../rica.hpp"
#include "../../Component.hpp"
#include "raymath.h"

class Transform3DComponent : public Component {
public:
    Transform3DComponent(
        Vector3 position = {0.0f, 0.0f, 0.0f},
        Vector3 rotationAngles = {0.0f, 0.0f, 0.0f},
        Vector3 scale = {1.0f, 1.0f, 1.0f}
    )
        : position(position), rotationAngles(rotationAngles), scale(scale) {
        var(position, &this->position);
        var(rotationAngles, &this->rotationAngles);
        var(scale, &this->scale);
    }

    const char* getComponentName() const override { return "Transform3D"; }

    void setPosition(const Vector3& pos) { position = pos; }
    void setRotation(const Vector3& rot) { rotationAngles = rot; }
    void setScale(const Vector3& s) { scale = s; }

    void setX(float x) { position.x = x; }
    void setY(float y) { position.y = y; }
    void setZ(float z) { position.z = z; }

    void setRotationX(float rx) { rotationAngles.x = rx; }
    void setRotationY(float ry) { rotationAngles.y = ry; }
    void setRotationZ(float rz) { rotationAngles.z = rz; }

    void setScaleX(float sx) { scale.x = sx; }
    void setScaleY(float sy) { scale.y = sy; }
    void setScaleZ(float sz) { scale.z = sz; }

    const Vector3& getPosition() const { return position; }
    const Vector3& getRotationAngles() const { return rotationAngles; }
    const Vector3& getScale() const { return scale; }

    Vector3 getRotationAxis() const {
        Quaternion q = QuaternionFromEuler(
            DEG2RAD * rotationAngles.x,
            DEG2RAD * rotationAngles.y,
            DEG2RAD * rotationAngles.z
        );

        Vector3 axis;
        float angle;
        QuaternionToAxisAngle(q, &axis, &angle);
        return axis;
    }

    float getRotationAngle() const {
        Quaternion q = QuaternionFromEuler(
            DEG2RAD * rotationAngles.x,
            DEG2RAD * rotationAngles.y,
            DEG2RAD * rotationAngles.z
        );

        Vector3 axis;
        float angle;
        QuaternionToAxisAngle(q, &axis, &angle);
        return RAD2DEG * angle;
    }

    Matrix getTransformMatrix() const {
        Quaternion q = QuaternionFromEuler(
            DEG2RAD * rotationAngles.x,
            DEG2RAD * rotationAngles.y,
            DEG2RAD * rotationAngles.z
        );

        Matrix mRot = QuaternionToMatrix(q);
        Matrix mScale = MatrixScale(scale.x, scale.y, scale.z);
        Matrix mTrans = MatrixTranslate(position.x, position.y, position.z);

        return MatrixMultiply(MatrixMultiply(mScale, mRot), mTrans);
    }

private:
    Vector3 position;
    Vector3 rotationAngles; 
    Vector3 scale;
};
