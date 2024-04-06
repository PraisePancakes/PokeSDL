#pragma once
#include "GameObject.hpp"

class Pokemon : public GameObject
{
    std::string m_nameSerializable;
    Textbox *m_nameBox;
    void _spawn();

public:
    Pokemon(const char *name, const char *img_path, int xPos, int yPos);

    void Update() override;
    void Render() override;

    ~Pokemon();
};