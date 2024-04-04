#include "../include/Game.hpp"
#include "../include/Console.hpp"
#include "../lib/SDL2TTF/include/SDL2/SDL_ttf.h"
#include "../include/Player.hpp"
#include <iostream>

Console *console = nullptr;
SDL_Renderer *Game::Renderer = nullptr;
SDL_Rect rect;
Player *player = nullptr;

Game::Game(const char *title, int screen_xpos, int screen_ypos, int screen_width, int screen_height)
    : m_screen_xpos(screen_xpos), m_screen_ypos(screen_ypos), m_screen_width(screen_width), m_screen_height(screen_height)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "[f. err] SDL failed to initialize sub-systems " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() < 0)
    {
        std::cout << "[f. err] TTF failed to initialize " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    };

    this->m_window = SDL_CreateWindow(title, m_screen_xpos, m_screen_ypos, m_screen_width, m_screen_height, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_ALWAYS_ON_TOP);
    if (this->m_window == NULL)
    {
        std::cout << "[f. err] SDL failed to initialize window " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    this->Renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (this->Renderer == NULL)
    {
        std::cout << "[f. err] SDL failed to initialize renderer " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    if (!_initializeButtons())
    {
        std::cout << "[f. err] Buttons failed to initialize " << std::endl;
    };

    console = new Console(0, m_screen_height / 2, m_screen_width, m_screen_height / 2, {95, 200, 200, 1});
    player = new Player("assets/player/idle.png", m_screen_width - (m_screen_width / 2), 20);
    m_current_gstate = STATE::_GSTATE_MENU;
    m_running = true;
};

bool Game::_initializeButtons()
{
    SDL_Color white = {255, 255, 255, 255};

    Button *b1 = new Button(new Textbox({20, 25, 150, 50}, white, "Catch", 12));
    Button *b2 = new Button(new Textbox({20, 50 + 25, 150, 50}, white, "Pokedex", 12));
    Button *b3 = new Button(new Textbox({20, 75 + 50, 150, 50}, white, "Achievements", 12));
    Button *b4 = new Button(new Textbox({20, 100 + 75, 150, 50}, white, "Quit", 12));

    if (!b1 || !b2 || !b3 || !b4)
    {
        return false;
    }

    m_buttons.push_back(b1);
    m_buttons.push_back(b2);
    m_buttons.push_back(b3);
    m_buttons.push_back(b4);

    return true;
};

void Game::SetGameState(STATE gs)
{
    m_current_gstate = gs;
}
bool Game::IsRunning() const
{
    return m_running;
}

int Game::GetScreenWidth() const
{
    return this->m_screen_width;
};
int Game::GetScreenHeight() const
{
    return this->m_screen_height;
};
int Game::GetScreenXPos() const
{
    return this->m_screen_xpos;
};
int Game::GetScreenYPos() const
{
    return this->m_screen_ypos;
};

void Game::Update()
{
    // console->Update()
    player->Update();
    switch (m_current_gstate)
    {
    case STATE::_GSTATE_POKEDEX:
        break;
    case STATE::_GSTATE_CATCH:
        break;
    case STATE::_GSTATE_MENU:
        break;
    }
};

void Game::Render()
{

    SDL_SetRenderDrawColor(Renderer, 40, 60, 175, 1);
    SDL_RenderClear(Renderer);
    console->Render();
    player->Render();
    if (m_current_gstate == STATE::_GSTATE_MENU)
    {
        for (int i = 0; i < 4; i++)
        {
            m_buttons[i]->Render();
        }
    }

    SDL_RenderPresent(Renderer);
};

void Game::HandleEvents()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        player->HandleInput(&e);
        switch (e.type)
        {
        case SDL_QUIT:
            m_running = false;
            _clean();
        default:
            break;
        }
    }
};
void Game::_clean()
{
    if (Renderer)
    {
        SDL_DestroyRenderer(this->Renderer);
    }

    if (m_window)
    {
        SDL_DestroyWindow(this->m_window);
    }

    m_running = false;
};
Game::~Game()
{
    for (Button *button : m_buttons)
    {
        delete button;
    }

    console->~Console();
    delete console;
    _clean();
}