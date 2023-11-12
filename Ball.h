#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "ECS.h"

class Ball : public Component
{
private:
    SDL_Texture *texture;
    SDL_Rect dst;
    int u, v;

public:
    Ball()
    {
        texture = TextureManager::LoadTexture("assets/ball.png");
        dst.w = dst.h = 100;
    }
    void update() override
    {
        SDL_GetMouseState(&u, &v);
        Game::ballx = u;
        Game::bally = v;
    }
    void render() override
    {
        dst.x = Game::ballx - dst.w / 2;
        dst.y = Game::bally - dst.h / 2;
        TextureManager::RenderCopy(texture, 0, &dst);
    }
};
