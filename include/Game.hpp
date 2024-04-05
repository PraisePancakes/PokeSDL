#pragma once
#include "../lib/SDL2/include/SDL2/SDL.h"
#include "Textbox.hpp"
#include <vector>

enum class STATE
{
    _GSTATE_POKEDEX,
    _GSTATE_CATCH,
    _GSTATE_ACHIEVEMENTS,
    _GSTATE_QUIT,
    _GSTATE_MENU
};

class Game
{
    int m_screen_xpos;
    int m_screen_ypos;
    int m_screen_width;
    int m_screen_height;
    SDL_Window *m_window;
    STATE m_current_gstate;
    bool m_running;
    void _clean();
    Textbox *m_markers[4];
    Textbox *m_quitMarkers[3];
    Textbox *m_backMarker;
    bool _lockState;

    bool _initMarkers();

public:
    Game(const char *username, const char *title, int screen_xpos, int screen_ypos, int screen_width, int screen_height);
    static SDL_Renderer *Renderer;

    void SetGameState(STATE gs);
    int GetScreenWidth() const;
    int GetScreenHeight() const;
    int GetScreenXPos() const;
    int GetScreenYPos() const;
    bool IsRunning() const;

    void Update();
    void Render();
    void HandleEvents();

    ~Game();
};