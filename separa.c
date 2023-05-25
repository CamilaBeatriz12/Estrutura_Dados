#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NoLista *Ponteiro;

typedef struct NoLista{
  int key;
  Ponteiro proximo;
  Ponteiro anterior;
}NoLista;

typedef struct {
  Ponteiro primeiro;
  Ponteiro fim;
  int tamanho;
}Lista;

void IniciaLista(Lista *lista){
  lista -> primeiro = NULL;
  lista -> tamanho = 0;
}

int TamanhoLista(Lista *lista){
  return (lista -> tamanho);
}

int EstaVazia(Lista *lista){
  return (lista -> tamanho == 0);
}

void Inserir(Lista *lista, int x){
  Ponteiro aux = (Ponteiro) malloc(sizeof(NoLista));

  aux -> key = x;

  if(EstaVazia(lista)){
    aux -> proximo = NULL;
    aux -> anterior = NULL;
    lista -> primeiro = aux;
  }

  else if(x < lista -> primeiro -> key){
    aux -> anterior = NULL;
    lista -> primeiro -> anterior = aux;
    aux -> proximo = lista -> primeiro;
    lista -> primeiro = aux;
  }

  else{
    Ponteiro new;

    new = lista -> primeiro;

    while(new -> proximo != NULL && x > new -> proximo -> key){
      new = new -> proximo;
    }
    aux -> proximo = new -> proximo;

    if(new -> proximo != NULL){
      new -> proximo -> anterior = aux;
    }

    aux -> anterior = new;
    new -> proximo = aux;

  }

  lista -> tamanho++;
}

void ImprimeLista(Lista *lista){
  Ponteiro  ptr;

  printf("{");

  for(ptr = lista -> primeiro; ptr != NULL; ptr = ptr -> proximo){
    printf("%i ", ptr -> key);

  }

  printf("}\n");
}

Lista * separa(Lista *lista, int n){
  Ponteiro ptr;
  Lista *lista1;
  Lista *lista2;

  IniciaLista(lista1);

  int x;

  for(ptr = lista -> primeiro; ptr != NULL; ptr = ptr -> proximo){
    x = ptr -> key;
    printf("valor de x: %i\n", x);
    if(x <= n){
      Inserir(lista1, x);
      printf("Imprimindo lista 1: \n");
      ImprimeLista(lista1);
    }

    if(x > n){
      printf("AAAAAAA\n");

      Inserir(lista2, x);
      printf("Imprimindo lista 2: \n");
      ImprimeLista(lista2);
    }
  }


  lista = lista1;

  return (lista2);
}

  int main(){

  Lista lista_dupla;
  Lista *lista_dupla2;
  //Ponteiro *vetor;

  IniciaLista(&lista_dupla);
  //IniciaLista(lista_dupla2);

  Inserir(&lista_dupla, 12);
  Inserir(&lista_dupla, 5);
  Inserir(&lista_dupla, 1);
  Inserir(&lista_dupla, 66);
  Inserir(&lista_dupla, 23);

  ImprimeLista(&lista_dupla);

  lista_dupla2 = separa(&lista_dupla, 66);


  return 0;
}
