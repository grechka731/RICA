#pragma once

struct Component;
class SpriteComponent;
class TransformComponent;
class Camera2DComponent;
class Physic3DComponent;
class Entity;
class Player;
class Terminal;
class Log;
class Collider2DSystem;
class Render2DSystem;
class AudioSystem;

#include <raylib.h>
#include <raymath.h>

#include <rapidjson/document.h>

#include <memory>
#include <string>
#include <vector>

#include "Var/Var.hpp"

#include "logSysem.h"
#include "logger.h"

#include "Property.h"
#include "Reflector.h"

#include "ECS/Components/Component.hpp"
#include "ECS/Components/Audio/Audio.hpp"
#include "ECS/Components/Camera/Camera2D/Camera2D.hpp"
#include "ECS/Components/Collider/Collider2D/Collider2D.hpp"
#include "ECS/Components/Sprite/Sprite.hpp"
#include "ECS/Components/Mesh/Mesh.hpp"
#include "ECS/Components/Transform/Transform2D/Transform.hpp"
#include "ECS/Components/Transform/Transform3D/Transform3D.hpp"
#include "ECS/Components/Physic/Physic3D/Physic3D.hpp"
#include "ECS/Objects/Entity.hpp"

#include "Audio/Audio.hpp"
#include "Collider/Collider2D/Collider2D.hpp"
#include "graphics/Render2D/Render2D.hpp"
#include "graphics/Render3D/Render3D.hpp"

#include "Input/Input.hpp"
#include "Scene/Scene.hpp"
#include "engine/Engine.hpp"