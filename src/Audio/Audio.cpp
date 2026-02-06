#include "../rica.hpp"
#include "Var/Var.hpp"
#include <algorithm>
#include <cmath>
// Если у пользователя не линукс?
// Убрать заголовок вручную - нетрудно, но зачем, если есть #if defined() ?
#if defined(__linux__)
#include <linux/limits.h>
#endif

AudioSystem& audioSystem = AudioSystem::getInstance();

void AudioSystem::update(const std::vector<std::shared_ptr<Entity>>& entities) {
  logger.addLog(LogLevel::DEBUG, basePath, __func__, "logRica.txt");

  std::shared_ptr<Camera2DComponent> cameraActive = nullptr;
  std::shared_ptr<TransformComponent> transformActive = nullptr;

  for (auto entity : entities) {
    auto camera = entity->getComponent<Camera2DComponent>();
    auto transform = entity->getComponent<TransformComponent>();

    if (camera && camera->isActiveCamera() && transform) {
      cameraActive = camera;
      transformActive = transform;
      break;
    }
  }

  for (auto entity : entities) {
    auto transform = entity->getComponent<TransformComponent>();
    auto audio = entity->getComponent<AudioComponent>();

    if (!transform || !audio)
      continue;

    if (cameraActive != nullptr && transformActive != nullptr) {
      float dx = transformActive->getPosition().x - transform->getPosition().x;
      float dy = transformActive->getPosition().y - transform->getPosition().y;

      float l = sqrt(dx * dx + dy * dy);

      float l1_max = sqrt((GetMonitorWidth(0) * GetMonitorWidth(0)) +
                          (GetMonitorHeight(0) * GetMonitorHeight(0)));

      if (l1_max > 0.0f) {
        float normalized_distance = l / l1_max;

        float volume = 1.0f - normalized_distance;

        if (volume < 0.0f) {
          volume = 0.0f;
        }

        audio->setVolumeAll(volume);
      }

      float deltax =
          transform->getPosition().x - transformActive->getPosition().x;
      float clamped_value =
          std::clamp(deltax / GetMonitorWidth(0), -1.0f, 1.0f);
      float pan_value = (1.0f - clamped_value) / 2.0f;
      audio->setPanAll(pan_value);
    }
  }
}
