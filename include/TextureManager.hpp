#pragma once
#include "../lib/SDL2/include/SDL2/SDL.h"
#include "../lib/SDL2TTF/include/SDL2/SDL_ttf.h"
#include "../lib/SDL2Image/include/SDL2/SDL_image.h"
#include "../include/Game.hpp"
#include <iostream>

namespace Texture
{
    class TextureManager
    {
    public:
        static SDL_Texture *LoadTexture(const char *img_path);
        static SDL_Texture *LoadTTF(const char *text, const char *ttf_path, SDL_Color font_color, int font_size);
    };
};