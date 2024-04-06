#pragma once
#include "Game.hpp"
#include "../lib/SDL2/include/SDL2/SDL.h"
#include "Textbox.hpp"
#include <vector>

class Console
{
    SDL_Rect m_consoleCanvas;
    SDL_Color m_consoleColor;
    Textbox *m_title;
    std::vector<Textbox *> m_log;

public:
    Console(int screen_xpos, int screen_ypos, int screen_width, int screen_height, SDL_Color console_color);
    void Render();
    void Update();
    void PushLog(const char *logString);
    void HandleConsoleEvents();
    ~Console();
};