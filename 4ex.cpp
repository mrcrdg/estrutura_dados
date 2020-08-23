/* Faça um programa que leia 2 valores inteiros e chame uma função que receba
estas 2 variáveis e troque o seu conteúdo, ou seja, esta função é chamada
passando duas variáveis A e B por exemplo e, após a execução da função, A
conterá o valor de B e B ter ´a o valor de A.*/

#include <stdio.h>

void trocarValores (int *x, int *y);

int main () {

    int a;
    int b;

    printf("Insert number: ");
    scanf("%d", &a);
    printf("Insert another: ");
    scanf("%d", &b);

    printf("A: %d B: %d", a, b);


    trocarValores (&a, &b);

    printf("\n\nA: %d B: %d", a, b);

    return 0;
}

void trocarValores (int *x, int *y) {

    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}



