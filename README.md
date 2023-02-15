# SAGE2D (WIP)
Sanil's Awesome Game Engine (SAGE), a 2D game engine created in C++, with OpenGL as the renderer.

# Features
* Visual editor to allow easy creation of scenes
* Scripting in lua
* Easy rendering of quad primitives, and textures
* Orthographic camera for rendering multiple viewports
* Scene serialiser and desiraliser to save and load scenes easily

# Screenshots
![Sample Scene](/repo/EngineLevel.png?raw=true "A level created in SAGE")
![Sample Script](/repo/LuaScript.png?raw=true "A sample script")
![Customising the editor](/repo/DockableTabs.png?raw=true "All tabs are moveable and dockable")

# Building
* Clone the repository using `git clone --recursive https://github.com/notSanil/SAGE2D.git`
* Run the premake script using the `generate_projects.bat` file
* This will generate visual studio projects, you can also use any other project type that premake supports
* Run the visual studio project, it should build and execute automatically

# Planned features
* Improve the scripting API
* Add text rendering into the engine
* Add music handler into the engine
* Increase the number of components
* Add a physics system
