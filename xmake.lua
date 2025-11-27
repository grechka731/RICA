add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = "build"}) -- generate compile commands

set_policy("build.sanitizer.address", true)
set_policy("build.sanitizer.leak", true)

add_requires("raylib", "rapidjson") -- libs
set_warnings("all") -- warns
set_languages("c++17")

includes("src", "game")