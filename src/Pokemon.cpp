#include "../include/Pokemon.hpp"
#include "../include/TextureManager.hpp"
#include "../lib/SDL2/include/SDL2/SDL.h"

Pokemon::Pokemon(const char *name, const char *img_path, int xPos, int yPos) : GameObject(img_path, xPos, yPos)
{

    this->m_objTexture = Texture::TextureManager::LoadTexture(img_path);
    this->m_nameSerializable = name;
    // TO DO FIX THIS
    this->m_nameBox = new Textbox({this->m_objRect.x + (this->m_objRect.w / 2), this->m_objRect.y + 20, 50, 10}, {255, 255, 255, 255}, m_nameSerializable.c_str(), 12);
};

void Pokemon::Render()
{
    this->m_nameBox->Render();
    SDL_RenderCopy(Game::Renderer, this->m_objTexture, NULL, &this->m_objRect);
};

void Pokemon::Update()
{
}

Pokemon::~Pokemon()
{
    SDL_DestroyTexture(this->m_objTexture);
    delete m_nameBox;
}