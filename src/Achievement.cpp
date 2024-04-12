#include "../include/Achievement.hpp"

Achievement::Achievement(const std::string &achievementName, const std::string &desc, ACHIEVEMENT_ID id)
{
    this->m_completed = false;
    this->m_nameSerializable = achievementName;
    this->m_descSerializable = desc;
    this->m_id = id;

    m_nameBox = new Textbox({0, 0, 150, 20}, {255, 255, 255, 255}, m_incompleteSerializable.c_str(), 24);
}

void Achievement::Render()
{
    this->m_nameBox->Render();
};

void Achievement::Update()
{
    if (m_completed)
    {
        m_nameBox->SetText(m_nameSerializable.c_str());
    }
};

void Achievement::SetPos(int x, int y)
{
    this->m_nameBox->SetPos(x, y);
};

bool Achievement::IsCompleted() const
{
    return this->m_completed;
}

void Achievement::SetCompleted()
{
    this->m_completed = true;
}

Achievement::~Achievement(){
    // delete m_nameBox
};