#pragma once
#include <string>

#include <memory>
#include <Sage/Core/Window.h>
#include "Sage/Events/Event.h"
#include "Sage/Events/ApplicationEvent.h"
#include "Sage/Core/Timer.h"
#include "Sage/ImGui/ImGuiOverlay.h"

class Engine
{
public:
    Engine(uint32_t width, uint32_t height, const std::string& name);
    ~Engine();

    static Engine& Get() { return *instance; }

    void run();

private:
    void EventCallback(Sage::Event& e);
    void WindowCloseEventCallback(Sage::WindowCloseEvent& e);

private:
    static Engine* instance;

    std::unique_ptr<Sage::Window> window;
    bool running = true;
    uint32_t ticksCount = 0;
    const int targetFrameRate = 60;
    const float timePerFrame = 1000.0f / targetFrameRate;

    Sage::Timer timer;
    Sage::ImGuiOverlay* ImGuiOverlay;

    friend class Sage::ImGuiOverlay;
};