#include "Game.h"
#include "TextureManager.h"
#include "ECS.h"
#include "Text.h"
#include "Point.h"
#include "Ball.h"

Manager manager;
auto &myPoints(manager.addEntity());
auto &myBall(manager.addEntity());

SDL_Renderer *Game::renderer;
SDL_Event Game::event;
Text *Game::printText;
double Game::ballx, Game::bally;

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int x, int y, int w, int h, int flag)
{
    window = SDL_CreateWindow(title, x, y, w, h, flag);
    Game::renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    running = 1;
    Game::printText = new Text();

    myPoints.addComponent <Point> ();

    myBall.addComponent <Ball>();
}

void Game::handleEvents()
{
    SDL_PollEvent(&Game::event);
    if (Game::event.type == SDL_QUIT) running = 0;
}

void Game::update()
{
    manager.refresh();
    manager.update();
}

void Game::render()
{
    SDL_RenderClear(Game::renderer);
    manager.render();
    SDL_RenderPresent(Game::renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
}
