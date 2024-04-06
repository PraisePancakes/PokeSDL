#include "../include/Game.hpp"
#include "../include/Console.hpp"
#include "../lib/SDL2TTF/include/SDL2/SDL_ttf.h"
#include "../include/Player.hpp"
#include <iostream>

Console *console = nullptr;
SDL_Renderer *Game::Renderer = nullptr;
SDL_Rect rect;
Player *player = nullptr;

Game::Game(const char *username, const char *title, int screen_xpos, int screen_ypos, int screen_width, int screen_height)
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

    console = new Console(0, m_screen_height / 2, m_screen_width, m_screen_height / 2, {95, 200, 200, 1});
    player = new Player(username, "assets/player/idle.png", m_screen_width - (m_screen_width / 2), 20);
    if (!_initMarkers())
    {
        std::cout << "[f. err] Game failed to initialize markers " << std::endl;
        exit(EXIT_FAILURE);
    };

    m_pokemonStorage = new Storage::Pokemons::PokemonStorage();

    m_current_gstate = STATE::_GSTATE_MENU;
    m_running = true;
};

bool Game::_initMarkers()
{
    const SDL_Color markerColor = {0, 0, 0, 0};
    const unsigned int MARKER_WIDHT = 150;
    const unsigned int MARKER_HEIGHT = 50;

    Textbox *m1 = new Textbox({m_screen_width / 2 - 100, 0, MARKER_WIDHT, MARKER_HEIGHT}, markerColor, "Catch", 24);
    Textbox *m2 = new Textbox({0, m_screen_height / 4, MARKER_WIDHT, MARKER_HEIGHT}, markerColor, "Pokedex", 24);
    Textbox *m3 = new Textbox({m_screen_width - 150, m_screen_height / 4, MARKER_WIDHT, MARKER_HEIGHT}, markerColor, "Achievements", 24);
    Textbox *m4 = new Textbox({m_screen_width / 2 - 100, m_screen_height / 2 - 50, MARKER_WIDHT, MARKER_HEIGHT}, markerColor, "Quit", 24);

    if (!m1 || !m2 || !m3 || !m4)
    {
        return false;
    }

    this->m_markers[0] = m1;
    this->m_markers[1] = m2;
    this->m_markers[2] = m3;
    this->m_markers[3] = m4;

    Textbox *q = new Textbox({m_screen_width / 2 - 100, 50, MARKER_WIDHT, MARKER_HEIGHT}, markerColor, "Quit?", 24);
    Textbox *q1 = new Textbox({0, m_screen_height / 4, MARKER_WIDHT, MARKER_HEIGHT}, markerColor, "Yes", 24);
    Textbox *q2 = new Textbox({m_screen_width - 150, m_screen_height / 4, MARKER_WIDHT, MARKER_HEIGHT}, markerColor, "No", 24);

    if (!q || !q1 || !q2)
    {
        return false;
    }

    this->m_backMarker = new Textbox({0, m_screen_width / 4, MARKER_WIDHT, MARKER_HEIGHT}, markerColor, "Back", 24);
    this->m_quitMarkers[0] = q;
    this->m_quitMarkers[1] = q1;
    this->m_quitMarkers[2] = q2;

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

    if (!_lockState)
    {
        if (player->m_objRect.x > m_screen_width - 150) // achievement state
        {
            m_current_gstate = STATE::_GSTATE_ACHIEVEMENTS;
            _lockState = true;
        }
        else if (player->m_objRect.x < 0 && player->m_objRect.y < m_screen_width / 4) // pokedex state
        {
            m_current_gstate = STATE::_GSTATE_POKEDEX;
            _lockState = true;
        }
        else if (player->m_objRect.y > m_screen_height / 2 - 100) // quit state
        {
            m_current_gstate = STATE::_GSTATE_QUIT;
            _lockState = true;
        }
        else if (player->m_objRect.y < 0) // catch state
        {
            m_current_gstate = STATE::_GSTATE_CATCH;
            _lockState = true;
        }
    }

    switch (m_current_gstate)
    {
    case STATE::_GSTATE_POKEDEX:
        std::cout << "POKEDEX" << std::endl;

        // display pokedex list
        if (player->m_objRect.x < 0 && player->m_objRect.y > m_screen_width / 4) // enter Pokedex state
        {
            player->CenterPos();
            if (_lockState) // back to menu
            {
                m_current_gstate = STATE::_GSTATE_MENU;
                _lockState = false; // Unlock the state when returning to menu
            }
        }
        break;
    case STATE::_GSTATE_CATCH:
        std::cout << "CATCH" << std::endl;
        if (player->m_objRect.x < 0 && _lockState)
        {
            m_current_gstate = STATE::_GSTATE_MENU;
            player->CenterPos();
            _lockState = false;
        }
        else
        {
            m_randomPokemon = m_pokemonStorage->GetRandomPokemon();
        }
        break;
    case STATE::_GSTATE_ACHIEVEMENTS:
        std::cout << "ACHIEVEMENTS" << std::endl;
        if (player->m_objRect.x < 0 && _lockState)
        {
            m_current_gstate = STATE::_GSTATE_MENU;
            player->CenterPos();
            _lockState = false;
        }
        else
        {
            // display achievements list
        }

        break;
    case STATE::_GSTATE_QUIT:
        if (player->m_objRect.x < 0 && _lockState) // quit game
        {
            m_running = false;
        }
        else if (player->m_objRect.x >= m_screen_width - 150) // dont quit game
        {
            m_current_gstate = STATE::_GSTATE_MENU;
            player->CenterPos();
            _lockState = false;
        }
        std::cout << "QUIT" << std::endl;
        break;
    case STATE::_GSTATE_MENU:

        std::cout << "MENU" << std::endl;
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
            m_markers[i]->Render();
        }
    }
    else if (m_current_gstate == STATE::_GSTATE_QUIT)
    {
        for (int i = 0; i < 3; i++)
        {
            m_quitMarkers[i]->Render();
        }
    }
    else if (m_current_gstate == STATE::_GSTATE_POKEDEX)
    {
        // handle rendering pokedex
        m_backMarker->Render();
    }
    else if (m_current_gstate == STATE::_GSTATE_CATCH)
    {
        // handle rendering catch
        m_backMarker->Render();
        m_randomPokemon->Render();
    }
    else if (m_current_gstate == STATE::_GSTATE_ACHIEVEMENTS)
    {
        m_backMarker->Render();
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
    console->~Console();
    delete console;
    _clean();
}