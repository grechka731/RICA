add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = "build"}) -- generate compile commands

set_policy("build.sanitizer.address", true) -- sanitizers
set_policy("build.sanitizer.leak", true)

-- libs
add_requires("raylib", {external=false})
add_requires("rapidjson", {external=false})

add_requires("imgui v1.90.4-docking", {configs = {docking = true}})
add_defines("IMGUI_ENABLE_DOCKING")
add_defines("IMGUI_HAS_DOCKING")
add_defines("IMGUI_ENABLE_VIEWPORTS")

set_warnings("all") -- warns
set_languages("c++17")

includes("src", "game", "lib/Slog")

-- editor: off or on
option("editor")
    set_default(true)
    add_defines("EDITOR")
