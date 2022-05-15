workspace "Sage"
   configurations { "Debug", "Release" }
   platforms { "x64" }
   startproject "Game"


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
   

filter "configurations:Debug"
   runtime "Debug"
   symbols "on"

filter "configurations:Release"
   runtime "Release"
   optimize "on"

project "Sage"
    language "C++"
    cppdialect "C++17"
    location "engine/"
    staticruntime "Off"
    kind "StaticLib"
    files {
        "engine/src/Sage/**.cpp",
        "engine/src/Sage/**.hpp",
        "engine/src/Sage/**.h",
    }
    includedirs {
        "engine/dependencies/SDL/include",
        "engine/src",
        "engine/dependencies/SDL_image",
        "engine/dependencies/SDL_ttf"
    }
    links {
        "SDL",
        "SDLmain",
        "SDL_image",
        "SDL_ttf"
    }
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

project "Game"
    language "C++"
    cppdialect "C++17"
    location "game/"
    staticruntime "Off"
    kind "ConsoleApp"
    files {
        "game/**.cpp",
        "game/**.hpp",
        "src/main.cpp"
    }
    includedirs {
        "engine/dependencies/SDL/include",
        "engine/src",
        "game/",
        "engine/dependencies/SDL_image",
        "engine/dependencies/SDL_ttf"
    }
    links {
        "Sage"
    }
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")


externalproject "SDL"
    location "engine/dependencies/SDL/VisualC/SDL"
    uuid "81CE8DAF-EBB2-4761-8E45-B71ABCCA8C68"
    kind "StaticLib"
    language "C"

externalproject "SDLmain"
    location "engine/dependencies/SDL/VisualC/SDLmain"
    uuid "DA956FD3-E142-46F2-9DD5-C78BEBB56B7A"
    kind "StaticLib"
    language "C"

externalproject "SDL_image"
    location "engine/dependencies/SDL_image/VisualC"
    uuid "2BD5534E-00E2-4BEA-AC96-D9A92EA24696"
    kind "StaticLib"
    language "C"

externalproject "SDL_ttf"
    location "engine/dependencies/SDL_ttf/VisualC"
    uuid "DDDBD07D-DC76-4AF6-8D02-3E2DEB6EE255"
    kind "StaticLib"
    language "C"