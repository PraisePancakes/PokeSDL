#include "../include/Ball.hpp"
#include "../include/TextureManager.hpp"

Ball::Ball(const std::string &ball_name, const char *img_path, int xPos, int yPos, BALLTYPE type) : GameObject(img_path, xPos, yPos)
{
    if (type == BALLTYPE::__TYPE_MASTERBALL)
    {
        this->m_amount = 1;
    }
    else
    {
        this->m_amount = 5;
    }
    this->ObjRect.w = 32;
    this->ObjRect.h = 32;
    this->m_nameSerializable = ball_name;
    this->m_objTexture = Texture::TextureManager::LoadTexture(img_path);
    this->m_nameBox = new Textbox({this->ObjRect.x, this->ObjRect.y + 30, 70, 30}, {255, 255, 255, 255}, ball_name.c_str(), 12);
};

void Ball::Update(){};

void Ball::Render()
{
    this->m_nameBox->Render();
    SDL_RenderCopy(Game::Renderer, this->m_objTexture, NULL, &this->ObjRect);
};