/* 02 Crie uma função recursiva que receba dois inteiros positivos k
e n e calcule k^n.*/

#include <stdio.h>
#include <math.h>

int somaRecursiva (int k, int n);

int main ()
{

    int number1;
    int number2;

    printf("Insert a positive integer: ");
    scanf("%d", &number1);
    printf("Insert another: ");
    scanf("%d", &number2);

    printf("The recursive exponencial of %d squared %d is %d", number1, number1, somaRecursiva(number1, number2));

    return 0;
}

int somaRecursiva (int k, int n)
{
    if (k != 0 && n !=0)
    {
        return ((pow(k, n)) + somaRecursiva((k - 1), (n - 1)));
    }
    else
        return 0;
}




