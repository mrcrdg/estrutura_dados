#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "grafo.h"
#include "grafo.c"
#include "arv_bin_din_strings.c"
#include "fila_dinamica.c"


int main(){
    Grafo g1 = cria_grafo(false);

    char mae[30] = "Fernanda Rossatto";
    char tia[30] = "Regina Rossatto";
    char vo[30] = "Terezinha Rossatto";
    char mad[30] = "Andreia Gomes";
    char irma[30] = "Yasmin Gomes";
    char pai[30] = "Edilson Gomes";
    char mat[30] = "Matheus Rossatto Gomes";

    char a1[30] = "Amigo1";
    char a2[30] = "Amigo2";
    char a3[30] = "Amigo3";
    char a4[30] = "Amigo4";
    char a5[30] = "Amigo5";
    char a6[30] = "Amigo6";
    char a7[30] = "Amigo7";
    char a8[30] = "Amigo8";

    insere_vertice(g1, mae);
    insere_vertice(g1, tia);
    insere_vertice(g1, vo);
    insere_vertice(g1, mad);
    insere_vertice(g1, irma);
    insere_vertice(g1, pai);
    insere_vertice(g1, mat);
    insere_vertice(g1, a1);
    insere_vertice(g1, a2);
    insere_vertice(g1, a3);
    insere_vertice(g1, a4);
    insere_vertice(g1, a5);
    insere_vertice(g1, a6);
    insere_vertice(g1, a7);
    insere_vertice(g1, a8);

    insere_vertice(g1, "martin");
    insere_vertice(g1, "marian");
    insere_vertice(g1, "julia");
    insere_vertice(g1, "joana");
    insere_vertice(g1, "juca");
    insere_vertice(g1, "murilo");
    insere_vertice(g1, "marcel");
    insere_vertice(g1, "michel");
    insere_vertice(g1, "marina");
    insere_vertice(g1, "jaques");
    insere_vertice(g1, "joaquim");
    insere_vertice(g1, "jon");
    insere_vertice(g1, "juliete");
    insere_vertice(g1, "jade");


    insere_vertice(g1, "Jean");
    insere_vertice(g1, "Julio");
    insere_vertice(g1, "Oscar");
    insere_vertice(g1, "Gabriel");
    insere_vertice(g1, "Rosa");
    insere_vertice(g1, "Dayane");
    insere_vertice(g1, "Gabriela");
    insere_vertice(g1, "Eduardo");
    insere_vertice(g1, "Lígia");
    insere_vertice(g1, "Simone");
    insere_vertice(g1, "Fabio");
    insere_vertice(g1, "Oscar");
    insere_vertice(g1, "Livia");
    insere_vertice(g1, "Otavio");
    insere_vertice(g1, "Gabriela");
    insere_vertice(g1, "Adriana");
    insere_vertice(g1, "Mayara");

    insere_aresta(g1, "martin", "julia", 35);
    insere_aresta(g1, "martin", "mirian", 30);
    insere_aresta(g1, "martin", "murilo", 20);
    insere_aresta(g1, "martin", "michel", 5);
    insere_aresta(g1, "julia", "joana", 35);
    insere_aresta(g1, "julia", "juca", 40);
    insere_aresta(g1, "julia", "mirian", 3);
    insere_aresta(g1, "joana", "joaquim", 30);
    insere_aresta(g1, "murilo", "marcel", 30);
    insere_aresta(g1, "murilo", "mirian", 20);
    insere_aresta(g1, "joaquim", "murilo", 8);
    insere_aresta(g1, "marcel", "jade", 7);
    insere_aresta(g1, "mirian", "jaques", 25);
    insere_aresta(g1, "mirian", "michel", 40);
    insere_aresta(g1, "mirian", "marina", 40);
    insere_aresta(g1, "michel", "marina", 70);
    insere_aresta(g1, "juca", "jon", 15);
    insere_aresta(g1, "juca", "juliete", 20);
    insere_aresta(g1, "jon", "juliete", 80);
    insere_aresta(g1, "juca", "jade", 40);

    insere_aresta(g1, "Jean", "Julio", 40); // trabalham
    insere_aresta(g1, "Jean", "Oscar", 40); // trabalham
    insere_aresta(g1, "Jean", "Gabriel", 40);	// trabalham
    insere_aresta(g1, "Jean", "Rosa", 40);	// trabalham
    insere_aresta(g1, "Jean", "Dayane", 35);  // casados
    insere_aresta(g1, "Jean", "Gabriela", 15); // pai e filha
    insere_aresta(g1, "Jean", "Eduardo", 15);	// pai e filho
    insere_aresta(g1, "Dayane", "Gabriela", 15); // mae e filha
    insere_aresta(g1, "Dayane", "Eduardo", 15);  // mae e filho
    insere_aresta(g1, "Julio", "Ligia", 36);  // casados
    insere_aresta(g1, "Julio", "Simone", 15); // pai e filha
    insere_aresta(g1, "Julio", "Fabio", 15); // pai e filho
    insere_aresta(g1, "Ligia", "Simone", 15); // mae e filha
    insere_aresta(g1, "Ligia", "Fabio", 15);  // mae e filho
    insere_aresta(g1, "Oscar", "Livia", 20); // pai e filha
    insere_aresta(g1, "Oscar", "Otavio", 20);   // pai e filho
    insere_aresta(g1, "Gabriela", "Adriana", 30);    // mae e filha
    insere_aresta(g1, "Rosa", "Mayara", 30);    // mae e filha
    insere_aresta(g1, "Eduardo", "Livia", 25);  // estudam juntos
    insere_aresta(g1, "Eduardo", "Otavio", 25);   // estudam juntos
    insere_aresta(g1, "Livia", "Otavio", 40); // sao irmaos
    insere_aresta(g1, "Gabriela", "Mayara", 40);  // trabalham
    insere_aresta(g1, "Gabriela", "Fabio", 8);	// almoçam


    insere_aresta(g1, mat, mae, 20);
    insere_aresta(g1, mat, tia, 20);
    insere_aresta(g1, mat, vo, 20);
    insere_aresta(g1, mat, mad, 8);
    insere_aresta(g1, mat, irma, 8);
    insere_aresta(g1, mat, pai, 5);

    insere_aresta(g1, mad, irma, 98);
    insere_aresta(g1, mad, pai, 34);
    insere_aresta(g1, irma, pai, 34);

    insere_aresta(g1, tia, vo, 112);
    insere_aresta(g1, mae, vo, 62);
    insere_aresta(g1, mae, tia, 62);


    insere_aresta(g1, mat, a1, 20);
    insere_aresta(g1, mat, a2, 25);
    insere_aresta(g1, mat, a3, 30);
    insere_aresta(g1, mat, a4, 10);
    insere_aresta(g1, mat, a5, 5);
    insere_aresta(g1, mat, a6, 10);
    insere_aresta(g1, mat, a7, 12);
    insere_aresta(g1, mat, a8, 3);

    insere_aresta(g1, a1, a2, 90);
    insere_aresta(g1, a1, a3, 90);
    insere_aresta(g1, a2, a3, 90);

//-----------------------

    define_paciente_zero(g1);
    int dias = 60, i;
    for(i=0; i<dias; i++){
        printf("-----------------DIA %d ------------------\n", i);
        atualiza_contaminacao(g1, i);
        printf("------------------------------------------\n");
    }

    desenha_arvore_contaminacao(g1);

    libera_grafo(g1);
    printf("Ok\n");
    return 0;
}

