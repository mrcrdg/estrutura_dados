/* 03 A multiplicação de dois números inteiros pode ser feita através de
somas sucessivas.
Proponha um algoritmo recursivo multiplica_rec(n1,n2) que calcule a
multiplicação de dois inteiros.*/

#include <stdio.h>
#include <math.h>


int multiplicacaoRecursiva (int k, int n);

int main ()
{
    int number1;
    int number2;

    printf("Insert a positive integer: ");
    scanf("%d", &number1);
    printf("Insert another: ");
    scanf("%d", &number2);

    printf("The recursive sum of %d squared to %d is %d", number1, number1, somaRecursiva(number1, number2));

    return 0;
}

int multiplicacaoRecursiva (int k, int n)
{
    if (k != 0 && n !=0)
    {
        return ((k * n) + multiplicacaoRecursiva((k - 1), (n - 1)));
    }
    else
        return 0;
}







