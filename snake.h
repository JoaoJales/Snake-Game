#ifndef SNAKE_H
#define SNAKE_H

#define LARGURA_MAX 40
#define ALTURA_MAX 20

typedef struct cobra{
    int x;
    int y;
    struct cobra *prox;
}cobra_t;

typedef struct comida{
    int x;
    int y;
}comida_t;

typedef struct estatisticas{
    int maior;
    int atual;
}estatisticas_t;


cobra_t *cobra(int x, int y);

void carregar_mapa(const char *arquivo_fase);

void gerarComida(comida_t *comida);

void Tela_Inicial();

void jogar();

void game_over();

void mostrar_estatisticas();

void como_jogar();


#endif
