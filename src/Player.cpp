#include "../include/Player.hpp"
#include "../include/TextureManager.hpp"
#define __MOVEMENT_SPEED__ 5
#include <math.h>

Player::Player(const char *username, const char *img_path, int xPos, int yPos) : GameObject(img_path, xPos, yPos)
{

    m_currentBall = nullptr;
    m_previousBall = nullptr;
    m_movementState[static_cast<int>(_MOVING_STATE::__STATE_LEFT)] = false;
    m_movementState[static_cast<int>(_MOVING_STATE::__STATE_RIGHT)] = false;
    m_movementState[static_cast<int>(_MOVING_STATE::__STATE_DOWN)] = false;
    m_movementState[static_cast<int>(_MOVING_STATE::__STATE_UP)] = false;
    m_nameSerializable = username;
    m_nameBox = new Textbox({this->ObjRect.x + (this->ObjRect.w / 2), this->ObjRect.y + 20, 50, 10}, {255, 255, 255, 255}, m_nameSerializable.c_str(), 12);
    _initBallInv();
    ErrCode = PLAYER_ERROR_CODE::__OK;
    m_moving = false;
};
Ball *Player::GetPreviousBall() const
{
    return m_previousBall;
}

void Player::_initBallInv()
{
    for (int i = 0; i < 4; i++)
    {
        m_ballInv[i] = nullptr;
    }

    m_ballInv[0] = new Ball("Pokeball", "assets/ball/pokeball.png", this->ObjRect.x, 300, BALLTYPE::__TYPE_POKEBALL);
    m_ballInv[1] = new Ball("Greatball", "assets/ball/greatball.png", this->ObjRect.x + 100, 300, BALLTYPE::__TYPE_GREATBALL);
    m_ballInv[2] = new Ball("Ultraball", "assets/ball/ultraball.png", this->ObjRect.x + 200, 300, BALLTYPE::__TYPE_ULTRABALL);
    m_ballInv[3] = new Ball("Masterball", "assets/ball/masterball.png", this->ObjRect.x + 300, 300, BALLTYPE::__TYPE_MASTERBALL);
}

void Player::RenderBallInventory() const
{
    for (size_t i = 0; i < 4; i++)
    {
        m_ballInv[i]->Render();
    }
}

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

void Player::NullifyBallState()
{
    this->m_currentBall = nullptr;
    this->m_previousBall = nullptr;
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

    for (int i = 0; i < 4; i++)
    {
        m_ballInv[i]->Update();
        int playerCenterX = ObjRect.x + (ObjRect.w / 2);
        int playerCenterY = ObjRect.y + (ObjRect.h / 2);
        int ballCenterX = m_ballInv[i]->ObjRect.x + (m_ballInv[i]->ObjRect.w / 2);
        int ballCenterY = m_ballInv[i]->ObjRect.y + (m_ballInv[i]->ObjRect.h / 2);
        int distance = sqrt(pow(playerCenterX - ballCenterX, 2) + pow(playerCenterY - ballCenterY, 2));

        int threshold = 50;

        if (distance < threshold)
        {
            m_previousBall = m_currentBall;
            m_currentBall = m_ballInv[i];
            break;
        }
    }
}

Ball *Player::GetCurrentBall() const
{

    return this->m_currentBall;
}

PLAYER_ERROR_CODE Player::HandleInput(const SDL_Event *e)
{
    ErrCode = PLAYER_ERROR_CODE::__OK;
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
        case SDLK_RETURN:
            if (this->GetCurrentBall() == nullptr)
            {
                ErrCode = PLAYER_ERROR_CODE::__NULL_BALL;
            }
            else if (this->GetCurrentBall()->GetAmount() == 0)
            {
                ErrCode = PLAYER_ERROR_CODE::__NULL_AMOUNT;
            }
            else
            {
                ErrCode = PLAYER_ERROR_CODE::__OK_THROW;
            }
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
        case SDLK_RETURN:
            ErrCode = PLAYER_ERROR_CODE::__OK;
            break;
        default:
            break;
        }
    }

    // Check if any movement key is pressed
    m_moving = m_movementState.any();
    return ErrCode;
}

Player::~Player()
{
    for (int i = 0; i < 4; i++)
    {
        delete m_ballInv[i];
        m_ballInv[i] = nullptr;
    }
    SDL_DestroyTexture(this->m_objTexture);
    delete this->m_nameBox;
}
