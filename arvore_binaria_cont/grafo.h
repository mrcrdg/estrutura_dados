#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED


#define QTDADE_MAX_VERT 70 // definir este valor de acordo com o numero de vertices do grafo
typedef struct grafoo* Grafo;

Grafo cria_grafo(bool eh_dig);

void libera_grafo(Grafo g);

void insere_vertice(Grafo g, char* nome);

void insere_aresta(Grafo g, char *nome1, char *nome2, int peso);

void imprime_peso(Grafo g, char *nome1, char *nome2);

bool possui_laco(Grafo g, char *nome);

void imprime_grau(Grafo g, char *nome);

void print_matriz(Grafo g);

void desenhe_grafo(Grafo g);

bool sao_adjacentes(Grafo g, char *nome1, char *nome2);

void imprime_adjacentes(Grafo g, char *nome);

void busca_profundidade(Grafo g, char *nome);

void busca_largura(Grafo g, char *nome);

void define_paciente_zero(Grafo g);

void atualiza_contaminacao(Grafo g, int dia_num);

void desenha_arvore_contaminacao(Grafo g);

#endif // GRAFO_H_INCLUDED
