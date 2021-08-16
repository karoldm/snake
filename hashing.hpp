#include <SDL.h>
#include <string>

#define MAX 17 //preferencia por números primos

struct jogador {
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

    int hashing(char* chave);

public:
    struct jogador* jogadores[MAX];
    void inicializar ();
    bool inserir(char* nome, int score);
    void remover( char* nome);
    struct jogador* buscar( char* nome);
    void atualizarScore(int score, char* nome);
    void renderTabela(SDL_Renderer *renderer);
};
