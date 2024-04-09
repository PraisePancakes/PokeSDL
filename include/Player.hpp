#pragma once
#include "GameObject.hpp"
#include <bitset>
#include "Ball.hpp"

enum class _MOVING_STATE
{
    __STATE_LEFT,
    __STATE_RIGHT,
    __STATE_DOWN,
    __STATE_UP,
};

enum class PLAYER_ERROR_CODE
{
    __OK,
    __OK_THROW,
    __NULL_AMOUNT,
    __NULL_BALL,
};

class Player : public GameObject
{
    std::bitset<4> m_movementState;
    bool m_moving;
    std::string m_nameSerializable;
    Textbox *m_nameBox;
    Ball *m_ballInv[4];
    void _initBallInv();
    Ball *m_currentBall;
    Ball *m_previousBall;

public:
    Player(const char *username, const char *img_path, int xPos, int yPos);
    PLAYER_ERROR_CODE ErrCode;
    void Update() override;
    void Render() override;
    void RenderBallInventory() const;
    Ball *GetCurrentBall() const;
    Ball *GetPreviousBall() const;
    void NullifyBallState();
    PLAYER_ERROR_CODE HandleInput(const SDL_Event *e);
    void CenterPos();

    ~Player();
};