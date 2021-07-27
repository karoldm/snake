#include <SDL.h>
#include <string>

#define MAX 17 //preferencia por números primos

struct jogador {
    std::string nome;
    int score;
    struct jogador *prox;
};

class TabelaJogadores {
    struct jogador *jogadores[MAX];

    TTF_Font* Font;
    SDL_Color White;
    SDL_Rect messageRect;
    SDL_Surface *surfaceText;
    SDL_Texture *messageText;

    int hashing(std::string chave);

public:
    void inicializar ();
    bool inserir( struct jogador reg);
    void remover( std::string nome);
    struct jogador* buscar( std::string nome);
    void atualizarScore(int score, std::string nome);
    void renderTabela(SDL_Renderer *renderer);
};
