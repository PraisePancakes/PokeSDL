#pragma once
#include "../lib/SDL2/include/SDL2/SDL.h"
#include "Textbox.hpp"

class GameObject
{
protected:
    SDL_Texture *m_objTexture;

public:
    GameObject(const char *img_path, int xPos, int yPos);
    SDL_Rect m_objRect;
    virtual void Render() = 0; // Render is now a virtual because player render will be different from each other object
    virtual void Update() = 0; // update can be different for children, where each child has its own updateable states

    ~GameObject();
};