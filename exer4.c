#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NoLista *Ponteiro; //ponteiro para o NoLista

//estrtura do NoLista
typedef struct NoLista{
  int key;
  Ponteiro proximo;
  Ponteiro anterior;
}NoLista;

//estrtura da lista
typedef struct {
  Ponteiro primeiro;
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

  aux -> key = x; //pessoa recebe a estrutura de um único cliente

  if(EstaVazia(lista)){ //verificação de lista vazia para inserção ma primeira posição
    aux -> proximo = NULL;
    aux -> anterior = NULL;
    lista -> primeiro = aux;
  }
  //-------------------------------------------------------------
  //procura o posição ideal na lista do menor para o maior código
  else if(x < lista -> primeiro -> key){
    aux -> anterior = NULL;
    lista -> primeiro -> anterior = aux;
    aux -> proximo = lista -> primeiro;
    lista -> primeiro = aux;
  }

  else{
    Ponteiro percorre = malloc(sizeof(NoLista));

    for(percorre = lista -> primeiro; percorre -> proximo != NULL && x > percorre -> proximo -> key; percorre = percorre -> proximo);

    aux -> key = x;
    aux -> proximo = percorre -> proximo;
    aux -> anterior = percorre;

    percorre -> proximo = aux;
  }
  //--------------------------------------------------------------
  lista -> tamanho++; //incrementa o tamanho

  //free(aux); //desaloca o ponteiro auxiliar
}

void ImprimeLista(Lista *lista){
  Ponteiro  ptr;


  printf("{");

  for(ptr = lista -> primeiro; ptr != NULL; ptr = ptr -> proximo){
    printf("%i ", ptr -> key);

  }

  printf("}\n");
}

void separa(Lista *lista, int n){
  Ponteiro ptr;
  Lista *lista1;
  Lista *lista2;
  int cont = 0, aux = 0;

  for(ptr = lista -> primeiro; ptr != NULL || ptr -> key > n; ptr = ptr -> proximo){
    cont++;

    if(n == ptr -> key){
      break;
    }
  }

  printf("cont: %i\n", cont);
  printf("valor de n: %i\n", n);
  int tam = TamanhoLista(lista);
  printf("tamanho na func: %i\n", tam);
  int dif = (tam-1) - cont;
  printf("diferenca: %i\n", dif);

  for(ptr = lista -> primeiro; ptr != NULL; ptr = ptr -> proximo){
    if(aux != tam){
      printf("inserido na lista1: %i\n", ptr -> key);
      Inserir(&lista1, ptr -> key);

      ImprimeLista(&lista1);
    }

    else if(aux == tam){
      printf("inserido na lista2: %i\n", ptr -> key);
      Inserir(&lista2, ptr -> key);

      ImprimeLista(&lista2);
    }

    aux++;
  }
}


  int main(){
  Lista lista_dupla;
  Ponteiro *vetor;

  IniciaLista(&lista_dupla);

  Inserir(&lista_dupla, 12);
  Inserir(&lista_dupla, 5);
  Inserir(&lista_dupla, 20);
  Inserir(&lista_dupla, 66);
  Inserir(&lista_dupla, 2);
  Inserir(&lista_dupla, 23);

  ImprimeLista(&lista_dupla);

  printf("Tamanho na main: %i\n", TamanhoLista(&lista_dupla));

  separa(&lista_dupla, 20);




  return 0;
}
