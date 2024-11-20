#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define LARGURA  40
#define ALTURA 20

typedef struct cobra{
    int x;
    int y;
    struct cobra *prox;
}cobra_t;

typedef struct comida{
    int x;
    int y;
}comida_t;

cobra_t *cobra(int x, int y){
    cobra_t *novaParte = (cobra_t *) malloc(sizeof(cobra_t));

    novaParte->x = x;
    novaParte->y = y;
    novaParte->prox = NULL;
    return novaParte;
}



void jogar(){
    cobra_t *cabeca = cobra(LARGURA/2, ALTURA/2);
    cobra_t *novaCabeca;
    cobra_t *aux;
    comida_t comida; 
    int fim = 0,pontos = 0, verificador_corpo = 0;
    char direcao_cobra;
    int i, j;

    srand(time(0));
    comida.x = rand() % (LARGURA -2) + 1;
    comida.y = rand() % (ALTURA -2) + 1;

    while (!fim)
    {   
        Sleep(150);
        system("cls");
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
        }

        
        int proximoX = cabeca->x, proximoY = cabeca->y;
        // proximoX e proximoY recebem as coordenadas da cabeca;

        // ao clicar em alguma tecla essas coordenadas sao alteradas: ;
        if (direcao_cobra == 'w') proximoY--;
        else if (direcao_cobra == 's') proximoY++;
        else if (direcao_cobra == 'a') proximoX --;
        else if (direcao_cobra == 'd') proximoX++;

        // Verificar se bateu nas bordas
        if (proximoX == 0 || proximoX == LARGURA -1 || proximoY == 0 || proximoY == ALTURA -1)
        {
            fim = 1;
            continue;
        }


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

    }

    
    
    
    
}


void Tela_Inicial(){
    printf("\t-------------------------------------\n");
    printf("\t|            SNAKE GAME             |\n");
    printf("\t-------------------------------------\n");
    printf("\n");
    printf("\t           MENU:               \n");
    printf("\t           Inicia Jogo:  (1)               \n");
    printf("\t           Estatisticas: (2)              \n");
    printf("\t           Como Jogar?   (3)                \n");
    printf("\t           Sair do Jogo: (4)              \n\n");
    printf("\t           Escolha uma opcao: ");
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
            //estatisticas();
            break;
        case 3:
            //como_jogar();
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