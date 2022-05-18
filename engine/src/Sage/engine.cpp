#include "engine.hpp"

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Sage/renderer/renderer.hpp"
#include "Sage/gameScene/sceneManager.hpp"
#include "Sage/texture/texture.hpp"
#include "Sage/Core/Log.h"

Engine::Engine(uint32_t width, uint32_t height, const std::string &name)
{
    Sage::Log::Init();
    initialiseSDL();
    Sage::WindowProperties properties{ width, height, name };
    window = Sage::Window::Create(properties);
	initialiseComponents();
}

void Engine::initialiseSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SAGE_CORE_CRIT("SDL Failed to initialise!");
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        SAGE_CORE_CRIT("SDL Image Failed to initialise!");
    }

    if (TTF_Init() < 0)
    {
        SAGE_CORE_CRIT("SDL TTF Failed to initialise!");
    }
}

void Engine::initialiseComponents()
{
	Renderer::init(window.get());
}

Engine::~Engine()
{
    sceneManager::quit();
    Renderer::destroy();
    Font::freeAllFonts();

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Engine::run()
{
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) {
                running = false;
                break;
            }
            sceneManager::getCurrentScene()->on_event(e);
        }
        float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
        if (deltaTime > 0.5) {
            deltaTime = 0.5f;
        }
        ticksCount = SDL_GetTicks();
        sceneManager::getCurrentScene()->on_step(deltaTime);
        sceneManager::getCurrentScene()->on_render();
    }
}
