#include <SDL3/SDL.h>
#include <iostream>
#include <map>

struct KeyState
{
    bool pressed  = false;
    bool released = false;
};

int main(int argc, char* argv[])
{
    SDL_Window* window =
        SDL_CreateWindow("Keyboard events", 640, 480, SDL_WINDOW_OPENGL);
    bool      loop = true;
    SDL_Event event;

    std::map<SDL_Keycode, std::string> keyNames{ { SDLK_w, "up" },
                                                 { SDLK_a, "left" },
                                                 { SDLK_s, "down" },
                                                 { SDLK_d, "right" },
                                                 { SDLK_SPACE, "start" } };

    std::map<SDL_Keycode, KeyState> keyStates;

    while (loop)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    loop = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    if (keyNames.count(event.key.keysym.sym) > 0)
                    {
                        std::string keyName = keyNames[event.key.keysym.sym];
                        if (!keyStates[event.key.keysym.sym].pressed)
                        {
                            keyStates[event.key.keysym.sym].pressed = true;
                            std::cout << "Key pressed: " << keyName
                                      << std::endl;
                        }
                    }
                    break;
                case SDL_EVENT_KEY_UP:
                    if (keyNames.count(event.key.keysym.sym) > 0)
                    {
                        std::string keyName = keyNames[event.key.keysym.sym];
                        keyStates[event.key.keysym.sym].pressed  = false;
                        keyStates[event.key.keysym.sym].released = true;
                        std::cout << "Key released: " << keyName << std::endl;
                    }
                    break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}