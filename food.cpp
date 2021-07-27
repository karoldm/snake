#include <time.h>
#include "food.hpp"
#include "globalVariables.hpp"

bool Food::colisaoFoodObstaculo(int x, int y, SDL_Rect *vetObst){

    for(int i = 0; i < 4; i++)
        if(x == vetObst[i].x && y == vetObst[i].y ) return true;

    return false;
}

void Food::loadFood(SDL_Renderer *renderer, SDL_Rect *vetObst){

    int x, y;

    srand( time( NULL ) );

    foodImg = SDL_LoadBMP("food.bmp");
    foodText = SDL_CreateTextureFromSurface(renderer, foodImg);
    foodRect.w = 50;
    foodRect.h = 50;

    do {
        x = 10 + rand() % (SCREEN_WIDTH - 50);
        y = 10 + rand() % (SCREEN_HEIGHT-150);

    } while(colisaoFoodObstaculo(x, y, vetObst));

    foodRect.x = x;
    foodRect.y = y;

    renderFood(renderer);
}

void Food::renderFood(SDL_Renderer *renderer){
    SDL_RenderCopy(renderer, foodText, NULL, &foodRect);
}

SDL_Rect Food::getFoodPos(){
    return foodRect;
}

