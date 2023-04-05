#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Hello, world!",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640,
                                          480,
                                          SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Init();

    TTF_Font* font = TTF_OpenFont("../../assets/Roman-Cd-Bold.ttf", 24);
    if (font == nullptr)
    {
        std::cerr << "Failed to load font." << std::endl;
        return 1;
    }

    SDL_Color    color   = { 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Hello, world!", color);
    if (surface == nullptr)
    {
        std::cerr << "Failed to create surface." << std::endl;
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr)
    {
        std::cerr << "Failed to create texture." << std::endl;
        return 1;
    }

    SDL_Rect rect = { 0, 0, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
