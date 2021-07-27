#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "hashing.hpp"
#include <iostream>

void TabelaJogadores::inicializar(){
    int i = 0;
  	for (i=0; i < MAX; i++)
		jogadores[i] = NULL;
}

bool TabelaJogadores::inserir(struct jogador reg){
    struct jogador *newJogador;
    newJogador = (struct jogador*)malloc(sizeof(struct jogador));

    if(newJogador != NULL){
        newJogador->nome = reg.nome;
        newJogador->score = reg.score;
        newJogador->prox = NULL;
    }
    else return false;

    int endereco = hashing(reg.nome);
    if(jogadores[endereco] == NULL){ //posição disponivel
        jogadores[endereco] = newJogador;
    }
    else { //tratamento de colisão
        jogadores[endereco]->prox = newJogador;
        jogadores[endereco] = newJogador;
    }
    return true;

}

void TabelaJogadores::remover(std::string nome){
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

struct jogador* TabelaJogadores::buscar(std::string nome){
    int endereco = hashing(nome);
    struct jogador *aux;
    aux = jogadores[endereco];
    if(aux != NULL)
        while(aux->nome != nome || aux->prox != NULL)
            aux = aux->prox;
    else return NULL;
    if(aux->nome == nome) return aux;
    else return NULL;
}

void TabelaJogadores::atualizarScore(int score, std::string nome){
    struct jogador *aux;
    aux = buscar(nome);
    aux->score = score;
}

int TabelaJogadores::hashing(std::string chave) {
    int i, soma = 0;
    int tam = chave.length();
    for (i = 0; i < tam; i++){
        soma = soma + (i * chave[i]);
    }
    return (soma % MAX);
}

void TabelaJogadores::renderTabela(SDL_Renderer *renderer){

    Font = TTF_OpenFont("digital-7.ttf", 24);
    White = {255, 255, 255};

    messageRect.w = 300;
    messageRect.h = 50;
    messageRect.x = 50;

    int i = 0;
    struct jogador *aux;
    std::string message;
    for(aux = jogadores[i]; aux != NULL; aux = aux->prox, i++){
        messageRect.y = 50*(i+1);
        message = aux->nome;
        message += " ";
        message += std::to_string(aux->score);
        surfaceText = TTF_RenderText_Solid(Font,  message.c_str(), White);
        messageText = SDL_CreateTextureFromSurface(renderer, surfaceText);
        SDL_RenderCopy(renderer, messageText, NULL, &messageRect);
    }

    SDL_FreeSurface(surfaceText);
}


