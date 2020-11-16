#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv_bin_din_strings.h"

struct no{
    char nome[30];
    struct no* esq;
    struct no* dir;
};

struct arv_bin{
    No raiz;
};

ArvBinDin cria_arvore(){
    ArvBinDin a = (ArvBinDin) malloc(sizeof(struct arv_bin));
    a->raiz = NULL;
    return a;
}

void libera_no_rec(No no){
    if(no != NULL){
        libera_no_rec(no->esq);
        libera_no_rec(no->dir);
        free(no);
    }
}

void libera_arvore(ArvBinDin a){
    libera_no_rec(a->raiz);
    free(a);
}

No cria_no(char* nome){
    No novo_no = (No) malloc(sizeof(struct no));

    strcpy(novo_no->nome, nome);
    novo_no->esq = NULL;
    novo_no->dir = NULL;

    return novo_no;
}

void setRaiz(ArvBinDin a, No raiz){
    a->raiz = raiz;
}

void setFilhoEsq(No pai, No filhoEsq){
    pai->esq = filhoEsq;
}

void setFilhoDir(No pai, No filhoDir){
    pai->dir = filhoDir;
}

void percorre_pre_ordem_recursivo(No no){
    if(no != NULL){
        printf("%s ", no->nome);
        percorre_pre_ordem_recursivo(no->esq);
        percorre_pre_ordem_recursivo(no->dir);
    }
}

void percorre_pre_ordem(ArvBinDin a){
    printf("Percurso Pre-ordem:\n");
    percorre_pre_ordem_recursivo(a->raiz);
    printf("\n");
}

void percorre_em_ordem_recursivo(No no){
    if(no != NULL){
        percorre_em_ordem_recursivo(no->esq);
        printf("%s ", no->nome);
        percorre_em_ordem_recursivo(no->dir);
    }
}

void percorre_em_ordem(ArvBinDin a){
    printf("Percurso Em Ordem:\n");
    percorre_em_ordem_recursivo(a->raiz);
    printf("\n");
}

void percorre_pos_ordem_recursivo(No no){
    if(no != NULL){
        percorre_pos_ordem_recursivo(no->esq);
        percorre_pos_ordem_recursivo(no->dir);
        printf("%s ", no->nome);
    }
}

void percorre_pos_ordem(ArvBinDin a){
    printf("Percurso Pos-Ordem:\n");
    percorre_pos_ordem_recursivo(a->raiz);
    printf("\n");
}

int qtdade_nos_rec(No no){
    if(no == NULL)
        return 0;
    else
        return 1 + qtdade_nos_rec(no->esq) + qtdade_nos_rec(no->dir);
}

int quantidade_nos(ArvBinDin a){
    return qtdade_nos_rec(a->raiz);
}

int altura_subarvore(No no){
    if(no == NULL)
        return 0;

    int alt_esq = altura_subarvore(no->esq);
    int alt_dir = altura_subarvore(no->dir);

    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return (alt_dir + 1);
}

int altura_arvore(ArvBinDin a){
    return altura_subarvore(a->raiz) - 1;
}

void desenha_arvore_rec(No no){
    if(no->esq != NULL){
        printf("  \"%s\" -> \"%s\"\n", no->nome, no->esq->nome);
        desenha_arvore_rec(no->esq);
    }
    if(no->dir != NULL){
        printf("  \"%s\" -> \"%s\"\n", no->nome, no->dir->nome);
        desenha_arvore_rec(no->dir);
    }
}

void desenha_arvore(ArvBinDin a){
    printf("\ndigraph G {\n");
    desenha_arvore_rec(a->raiz);
    printf("}\n");
}

void procura_por_nome(No no, char* nome, No *ref_proc){
    if(no != NULL){
        if(!strcmp(no->nome, nome)){
            *ref_proc = no;
            return ;
        } else {
            procura_por_nome(no->esq, nome, ref_proc);
            procura_por_nome(no->dir, nome, ref_proc);
        }
    }
}

No referencia_nome_x(ArvBinDin a, char* nome){
    No no_ref = NULL;
    procura_por_nome(a->raiz, nome, &no_ref);
    return no_ref;
}
