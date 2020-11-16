#ifndef ARV_BIN_DIN_STRINGS_H_INCLUDED
#define ARV_BIN_DIN_STRINGS_H_INCLUDED

typedef struct no* No;
typedef struct arv_bin* ArvBinDin;

ArvBinDin cria_arvore();

void libera_no_rec(No no);
void libera_arvore(ArvBinDin a);

No cria_no(char* nome);

void setRaiz(ArvBinDin a, No raiz);

void setFilhoEsq(No pai, No filhoEsq);

void setFilhoDir(No pai, No filhoDir);

void percorre_pre_ordem_recursivo(No no);
void percorre_pre_ordem(ArvBinDin a);

void percorre_em_ordem_recursivo(No no);
void percorre_em_ordem(ArvBinDin a);

void percorre_pos_ordem_recursivo(No no);
void percorre_pos_ordem(ArvBinDin a);

int qtdade_nos_rec(No no);
int quantidade_nos(ArvBinDin a);

int altura_subarvore(No no);
int altura_arvore(ArvBinDin a);

void desenha_arvore_rec(No no);
void desenha_arvore(ArvBinDin a);

No referencia_nome_x(ArvBinDin a, char* nome);

#endif // ARV_BIN_DIN_STRINGS_H_INCLUDED
