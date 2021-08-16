#include <string.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "hashing.hpp"

#include <iostream>
#include <typeinfo>

void TabelaJogadores::inicializar(){
    int i = 0;
  	for (i=0; i < MAX; i++)
		jogadores[i] = NULL;
}

bool TabelaJogadores::inserir(char* nome, int score){
    struct jogador *newJogador;
    newJogador = (struct jogador*)malloc(sizeof(struct jogador));

    if(newJogador != NULL){
        strcpy(newJogador->nome, nome);
        newJogador->score = score;
        newJogador->prox = NULL;
    }
    else return false;

    int endereco = hashing(nome);
    if(jogadores[endereco] == NULL){ //posição disponivel
        jogadores[endereco] = newJogador;
    }
    else { //tratamento de colisão
        jogadores[endereco]->prox = newJogador;
        jogadores[endereco] = newJogador;
    }
    free(newJogador);
    return true;
}

void TabelaJogadores::remover(char* nome){
    int endereco = hashing(nome);
    struct jogador *aux, *anterior;
    aux = jogadores[endereco];

    if(aux->nome == nome) {
        free(aux);
        jogadores[endereco] = NULL;
    }
    else {
        while(aux->nome != nome && aux != NULL){
            anterior = aux;
            aux = aux->prox;
        }
        anterior->prox = aux->prox;
        free(aux);
    }
}

struct jogador* TabelaJogadores::buscar(char* nome){
    int endereco = hashing(nome);

    struct jogador *aux;
    aux = jogadores[endereco];
    if(aux != NULL)
        while(!(strcmp(aux->nome, nome) == 0) || aux->prox != NULL)
            aux = aux->prox;
    else {
     free(aux);
     return NULL;
    }

    if(strcmp(aux->nome, nome) == 0) return aux;
    else {
     free(aux);
     return NULL;
    }
}

void TabelaJogadores::atualizarScore(int score, char* nome){
    int endereco = hashing(nome);
    jogadores[endereco]->score = score;
}

int TabelaJogadores::hashing(char* chave) {
    int i, soma = 0;
    int tam = strlen(chave);
    for (i = 0; i < tam; i++){
        soma = soma + (i * chave[i]);
    }
    return (soma % MAX);
}

void TabelaJogadores::renderTabela(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    Font = TTF_OpenFont("digital-7.ttf", 24);
    White = {255, 255, 255};

    messageRect.w = 100;
    messageRect.h = 8;
    messageRect.x = 200;

    int i = 0;
    std::string message;
    struct jogador* aux;
    aux = jogadores[i];
    while(i < MAX){
        if(aux != NULL){
            do{
                messageRect.y += 50;
                message = aux->nome;
                message += ": ";
                message += std::to_string(aux->score);
                surfaceText = TTF_RenderText_Solid(Font,  message.c_str(), White);
                messageText = SDL_CreateTextureFromSurface(renderer, surfaceText);
                SDL_RenderCopy(renderer, messageText, NULL, &messageRect);
                aux = aux->prox;
            }while(aux != NULL);
        }
        i++;
        aux = jogadores[i];
    }

    SDL_FreeSurface(surfaceText);
}


