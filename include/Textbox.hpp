#pragma once
#include "../lib/SDL2/include/SDL2/SDL.h"
#include <ostream>

class Textbox
{
    SDL_Texture *m_boxTexture;
    SDL_Rect m_boxRect;
    SDL_Color m_textColor;

public:
    Textbox(SDL_Rect rect, SDL_Color color, const char *text, int font_size);

    void Render();
    void Update();
    void Print();
    
    ~Textbox();
};