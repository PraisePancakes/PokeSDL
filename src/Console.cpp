#include "../include/Console.hpp"
#include "../lib/SDL2TTF/include/SDL2/SDL_ttf.h"
#include "../include/TextureManager.hpp"

#include <iostream>

SDL_Color textColor;
SDL_Rect titleRect;

Console::Console(int console_xpos, int console_ypos, int console_width, int console_height, SDL_Color console_color)
{

    this->m_consoleCanvas.x = console_xpos;
    this->m_consoleCanvas.w = console_width;
    this->m_consoleCanvas.h = console_height;
    this->m_consoleCanvas.y = console_ypos;
    this->m_consoleColor = console_color;

    titleRect = {console_xpos + 20, console_ypos + 20, 100, 25};
    textColor = {0, 0, 0, 255};

    this->m_title = new Textbox(titleRect, textColor, "Game Log", 24);
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
}

void Console::Update(){

};

void Console::HandleConsoleEvents(){

};

Console::~Console()
{
    this->m_title->~Textbox();
    delete m_title;
}