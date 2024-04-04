#pragma once
#include "Textbox.hpp"
#include "Game.hpp"

class Button
{

    bool m_clicked;
    void _verifyClick(); // get mouse state and check if mouse is within textbox range if it is set clicked to true

public:
    Button(Textbox *textbox);
    Textbox *m_buttonTextbox;
    // void onClick(Game &gameRef, STATE gs);
    void Render();
};