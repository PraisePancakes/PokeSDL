#include "../include/GameObject.hpp"
#include "../include/TextureManager.hpp"

GameObject::GameObject(const char *img_path, int xPos, int yPos)
{
    this->m_objTexture = Texture::TextureManager::LoadTexture(img_path);
    this->m_objRect.x = xPos;
    this->m_objRect.y = yPos;
    this->m_objRect.w = 128;
    this->m_objRect.h = 128;
};

void GameObject::Render()
{
    SDL_RenderCopy(Game::Renderer, this->m_objTexture, NULL, &this->m_objRect);
}

void GameObject::Update()
{
}