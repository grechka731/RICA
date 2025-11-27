target("EngineLib")
    set_kind("static")
    add_files(
        "Audio/*.cpp",
        "Collider/**/*.cpp",
        "ECS/**/*.cpp",
        "engine/*.cpp",
        "graphics/*.cpp",
        "Logger/*.cpp",
        "Scene/*.cpp",
        "UI/*.cpp",
        "Var/*.cpp"
    )

    add_includedirs(
        ".",
        "ECS/Components/",
        "ECS/Components/Audio/",
        "ECS/Components/Camera/",
        "ECS/Components/Collider2D/",
        "ECS/Components/Physic/",
        "ECS/Components/Sprite/",
        "ECS/Components/Transform/",
        "ECS/Objects/",
        "ECS/Systems/",
        "Collider/",
        "Collider/Collider2D/",
        "engine/",
        "graphics/",
        "Logger/",
        "Scene/",
        "UI/"
    )

    add_packages("raylib", "rapidjson")
target_end()