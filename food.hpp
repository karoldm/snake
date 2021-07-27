#include <SDL.h>
#pragma once

class Food{
    SDL_Rect foodRect;
    SDL_Surface *foodImg;
    SDL_Texture *foodText;
public:
    void loadFood(SDL_Renderer *renderer, SDL_Rect *vetObst);
    bool colisaoFoodObstaculo(int x, int y, SDL_Rect *vetObst);
    void renderFood(SDL_Renderer *renderer);
    SDL_Rect getFoodPos();
};

