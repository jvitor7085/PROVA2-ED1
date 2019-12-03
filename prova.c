#include <stdio.h>
#include <stdlib.h>
#define v 7
void criarMatriz(int matriz[7][7])
{

    for(int i=0; i<v; i++)
    {
        for(int j=0; j<v; j++)
        {
            matriz[i][j]= rand() % 20;
        }
    }
}
void imprimir(int matriz[7][7])
{
    for(int i=0; i<v; i++)
    {
        for(int j=0; j<v; j++)
        {
            printf("[%d]  ",matriz[i][j]);
        }
        printf("\n");
    }
}
void ordenarMatriz(int matriz[7][7])
{
//ordenação Bubblesort
    int aux;
    for(int trocar=0; trocar<21; trocar++)
    {
        for(int i=0; i<v; i++)
        {
            for(int j=0; j<v; j++)
            {
                if (matriz[i][j] > matriz[i][j + 1])
                {
                    aux = matriz[i][j];
                    matriz[i][j] = matriz[i][j + 1];
                    matriz[i][j + 1] = aux;
                }
            }
        }
    }
}

typedef struct No{
  int dado;
  struct No* direita;
  struct No* esquerda;
} No;

No* criarArvore(){ return NULL; }

int ArvoreVazia(No* raiz){ // 1 se a arvore vazia, 0 caso contrario
  return raiz == NULL;
}

int getValor(No** no){
  if ((*no) != NULL){
    return (*no)->dado;
  }
}

void mostrarArvore(No* raiz){
  if(!ArvoreVazia(raiz)){ //No nao vazio
    printf("%p<-%d(%p)->%p\n\n", raiz->esquerda, raiz->dado, raiz, raiz->direita);
    printf("%d", getValor(&raiz->esquerda));
    mostrarArvore(raiz->esquerda);//esquerda (subNo)
    mostrarArvore(raiz->direita); //direita (subNo)
  }
}

// Metodo para desenhar a arvore em um arquivo arvore.png
// Precisa de ter o graphviz instalado
// Ubuntu: sudo apt install python-pydot python-pydot-ng graphviz
// Fedora: sudo dnf install graphviz
void gerarArquivoDot(FILE** arquivoDot, No* raiz){
  if(raiz != NULL){
    char s1[20];
    char s2[20];
    if (getValor(&raiz->esquerda)!=0){
      sprintf(s1, "%d:sw->%d [ label=\"esq\"];\n", raiz->dado, getValor(&raiz->esquerda));
      fprintf((*arquivoDot), "%s", s1);
    }
    if (getValor(&raiz->direita)!=0){
      sprintf(s2, "%d:se->%d [ label=\"dir\"];\n", raiz->dado, getValor(&raiz->direita));
      fprintf((*arquivoDot), "%s", s2);
    }
    gerarArquivoDot(arquivoDot,raiz->esquerda);//esquerda (subNo)
    gerarArquivoDot(arquivoDot,raiz->direita); //direita (subNo)
  }
}


void inserirDado(No** raiz, int dado){
    if(*raiz == NULL){
      *raiz = (No*)malloc(sizeof(No));
      (*raiz)->esquerda = NULL;
      (*raiz)->direita = NULL;
      (*raiz)->dado = dado;
    } else {
        if(dado < (*raiz)->dado){ //dado menor? vai pra esquerda
            //percorrer subNo da esquerda
            inserirDado(&(*raiz)->esquerda, dado);
        }
        if(dado > (*raiz)->dado){ //dado maior? vai pra direita
            //percorrer subNo da direita
            inserirDado(&(*raiz)->direita, dado);
        }
    }
}
void main()
{
    int matriz[v][v];
    criarMatriz(matriz[v][v]);
    imprimir(matriz[v][v]);
    ordenarMatriz(matriz[v][v]);
    printf("\n------------------------------------------\n");
    imprimir(matriz[v][v]);
    printf("\nvalores que estao na diagonal\n");
//-------------------------------------------------------------------//
    //apenas para separar um pouco o codigo
//-------------------------------------------------------------------//
//parte da arvore

No* raiz = criarArvore();
  for (int i = 0; i < 7; i++) {
        for(int j=0;j<7;i++)
    inserirDado(&raiz, matriz[i][j]);
  }

  FILE* arquivoDot;
  arquivoDot = fopen("arvore1.dot", "w");
  fprintf(arquivoDot, "%s", "digraph G {\nsplines=line;\n");
  gerarArquivoDot(&arquivoDot, raiz);
  fprintf(arquivoDot, "%s", "}\n");
  fclose(arquivoDot);
  system("dot -Tpng arvore1.dot -o arvore1.png");
}
//PROFESSOR A 1 E 2 ESTÃO FEITAS E CORRETAS,POREM QUANDO TENTO FORMAR A ARVORE TENHO PROBLEMAS,ESPERO QUE CONSIDERE UM POUCO
