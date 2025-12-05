add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = "build"}) -- generate compile commands
set_policy("package.include_external_headers", false)

set_policy("build.sanitizer.address", true) -- sanitizers
set_policy("build.sanitizer.leak", true)

-- libs
add_requires("raylib", {external=false})
add_requires("rapidjson", {external=false})
set_warnings("all") -- warns
set_languages("c++17")

includes("src", "game")
