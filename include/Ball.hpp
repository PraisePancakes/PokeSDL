#pragma once
#include "GameObject.hpp"
#include "Textbox.hpp"

enum class BALLTYPE
{
    __TYPE_POKEBALL,
    __TYPE_GREATBALL,
    __TYPE_ULTRABALL,
    __TYPE_MASTERBALL
};

class Ball : public GameObject
{
    int m_amount;

    Textbox *m_nameBox;

public:
    Ball(const std::string &ball_name, const char *img_path, int xPos, int yPos, BALLTYPE type);
    std::string m_nameSerializable;
    BALLTYPE BallType;
    void Update() override;
    void Render() override;
    void DecrementAmount();
    int GetAmount() const;

    ~Ball();
};