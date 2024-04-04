#include "../include/Player.hpp"

Player::Player(const char *img_path, int xPos, int yPos) : GameObject(img_path, xPos, yPos)
{
    this->m_moving = false;
};

void Player::HandleInput(const SDL_Event *event)
{

    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_LEFT:
            this->m_objRect.x -= 10;
            break;
        case SDLK_RIGHT:
            this->m_objRect.x += 10;
            break;
        case SDLK_DOWN:
            this->m_objRect.y += 10;
            break;
        case SDLK_UP:
            this->m_objRect.y -= 10;
            break;
        default:
            break;
        }
    }
}
