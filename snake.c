#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "snake.h"


cobra_t *cobra(int x, int y){

    cobra_t *novaParte = (cobra_t *) malloc(sizeof(cobra_t));
    novaParte->x = x;
    novaParte->y = y;
    novaParte->prox = NULL;
    return novaParte;
}

estatisticas_t pontuacao = {0, 0};
int mapa[ALTURA_MAX][LARGURA_MAX]; 
int NUM_COMIDAS, FASE_ATUAL, VELOCIDADE;
int ALTURA = 0, LARGURA = 0;

void carregar_mapa(const char *arquivo_fase) {
    FILE *arquivo = fopen(arquivo_fase, "r");
    int i;
    char linha[LARGURA_MAX + 2];
    int comprimento;
    
    ALTURA = 0;
    
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de mapa!\n");
        exit(EXIT_FAILURE);
    }
    // Ler a fase atual (metadado)
    if (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d", &FASE_ATUAL);
    }
    
    // Ler o número de comidas (metadado)
    if (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d", &NUM_COMIDAS);
    }

    if (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d", &VELOCIDADE);
    }
    
    
    while (fgets(linha, sizeof(linha), arquivo)) {

        // Remover o '\n' se existir
        comprimento = strlen(linha);
        
        if (linha[comprimento - 1] == '\n') {
            linha[comprimento - 1] = '\0';
            comprimento--; // 39
        }
        
    

        // Preencher o mapa com os valores lidos
        for (i = 0; i < comprimento; i++) {
            if (linha[i] == '1'){

                mapa[ALTURA][i] = 1;

            }else if (linha[i] == '0'){

                mapa[ALTURA][i] = 0;

            }else{
                break;
            }
        }
        ALTURA++;
    }
    LARGURA = comprimento;
    ALTURA = 20;
    fclose(arquivo);
}

void gerarComida(comida_t *comida) {
    do {
        comida->x = rand() % LARGURA;
        comida->y = rand() % ALTURA;
    } while (mapa[comida->y][comida->x] == 1);
}

int jogo(estatisticas_t *pontuacao){
    cobra_t *cabeca = cobra(LARGURA / 2, ALTURA / 2), *aux;
    cobra_t *novaCabeca;
    comida_t comida;
    int pontos = 0, verificador_corpo = 0, bateu = 0;

    char direcao_cobra = '\0';

    
    

    srand(time(0));
    gerarComida(&comida);

    while (pontos != NUM_COMIDAS && !bateu) {
        Sleep(150);
        system("cls");

        printf("\nCOMA %d FRUTAS (*)\n", NUM_COMIDAS);
        printf("Frutas: %d | FASE: %d\n", pontos, FASE_ATUAL);
        printf("Velociade: %d\n", VELOCIDADE);

        for (int i = 0; i < ALTURA; i++) {
            for (int j = 0; j < LARGURA; j++) {
                if (mapa[i][j] == 1) {
                    printf("%c", 219);
                } else if (i == cabeca->y && j == cabeca->x) {
                    printf("O");
                } else if (i == comida.y && j == comida.x) {
                    printf("*");
                } else {
                    verificador_corpo = 0;
                    aux = cabeca->prox;
                    while (aux != NULL) {
                        if (i == aux->y && j == aux->x) {
                            printf("o");
                            verificador_corpo = 1;
                            break;
                        }
                        aux = aux->prox;
                    }
                    if (!verificador_corpo) printf(" ");
                }
            }
            printf("\n");
        }

        if (_kbhit()) {
            char novaDirecao = _getch();
            if (novaDirecao == -32)
            {
                novaDirecao = _getch();
                if (novaDirecao == 72 && direcao_cobra != 's') direcao_cobra = 'w';
                if (novaDirecao == 80 && direcao_cobra != 'w') direcao_cobra = 's';
                if (novaDirecao == 75 && direcao_cobra != 'd') direcao_cobra = 'a';
                if (novaDirecao == 77 && direcao_cobra != 'a') direcao_cobra = 'd';

            }else if (novaDirecao == 27){
                break;

            }else{
                if (novaDirecao == 'w' && direcao_cobra != 's') direcao_cobra = 'w';
                if (novaDirecao == 's' && direcao_cobra != 'w') direcao_cobra = 's';
                if (novaDirecao == 'a' && direcao_cobra != 'd') direcao_cobra = 'a';
                if (novaDirecao == 'd' && direcao_cobra != 'a') direcao_cobra = 'd';
            }
        }

        int proximoX = cabeca->x;
        int proximoY = cabeca->y;

        if (direcao_cobra == 'w') proximoY--;
        if (direcao_cobra == 's') proximoY++;
        if (direcao_cobra == 'a') proximoX--;
        if (direcao_cobra == 'd') proximoX++;

        
        if (FASE_ATUAL == 1)
        {
            if (proximoX < 0) proximoX = LARGURA - 1;
            else if (proximoX >= LARGURA) proximoX = 0;
            if (proximoY < 0) proximoY = ALTURA - 1;
            else if (proximoY >= ALTURA) proximoY = 0;
        }else if (FASE_ATUAL > 1)
        {
            if (mapa[proximoY][proximoX] == 1)
            {
                bateu = 1;
                break;
            }
        
            if (FASE_ATUAL > 2)
            {
                aux = cabeca->prox;
                while (aux != NULL)
                {
                    if (aux->x == proximoX && aux->y == proximoY)
                    {
                        bateu = 1;
                        break;
                    }
                    aux = aux->prox;
                }
            }
            
        }
        
    
        
        novaCabeca = cobra(proximoX, proximoY);
        novaCabeca->prox = cabeca;
        cabeca = novaCabeca;

        if (cabeca->x == comida.x && cabeca->y == comida.y) {
            pontos++;
            gerarComida(&comida);
        } else {
            aux = cabeca;
            while (aux->prox->prox != NULL) {
                aux = aux->prox;
            }
            free(aux->prox);
            aux->prox = NULL;
        }

        printf("\nAperte ESC para sair!");
        printf("\nPontuacao: %d\n", pontuacao->atual + pontos);
    }

    pontuacao->atual += pontos;
    if (pontuacao->atual > pontuacao->maior) pontuacao->maior = pontuacao->atual;

    if (pontos == NUM_COMIDAS && FASE_ATUAL == 5){
        system("cls");
        printf("\n\n");
        printf("\t---------------------------------\n");
        printf("\t| PARABENS! VOCE CHEGOU AO FIM! |\n");
        printf("\t---------------------------------\n");
        Sleep(5000);
        return 1;
    }else if (pontos == NUM_COMIDAS)
    {
        system("cls");
        printf("\n\n\tFASE COMPLETA!\n");
        printf("\tCARREGANDO... ");
        Sleep(5000);
        return 1;
    }
    
    return 0;
}

void iniciar_jogo(){
    int situacao;
    pontuacao.atual = 0;

    carregar_mapa("../fase1.txt");
    situacao = jogo(&pontuacao);
    if (situacao == 0){
        game_over();
        return;
    }

    carregar_mapa("../fase2.txt");
    situacao = jogo(&pontuacao);
    if (situacao == 0){
        game_over();
        return;
    }

    carregar_mapa("../fase3.txt");
    situacao = jogo(&pontuacao);
    if (situacao == 0){
        game_over();
        return;
    }

    carregar_mapa("../fase4.txt");
    situacao = jogo(&pontuacao);
    if (situacao == 0){
        game_over();
        return;
    }

    carregar_mapa("../fase5.txt");
    situacao = jogo(&pontuacao);
    if (situacao == 0){
        game_over();
        return;
    }

}

void mostrar_estatisticas(){
    system("cls");
    printf("\t-------------------------------------\n");
    printf("\t|          ESTATISTICAS             |\n");
    printf("\t-------------------------------------\n");
    printf("\tMaior pontuacao: %d\n", pontuacao.maior);
    printf("\tUltima pontuacao: %d\n", pontuacao.atual);
    printf("\tPressione qualquer tecla para voltar ao menu...");
    getch();
}

void como_jogar(){
    system("cls");
    printf("\t-------------------------------------\n");
    printf("\t|           COMO JOGAR              |\n");
    printf("\t-------------------------------------\n\n");
    printf("\t1- Controle a cobra com as teclas:\n");
    printf("\t  W ou SETA PARA CIMA -> Move para cima\n");
    printf("\t  A ou SETA PARA ESQUERDA -> Move para a esquerda\n");
    printf("\t  S ou SETA PARA BAIXO -> Move para baixo\n");
    printf("\t  D ou SETA PARA DIREITA -> Move para a direita\n\n");
    printf("\t2- Colete '*' para crescer\n\n");
    printf("\t3- Ao passar de cada fase a dificuldade eh aumentada!\n");
    printf("\tFASE 1: Eh posssivel atravessar as paredes e bater em si mesmo.\n");
    printf("\tFASE 2: Eh possivel bater em si mesmo.\n");
    printf("\tFASE 3, 4 e 5: Nao eh possivel bater em nenhum local!\n\n");
    printf("\tPressione qualquer tecla para voltar ao menu...");
    getch();
}

void Tela_Inicial(){
    system("cls");
    printf("\t-------------------------------------\n");
    printf("\t|            SNAKE GAME             |\n");
    printf("\t-------------------------------------\n\n");
    printf("\t           MENU:               \n");
    printf("\t           Inicia Jogo:  (1)               \n");
    printf("\t           Estatisticas: (2)              \n");
    printf("\t           Como Jogar?   (3)                \n");
    printf("\t           Sair do Jogo: (4)              \n\n");
    printf("\t           Escolha uma opcao: ");
}

void game_over(){
    system("cls");
    printf("\t-------------------------------------\n");
    printf("\t|            GAME OVER!             |\n");
    printf("\t-------------------------------------\n");
    printf("\n");
    printf("\tPressione qualquer tecla para voltar ao menu...");
    getch();
}

int main(){
    int opcao;

    do{
        Tela_Inicial();
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao){
        case 1:
            iniciar_jogo();
            break;
        case 2:
            mostrar_estatisticas();
            break;
        case 3:
            como_jogar();
            break;
        case 4:
            opcao = 0;
            break;
        default:
            printf("Escolha invalida!");
            break;
        }
        
    } while (opcao);
    
    return 0;
}