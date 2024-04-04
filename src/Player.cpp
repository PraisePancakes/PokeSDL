#include "../include/Player.hpp"
#include "../include/TextureManager.hpp"
#define __MOVEMENT_SPEED__ 1
Player::Player(const char *img_path, int xPos, int yPos) : GameObject(img_path, xPos, yPos)
{

    m_movementState[(int)(_MOVING_STATE::__STATE_LEFT)] = false;
    m_movementState[(int)(_MOVING_STATE::__STATE_RIGHT)] = false;
    m_movementState[(int)(_MOVING_STATE::__STATE_DOWN)] = false;
    m_movementState[(int)(_MOVING_STATE::__STATE_UP)] = false;

    m_moving = false;
};

void Player::Update()
{
    if (m_moving)
    {
        this->m_objTexture = Texture::TextureManager::LoadTexture("assets/player/run.png");
        if (m_movementState[(int)(_MOVING_STATE::__STATE_LEFT)] == true)
        {
            m_objRect.x -= __MOVEMENT_SPEED__;
        }
        if (m_movementState[(int)(_MOVING_STATE::__STATE_RIGHT)] == true)
        {
            m_objRect.x += __MOVEMENT_SPEED__;
        }
        if (m_movementState[(int)(_MOVING_STATE::__STATE_DOWN)] == true)
        {
            m_objRect.y += __MOVEMENT_SPEED__;
        }
        if (m_movementState[(int)(_MOVING_STATE::__STATE_UP)] == true)
        {
            m_objRect.y -= __MOVEMENT_SPEED__;
        }
    }
    else
    {

        this->m_objTexture = Texture::TextureManager::LoadTexture("assets/player/idle.png");
    }
}

void Player::HandleInput(const SDL_Event *e)
{
    if (e->key.type == SDL_KEYDOWN)
    {
        switch (e->key.keysym.sym)
        {
        case SDLK_LEFT:
            m_movementState.set(static_cast<int>(_MOVING_STATE::__STATE_LEFT));
            break;
        case SDLK_DOWN:
            m_movementState.set(static_cast<int>(_MOVING_STATE::__STATE_DOWN));
            break;
        case SDLK_UP:
            m_movementState.set(static_cast<int>(_MOVING_STATE::__STATE_UP));
            break;
        case SDLK_RIGHT:
            m_movementState.set(static_cast<int>(_MOVING_STATE::__STATE_RIGHT));
            break;
        default:
            break;
        }
    }
    else if (e->key.type == SDL_KEYUP)
    {
        switch (e->key.keysym.sym)
        {
        case SDLK_LEFT:
            m_movementState.reset(static_cast<int>(_MOVING_STATE::__STATE_LEFT));
            break;
        case SDLK_DOWN:
            m_movementState.reset(static_cast<int>(_MOVING_STATE::__STATE_DOWN));
            break;
        case SDLK_UP:
            m_movementState.reset(static_cast<int>(_MOVING_STATE::__STATE_UP));
            break;
        case SDLK_RIGHT:
            m_movementState.reset(static_cast<int>(_MOVING_STATE::__STATE_RIGHT));
            break;
        default:
            break;
        }
    }

    // Check if any movement key is pressed
    m_moving = m_movementState.any();
}
