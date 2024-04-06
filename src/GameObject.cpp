#include "../include/GameObject.hpp"
#include "../include/TextureManager.hpp"

GameObject::GameObject(const char *img_path, int xPos, int yPos)
{
    this->m_objTexture = Texture::TextureManager::LoadTexture(img_path);
    this->ObjRect.x = xPos;
    this->ObjRect.y = yPos;
    this->ObjRect.w = 128;
    this->ObjRect.h = 128;
};

GameObject::~GameObject()
{
    SDL_DestroyTexture(this->m_objTexture);
}