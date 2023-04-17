#include "engine.hxx"
#include <chrono>
#include <filesystem>
#include <iostream>
#include <memory>
#include <thread>

namespace nn
{
static std::map<SDL_Keycode, std::string> keyNames_{ { SDLK_w, "up" },
                                                     { SDLK_a, "left" },
                                                     { SDLK_s, "down" },
                                                     { SDLK_d, "right" },
                                                     { SDLK_SPACE, "start" } };

std::map<SDL_Keycode, KeyState> keyStates_;

void HandleKeyDown(const SDL_KeyboardEvent& key)
{
    if (keyNames_.count(key.keysym.sym) > 0)
    {
        std::string keyName = keyNames_[key.keysym.sym];

        if (!keyStates_[key.keysym.sym].pressed)
        {
            keyStates_[key.keysym.sym].pressed = true;
            std::cout << "Key pressed: " << keyName << std::endl;
        }
    }
}

void HandleKeyUp(const SDL_KeyboardEvent& key)
{
    if (keyNames_.count(key.keysym.sym) > 0)
    {
        std::string keyName = keyNames_[key.keysym.sym];

        keyStates_[key.keysym.sym].pressed  = false;
        keyStates_[key.keysym.sym].released = true;

        std::cout << "Key released: " << keyName << std::endl;
    }
}

class init : public engine
{
public:
    void run()
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
};

engine::~engine()     = default;
bool    already_exist = false;
engine* create_engine()
{
    if (already_exist)
    {
        throw std::runtime_error("engine already exist");
    }

    already_exist = true;
    return new init();
}
} // namespace nn

nn::game* reload_game(nn::game*   old,
                      const char* library_name,
                      const char* tmp_library_name,
                      nn::engine& engine,
                      void*&      old_handle);

int main(int /*argc*/, char* /*argv*/[])
// clang-format on
{
    std::unique_ptr<nn::engine> engine(nn::create_engine());

    std::cout << "start app\n" << std::endl;

    using namespace std::string_literals;
    using namespace std::filesystem;

    const char* library_name     = "./libgame-03-4.so";
    const char* tmp_library_file = "./temp.so";

    void*     game_library_handle{};
    nn::game* game = reload_game(
        nullptr, library_name, tmp_library_file, *engine, game_library_handle);

    auto time_during_loading = last_write_time(library_name);

    game->initialize();

    bool continue_loop = true;
    while (continue_loop)
    {
        auto current_write_time = last_write_time(library_name);

        if (current_write_time != time_during_loading)
        {
            file_time_type next_write_time;

            for (;;)
            {
                using namespace std::chrono;
                std::this_thread::sleep_for(milliseconds(100));
                next_write_time = last_write_time(library_name);
                if (next_write_time != current_write_time)
                {
                    current_write_time = next_write_time;
                }
                else
                {
                    break;
                }
            }

            std::cout << "\n"
                      << "reloading game" << std::endl;
            game = reload_game(game,
                               library_name,
                               tmp_library_file,
                               *engine,
                               game_library_handle);

            if (game == nullptr)
            {
                std::cerr << "next attempt to reload game..." << std::endl;
                continue;
            }

            time_during_loading = next_write_time;
        }

        game->update();
        game->render();
    }

    return EXIT_SUCCESS;
}

nn::game* reload_game(nn::game*   old,
                      const char* library_name,
                      const char* tmp_library_name,
                      nn::engine& engine,
                      void*&      old_handle)
{
    using namespace std::filesystem;

    if (old)
    {
        SDL_UnloadObject(old_handle);
    }

    if (std::filesystem::exists(tmp_library_name))
    {
        if (0 != remove(tmp_library_name))
        {
            std::cerr << "error: can't remove: " << tmp_library_name
                      << std::endl;
            return nullptr;
        }
    }

    try
    {
        copy(library_name, tmp_library_name); // throw on error
    }
    catch (const std::exception& ex)
    {
        std::cerr << "error: can't copy [" << library_name << "] to ["
                  << tmp_library_name << "]" << std::endl;
        return nullptr;
    }

    void* game_handle = SDL_LoadObject(tmp_library_name);

    if (game_handle == nullptr)
    {
        std::cerr << "error: failed to load: [" << tmp_library_name << "] "
                  << SDL_GetError() << std::endl;
        return nullptr;
    }

    old_handle = game_handle;

    SDL_FunctionPointer create_game_func_ptr =
        SDL_LoadFunction(game_handle, "create_game");

    if (create_game_func_ptr == nullptr)
    {
        std::cerr << "error: no function [create_game] in " << tmp_library_name
                  << " " << SDL_GetError() << std::endl;
        return nullptr;
    }

    using create_game_ptr = decltype(&create_game);

    auto create_game_func =
        reinterpret_cast<create_game_ptr>(create_game_func_ptr);

    nn::game* game = create_game_func(&engine);

    if (game == nullptr)
    {
        std::cerr << "error: func [create_game] returned: nullptr" << std::endl;
        return nullptr;
    }
    return game;
}
