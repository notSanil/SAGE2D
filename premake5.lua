workspace "Sage"
   configurations { "Debug", "Release" }
   platforms { "x64" }
   startproject "SageEditor"


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
        "engine/src/Platform/**.h",
        "engine/src/Platform/**.cpp",
        "engine/dependencies/stb_image/stb_image.cpp"
    }
    includedirs {
        "engine/dependencies/SDL/include",
        "engine/src",
        "engine/dependencies/SDL_image",
        "engine/dependencies/SDL_ttf",
        "engine/dependencies/spdlog/include/",
        "engine/dependencies/imgui/",
        "engine/dependencies/entt/",
        "engine/dependencies/stb_image/",
    }
    links {
        "SDL",
        "SDLmain",
        "SDL_image",
        "SDL_ttf",
        "ImGui"
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
    }
    includedirs {
        "engine/dependencies/SDL/include",
        "engine/src",
        "game/",
        "engine/dependencies/SDL_image",
        "engine/dependencies/SDL_ttf",
        "engine/dependencies/spdlog/include/",
        "engine/dependencies/imgui/"
    }
    links {
        "Sage"
    }
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")


project "SageEditor"
    language "C++"
    cppdialect "C++17"
    location "editor/"
    staticruntime "Off"
    kind "ConsoleApp"
    files {
        "editor/**.cpp",
        "editor/**.hpp",
        "editor/**.h",
        "src/main.cpp"
    }
    includedirs {
        "engine/dependencies/SDL/include",
        "engine/src",
        "editor/",
        "engine/dependencies/SDL_image",
        "engine/dependencies/SDL_ttf",
        "engine/dependencies/spdlog/include/",
        "engine/dependencies/imgui/",
        "engine/dependencies/entt/",
        "engine/dependencies/stb_image/",
    }
    links {
        "Sage"
    }
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

externalproject "SDL"
    location "engine/dependencies/SDL/VisualC/SDL"
    uuid "81CE8DAF-EBB2-4761-8E45-B71ABCCA8C68"
    kind "SharedLib"
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

project "ImGui"
	kind "StaticLib"
	language "C++"
    location "engine/dependencies/imgui/"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"engine/dependencies/imgui/imconfig.h",
		"engine/dependencies/imgui/imgui.h",
		"engine/dependencies/imgui/imgui.cpp",
		"engine/dependencies/imgui/imgui_draw.cpp",
		"engine/dependencies/imgui/imgui_internal.h",
		"engine/dependencies/imgui/imgui_widgets.cpp",
		"engine/dependencies/imgui/imgui_tables.cpp",
		"engine/dependencies/imgui/imstb_rectpack.h",
		"engine/dependencies/imgui/imstb_textedit.h",
		"engine/dependencies/imgui/imgui_demo.cpp",
		"engine/dependencies/imgui/imstb_truetype.h",
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"