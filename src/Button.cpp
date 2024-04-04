#include "../include/Button.hpp"

Button::Button(Textbox *textbox)
{
    this->m_buttonTextbox = textbox;
    m_clicked = false;
}

/*
void Button::onClick(Game &gameRef, STATE gs)
{
    _verifyClick();
    if (m_clicked)
    {
        gameRef.SetGameState(gs);
    }
};
*/

void Button::_verifyClick(){

};

void Button::Render()
{
    this->m_buttonTextbox->Render();
}