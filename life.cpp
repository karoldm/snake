#include <SDL.h>
#include "life.hpp"

void Life::loadLife(SDL_Renderer *renderer){

    countLife = INITIAL_LIFE;
    heartImg = SDL_LoadBMP("heart.bmp");
    heartText = SDL_CreateTextureFromSurface(renderer, heartImg);

    for(int i = 0; i < countLife; i++){

        vetLife[i].x = i*20;
        vetLife[i].y = 450;
        vetLife[i].w = 50;
        vetLife[i].h = 60;

    }

    renderLife(renderer);
}

void Life::renderLife(SDL_Renderer *renderer){

    for(int i = 0; i < countLife; i++)
        SDL_RenderCopy(renderer, heartText, NULL, &vetLife[i]);
}

void Life::popLife(){
    countLife--;
    if(countLife < 1) isAlive = false;
}

void Life::pushLife(){
    if(countLife < INITIAL_LIFE){
        countLife++;
    }
}

bool Life::getAlive(){
    return isAlive;
}

