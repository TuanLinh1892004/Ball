#include "Game.h"

int main(int argc, char* argv[])
{
    Game *game;
    game = new Game();
    game->init("Ball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 700, SDL_WINDOW_SHOWN);
    while (game->running)
    {
        game->handleEvents();
        game->update();
        game->render();
    }
    game->clean();
}
