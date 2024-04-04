#include "../include/TextureManager.hpp"

SDL_Texture *Texture::TextureManager::LoadTexture(const char *img_path)
{
    SDL_Texture *texture = nullptr;

    SDL_Surface *tempSurface = IMG_Load(img_path);
    if (tempSurface == NULL)
    {
        std::cout << "[f. err] SDL IMG failed to load image to temporary surface " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    texture = SDL_CreateTextureFromSurface(Game::Renderer, tempSurface);
    if (texture == NULL)
    {
        std::cout << "[f. err] Texture failed to load from temporary surface " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(tempSurface);

    return texture;
}

SDL_Texture *Texture::TextureManager::LoadTTF(const char *text, const char *ttf_path, SDL_Color font_color, int font_size)
{
    SDL_Texture *texture = nullptr;
    TTF_Font *font = TTF_OpenFont(ttf_path, font_size);
    if (font == NULL)
    {
        std::cout << "[f. err] TTF font unable to load " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_Surface *tempSurface = TTF_RenderText_Solid(font, text, font_color);
    if (tempSurface == NULL)
    {
        std::cout << "[f. err] TTF failed to render text to temporary surface " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    texture = SDL_CreateTextureFromSurface(Game::Renderer, tempSurface);
    if (texture == NULL)
    {
        std::cout << "[f. err] Texture failed to load from temporary surface " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(tempSurface);

    return texture;
};