#pragma once
#include <string>

#include <memory>
#include <Sage/Core/Window.h>


class Engine
{
public:
    Engine(uint32_t width, uint32_t height, const std::string& name);
    ~Engine();

    void run();

private:
    void initialiseSDL();
    void initialiseComponents();

private:
    std::unique_ptr<Sage::Window> window;
    bool running = true;
    uint32_t ticksCount = 0;
    const int targetFrameRate = 60;
    const float timePerFrame = 1000.0f / targetFrameRate;
};