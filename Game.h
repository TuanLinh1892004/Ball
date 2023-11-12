#ifndef Game_h
#define Game_h
#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

class Text;

class Game
{
private:
    SDL_Window *window;

public:
    Game();
    ~Game();

    void init(const char *title, int x, int y, int w, int h, int flag);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running;

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static Text *printText;
    static double ballx, bally;
};

#endif // Game_h
