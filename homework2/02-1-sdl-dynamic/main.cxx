#include <iostream>

#include <SDL2/SDL.h>

int main()
{
    using namespace std;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        cout << "SDL initialization failed: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    cout << "Compiled SDL version: " << (int)compiled.major << "."
         << (int)compiled.minor << "." << (int)compiled.patch << endl;
    cout << "Linked SDL version: " << (int)linked.major << "."
         << (int)linked.minor << "." << (int)linked.patch << endl;
    return cout.good();
}