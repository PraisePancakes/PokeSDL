#include "../include/Ball.hpp"
#include "../include/TextureManager.hpp"
#include <unistd.h>

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

    switch (type)
    {
    case BALLTYPE::__TYPE_POKEBALL:
        m_ballMod = 1;
        break;
    case BALLTYPE::__TYPE_GREATBALL:
        m_ballMod = 5;
        break;
    case BALLTYPE::__TYPE_ULTRABALL:
        m_ballMod = 7;
        break;
    case BALLTYPE::__TYPE_MASTERBALL:
        m_ballMod = 10;
        break;
    };
    this->ObjRect.w = 32;
    this->ObjRect.h = 32;
    this->m_nameSerializable = ball_name;
    this->m_objTexture = Texture::TextureManager::LoadTexture(img_path);
    this->BallType = type;
    this->m_nameBox = new Textbox({this->ObjRect.x, this->ObjRect.y + 30, 80, 30}, {255, 255, 255, 255}, " ", 12);

    this->m_catchRate = m_ballMod * 10;
};

void Ball::DecrementAmount()
{
    if (this->m_amount > 0)
        this->m_amount -= 1;
}

void Ball::Update()
{
    std::string amount_str = std::to_string(this->m_amount);
    std::string nameBoxBuilder = this->m_nameSerializable + " x " + amount_str;
    this->m_nameBox->SetText(nameBoxBuilder.c_str());
};

int Ball::GetCatchRate() const
{
    return this->m_catchRate;
}

int Ball::GetAmount() const
{
    return this->m_amount;
}

void Ball::Render()
{
    this->m_nameBox->Render();
    SDL_RenderCopy(Game::Renderer, this->m_objTexture, NULL, &this->ObjRect);
};

Ball::~Ball()
{
    delete m_nameBox;
    SDL_DestroyTexture(this->m_objTexture);
}