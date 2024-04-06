#include "../include/Pokemon.hpp"
#include "../include/TextureManager.hpp"
#include "../lib/SDL2/include/SDL2/SDL.h"

Pokemon::Pokemon(const char *name, const char *img_path, int xPos, int yPos) : GameObject(img_path, xPos, yPos)
{
    _spawn();
    this->m_objTexture = Texture::TextureManager::LoadTexture(img_path);
    this->m_nameSerializable = name;
    this->m_nameBox = new Textbox({this->ObjRect.x, this->ObjRect.y - 20, 100, 20}, {255, 255, 255, 255}, m_nameSerializable.c_str(), 12);
};

void Pokemon::_spawn()
{
    this->ObjRect.x = 500;
    this->ObjRect.y = 150;
    this->ObjRect.w = 64;
    this->ObjRect.h = 64;
}

const std::string Pokemon::BuildSpawnString() const
{
    std::string stringBuilder = "";
    stringBuilder += this->m_nameSerializable;
    stringBuilder += " Has Appeared!";

    return stringBuilder;
}

void Pokemon::Render()
{
    this->m_nameBox->Render();
    SDL_RenderCopy(Game::Renderer, this->m_objTexture, NULL, &this->ObjRect);
};

void Pokemon::Update()
{
    // maybe make pokemon move around a little?
}

Pokemon::~Pokemon()
{
    SDL_DestroyTexture(this->m_objTexture);
    delete m_nameBox;
}