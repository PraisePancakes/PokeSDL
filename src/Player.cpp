#include "../include/Player.hpp"
#include "../include/TextureManager.hpp"
#define __MOVEMENT_SPEED__ 1
Player::Player(const char *username, const char *img_path, int xPos, int yPos) : GameObject(img_path, xPos, yPos)
{

    m_movementState[static_cast<int>(_MOVING_STATE::__STATE_LEFT)] = false;
    m_movementState[static_cast<int>(_MOVING_STATE::__STATE_RIGHT)] = false;
    m_movementState[static_cast<int>(_MOVING_STATE::__STATE_DOWN)] = false;
    m_movementState[static_cast<int>(_MOVING_STATE::__STATE_UP)] = false;
    m_nameSerializable = username;
    m_nameBox = new Textbox({this->ObjRect.x + (this->ObjRect.w / 2), this->ObjRect.y + 20, 50, 10}, {255, 255, 255, 255}, m_nameSerializable.c_str(), 12);

    m_moving = false;
};

void Player::Render()
{
    this->m_nameBox->Render();
    SDL_RenderCopy(Game::Renderer, this->m_objTexture, NULL, &this->ObjRect);
}

void Player::CenterPos()
{
    this->ObjRect.x = 550;
    this->ObjRect.y = 150;
}

void Player::Update()
{
    if (m_moving)
    {
        this->m_objTexture = Texture::TextureManager::LoadTexture("assets/player/run.png");
        if (m_movementState[static_cast<int>(_MOVING_STATE::__STATE_LEFT)] == true)
        {
            ObjRect.x -= __MOVEMENT_SPEED__;
        }
        if (m_movementState[static_cast<int>(_MOVING_STATE::__STATE_RIGHT)] == true)
        {
            ObjRect.x += __MOVEMENT_SPEED__;
        }
        if (m_movementState[static_cast<int>(_MOVING_STATE::__STATE_DOWN)] == true)
        {
            ObjRect.y += __MOVEMENT_SPEED__;
        }
        if (m_movementState[static_cast<int>(_MOVING_STATE::__STATE_UP)] == true)
        {
            ObjRect.y -= __MOVEMENT_SPEED__;
        }
    }
    else
    {
        this->m_objTexture = Texture::TextureManager::LoadTexture("assets/player/idle.png");
    }

    this->m_nameBox->m_boxRect.x = this->ObjRect.x + (this->ObjRect.w / 4);
    this->m_nameBox->m_boxRect.y = this->ObjRect.y + 20;
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

Player::~Player()
{

    SDL_DestroyTexture(this->m_objTexture);
    delete this->m_nameBox;
}
