
#include <SDL.h>
#include <SDL_ttf.h>
#pragma once

class Score {
    int scoreW;
    int scoreH;
    int scoreDigits;

    TTF_Font* Font;
    SDL_Color White;

    SDL_Surface* surfaceScore;
    SDL_Texture* MessageTextScore;
    SDL_Texture* MessageScore;
    SDL_Rect MessageTextScore_Rect;
    SDL_Rect MessageScore_Rect;

public :
    void renderScore(SDL_Renderer *renderer);
    void loadScore(SDL_Renderer *renderer);
    void updateScore(SDL_Renderer *renderer, int score);

};
