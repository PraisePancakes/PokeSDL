#pragma once
#include "GameObject.hpp"

class Player : public GameObject
{
    bool m_moving;
    bool m_movingLeft;
    bool m_movingRight;
    bool m_movingUp;
    bool m_movingDown;

public:
    Player(const char *img_path, int xPos, int yPos);

    void Update();
    void HandleInput(const SDL_Event *event);

    ~Player();
};