#pragma once
#include "../Component.hpp"
#include <raylib.h>
#include <raymath.h>
#include "../../../rica.hpp"

class MeshComponent : public Component {
public:
    MeshComponent() {
        var(loaded, &loaded);
        var(color, &color);
    }

    const char* getComponentName() const override { return "Mesh"; }

    ~MeshComponent() override {
        if (loaded) {
            UnloadModel(model);
        }
    }

    void loadMesh(const char *path) {
        // ✅ Регистрируем поля для Details панели
        model = LoadModel(path);

        if (model.meshCount == 0) {
            return;
        }

        loaded = true;
    }

    void setColor(Color newColor) {
        color = newColor;
    }

    Color getColor() const {
        return color;
    }

    Model& getModel() {
        return model;
    }

    bool isLoaded() const {
        return loaded;
    }

private:
    Model model = { 0 };
    Color color = WHITE;
    bool loaded = false;
};
