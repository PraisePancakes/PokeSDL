#pragma once
#include "GameObject.hpp"

class Pokemon : public GameObject
{

    Textbox *m_nameBox;
    void _spawn();
    std::string m_nameSerializable;

public:
    Pokemon(const char *name, const char *img_path, int xPos, int yPos);
    const std::string BuildSpawnString() const;
    void Update() override;
    void Render() override;

    ~Pokemon();
};