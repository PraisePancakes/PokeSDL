#include "../include/Console.hpp"
#include "../lib/SDL2TTF/include/SDL2/SDL_ttf.h"
#include "../include/TextureManager.hpp"
#include <algorithm>
#include <iostream>

SDL_Color white;
SDL_Rect titleRect;
SDL_Rect logRect;

Console::Console(int console_xpos, int console_ypos, int console_width, int console_height, SDL_Color console_color)
{

    this->m_consoleCanvas.x = console_xpos;
    this->m_consoleCanvas.w = console_width;
    this->m_consoleCanvas.h = console_height;
    this->m_consoleCanvas.y = console_ypos;
    this->m_consoleColor = console_color;
    titleRect = {console_xpos + 20, console_ypos + 20, 100, 25};
    white = {0, 0, 0, 255};

    this->m_title = new Textbox(titleRect, white, "Game Log", 24);
}

void Console::PushLog(const char *logString)
{
    SDL_Rect logRect = {
        this->m_title->m_boxRect.x,
        this->m_title->m_boxRect.y,
        200,
        20};

    Textbox *logText = new Textbox(logRect, white, logString, 24);
    this->m_log.insert(this->m_log.begin(), logText);
}

void Console::PushLog(const char *logString, SDL_Color textColor)
{

    SDL_Rect logRect = {
        this->m_title->m_boxRect.x,
        this->m_title->m_boxRect.y,
        200,
        20};

    Textbox *logText = new Textbox(logRect, textColor, logString, 24);
    this->m_log.insert(this->m_log.begin(), logText);
}
void Console::_updateLogItemPositions()
{
    int yOffset = 50;
    for (const auto &logText : this->m_log)
    {
        logText->m_boxRect.y = this->m_title->m_boxRect.y + yOffset;
        yOffset += 50;
    }
}

void Console::Render()
{

    if (SDL_SetRenderDrawColor(Game::Renderer, this->m_consoleColor.r, this->m_consoleColor.g, this->m_consoleColor.b, this->m_consoleColor.a) < 0)
    {
        std::cout << "[err] SDL failed to set the console render draw color " << SDL_GetError() << std::endl;
    }

    if (SDL_RenderFillRect(Game::Renderer, &m_consoleCanvas) < 0)
    {
        std::cout << "[err] SDL failed to fill the console rect " << SDL_GetError() << std::endl;
    };

    this->m_title->Render();

    for (const auto &logText : this->m_log)
    {
        logText->Render();
    }
}

void Console::Update()
{
    _updateLogItemPositions();
};

Console::~Console()
{
    this->m_title->~Textbox();
    delete m_title;
}