/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

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

int main(){
    int i = 0, j = 0;

        for (i = 0; i < ALTURA; i++){
            for (j = 0; j < LARGURA; j++){
                if (i == 10 && j == 20)
                {
                    printf("&");
                }
                
                if (i == 0 || i == ALTURA - 1 || j == 0 || j == LARGURA - 1)        //i == 0 || i == ALTURA -1 || j == 0 || j == LARGURA -1
                {
                    printf("#");
                }else{
                    printf(" ");
                }
                
            }
            printf("\n");
        }
    }
*/


#include <stdio.h>

int main() {
 int a = 1, b = 2, c = 3, d = 4, e = 5;
 printf("A: %d, B: %d, C: %d, D: %d, E: %d\n\n", a, b, c, d, e);

 printf("a * b / c = %.3f\n", (float)a * b / c);
 printf("A: %d, B: %d, C: %d, D: %d, E: %d\n\n", a, b, c, d, e);

 printf("a * b %% c + 1 = %d\n", a * b % c + 1);
 printf("A: %d, B: %d, C: %d, D: %d, E: %d\n\n", a, b, c, d, e);

 printf("++a * b - c-- = %d\n", ++a * b - c--);
 printf("A: %d, B: %d, C: %d, D: %d, E: %d\n\n", a, b, c, d, e);

 printf("7 - - b * ++d = %d\n", 7 - - b * ++d);
 printf("A: %d, B: %d, C: %d, D: %d, E: %d\n\n", a, b, c, d, e);

 printf("a / b / c = %.3f\n", (float)a / b / c);
 printf("A: %d, B: %d, C: %d, D: %d, E: %d\n\n", a, b, c, d, e);

 printf("7 + c * --d / e = %.3f\n", 7 + c * --d / (float)e);
 printf("A: %d, B: %d, C: %d, D: %d, E: %d\n\n", a, b, c, d, e);

 printf("2 * a %% - b + c + 1 = %d\n", 2 * a % - b + c + 1);
 printf("A: %d, B: %d, C: %d, D: %d, E: %d\n\n", a, b, c, d, e);

 printf("39 / - ++e - + 29 %% c = %.3f\n", 39.0 / - ++e - + 29 % c);
 printf("A: %d, B: %d, C: %d, D: %d, E: %d\n\n", a, b, c, d, e);

 printf("7 - + ++a %% (3+b) = %d\n\n", 7 - + ++a % (3+b));
 printf("A: %d, B: %d, C: %d, D: %d, E: %d\n\n", a, b, c, d, e);




 return 0;
}
