#include "obstaculos.hpp"
#include "globalVariables.hpp"
#include <time.h>
#include <SDL.h>

void Obstaculos::loadObstaculos(SDL_Renderer *renderer){
    srand( time( NULL ) );

    obstImg = SDL_LoadBMP("obstaculo.bmp");
    obstText = SDL_CreateTextureFromSurface(renderer, obstImg);

    for(int i = 0; i < QUANTIDADE_OBSTACULOS; i++){

        vetObst[i].x = 10 + rand() % (SCREEN_WIDTH-50);
        vetObst[i].y = 10 + rand() % (SCREEN_HEIGHT-150);
        vetObst[i].w = 30;
        vetObst[i].h = 30;
    }
    renderObstaculos(renderer);
}

void Obstaculos::renderObstaculos(SDL_Renderer *renderer){
    for(int i = 0; i < QUANTIDADE_OBSTACULOS; i++){
        SDL_RenderCopy(renderer, obstText, NULL, &vetObst[i]);
    }
}

SDL_Rect* Obstaculos::getVetObst(){
    return vetObst;
}
