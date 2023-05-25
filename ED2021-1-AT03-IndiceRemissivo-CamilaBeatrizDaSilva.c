#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct Nofila *PtrFila;

typedef struct NoFila{
    int x;
    PtrFila next;
}NoFila;

typedef struct {
    PtrFila start;
    PtrFila end;
    int size;
}Fila;

void iniciaFila (Fila *fila) {
    fila->start = fila->end = NULL;
    fila->size = 0;
}

int tamanhoFila (Fila *fila) {
    return fila->size;
}

bool estavaziaFila (Fila *fila) {
    return tamanhoFila (fila) == 0;
}

void insereFila (int x, Fila *fila) {
    PtrFila aux;
    aux = (PtrFila) malloc (sizeof (PtrFila));
    aux -> x = x;

    if (estavaziaFila (fila) == true) {
        fila->start = fila->end = aux;
        aux->next = NULL;

    }
    else {
        aux -> next = fila -> end -> next;
        fila->end->next = aux;
        fila->end = fila -> end -> next;
    }

    fila->size ++;
}

void imprimeFila (FILE *arq, Fila *fila) {
    PtrFila aux;
    if (estavaziaFila (fila) == true)
        printf ("Lista vazia");
    else {
        fprintf(arq, "{");

        for (aux = fila->start; aux != NULL; aux = aux->next) {
            fprintf(arq, "%i, ", aux -> x);
        }
        fprintf(arq, "}\n");
    }
}

typedef struct{
  char *palavra;
  Fila fila;
  Item itemFila;
  int insercao;
}Arvore;

typedef struct NoArvore *Ponteiro;

typedef struct NoArvore{
  Arvore x;
  Ponteiro direita;
  Ponteiro esquerda;
}NoArvore;

void iniciaArvore(Ponteiro *tree){
  (*tree) = NULL;
}

bool estavazia(Ponteiro *tree){
  return ((*tree) == NULL);
}

int tamanhoArvore(Ponteiro *tree){
  if((*tree) == NULL){
    return 0;
  }
  else{
    return (tamanhoArvore(&(*tree) -> esquerda) + 1 + tamanhoArvore(&(*tree) -> direita));
  }
}

bool insere(Ponteiro *tree, Arvore x){
  if(estavazia(&(*tree)) == true){
    (*tree) = (Ponteiro) malloc(sizeof(NoArvore));
    (*tree)->direita = (*tree)->esquerda = NULL;
    (*tree) -> x = x;

    printf("INSERIDO COM SUCESSO (1)\n");

    return(true);
  }

  else if(strcmp((*tree) -> x.palavra, x.palavra) == 0){
    return false;
  }

  else if(strcmp((*tree) -> x.palavra, x.palavra) > 0){
    printf("INSERIDO COM SUCESSO (2)\n");
    return (insere(&(*tree)->esquerda, x));
  }

  else{
    printf("INSERIDO COM SUCESSO (3)\n");
    return (insere(&(*tree)->direita, x));
  }
}

void percursoEmOrdem(Ponteiro *tree){
    if((*tree) == NULL){
        return;
    }

    percursoEmOrdem(&(*tree)->esquerda);
    printf ("%s ", (*tree)-> x.palavra);
    percursoEmOrdem(&(*tree)->direita);
}

void search(Ponteiro *tree, int x, Ponteiro *r){
  if((*tree) == NULL){
    return;
  }

  if((*tree) -> x.insercao == x){
    (*r) = (*tree);
  }

  search(&(*tree) -> esquerda, x, &(*r));
  search(&(*tree) -> direita, x, &(*r));
}

void destroiArvore(Ponteiro *tree){
  if((*tree) == NULL){
    destroiArvore(&(*tree) -> esquerda);
	  destroiArvore(&(*tree) -> direita);
	  free(*tree);
	  *tree = NULL;
  }
}

bool delimitador(char c){
  if(c == ' ' || c == ',' || c == ';' || c == '.' || c == ':' || c == '<' ||
        c == '>' || c == '/' || c == '\n' || c == '\0' || c == '\t' || c == '?' || c == '!' ||
        c == '[' || c == ']' || c == '{' || c == '}' || c == '(' || c == ')' || c == '-' || c == '_'){
          return true;
        }
  else{
    return false;
  }
}

int main(){
  FILE *arq1 = fopen (argv[1], "r");
  FILE *arq2 = fopen (argv[2], "w");

  if ((arq1 == NULL) || (arq2 == NULL)){
    printf ("Erro na abertura dos arquivos!\n");
  }

  if(argc != 3){
    printf("Erro nos argumentos!\n");
    return 0;
  }

  char text[100];
  char text2[10000];
  char text3[10000];
  int paginas;

  Ponteiro arvore;
  Ponteiro ret;
  Arvore tree;

  iniciaArvore(&arvore);

  tree.insercao = 0;

  fgets(text, sizeof(text), arq1);
  printf("%s", text);

  text[strcspn (text, ">")] = '\0';

  for(int i = 0; i < strlen(text); i++){
    text[i] = tolower(text[i]);
  }

  printf("%s", text);

  printf("------------------------------------------------------------\n");

  char *token = strtok (text, "<:,>\n");

  printf("Retorno: %s\n", token);
  printf("------------------------------------------------------------\n");

  while (token != NULL) {
    printf("Retorno: %s\n", token);
    printf("\n\n");
    token = strtok (NULL, "<:,>\n");
    tree.insercao++;
    tree.palavra = token;
    iniciaFila(&tree.fila);

    if(estavazia(&arvore)){
      printf("arvore vazia\n");
    }

    insere(&arvore, tree);

    printf("\n");

    if(estavazia(&arvore)){
      printf("arvore vazia\n");
    }
    else{
      printf("Existe algo aqui!\n");
    }
  }

  printf("Percurso EmOrdem =  ");
  percursoEmOrdem(&arvore);
  printf("\n");

  printf("------------------------------------------------------------\n\n\n");

  while(!feof(arq1)){
    fgets(text2, sizeof(text2), arq1);
    for (int i = 0; i < strlen (text2); i++){
      text2[i] = tolower (text2[i]);
    }
    printf("%s", text2);

    if(text2[0] == '<' && text2[1] == 'p' && text2[2] == 'a' && text2[3] == 'g' && text2[4] == 'e' && text2[5] == ':'){
      paginas++;
    }

    else{
      for(int i = 0; i < strlen (text2); i++){
        if(delimitador(text2[i]) == false){
          strncat(text3, &text2[i], 1); //enquanto não tiver delimitador, vai acrescentado letras
        }

        else{
          for(int k = 1; k < tamanhoArvore(&arvore) + 1; k++){
            search(&arvore, k, &ret);
            if(strcmp(text3, ret -> x.palavra) == 0){
              if(estavaziaFila (&ret -> x.fila) == true){
                ret -> x.itemFila.key = paginas;
                insereFila(ret -> x.itemFila, &ret -> x.fila);
              }

              else if(ret->x.fila.end->x.key != paginas){
                ret -> x.itemFila.key = paginas;
                insereFila(ret -> x.itemFila, &ret -> x.fila);
              }
            }
          }
          strcpy(text3, "");
        }
      }
    }
  }

  for (int i = 1; i < tamanhoArvore(&arvore) + 1; i ++) {
      search(&arvore, i, &ret);
      fprintf (arq2 ,"%s", ret -> x.palavra);
      imprimeFila (arq2, &ret -> x.fila);
      fprintf (arq2, "\n");
  }

  destroiArvore(&arvore);

  fclose(arq1);
  fclose(arq2);

  return 0;
}
