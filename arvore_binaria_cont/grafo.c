#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "grafo.h"
#include "fila_dinamica.h"
#include "arv_bin_din_strings.h"

enum gravidade{leve, moderado, grave, critico};
typedef enum gravidade Gravidade;

enum estado_paciente{sem_sint, sint_leve, sint_sev, internacao, uti, imune};
typedef enum estado_paciente EstadoPaciente;

int num_aleatorio_0_a_x(int x){
    time_t t;
    srand((unsigned) time(&t));
    return rand() % x+1;
}

Gravidade gravidade_infeccao(){
    Gravidade g;
    int num_ale = num_aleatorio_0_a_x(100);

    if(num_ale >= 0 && num_ale < 30)
        g = leve;
    else if(num_ale >= 30 && num_ale < 85)
        g =moderado;
    else if(num_ale >= 85 && num_ale < 95)
        g =grave;
    else if(num_ale >= 95)
        g =critico;

    return g;
}

bool sobrevive_ou_nao(Gravidade g) {
    if(g == leve || g==moderado)
        return true;
    else{
        int num_ale = num_aleatorio_0_a_x(100);

        if(g==grave){
            if(num_ale >=0 && num_ale< 15)
                return false;
            else
                return true;
        }
        if(g == critico){
            if(num_ale >=0 && num_ale< 50)
                return false;
            else
                return true;
        }
    }
}

bool esta_contagioso_agora_ou_nao(Gravidade g, int dias){
    if(g == leve)
        return dias <= 14;
    else if(g == moderado)
        return dias <= 20;
    else
        return dias <= 25;
}

EstadoPaciente estado_atual_paciente(Gravidade g, int dias){
    if(dias < 5)
        return sem_sint;
    else{
        switch(g) {
            case leve:
                return imune;
            case moderado:
                if(dias < 9)
                    return sint_leve;
                else
                    return imune;
            case grave:
                if(dias < 8)
                    return sint_sev;
                else if (dias >=8 && dias < 20)
                    return internacao;
                else
                    return imune;
            case critico:
                if(dias < 7)
                    return sint_sev;
                else if (dias >=7 && dias <22)
                    return uti;
                else
                    return imune;
        }
    }
}

typedef struct grafoo{
    char nomes_vertices[QTDADE_MAX_VERT][30];
    int matriz[QTDADE_MAX_VERT][QTDADE_MAX_VERT];

    Gravidade vet_gravidade[QTDADE_MAX_VERT];
    bool vet_sobrevivencia[QTDADE_MAX_VERT];
    bool vet_contagibilidade[QTDADE_MAX_VERT];
    EstadoPaciente vet_estado_paciente[QTDADE_MAX_VERT];
    int vet_num_infectados[QTDADE_MAX_VERT];
    int vet_dia_infeccao[QTDADE_MAX_VERT];
    char paciente0[30];
    ArvBinDin arvore_infeccao;

    int qtdade_atual_vert;
    bool eh_digrafo;
} grafo;

Grafo cria_grafo(bool eh_dig){
    int i, j;
    Grafo g = (Grafo) malloc(sizeof(grafo));

    if(g != NULL){
        g->eh_digrafo = eh_dig;
        g->qtdade_atual_vert = 0;
        g->arvore_infeccao = cria_arvore();

        for(i=0; i<QTDADE_MAX_VERT; i++){
            g->vet_contagibilidade[i] = false;
            g->vet_estado_paciente[i] = sem_sint;
            g->vet_gravidade[i] = gravidade_infeccao();
            g->vet_sobrevivencia[i] = sobrevive_ou_nao(g->vet_gravidade[i]);
            g->vet_num_infectados[i] = 0;
            g->vet_dia_infeccao[i] = -1;

            for(j=0; j<QTDADE_MAX_VERT; j++){
                g->matriz[i][j] = -1;
            }
        }
    }

    return g;
}

void libera_grafo(Grafo g){
    free(g);
}

void insere_vertice(Grafo g, char* nome){
    int num_do_vert = g->qtdade_atual_vert;
    g->qtdade_atual_vert++;
    int i, j;

    for(i=0; i<num_do_vert+1; i++){
        for(j=0; j<num_do_vert+1; j++){
            g->matriz[i][j] = 0;
        }
    }

    strcpy(g->nomes_vertices[num_do_vert], nome);
}

int nome_por_id(Grafo g, char *nome){
    int i;

    for(i=0; i<g->qtdade_atual_vert; i++){
        if(!strcmp(g->nomes_vertices[i], nome))
            return i;
    }

    return -1;
}

void insere_aresta(Grafo g, char *nome1, char *nome2, int peso){
    int id_nome1 = nome_por_id(g, nome1);
    int id_nome2 = nome_por_id(g, nome2);

    if(id_nome1 != -1 && id_nome2 != -1){
        g->matriz[id_nome1][id_nome2] = peso;

        if(!g->eh_digrafo)
            g->matriz[id_nome2][id_nome1] = peso;
    }
}

void imprime_peso(Grafo g, char *nome1, char *nome2){
    int id_nome1 = nome_por_id(g, nome1);
    int id_nome2 = nome_por_id(g, nome2);

    if(id_nome1 != -1 && id_nome2 != -1)
        printf("Peso: %d\n", g->matriz[id_nome1][id_nome2]);
    else
        printf("Erro: n�o existe pelo menos 1 dos 2 vertices\n");
}

bool possui_laco(Grafo g, char *nome){
    int id_nome = nome_por_id(g, nome);
    int peso = g->matriz[id_nome][id_nome];

    if(id_nome != -1){
        return peso > 0;
    } else
        return false;
}

void imprime_grau(Grafo g, char *nome){
    int id_nome = nome_por_id(g, nome);

    if(id_nome != -1){
        if(g->eh_digrafo){
            int i, cont=0;
            for(i=0; i<g->qtdade_atual_vert; i++){
                if(g->matriz[id_nome][i] > 0)
                    cont++;
            }
            printf("O vertice %s possui grau_saida=%d\n", nome, cont);
            cont=0;
            for(i=0; i<g->qtdade_atual_vert; i++){
                if(g->matriz[i][id_nome] > 0)
                    cont++;
            }
            printf("O vertice %s possui grau_entrada=%d\n", nome, cont);
        } else {
            int i, cont=0;
            for(i=0; i<g->qtdade_atual_vert; i++){
                if(g->matriz[i][id_nome] > 0)
                    cont++;
            }
            printf("O vertice %s possui grau=%d\n", nome, cont);
        }
    } else
        printf("Erro: vertice informado nao existe.\n");
}

void print_matriz(Grafo g){
    int i, j;
    for(i=0; i<g->qtdade_atual_vert; i++){
        for(j=0; j<g->qtdade_atual_vert; j++){
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
    printf("--------\n");
    for(i=0; i<g->qtdade_atual_vert; i++){
        printf("%s\n", g->nomes_vertices[i]);
    }
    printf("--------\n");
}

void desenhe_grafo(Grafo g){
    int i, j;
    printf("\n");

    if(!g->eh_digrafo){
        printf("graph G {\n");
        for(i=0; i<g->qtdade_atual_vert; i++){
            for(j=0; j<g->qtdade_atual_vert; j++){
                if(i >= j && g->matriz[i][j] > 0)
                    printf("  \"%s\" -- \"%s\"\n", g->nomes_vertices[i], g->nomes_vertices[j]);
            }
        }
    } else {
        printf("digraph G {\n");
        for(i=0; i<g->qtdade_atual_vert; i++){
            for(j=0; j<g->qtdade_atual_vert; j++){
                if(g->matriz[i][j] > 0)
                    printf("  \"%s\" -> \"%s\"\n", g->nomes_vertices[i], g->nomes_vertices[j]);
            }
        }
    }
    printf("}\n");
}

bool sao_adjacentes(Grafo g, char *nome1, char *nome2){
    int id_nome1 = nome_por_id(g, nome1);
    int id_nome2 = nome_por_id(g, nome2);

    if(id_nome1 != -1 && id_nome2 != -1){
        if((!g->eh_digrafo) && g->matriz[id_nome1][id_nome2] > 0)
            return true;
        else if(g->eh_digrafo && (g->matriz[id_nome1][id_nome2] > 0 || g->matriz[id_nome2][id_nome1] > 0))
            return true;
        else
            return false;
    } else {
        printf("Erro: n�o existe pelo menos 1 dos 2 vertices\n");
        return false;
    }
}

void imprime_adjacentes(Grafo g, char *nome){
    int id_nome = nome_por_id(g, nome), i;
    printf("Os vertices adjacentes de %s sao:\n", nome);

    if(g->eh_digrafo){
        for(i=0; i<g->qtdade_atual_vert; i++){
            if(g->matriz[id_nome][i] > 0)
                printf("%s\n", g->nomes_vertices[i]);
        }
        for(i=0; i<g->qtdade_atual_vert; i++){
            if(g->matriz[i][id_nome] > 0)
                printf("%s\n", g->nomes_vertices[i]);
        }
    } else {
        for(i=0; i<g->qtdade_atual_vert; i++){
            if(g->matriz[i][id_nome] > 0)
                printf("%s\n", g->nomes_vertices[i]);
        }
    }
    printf("--------------\n");
}

void busca_largura(Grafo g, char *nome){
    int i, visitados[g->qtdade_atual_vert];

    for(i=0; i<g->qtdade_atual_vert; i++)
        visitados[i] = 0;

    int id_nome = nome_por_id(g, nome);

    visitados[id_nome] = 1;

    Fila f = create_queue();
    Info inf;
    inf.valor = id_nome;
    insert_queue(f, inf);

    while(!empty_queue(f)){
        Info el = remove_queue(f);
        int no_atual = el.valor;
        printf("Visitei: %s\n", g->nomes_vertices[no_atual]);

        for(i=0; i<g->qtdade_atual_vert; i++){
            if(g->matriz[no_atual][i] > 0){
                if(visitados[i] == 0){
                    visitados[i] = 1;
                    Info inf;
                    inf.valor = i;
                    insert_queue(f, inf);
                }
            }
        }
    }
    free_queue(f);
}

void define_paciente_zero(Grafo g){
        int id_sorteado = num_aleatorio_0_a_x(g->qtdade_atual_vert);
        char nome[30];
        strcpy(nome, g->nomes_vertices[id_sorteado]);

        printf("Paciente-0 e: %s\n", nome);
        strcpy(g->paciente0, nome);

        int dia = 0;
        Gravidade grav = g->vet_gravidade[id_sorteado];

        g->vet_dia_infeccao[id_sorteado] =  0;
        g->vet_contagibilidade[id_sorteado] = esta_contagioso_agora_ou_nao(grav, dia);
        g->vet_estado_paciente[id_sorteado] = estado_atual_paciente(grav, dia);

        No no_arv = cria_no(nome);
        setRaiz(g->arvore_infeccao, no_arv);
}

void imprime_estado_atual_completo_paciente(Grafo g, int dia_num, int id){
    Gravidade grav = g ->vet_gravidade[id];
    EstadoPaciente est = estado_atual_paciente(grav, dia_num);
    bool eh_contagioso = esta_contagioso_agora_ou_nao(grav, dia_num);

    if(g->vet_dia_infeccao[id] != -1){
        printf("A pessoa %s:\n", g->nomes_vertices[id]);

        if(eh_contagioso)
            printf("-- esta contagiodo\n");
        else
            printf("-- Nao esta contagioso\n");

        switch (est){
            case sem_sint:
                printf("-- Sem sintomas\n");
            break;
            case sint_leve:
                printf("-- Com sintomas leves\n");
            break;
            case sint_sev:
                printf("-- Com sintomas severos\n");
            break;
            case internacao:
                printf("-- Internado na enfermaria\n");
            break;
            case uti:
                printf("-- Internado na UTI\n");
            break;
            case imune:
                printf("-- Esta imune (curado) \n");
            break;
        }
    }
}

bool houve_contagio(Grafo g, int dia_num, int pessoa_x, int pessoa_y){
    int tempo_juntas = g->matriz[pessoa_x][pessoa_y];
    float tempo_diario = tempo_juntas / 7;
    int tempo_juntas_total = tempo_diario * dia_num;
    if(tempo_juntas_total >= 100)
        return true;
    else {
        if(tempo_juntas_total > num_aleatorio_0_a_x(50)) //50 eh a velocidade de contagio
            return true;
        else
            return false;
    }
}

void processo_contagio(Grafo g, int dia_atual, int dias_infec, int id){
    //i = vizinho, id = infectador/pessoa_infectada

    int i;
    for (i=0; i<g->qtdade_atual_vert; i++){
        if(g->matriz[id][i] > 0){
            if(g->vet_contagibilidade[id] && g->vet_num_infectados[id] < 2 && g->vet_dia_infeccao[i] == -1) {
                bool x_contagiou_y = houve_contagio(g, dias_infec, id, i);
                if(x_contagiou_y){
                    printf("A pessoa %s contagiou a pessoa %s\n", g->nomes_vertices[id], g-> nomes_vertices[i]);

                    g->vet_num_infectados[id] += 1;
                    g->vet_dia_infeccao[i] = dia_atual;
                    g->vet_contagibilidade[i] = true;

                    No infectador = referencia_nome_x(g->arvore_infeccao, g->nomes_vertices[id]);
                    No infectado = cria_no(g->nomes_vertices[i]);
                    if(g->vet_num_infectados[id] == 1)
                        setFilhoEsq(infectador, infectado);
                    else
                        setFilhoDir(infectador, infectado);

                }
            }
        }
    }
}

void atualiza_contaminacao(Grafo g, int dia_num) {
    int i, visitados[g->qtdade_atual_vert];

    for(i=0; i<g->qtdade_atual_vert; i++){
        visitados[i] = 0;
    }
    int id_nome = nome_por_id(g, g->paciente0);

    visitados[id_nome] = 1;

    Fila f = create_queue();
    Info inf;
    inf.valor = id_nome;
    insert_queue(f, inf);

    while(!empty_queue(f)){
        Info el = remove_queue(f);
        int no_atual = el.valor;

        //-----------
        int dias_infectado = dia_num - g->vet_dia_infeccao[no_atual];
        imprime_estado_atual_completo_paciente(g, dias_infectado, no_atual);
        processo_contagio(g, dia_num, dias_infectado, no_atual);
        //-----------

        for(i=0; i<g->qtdade_atual_vert; i++){
            if(g->matriz[no_atual][i] > 0) {
                if (visitados[i] == 0) {
                    visitados[i] = 1;
                    Info inf;
                    inf.valor = i;
                    insert_queue(f, inf);
                }
            }
        }
    }
    free_queue(f);
}

void desenha_arvore_contaminacao(Grafo g) {
    desenha_arvore(g->arvore_infeccao);
}




























