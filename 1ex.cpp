/* 01 Crie uma função recursiva que receba um número inteiro positivo N e
calcule o somatório dos números de 1 a N. */

#include <stdio.h>

int somaRecursiva (int n);

int main ()
{

    int number;

    printf("Insert a positive integer: ");
    scanf("%d", &number);

    printf("The recursive sum of %d is %d", number, somaRecursiva(number));

    return 0;
}

int somaRecursiva (int n)
{
    if (n != 0)
    {
        return (n + somaRecursiva(n - 1));
    }
    else
        return n;
}
