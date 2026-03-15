target("rlImGui")
	set_kind("static")

	add_files(
			"$(projectdir)/lib/rlImGui/*.cpp"
	)

	add_includedirs("$(projectdir)/lib/rlImGui", {public=true})

	add_packages("raylib", "imgui", {public=true})
target_end()

target("EngineLib")
    set_kind("static")
    add_files(
        "$(projectdir)/src/Audio/*.cpp",
        "$(projectdir)/src/Collider/**/*.cpp",
        "$(projectdir)/src/ECS/**/*.cpp",
        "$(projectdir)/src/engine/*.cpp",
        "$(projectdir)/src/graphics/**/*.cpp",
        "$(projectdir)/src/Physic/**/*.cpp",
        "$(projectdir)/src/Scene/*.cpp",
        "$(projectdir)/src/UI/*.cpp",
        "$(projectdir)/src/Var/*.cpp",
        "$(projectdir)/src/Input/*.cpp"
    )

    if has_config("editor") then
        add_files(        
        "$(projectdir)/src/editor/editor/*.cpp",
        "$(projectdir)/src/editor/panel/allPanels/terminal/*.cpp",
        "$(projectdir)/src/editor/panel/allPanels/viewport/*.cpp",
        "$(projectdir)/src/editor/panel/allPanels/details/*.cpp")

        add_includedirs("$(projectdir)/src/editor/editor/")
    end

    add_includedirs(
        "$(projectdir)/src",
        "$(projectdir)/src/ECS/Components/",
        "$(projectdir)/src/ECS/Components/Audio/",
        "$(projectdir)/src/ECS/Components/Camera/",
        "$(projectdir)/src/ECS/Components/Collider/Collider2D/",
        "$(projectdir)/src/ECS/Components/Physic/",
        "$(projectdir)/src/ECS/Components/Sprite/",
        "$(projectdir)/src/ECS/Components/Transform/",
        "$(projectdir)/src/ECS/Objects/",
        "$(projectdir)/src/ECS/Systems/",
        "$(projectdir)/src/Collider/",
        "$(projectdir)/src/Collider/Collider2D/",
        "$(projectdir)/src/engine/",
        "$(projectdir)/src/graphics/",
        "$(projectdir)/src/Scene/",
        "$(projectdir)/src/UI/",
        "$(projectdir)/src/Input/",
        "$(projectdir)/src/Reflection/"
    )

    add_packages("raylib", "rapidjson", "imgui", {public=true})
    add_deps("rlImGui", "Slog", {public=true})
    add_options("editor") 
target_end()
