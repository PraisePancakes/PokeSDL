#pragma once
#include "GameObject.hpp"

class Player : public GameObject
{
    bool m_moving;

public:
    Player(const char *img_path, int xPos, int yPos);

    void Update();
    void HandleInput(const SDL_Event *event);

    ~Player();
};