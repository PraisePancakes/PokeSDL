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
    std::string m_nameSerializable;
    Textbox *m_nameBox;

public:
    Player(const char *username, const char *img_path, int xPos, int yPos);

    void Update() override;
    void Render() override;
    void HandleInput(const SDL_Event *e);
    void CenterPos();

    ~Player();
};