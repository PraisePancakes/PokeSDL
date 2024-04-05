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
    Game *g = new Game(username.c_str(), "PokeSDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _WINDOW_WIDTH, _WINDOW_HEIGHT);

    while (g->IsRunning())
    {
        g->HandleEvents();
        g->Render();
        g->Update();
    }

    return EXIT_SUCCESS;
}