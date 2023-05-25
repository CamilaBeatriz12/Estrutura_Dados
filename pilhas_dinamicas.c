#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NoPilha *PtrNoPilha;

typedef struct NoPilha{
  char x;
  PtrNoPilha proximo;
}NoPilha;

typedef struct{
  PtrNoPilha topo;
  int qtdElementos;
}PilhaDinamica;

void inicia(PilhaDinamica *p){
  p -> topo = NULL;
  p -> qtdElementos = 0;
}

bool Vazia(PilhaDinamica *p){
  return(p -> topo == NULL);
}

int tamanhoP(PilhaDinamica *p){
  return(p -> qtdElementos);
}

void insere(PilhaDinamica *p, char x){
  PtrNoPilha aux;
  aux = (PtrNoPilha)malloc(sizeof(NoPilha));
  aux -> x = x;
  aux -> proximo = p -> topo;
  p -> topo = aux;
  p -> qtdElementos++;
}

void imprime(PilhaDinamica *p){
  printf("Pilha: {");

  for(PtrNoPilha ptr = p -> topo; ptr != NULL; ptr = ptr -> proximo){
    printf("%c ", ptr -> x);
  }

  printf("}\n");
}

int remover(PilhaDinamica *p){
  int ret = -1;

  if(!Vazia(p)){
    PtrNoPilha aux = p -> topo;
    ret = aux -> x;
    p -> topo = p -> topo -> proximo;
    free(aux);
    p -> qtdElementos--;
  }
  else{
    printf("Vazia!\n");
  }

  return ret;
}

int main(){
  PilhaDinamica pilhas;

  inicia(&pilhas);

  if(Vazia(&pilhas)){
    printf("Vazia!\n");
  }
  else{
    printf("Tem algo aqui!\n");
  }

  printf("Tamanho da pilha dinamica: %d\n", tamanhoP(&pilhas));

  insere(&pilhas, '$');
  imprime(&pilhas);
  insere(&pilhas, 'l');
  imprime(&pilhas);
  insere(&pilhas, 'i');
  imprime(&pilhas);
  insere(&pilhas, 'm');
  imprime(&pilhas);
  insere(&pilhas, 'a');
  imprime(&pilhas);
  insere(&pilhas, 'c');
  imprime(&pilhas);

  printf("Tamanho da pilha dinamica: %d\n", tamanhoP(&pilhas));

  printf("\n");

  char retorno = remover(&pilhas);
  printf("Elemento removido: %c\n", retorno);
  imprime(&pilhas);

  printf("Tamanho da pilha dinamica: %d\n", tamanhoP(&pilhas));


  return 0;
}
