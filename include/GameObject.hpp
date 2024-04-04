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
    void Render();             // Render method is the same for all game_objects, it just renders the texture at the given transform
    virtual void Update() = 0; // update can be different for children, where each child has its own updateable states

    ~GameObject();
};