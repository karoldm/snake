#include <SDL.h>
#include <string>

#define MAX 17 //preferencia por números primos

struct jogador { //TAD para jogador
    char nome[15];
    int score;
    struct jogador *prox;
};

class TabelaJogadores {

    TTF_Font* Font;
    SDL_Color White;
    SDL_Rect messageRect;
    SDL_Surface *surfaceText;
    SDL_Texture *messageText;

    int hashing(char* chave); //função hash

public:
    struct jogador* jogadores[MAX]; //vetor de jogadores
    void inicializar (); //iniciar tabela
    bool inserir(char* nome, int score); //inserir novo jogador
    struct jogador* buscar( char* nome); //buscar jogador
    void atualizarScore(int score, char* nome); //atualizar score do jogador
    void renderTabela(SDL_Renderer *renderer); //exibir tabela
};
