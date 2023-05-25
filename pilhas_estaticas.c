#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define tam 10

typedef struct{
  int vetor[tam];
  int topo;
  int qtd_elementos;
}PilhaEstatica;

void criar(PilhaEstatica *p){
  p -> topo = 0;
  p -> qtd_elementos = 0;
}

bool vazia(PilhaEstatica *p){
  return(p -> topo == 0);
}

bool cheia(PilhaEstatica *p){
  return(p -> topo == tam);
}

int tamanho(PilhaEstatica *p){
  return(p -> qtd_elementos);
}

void inserir(PilhaEstatica *p, int x){
  if(!cheia(p)){
    p -> vetor[p -> topo] = x;
    p -> topo++;
    p -> qtd_elementos++;
  }
  else{
    printf("Cheia!");
  }
}

void imprimir(PilhaEstatica *p){
  printf("Pilha: {");

  for(int i = 0; i <= p -> topo-1; i++){
    printf("%i ", p -> vetor[i]);
  }
  printf("}\n");
}

int remover(PilhaEstatica *p){
  int aux = -1;
  if(!vazia(p)){
    aux = p -> vetor[p -> topo-1];
    p -> topo--;
    p -> qtd_elementos--;
  }
  else{
    printf("Vazia!");
  }

  return(aux);
}

int main(){
  PilhaEstatica pilha;

  criar(&pilha);

  if(vazia(&pilha)){
    printf("Vazia!\n");
  }
  else{
    printf("Nao esta vazia!\n");
  }
  //
  // if(cheia(&pilha)){
  //   printf("Cheia!\n");
  // }
  // else{
  //   printf("Nao esta cheia!\n");
  // }

  printf("Tamanho da Pilha: %d\n", tamanho(&pilha));

  inserir(&pilha, 10);
  imprimir(&pilha);
  inserir(&pilha, 12);
  imprimir(&pilha);
  inserir(&pilha, 20);
  imprimir(&pilha);

  printf("Tamanho da Pilha: %d\n", tamanho(&pilha));

  int ret = remover(&pilha);
  printf("Elemento removido: %i\n", ret);

  imprimir(&pilha);

  printf("Tamanho da Pilha: %d\n", tamanho(&pilha));

  return 0;
}
