#include <SDL.h>
#pragma once

class Life{
    static const int INITIAL_LIFE = 5;
    SDL_Rect vetLife[INITIAL_LIFE];
    int countLife;
    bool isAlive = true;
    SDL_Surface *heartImg;
    SDL_Texture *heartText;
public:
    void renderLife(SDL_Renderer *renderer);
    void loadLife(SDL_Renderer *renderer);
    void popLife();
    void pushLife();
    void updateLife(SDL_Renderer *renderer);
    bool getAlive();
};

