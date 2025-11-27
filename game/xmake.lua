target("MyGame")
    set_kind("binary")
    add_files("*.cpp")

    add_deps("EngineLib")
target_end()