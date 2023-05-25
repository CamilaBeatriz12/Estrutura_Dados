#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// typedef struct{
//     int lista[1000];
//     int ordem;
//     char *nome;
// }Item;

typedef struct NoArvore *PtrNoArvore;

typedef struct NoArvore{
    int x;
    PtrNoArvore direita;
    PtrNoArvore esquerda;
}NoArvore;

void TreeInicia(PtrNoArvore *tree){
  (*tree) = NULL;
}

bool TreeVazia(PtrNoArvore *tree){
  return ((*tree) == NULL);
}

// int TreeAltura(PtrNoArvore *tree){
//   if((*tree) == NULL){
//     return 0;
//   }
//
//   else{
//     int aE = TreeAltura((*tree) -> esquerda);
//     int aD = TreeAltura((*tree) -> direita);
//
//     if(aE > aD){
//       return aE + 1;
//     }
//
//     else{
//       return aD + 1;
//     }
//   }
// }

void TreeInsere(PtrNoArvore *tree, int x){
  if((*tree) == NULL){
        (*tree) = malloc(sizeof(NoArvore));
        (*tree)->direita = (*tree)->esquerda = NULL;
        (*tree)->x = x;
        return (true);
    }

    else if((*tree)-> x == x){
        return false;

    }
    else if(x < (*tree)-> x){
        return (TreeInsere(&(*tree)->esquerda, x));

    }
    else if(x > (*tree)-> x){
        return (TreeInsere(&(*tree)->direita, x));

    }else{
        return false;
    }
}

void percursoPreOrdem(PtrNoArvore *tree){
    if((*tree) == NULL){
        return 0;
    }

    printf("%i ", (*tree) -> x);
    percursoPreOrdem(&(*tree)->esquerda);
    percursoPreOrdem(&(*tree)->direita);

}


void percursoPosOrdem(PtrNoArvore *tree){
    if((*tree) == NULL){
        return 0;
    }

    percursoPosOrdem(&(*tree)->esquerda);
    percursoPosOrdem(&(*tree)->direita);
    printf ("%i ", (*tree) -> x);

}

void percursoEmOrdem(Ponteiro *tree){
    if((*tree) == NULL){
        return 0;
    }

    percursoEmOrdem(&(*tree)->esquerda);
    printf ("%i ", (*tree) -> x);
    percursoEmOrdem(&(*tree)->direita);
}

int main(){
  PtrNoArvore arvore;

  TreeInicia(&arvore);

  if(TreeVazia(&arvore)){
    printf("Vazia!\n");
  }
  else{
    printf("Tem algo\n!");
  }

  TreeInsere(&arvore, 1);
  TreeInsere(&arvore, 2);
  TreeInsere(&arvore, 3);

  if(TreeVazia(&arvore)){
    printf("Vazia!\n");
  }
  else{
    printf("Tem algo!\n");
  }

  return 0;
}
