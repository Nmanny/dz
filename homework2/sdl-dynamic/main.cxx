#include <SDL2/SDL_version.h>
#include <iostream>

int main()
{
    using namespace std;
    setenv("SDL_DYNAMIC_API", "/usr/local/lib/libSDL2-2.0.so.0.26.5", 1);

    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    cout << "Compiled SDL version: " << (int)compiled.major << "."
         << (int)compiled.minor << "." << (int)compiled.patch << endl;
    cout << "Linked SDLd version: " << (int)linked.major << "."
         << (int)linked.minor << "." << (int)linked.patch << endl;
    return cout.good();
}