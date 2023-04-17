#include "engine.hxx"
#include <SDL3/SDL.h>
#include <iostream>
#include <map>
#include <string>

namespace nn
{
static std::map<SDL_Keycode, std::string> keyNames{ { SDLK_w, "up" },
                                                    { SDLK_a, "left" },
                                                    { SDLK_s, "down" },
                                                    { SDLK_d, "right" },
                                                    { SDLK_SPACE, "start" } };

std::map<SDL_Keycode, KeyState> keyStates;

void HandleKeyDown(const SDL_KeyboardEvent& key)
{
    if (keyNames.count(key.keysym.sym) > 0)
    {
        std::string keyName = keyNames[key.keysym.sym];

        if (!keyStates[key.keysym.sym].pressed)
        {
            keyStates[key.keysym.sym].pressed = true;
            std::cout << "Key pressed: " << keyName << std::endl;
        }
    }
}
void HandleKeyUp(const SDL_KeyboardEvent& key)
{
    if (keyNames.count(key.keysym.sym) > 0)
    {
        std::string keyName = keyNames[key.keysym.sym];

        keyStates[key.keysym.sym].pressed  = false;
        keyStates[key.keysym.sym].released = true;

        std::cout << "Key released: " << keyName << std::endl;
    }
}

void engine::run()
{
    SDL_Window* const window =
        SDL_CreateWindow("Keyboard events", 640, 480, SDL_WINDOW_OPENGL);
    SDL_Event event;
    bool      loop = true;

    while (loop)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_KEY_DOWN:
                    HandleKeyDown(event.key);
                    break;
                case SDL_EVENT_KEY_UP:
                    HandleKeyUp(event.key);
                    break;
            }

            if (event.type == SDL_EVENT_QUIT)
            {
                loop = false;
            }
        }
    }
}

engine::engine() {}

engine::~engine() = default;
} // namespace nn