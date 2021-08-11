#include <iostream>
#include <time.h>
#include <string>
#include <windows.h>

#include "snake.hpp"
#include "hashing.hpp"
#include "globalVariables.hpp"

#include <SDL.h>
#include <SDL_ttf.h>

SDL_Window *window;
SDL_Renderer *renderer;


void menu(SDL_Window *window, SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_Surface *image = SDL_LoadBMP("menu.bmp");
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect rect = {160, 100, 302, 281};
    SDL_RenderCopy(renderer, image_texture, NULL, &rect);
    SDL_RenderPresent(renderer);
}

bool init(){

    if(SDL_Init(SDL_INIT_EVERYTHING)<0){
        printf("%s", SDL_GetError());
        return false;
    }
    if(TTF_Init() < 0){
        printf("%s", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Snake 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!window){
        printf("%s", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        printf("%s", SDL_GetError());
        return false;
    }
    return true;
}


void GameOver(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_Surface *image = SDL_LoadBMP("gameOver.bmp");
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect rect = {100, 50, 400, 400};
    SDL_RenderCopy(renderer, image_texture, NULL, &rect);

    SDL_Event e;
    while(1){
        SDL_WaitEvent(&e);
        if(e.type == SDL_QUIT) break;
        SDL_RenderPresent(renderer);
    }

}

void NovoJogo(std::string nome, TabelaJogadores *tabJogadores, bool jogadorExistente){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    Snake snake;
    snake.newGame(renderer);
    snake.renderGame(renderer);
    SDL_RenderPresent(renderer);
    SDL_Event e;

    while(snake.inGame){

        snake.events(&e);

        if(e.type == SDL_QUIT) break;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        snake.renderGame(renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    GameOver(renderer);
    //std::cout << "nome " << nome << " score " << snake.getScore();

    /*if(jogadorExistente){
        tabJogadores->atualizarScore(snake.getScore(), nome);
    }
    else {
        struct jogador newJogador;
        newJogador.nome = nome;
        newJogador.score = snake.getScore();
        tabJogadores->inserir(newJogador);
    }*/

    //struct jogador *newJogador = tabJogadores->buscar(nome);
    //std::cout << "nome " << newJogador->nome << " score " << newJogador->score;
}

std::string input(){ //retorna o nome do jogador
    SDL_Event e;
    SDL_StartTextInput();
    std::string nome = "", text = "Insira seu nome e pressione enter para continuar!";

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    TTF_Font* Font = TTF_OpenFont("digital-7.ttf", 24);
    SDL_Color White = {255, 255, 255};
    SDL_Surface* surface;
    SDL_Texture* Message;
    SDL_Rect MessageRect;
    SDL_Rect TextRect;

    MessageRect.x = 250;
    MessageRect.y = 250;
    MessageRect.w = 10;
    MessageRect.h = 10;

    TextRect.x = 50;
    TextRect.y = 200;
    TextRect.w = 500;
    TextRect.h = 12;

    while(1){
        SDL_WaitEvent(&e);
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) break;
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && nome.length() > 0){
            nome = nome.substr(0, nome.length()-1);
            MessageRect.w -= 10;
        }
        if(e.type == SDL_QUIT) break;
        if(e.type == SDL_TEXTINPUT){
            nome += e.text.text;
            MessageRect.w += 10;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        surface = TTF_RenderText_Solid(Font,  nome.c_str(), White);
        Message = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, Message, NULL, &MessageRect);

        surface = TTF_RenderText_Solid(Font,  text.c_str(), White);
        Message = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, Message, NULL, &TextRect);

        SDL_RenderPresent(renderer);
    }
    SDL_StopTextInput();
    SDL_FreeSurface(surface);

    return nome;
}

int main( int argc, char * argv[] ){

    TabelaJogadores tabJogadores;
    tabJogadores.inicializar();

    std::string nome;

    if(init()){ //se tudo foi inicializado com sucesso
        SDL_Event event;
        while(1){
            menu(window, renderer);
            SDL_WaitEvent(&event);
            if(event.type == SDL_QUIT) break;
            else if(event.type == SDL_MOUSEBUTTONDOWN){
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if(mouseX > 193 && mouseX < 410 && mouseY > 185 && mouseY < 216){
                    nome = input();
                    if(tabJogadores.buscar(nome) != NULL)
                        NovoJogo(nome, &tabJogadores, true);
                    else
                        NovoJogo(nome, &tabJogadores, false);
                }
                else if(mouseX > 193 && mouseX < 410 && mouseY > 235 && mouseY < 268){
                    tabJogadores.renderTabela(renderer);
                    SDL_RenderPresent(renderer);
                }
            }//evento click do mouse
        }//while
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }//init

    TTF_Quit();
    SDL_Quit();
    return 1;
}
