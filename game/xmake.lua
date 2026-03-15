target("MyGame")
    set_kind("binary")
    add_files("$(projectdir)/game/*.cpp")

    add_includedirs(
        "$(projectdir)/src",
        "$(projectdir)/src/Reflection/"
    )

    add_deps("EngineLib")

    add_packages("raylib", "rapidjson")
    add_options("editor")
target_end()
