#pragma once
#include "GameObject.hpp"
#include <bitset>

enum class _MOVING_STATE
{
    __STATE_LEFT,
    __STATE_RIGHT,
    __STATE_DOWN,
    __STATE_UP,
};

class Player : public GameObject
{
    std::bitset<4> m_movementState;
    bool m_moving;

public:
    Player(const char *img_path, int xPos, int yPos);

    void Update() override;
    void HandleInput(const SDL_Event *e);

    ~Player();
};