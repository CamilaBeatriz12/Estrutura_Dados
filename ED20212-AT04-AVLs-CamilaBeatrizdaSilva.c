#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
  int key;
}Item_AVL;

typedef struct Arvore_AVL *Ptr_Avl;

typedef struct Arvore_AVL{
  Item_AVL item;
  Ptr_Avl esquerda;
  Ptr_Avl direita;
  int altura;
}Arvore_AVL;

void inicia_AVL(Ptr_Avl *avl){
  (*avl) = NULL;
}

bool estaVazia_AVL(Ptr_Avl *avl){
  return (*avl) == NULL;
}

void preOrder(Ptr_Avl *avl){
  if(*avl == NULL){
    return;
  }

  printf("PRE ORDEM: ");
  printf("%d ", (*avl) -> item.key);
  preOrder(&(*avl) -> esquerda);
  preOrder(&(*avl) -> direita);
}

int profundidade_AVL(Ptr_Avl *avl){
  if((*avl) == NULL){
    return 0;
  }

  else{
    int ae = profundidade_AVL(&(*avl) -> esquerda);
    int ad = profundidade_AVL(&(*avl) -> direita);

    if(ae > ad){
      return (ae + 1);
    }

    else{
      return (ad + 1);
    }
  }
}

int altura_AVL(Ptr_Avl avl){
  if(avl == NULL){
    return 0;
  }

  else{
    return (avl -> altura);
  }
}

int up_Altura_AVL(Ptr_Avl esquerda, Ptr_Avl direita){
  int ae, ad;

  ae = altura_AVL(esquerda);
  ad = altura_AVL(direita);

  if(ae > ad){
    return (ae + 1);
  }

  else{
    return (ad + 1);
  }
}

void rotacao_s_dir(Ptr_Avl *avl){
  Ptr_Avl aux = (*avl) -> esquerda;
  (*avl) -> esquerda = aux -> direita;
  aux -> direita = (*avl);
  (*avl) -> altura = 0;
  (*avl) -> altura = up_Altura_AVL((*avl) -> esquerda, (*avl) -> direita);
  aux -> altura = up_Altura_AVL(aux -> esquerda, aux -> direita);
  (*avl) = aux;
}

void rotacao_s_esq(Ptr_Avl *avl){
  Ptr_Avl aux = (*avl) -> direita;
  (*avl) -> direita = aux -> esquerda;
  aux -> esquerda = (*avl);
  (*avl) -> altura = 0;
  (*avl) -> altura = up_Altura_AVL((*avl) -> esquerda, (*avl) -> direita);
  aux -> altura = up_Altura_AVL(aux -> esquerda, aux -> direita);
  (*avl) = aux;
}

void rotacao_d_dir(Ptr_Avl *avl){
  Ptr_Avl aux = (*avl) -> esquerda;
  Ptr_Avl aux2 = aux -> direita;
  aux -> direita = aux2 -> esquerda;
  aux2 -> esquerda = aux;
  (*avl) -> esquerda = aux2 -> direita;
  aux2 -> direita = (*avl);
  (*avl) -> altura = up_Altura_AVL((*avl) -> esquerda, (*avl) -> direita);
  aux -> altura = up_Altura_AVL(aux -> esquerda, aux -> direita);
  aux2 -> altura = up_Altura_AVL(aux2 -> esquerda, aux2 -> direita);
  (*avl) = aux2;
}

void rotacao_d_esq(Ptr_Avl *avl){
  Ptr_Avl aux = (*avl) -> direita;
  Ptr_Avl aux2 = aux -> esquerda;
  (*avl) -> direita = aux2 -> esquerda;
  aux -> esquerda = aux2 -> direita;
  aux2 -> direita = aux;
  aux2 -> esquerda = (*avl);
  (*avl) -> altura = up_Altura_AVL((*avl) -> esquerda, (*avl) -> direita);
  aux -> altura = up_Altura_AVL(aux -> esquerda, aux -> direita);
  aux2 -> altura = up_Altura_AVL(aux2 -> esquerda, aux2 -> direita);
  (*avl) = aux2;
}

void rotacao_AVL(Ptr_Avl *avl){
  if(altura_AVL((*avl) -> esquerda) > altura_AVL((*avl) -> direita)){
    Ptr_Avl aux = (*avl) -> esquerda;

    if(altura_AVL(aux -> esquerda) >= altura_AVL(aux -> direita)){
      rotacao_s_dir(&(*avl));
    }

    else{
      rotacao_d_dir(&(*avl));
    }
  }

  else{
    Ptr_Avl aux2 = (*avl) -> direita;

    if(altura_AVL(aux2 -> direita) >= altura_AVL(aux2 -> esquerda)){
      rotacao_s_esq(&(*avl));
    }

    else{
      rotacao_d_esq(&(*avl));
    }
  }
}

bool insercao_AVL(Ptr_Avl *avl, Item_AVL x){
  if((*avl) == NULL){
    (*avl) = (Ptr_Avl) malloc(sizeof(Arvore_AVL));
    (*avl) -> esquerda = (*avl) -> direita = NULL;
    (*avl) -> item = x;
    (*avl) -> altura = 1;
    printf("\nElemento: %d foi inserido com sucesso.\n", x.key);
    return true;
  }

  if((*avl) -> item.key == x.key){
    printf("\nWarning: elemento %d ja existe na arvore. Não foi inserido. \n", x.key);
    return false;
  }

  bool aux;

  if((*avl) -> item.key > x.key){
    aux = insercao_AVL(&(*avl) -> esquerda, x);
  }

  else{
    aux = insercao_AVL(&(*avl) -> direita, x);
  }

  if(aux == false){
    return false;
  }

  int ae, ad;

  ae = altura_AVL((*avl) -> esquerda);
  ad = altura_AVL((*avl) -> direita);

  if((ad - ae == -2) || (ad - ae) == 2){
    printf("Desbalanceada...\n");
    rotacao_AVL(&(*avl));
  }

  (*avl) -> altura = up_Altura_AVL((*avl) -> esquerda, (*avl) -> direita);

  return true;
}

Ptr_Avl maximo_AVL(Ptr_Avl *avl){
  if((*avl) -> direita == NULL){
    Ptr_Avl aux = (*avl);
    (*avl) = (*avl) -> esquerda;
    return (aux);
  }

  return (maximo_AVL(&(*avl) -> direita));
}

Ptr_Avl minimo_AVL(Ptr_Avl *avl){
  if((*avl) -> esquerda == NULL){
    Ptr_Avl aux = (*avl);
    aux = aux -> direita;
    return (aux);
  }

  return (minimo_AVL(&(*avl) -> esquerda));
}

bool remover_AVL(Ptr_Avl *avl, int x){
  bool aux;
  int altura_esquerda;
  int altura_direita;

  if((*avl) == NULL){
    printf("Não existe o elemento %d para ser removido!\n", x);
    return false;
  }

  if((*avl) -> item.key == x){
    Ptr_Avl aux2 = (*avl);

    if((*avl) -> direita == NULL && (*avl) -> esquerda == NULL){
      (*avl) = NULL;
    }

    else if((*avl) -> esquerda == NULL){
      (*avl) = (*avl) -> direita;
    }

    else if((*avl) -> direita == NULL){
      (*avl) = (*avl) -> esquerda;
    }

    else{
      aux2 = maximo_AVL(&(*avl) -> esquerda);
      (*avl) -> item = aux2 -> item;
    }

    free(aux2);
    return true;
  }

  if((*avl) -> item.key > x){
    aux = remover_AVL(&(*avl) -> esquerda, x);
  }

  else{
    aux = remover_AVL(&(*avl) -> direita, x);
  }

  if(aux){
    altura_esquerda = profundidade_AVL(&(*avl) -> esquerda);
    altura_direita = profundidade_AVL(&(*avl) -> direita);

    if(abs(altura_esquerda - altura_direita) == 2){
      rotacao_AVL(&(*avl));
    }

    (*avl) -> altura = up_Altura_AVL((*avl) -> esquerda, (*avl) -> direita);

    return true;
  }

  else{
    return false;
  }
}

void imprimir_AVL(Ptr_Avl *avl, int n, FILE *arq){
  if((*avl) == NULL){
    return;
  }

  else if(n == 1){
    int aux = 0;
    aux = profundidade_AVL(&(*avl) -> direita) - profundidade_AVL(&(*avl) -> esquerda);
    fprintf(arq, "%i (%i), ", (*avl) -> item.key, aux);
  }

  else{
    imprimir_AVL(&(*avl) -> esquerda, n - 1, arq);
    imprimir_AVL(&(*avl) -> direita, n - 1, arq);
  }
}

void imprimir_arq_AVL(Ptr_Avl *avl, FILE *arq){
  for(int i = 1; i <= profundidade_AVL(&(*avl)); i++){
    imprimir_AVL(&(*avl), i, arq);
    fprintf(arq, "\n");
  }
}

void destroi_AVL(Ptr_Avl *avl){
  if((*avl) != NULL){
    destroi_AVL(&(*avl) -> esquerda);
    destroi_AVL(&(*avl) -> direita);
    free(*avl);
    *avl = NULL;
  }

  printf("Arvore AVL destruida!\n");
}

int main(){
  Ptr_Avl arvore_avl;
  Item_AVL item;

  FILE *entrada = fopen("entrada.txt", "r");
  FILE *saida = fopen("saida.txt", "w");

  if(entrada == NULL || saida == NULL){
    printf("Erro ao abrir os arquivos!\n");
    exit(1);
  }

  // if(argc != 3){
  //   printf("Erro nos argumentos!\n");
  //   return 0;
  // }

  char vetor[201];
  char caracter;
  char *token;
  char *t;

  inicia_AVL(&arvore_avl);

  fgets(vetor, sizeof(vetor), entrada);
  printf("VETOR = %s\n", vetor);
  vetor[strcspn(vetor, "\n")] = '\0';

  token = strtok(vetor, ",");
  printf("%s\n", token);
  item.key = strtol(token, &t, 10);
  printf("%i\n", item.key);
  insercao_AVL(&arvore_avl, item);
  printf("AAAAAAAA\n");

  while(token != NULL){
    token = strtok(NULL, ",");
    printf("%s\n", token);

    if(token != NULL){
      item.key = strtol(token, &t, 10);
      insercao_AVL(&arvore_avl, item);
    }
  }

  fgets(vetor, sizeof(vetor), entrada);
  printf("VETOR = %s\n", vetor);
  vetor[strcspn(vetor, "\n")] = '\0';

  token = strtok(vetor, ",");
  item.key = strtol(token, &t, 10);

  remover_AVL(&arvore_avl, item.key);

  while(token != NULL){
    token = strtok(NULL, ",");

    if(token != NULL){
      item.key = strtol(token, &t, 10);
      remover_AVL(&arvore_avl, item.key);
    }
  }

  preOrder(&arvore_avl);

  // fprintf(saida, "\n[*]depois\n");
  // imprimir_arq_AVL(&arvore_avl, saida);

  //destroi_AVL(&arvore_avl);

  fclose(entrada);
  fclose(saida);

  return 0;
}
