#include <iostream>
#include "SDL2/SDL.h"
#include "../include/Game.hpp"

int main(int argc, char *argv[])
{

    std::string username;

    std::cout << "Befor we begin, give me your name : ";
    std::cin >> username;

    const int _WINDOW_WIDTH = 1024;
    const int _WINDOW_HEIGHT = 728;
    Game g(username.c_str(), "PokeSDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _WINDOW_WIDTH, _WINDOW_HEIGHT);

    const int TARGET_FPS = 60;
    const int DELAY_TIME = 1000 / TARGET_FPS;

    Uint32 frameStart, frameTime;

    while (g.IsRunning())
    {
        frameStart = SDL_GetTicks();

        g.HandleEvents();
        g.Render();
        g.Update();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < DELAY_TIME)
        {
            SDL_Delay(DELAY_TIME - frameTime);
        }
    }

    return EXIT_SUCCESS;
}