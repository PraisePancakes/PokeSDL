#pragma once
#include "Game.hpp"
#include "../lib/SDL2/include/SDL2/SDL.h"
#include "Textbox.hpp"

class Console
{
    SDL_Rect m_consoleCanvas;
    SDL_Color m_consoleColor;
    Textbox *m_title;

public:
    Console(int screen_xpos, int screen_ypos, int screen_width, int screen_height, SDL_Color console_color);
    void Render();
    void Update();
    void HandleConsoleEvents();
    ~Console();
};