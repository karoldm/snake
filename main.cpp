#include <iostream>
#include <time.h>
#include <string>
#include <windows.h>

//classes
#include "snake.hpp"
#include "hashing.hpp"
#include "globalVariables.hpp"

//biblioteca SDL
#include <SDL.h>
#include <SDL_ttf.h>

//janela principal
SDL_Window *window;
SDL_Renderer *renderer;


void menu(SDL_Window *window, SDL_Renderer *renderer);
bool init();
void GameOver(SDL_Renderer *renderer);
int NovoJogo();
std::string input();


void menu(SDL_Window *window, SDL_Renderer *renderer){ //função para exibir o menu
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer); //limpando a tela

    SDL_Surface *image = SDL_LoadBMP("menu.bmp"); //carregando imagem do menu
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect rect = {160, 100, 302, 281};
    SDL_RenderCopy(renderer, image_texture, NULL, &rect);
    SDL_RenderPresent(renderer); //renderizando menu
}

bool init(){ //função para inicializar funções necessárias

    if(SDL_Init(SDL_INIT_EVERYTHING)<0){ //iniciando SDL
        printf("%s", SDL_GetError());
        return false;
    }
    if(TTF_Init() < 0){ //iniciando TTF para input e output
        printf("%s", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Snake 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0); //criação da janela
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


void GameOver(SDL_Renderer *renderer){ //função para exibir tela de game over
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer); //limpando a tela

    SDL_Surface *image = SDL_LoadBMP("gameOver.bmp"); //carregando imagem de game over
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect rect = {100, 50, 400, 400};
    SDL_RenderCopy(renderer, image_texture, NULL, &rect);

    SDL_Event e;
    while(1){ //a imagem fica na tela até o usuário fechar a janela
        SDL_WaitEvent(&e);
        if(e.type == SDL_QUIT) break;
        SDL_RenderPresent(renderer); //renderizando imagem
    }
}

int NovoJogo(){ //função para iniciar o jogo

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer); //limpando a tela

    Snake snake; //classe principal do jogo
    snake.newGame(renderer); //iniciando jogo
    snake.renderGame(renderer); //renderizando jogo
    SDL_RenderPresent(renderer); //rederizando o jogo na tela
    SDL_Event e;

    while(snake.inGame){

        snake.events(&e); //verificando eventos

        if(e.type == SDL_QUIT) break;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer); //limpando a tela

        snake.renderGame(renderer); //renderizando jogo após atualizações

        SDL_RenderPresent(renderer);

        SDL_Delay(100); //velocidade do jogo
    }

    GameOver(renderer);
    return snake.getScore(); //retornando score
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
            MessageRect.w -= 15;
        }
        if(e.type == SDL_QUIT) break;
        if(e.type == SDL_TEXTINPUT){
            nome += e.text.text;
            MessageRect.w += 15;
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

    TabelaJogadores tabJogadores; //tabela hash para armazenar os jogadores
    tabJogadores.inicializar(); //iniciando tabela

    std::string nome;

    if(init()){ //se tudo foi inicializado com sucesso
        SDL_Event event;

        while(1){ //loop do jogo

            menu(window, renderer); //exibir menu
            SDL_WaitEvent(&event);

            if(event.type == SDL_QUIT) break; //usuario fechou a janela

            else if(event.type == SDL_MOUSEBUTTONDOWN){ //evento de click do mouse

                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if(mouseX > 193 && mouseX < 410 && mouseY > 185 && mouseY < 216){ //primeiro "botão" de novo jogo
                    nome = input(); //solicitando nome do jogador
                    char nomeChar[15];
                    for(int i=0; i<nome.length(); i++) nomeChar[i] = nome[i];

                    if(tabJogadores.buscar(nomeChar) == NULL) tabJogadores.inserir(nomeChar, 0); //verificar se o jogador existe
                    int score = NovoJogo(); //iniciando jogo
                    tabJogadores.atualizarScore(score, nomeChar); //atualizando score do jogador
                }
                else if(mouseX > 193 && mouseX < 410 && mouseY > 235 && mouseY < 268){ //segundo "botão" de recordes
                    tabJogadores.renderTabela(renderer); //exibindo tabela
                    while(event.type != SDL_QUIT)
                        SDL_RenderPresent(renderer); //renderizando tabela
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
