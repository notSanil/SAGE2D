#pragma once

#include <exception>

enum SDL_EXCEPTIONS{
    SDL_Uninitialised,
    Window_Failed,
    Renderer_Failed,
    Image_Failed,
    Font_Failed
};

struct SDLException: public std::exception{
    SDL_EXCEPTIONS error;

    SDLException(SDL_EXCEPTIONS error): error(error){};

    const char* what() const throw(){
        switch(error){
            case SDL_Uninitialised:
                return "SDL FAILED TO INITIALISE.";
            case Window_Failed:
                return "WINDOW CREATION FAILED.";
            case Renderer_Failed:
                return "RENDERER CREATION FAILED.";
            case Image_Failed:
                return "SDL IMAGE FAILED TO INITIALISE.";
            case Font_Failed:
                return "SDL TTF FAILED TO INITIALISE.";
            default:
                return "NO INFORMATION AVAILABLE";
        }

    }
};