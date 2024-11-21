#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "snake.h"

estatisticas_t pontuacao = {0, 0};

void jogar(){
    int situacao;

    situacao = fase1(&pontuacao);
    if (!situacao) game_over();

    
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
    printf("\tFASE 3, 4 e 5: Nao pode bater em nenhum local!\n\n");
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
            jogar();
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