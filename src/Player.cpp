#include "../include/Player.hpp"
#include "../include/TextureManager.hpp"

Player::Player(const char *img_path, int xPos, int yPos) : GameObject(img_path, xPos, yPos)
{
    this->m_moving = false;
};

void Player::Update()
{
    if (m_moving)
    {
        this->m_objTexture = Texture::TextureManager::LoadTexture("assets/player/run.png");
        if (m_movingLeft)
        {

            m_objRect.x -= 1;
        }
        if (m_movingRight)
        {

            m_objRect.x += 1;
        }
        if (m_movingUp)
        {

            m_objRect.y -= 1;
        }
        if (m_movingDown)
        {

            m_objRect.y += 1;
        }
    }
    else
    {
        this->m_objTexture = Texture::TextureManager::LoadTexture("assets/player/idle.png");
    }
}

void Player::HandleInput(const SDL_Event *event)
{

    if (event->type == SDL_KEYDOWN)
    {
        m_moving = true;
        switch (event->key.keysym.sym)
        {
        case SDLK_LEFT:
            m_movingLeft = true;

            break;
        case SDLK_RIGHT:
            m_movingRight = true;

            break;
        case SDLK_DOWN:
            m_movingDown = true;

            break;
        case SDLK_UP:
            m_movingUp = true;

            break;
        default:
            break;
        }
    }
    else if (event->type == SDL_KEYUP)
    {
        m_moving = false;
        switch (event->key.keysym.sym)
        {
        case SDLK_LEFT:
            m_movingLeft = false;
            break;
        case SDLK_RIGHT:
            m_movingRight = false;
            break;
        case SDLK_DOWN:
            m_movingDown = false;
            break;
        case SDLK_UP:
            m_movingUp = false;
            break;
        default:
            break;
        }
    }
}
