workspace "Sage"
   configurations { "Debug", "Release" }
   platforms { "x64" }
   startproject "SageEditor"
   defines{ "YAML_CPP_STATIC_DEFINE" }

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
        "engine/dependencies/stb_image/stb_image.cpp",
        "engine/dependencies/glm/glm/**.hpp",
        "engine/dependencies/glm/glm/**.inl",
    }
    includedirs {
        "engine/dependencies/SDL/include",
        "engine/src",
        "engine/dependencies/spdlog/include/",
        "engine/dependencies/imgui/",
        "engine/dependencies/entt/",
        "engine/dependencies/stb_image/",
        "engine/dependencies/glm/",
        "engine/dependencies/Glad/include/",
        "engine/dependencies/yaml-cpp/include/",
    }
    links {
        "SDL",
        "SDLmain",
        "ImGui",
        "Glad",
        "yaml-cpp"
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
        "engine/dependencies/spdlog/include/",
        "engine/dependencies/imgui/",
        "engine/dependencies/entt/",
        "engine/dependencies/stb_image/",
        "engine/dependencies/glm/",
        "engine/dependencies/Glad/include/",
    }
    links {
        "Sage"
    }
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

group "Dependencies"
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

project "Glad"
    location "engine/dependencies/Glad/"
    kind "StaticLib"
    language "C"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    files {
        "engine/dependencies/Glad/include/glad/glad.h",
        "engine/dependencies/Glad/include/KHR/khrplatform.h",
        "engine/dependencies/Glad/src/glad.c"
    }
    includedirs{
        "engine/dependencies/Glad/include/",
    }

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

project "yaml-cpp"
    kind "StaticLib"
    location "engine/dependencies/yaml-cpp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    files{
        "engine/dependencies/yaml-cpp/src/**.h",
        "engine/dependencies/yaml-cpp/src/**.cpp",
        "engine/dependencies/yaml-cpp/include/**.h",
    }
    includedirs {
        "engine/dependencies/yaml-cpp/include",
    }