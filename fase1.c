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

int fase1(estatisticas_t *pontuacao){
    cobra_t *cabeca = cobra(LARGURA/2, ALTURA/2), *aux;
    cobra_t *novaCabeca;
    comida_t comida; 
    int pontos = 0,  verificador_corpo = 0;
    char direcao_cobra;
    int i, j;

    srand(time(0));
    comida.x = rand() % (LARGURA -2) + 1;
    comida.y = rand() % (ALTURA -2) + 1;
    
    
    while (pontos != 5)
    {   
        Sleep(150);
        system("cls");
        
        printf("\nPontuacao: %d | FASE: 1\n", pontos);

        for (i = 0; i < ALTURA; i++){
            for (j = 0; j < LARGURA; j++){

                if (i == 0 || i == ALTURA - 1 || j == 0 || j == LARGURA - 1)     
                {
                    printf("#");
                }else if (i == cabeca->y && j == cabeca->x){
                    printf("O");
                }else if (i == comida.y && j == comida.x){
                    printf("*");
                }else{
                    verificador_corpo = 0;
                    aux = cabeca->prox;
                    while (aux != NULL)
                    {
                        if (i == aux->y && j == aux->x)
                        {
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

        // Logica de movimentação
        if (_kbhit()) {
            char novaDirecao = _getch();
            if ((novaDirecao == 72 || novaDirecao == 'w') && direcao_cobra != 's') direcao_cobra = 'w';
            if ((novaDirecao == 80 || novaDirecao == 's') && direcao_cobra != 'w') direcao_cobra = 's';
            if ((novaDirecao == 75 || novaDirecao == 'a') && direcao_cobra != 'd') direcao_cobra = 'a';
            if ((novaDirecao == 77 || novaDirecao == 'd') && direcao_cobra != 'a') direcao_cobra = 'd';


            if (novaDirecao == 27) return 0; // Verificar se apertou ESQ para sair do jogo
        }

        
        int proximoX = cabeca->x;
        int proximoY = cabeca->y;
        // proximoX e proximoY recebem as coordenadas da cabeca;

        // ao clicar em alguma tecla essas coordenadas sao alteradas: ;
        if (direcao_cobra == 'w') proximoY--;
        if (direcao_cobra == 's') proximoY++;
        if (direcao_cobra == 'a') proximoX --;
        if (direcao_cobra == 'd') proximoX++;
        
        
        // Verifica se a cobra atravessou as bordas e reaparece do outro lado
        if (proximoX <= 0) proximoX = LARGURA - 2;           
        else if (proximoX >= LARGURA - 1) proximoX = 1;      
        if (proximoY <= 0) proximoY = ALTURA - 2;            
        else if (proximoY >= ALTURA - 1) proximoY = 1;

    
        // Movimentacao da cobra
        novaCabeca = cobra(proximoX, proximoY);
        novaCabeca->prox = cabeca;     // a nova cabeca passa apontar para a "antiga cabeca";
        cabeca = novaCabeca;           // A cabeca definitiva passa a ser essa nova cabeca que contem essa nova coordenada;

        // verificar se ela comeu ou nao;
        if (cabeca->x == comida.x && cabeca->y == comida.y)
        {
            pontos++;
            comida.x = rand() % (LARGURA -2) + 1;
            comida.y = rand() % (ALTURA -2) + 1;
        }else{
            // remover a parte adicional // Como a cobra nao comeu, eh preciso remover a ultima parte dela
            aux = cabeca;
            while (aux->prox->prox != NULL) // procura o penultimo elemento na lista
            {
                aux = aux->prox;
            }
            free(aux->prox);
            aux->prox = NULL;
        }
        printf("\n Aperte ESQ para sair!");
    
        
    }
    pontuacao->atual += pontos;
    if (pontuacao->atual > pontuacao->maior) pontuacao->maior = pontuacao->atual;

    if (pontos == 5){
        system("cls");
        printf("\n\n\tFASE COMPLETA!\n");
        printf("\tCARREGANDO... ");
        Sleep(5000);
        return 1;
    }
    return 0;
}