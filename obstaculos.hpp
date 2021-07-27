#include <SDL.h>
#pragma once

#define QUANTIDADE_OBSTACULOS 4

class Obstaculos{
    SDL_Texture *obstText;
    SDL_Surface *obstImg;
    SDL_Rect vetObst[QUANTIDADE_OBSTACULOS];
public:
    void loadObstaculos(SDL_Renderer *renderer);
    void renderObstaculos(SDL_Renderer *renderer);
    SDL_Rect* getVetObst();
};
