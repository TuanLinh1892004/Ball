#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "ECS.h"
#include <math.h>
#include <iostream>

class Point : public Component
{
private:
    double x[14][10], y[14][10];
    SDL_Texture *texture, *type[14][10];
    SDL_Rect dst, e[14][10];
    bool draw[14][10];
    int flip[14][10];
    int o;

public:
    Point()
    {
        texture = TextureManager::LoadTexture("assets/point.png");
        dst.w = dst.h = 4;
        for (int i = 0; i < 14; i++) for (int j = 0; j < 10; j++) {
            x[i][j] = rand() % 60 + i * 70 + 5;
            y[i][j] = rand() % 60 + j * 70 + 5;
            o = rand() % 5;
            if (o == 0)      type[i][j] = TextureManager::LoadTexture("assets/type0.png");
            else if (o == 1) type[i][j] = TextureManager::LoadTexture("assets/type1.png");
            else if (o == 2) type[i][j] = TextureManager::LoadTexture("assets/type2.png");
            else if (o == 3) type[i][j] = TextureManager::LoadTexture("assets/type3.png");
            else             type[i][j] = TextureManager::LoadTexture("assets/type4.png");
        }
    }
    void update() override
    {
        for (int i = 0; i < 14; i++) for (int j = 0; j < 10; j++) {
            if ((x[i][j] - Game::ballx) * (x[i][j] - Game::ballx) + (y[i][j] - Game::bally) * (y[i][j] - Game::bally) > 200 * 200) { draw[i][j] = 0; continue; }
            draw[i][j] = 1;
            e[i][j].w = abs(x[i][j] - Game::ballx); e[i][j].h = abs(y[i][j] - Game::bally);
            e[i][j].x = std::min(x[i][j], Game::ballx); e[i][j].y = std::min(y[i][j], Game::bally);
            if (x[i][j] < Game::ballx) {
                if (y[i][j] < Game::bally) flip[i][j] = 0;
                else                       flip[i][j] = 1;
            }
            else {
                if (y[i][j] < Game::bally) flip[i][j] = 2;
                else                       flip[i][j] = 3;
            }
        }
    }
    void render() override
    {
        for (int i = 0; i < 14; i++) for (int j = 0; j < 10; j++) {
            dst.x = x[i][j]; dst.y = y[i][j];
            TextureManager::RenderCopy(texture, 0, &dst);
            if (draw[i][j]) {
                if      (flip[i][j] == 0) TextureManager::RenderCopyEx(type[i][j], 0, &e[i][j], 0, 0, SDL_FLIP_NONE);
                else if (flip[i][j] == 1) TextureManager::RenderCopyEx(type[i][j], 0, &e[i][j], 0, 0, SDL_FLIP_HORIZONTAL);
                else if (flip[i][j] == 2) TextureManager::RenderCopyEx(type[i][j], 0, &e[i][j], 0, 0, SDL_FLIP_VERTICAL);
                else                      TextureManager::RenderCopyEx(type[i][j], 0, &e[i][j], 180, 0, SDL_FLIP_NONE);
            }
        }
    }
};
