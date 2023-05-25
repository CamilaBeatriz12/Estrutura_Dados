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

int consulta(Lista *lista, int x){
  Ponteiro ptr;

  for(ptr = lista -> primeiro; ptr != NULL; ptr = ptr -> proximo){
    if(EstaVazia(lista) || (x < lista -> primeiro -> key)){
      return 1;
    }

    if(ptr -> key == x){
      return 0;
    }
  }
}

void Inserir(Lista *lista, int x){

    Ponteiro aux = (Ponteiro) malloc(sizeof(NoLista));

    aux -> key = x;

    if(consulta(lista, x) == 1){
      printf("Ja existe!\n");
    }

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

Lista* uniao(Lista *lista, Lista *lista2){
  Ponteiro ptr;
  int n;

  for(ptr = lista2 -> primeiro; ptr != NULL; ptr = ptr -> proximo){
    n = ptr -> key;
    printf("Valor de n: %i\n", n);

    Inserir(lista, n);

  }
  ImprimeLista(lista);
  return lista;
}

int main(){
Lista lista_dupla;
Lista lista_dupla2;

IniciaLista(&lista_dupla);
IniciaLista(&lista_dupla2);

Inserir(&lista_dupla, 12);
Inserir(&lista_dupla, 5);
Inserir(&lista_dupla, 1);
Inserir(&lista_dupla, 66);
Inserir(&lista_dupla, 23);

Inserir(&lista_dupla2, 45);
Inserir(&lista_dupla2, 12);
Inserir(&lista_dupla2, 3);

ImprimeLista(&lista_dupla);
ImprimeLista(&lista_dupla2);

Lista * listaFINAL;

listaFINAL = uniao(&lista_dupla, &lista_dupla2);

return 0;
}
