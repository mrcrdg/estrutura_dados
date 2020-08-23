/* 5 - Crie um programa que contenha uma função que permita passar por parâmetro
dois números inteiros A e B.
A função dever ´a calcular a soma entre estes dois
números e armazenar o resultado na variável A.
Esta função não deve possuir retorno, mas deverá modificar o valor do primeiro parâmetro.
Imprima os valores
de A e B na função principal.
*/

#include <stdio.h>

void calcularSoma(int *x, int y);

int main () {

    int a;
    int b;

    printf("Insert number: ");
    scanf("%d", &a);
    printf("Insert another: ");
    scanf("%d", &b);

    printf("A: %d B: %d", a, b);

    calcularSoma(&a, b);

    printf("\n\nA: %d B: %d", a, b);

    return 0;
}

void calcularSoma(int *x, int y) {

    int soma;
    soma = *x + y;
    *x = soma;

}
