#include "../include/Textbox.hpp"
#include "../include/TextureManager.hpp"

Textbox::Textbox(SDL_Rect rect, SDL_Color color, const char *text, int font_size)
{
    this->m_boxRect = rect;
    this->m_textColor = color;
    this->m_boxTexture = Texture::TextureManager::LoadTTF(text, "assets/font/8bit.ttf", color, font_size);
};

void Textbox::Render()
{
    SDL_RenderCopy(Game::Renderer, this->m_boxTexture, NULL, &this->m_boxRect);
};

void Textbox::SetPos(int x, int y)
{
    this->m_boxRect.x = x;
    this->m_boxRect.y = y;
}

void Textbox::SetText(const char *text)
{
    SDL_DestroyTexture(this->m_boxTexture);
    this->m_boxTexture = Texture::TextureManager::LoadTTF(text, "assets/font/8bit.ttf", this->m_textColor, 12);
}

void Textbox::Print()
{

    std::cout << "TEXTBOX" << std::endl;
    std::cout << "xpos : " << this->m_boxRect.x << std::endl;
    std::cout << "ypos : " << this->m_boxRect.y << std::endl;
    std::cout << "w : " << this->m_boxRect.w << std::endl;
    std::cout << "h : " << this->m_boxRect.h << std::endl;
}

Textbox::~Textbox()
{
    if (this->m_boxTexture)
    {
        SDL_DestroyTexture(this->m_boxTexture);
    }
}