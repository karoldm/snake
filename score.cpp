#include "score.hpp"
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

void Score::loadScore(SDL_Renderer *renderer){

    scoreDigits = 1;
    scoreW = 10;
    scoreH = 0;

    Font = TTF_OpenFont("digital-7.ttf", 24);
    White = {255, 255, 255};
    surfaceScore = TTF_RenderText_Solid(Font,  "Score: ", White);
    MessageTextScore = SDL_CreateTextureFromSurface(renderer, surfaceScore);
    SDL_FreeSurface(surfaceScore);

    MessageTextScore_Rect.x = 420;
    MessageTextScore_Rect.y = 450;
    MessageTextScore_Rect.w = 80;
    MessageTextScore_Rect.h = 10;

    renderScore(renderer);

}

void Score::updateScore(SDL_Renderer *renderer, int score){
    std::string scoreStr = std::to_string(score);

    if(scoreDigits < (int)scoreStr.length()){
        scoreW += 10;
        scoreH += 1;
        scoreDigits++;
    }
    surfaceScore = TTF_RenderText_Solid(Font,  scoreStr.c_str(), White);
    MessageScore = SDL_CreateTextureFromSurface(renderer, surfaceScore);
    SDL_FreeSurface(surfaceScore);

    MessageScore_Rect.x = 500;
    MessageScore_Rect.y = 450;
    MessageScore_Rect.w = 10 + scoreW;
    MessageScore_Rect.h = 10 + scoreH;

    renderScore(renderer);

}

void Score::renderScore(SDL_Renderer *renderer){
    SDL_RenderCopy(renderer, MessageTextScore, NULL, &MessageTextScore_Rect);
    SDL_RenderCopy(renderer, MessageScore, NULL, &MessageScore_Rect);
}
