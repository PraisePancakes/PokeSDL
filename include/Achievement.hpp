#pragma once
#include <iostream>
#include "Textbox.hpp"

enum class ACHIEVEMENT_ID
{
    POKEDEX_1_POKEMON,
    POKEDEX_5_POKEMON,
    POKEDEX_10_POKEMON,
    POKEDEX_50_POKEMON,
    POKEDEX_100_POKEMON,
};

class Achievement
{
    bool m_completed;
    std::string m_nameSerializable;
    const std::string m_incompleteSerializable = "???";
    std::string m_descSerializable;
    Textbox *m_nameBox;
    ACHIEVEMENT_ID m_id;

public:
    Achievement(const std::string &achievemntName, const std::string &desc, ACHIEVEMENT_ID id);
    void SetPos(int x, int y);
    void Render();
    void Update();
    bool IsCompleted() const;
    void SetCompleted();
    ~Achievement();
};