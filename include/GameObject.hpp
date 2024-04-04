#pragma once
#include "../lib/SDL2/include/SDL2/SDL.h"
#include "Textbox.hpp"

class GameObject
{
protected:
    SDL_Texture *m_objTexture;
    SDL_Rect m_objRect;

public:
    GameObject(const char *img_path, int xPos, int yPos);

    void Render();
    void Update();

    ~GameObject();
};