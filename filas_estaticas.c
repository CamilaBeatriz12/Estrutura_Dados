#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define tam 3

typedef struct{
  int inicio;
  int fim;
  int vetor[tam];
  int qtd_elementos;
}FilaEstatica;

void inicia(FilaEstatica *f){
  f -> qtd_elementos = 0;
  f -> inicio = 0;
  f -> fim = -1;
}

void estaVazia(FilaEstatica *f){
  return (f -> qtd_elementos == 0);
}

void estaCheia(FilaEstatica *f){
  return (f -> qtd_elementos == tam - 1);
}

int tamanho_fila(FilaEstatica *f){
  return f -> qtd_elementos;
}

void imprimir(FilaEstatica *f){
  int n = tamanho_fila(f);
  printf("Fila - {");

  for(int i = 0; i < n; i++){
    printf("%d ", f -> vetor[i]);
  }

  printf("}\n");
}

int incrementaIndice(int i){
  int novo_x = (i+1) % tam;
  return novo_x;
}

void inserir(FilaEstatica *f, int x){
  if(!estaCheia(f)){
    f -> fim++;
    f - > vetor[f -> fim] = x;
    f -> qtd_elementos++;
  }
  else{
    printf("Cheia!\n");
  }
}

int remover(FilaEstatica *f){
  int ret = -999;
  if(!estaVazia(f)){
    ret = f -> vetor[f -> inicio];

  }
  else{
    printf("Vazia!\n");
  }
}

int main(){
  FilaEstatica fila;
  inicia(&fila);

  if(estaVazia(&fila)){
    printf("Vazia!\n");
  }

  if(estaCheia(&fila)){
    printf("Cheia!\n");
  }

  inserir(&fila, 5);
  inserir(&fila, 7);
  inserir(&fila, 20);

  printf("Tamanho: %d\n", );

  return 0;
}
