#include "Collider2D.hpp"
#include "../../rica.hpp"

Collider2DSystem& collider2DSystem = Collider2DSystem::getInstance();

void Collider2DSystem::update(
    const std::vector<std::shared_ptr<Entity>>& entities) {
  LOG_DEBUG("Collider2D update: checking entities");
  for (auto entity : entities) {
    auto transform = entity->getComponent<TransformComponent>();
    auto collider = entity->getComponent<Collider2DComponent>();

    if (!transform || !collider)
      continue;

    collider->setX(transform->getPosition().x);
    collider->setY(transform->getPosition().y);
  }
}

bool Collider2DSystem::isColliding(std::shared_ptr<Entity> entity1,
                                   std::shared_ptr<Entity> entity2) {
  auto transform1 = entity1->getComponent<TransformComponent>();
  auto collider1 = entity1->getComponent<Collider2DComponent>();
  auto transform2 = entity2->getComponent<TransformComponent>();
  auto collider2 = entity2->getComponent<Collider2DComponent>();

  if (!transform1 || !collider1 || !transform2 || !collider2) {
    return false;
  }

  float left1 = collider1->getPosition().x - collider1->getWidth();
  float right1 = collider1->getPosition().x;
  float top1 = collider1->getPosition().y - collider1->getHeight();
  float bottom1 = collider1->getPosition().y;

  float left2 = collider2->getPosition().x - collider2->getWidth();
  float right2 = collider2->getPosition().x;
  float top2 = collider2->getPosition().y - collider2->getHeight();
  float bottom2 = collider2->getPosition().y;

  return (left1 < right2 && right1 > left2 && top1 < bottom2 && bottom1 > top2);
}
