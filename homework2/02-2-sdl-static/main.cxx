#include <iostream>

// #include <SDL2/SDL_version.h>
#ifdef SDL3
#include <SDL2/SDL_version.h>
#else
#include <SDL3/SDL_version.h>
#endif
int main()
{
    using namespace std;
    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    cout << "Compiled SDL version: " << (int)compiled.major << "."
         << (int)compiled.minor << "." << (int)compiled.patch << endl;
    cout << "Linked SDLs version: " << (int)linked.major << "."
         << (int)linked.minor << "." << (int)linked.patch << endl;
    return cout.good();
}