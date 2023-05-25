#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Caixa *PtrCaixa;

typedef struct Caixa{
  char *nome;
  float peso;
  PtrCaixa proximo;
}Caixa;

typedef struct{
  PtrCaixa topo;
  int qtdElementos;
  int numero_pilha;
}Pilha;

void iniciaPilha(Pilha *pilha){
  pilha -> topo = NULL;
  pilha -> qtdElementos = 0;
}

bool Vazia(Pilha *pilha){
  return(pilha -> topo == NULL);
}

int tamanho(Pilha *pilha){
  return(pilha -> qtdElementos);
}

Caixa *topo(Pilha *pilha){
  if(Vazia(pilha)){
    printf("Vazia!");
  }

  else{
    return (pilha -> topo);
  }
}

void push(Pilha *pilha, Caixa *caixa){
  PtrNoPilha aux;
  aux = (PtrNoPilha)malloc(sizeof(NoPilha));
  aux -> x = x;
  aux -> proximo = p -> topo;
  p -> topo = aux;
  p -> qtdElementos++;
}

void imprime(Pilha *p){
  printf("Pilha: {");

  for(PtrNoPilha ptr = p -> topo; ptr != NULL; ptr = ptr -> proximo){
    printf("%d ", ptr -> x);
  }

  printf("}\n");
}

Caixa *pop(Pilha *pilha){
  int ret = -1;

  if(!Vazia(p)){
    PtrNoPilha aux = pilha -> topo;
    ret = aux -> x;
    pilha -> topo = pilha -> topo -> proximo;
    free(aux);
    pilha -> qtdElementos--;
  }
  else{
    printf("Vazia!\n");
  }

  return ret;
}

int main(){


  return 0;
}
