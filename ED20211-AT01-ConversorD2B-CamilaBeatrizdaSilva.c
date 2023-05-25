#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define tam 50 //tamanho definido para a pilha estática

//FUNÇÕES PERTENCENTES A PILHA ESTÁTICA
//estrutura para a pilha estática
typedef struct{
  int vetor[tam];
  int topo;
  int qtd_elementos;
}PilhaEstatica;

//função de criação da pilha estática
void criar(PilhaEstatica *p){
  p -> topo = 0;
  p -> qtd_elementos = 0;
}

//função para verificação de preenchimento de pilha estática
bool vazia(PilhaEstatica *p){
  return(p -> topo == 0);
}

//função para verificação de preenchimento de pilha estática
bool cheia(PilhaEstatica *p){
  return(p -> topo == tam);
}

//função para retornar o tamanho da pilha estática
int tamanho(PilhaEstatica *p){
  return(p -> qtd_elementos);
}

//função para inserção em pilha estática
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

//função de impressão no arquivo de saída da pilha estática
void imprimir(PilhaEstatica *p){
  printf("Pilha estatica: {");
  for(int i = 0; i <= p -> topo-1; i++){
    printf("%i ", p -> vetor[i]);
  }
  printf("}");

  printf("\n");
}

//função remover elemento da pilha estática
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

//FUNÇÕES PERTENCENTES A PILHA DINÂMICA
//estruturas para a pilha dinâmica
typedef struct NoPilha *PtrNoPilha;

typedef struct NoPilha{
  int x;
  PtrNoPilha proximo;
}NoPilha;

typedef struct{
  PtrNoPilha topo;
  int qtdElementos;
}PilhaDinamica;

//função de criação para a pilha dinâmica
void inicia(PilhaDinamica *pd){
  pd -> topo = NULL;
  pd -> qtdElementos = 0;
}

//função para verificação de preenchimento em pilha dinâmica
bool Vazia(PilhaDinamica *pd){
  return(pd -> topo == NULL);
}

//função que retona o tamanho da pilha dinâmica
int tamanhoP(PilhaDinamica *pd){
  return(pd -> qtdElementos);
}

//função de inserção em pilha dinâmica
void insere(PilhaDinamica *pd, int x){
  PtrNoPilha aux;
  aux = (PtrNoPilha)malloc(sizeof(NoPilha));
  aux -> x = x;
  aux -> proximo = pd -> topo;
  pd -> topo = aux;
  pd -> qtdElementos++;
  free(aux);
}

//função de impressão no arquivo de saída de pilhas dinâmicas
void imprime(PilhaDinamica *pd){
  for(PtrNoPilha ptr = pd -> topo; ptr != NULL; ptr = ptr -> proximo){
    printf("%d\n", ptr -> x);
  }

  printf("\n");
}

//função para destruir a pilha dinâmica
void destroi(PilhaDinamica *pd){
  if(Vazia(pd)){ //verifica se está vazia
    return 0; //retorna zero caso estiver
  }

  for(PtrNoPilha aux = pd -> topo; aux != NULL; aux -> proximo){
    free(aux); //libera a memória de cada elemento, um por vez
  }
}

//função main
int main(int argc, char const *argv[]){ //parâmetros da função main
  //desclaração das variáveis necessárias
  PilhaEstatica pilha_estatica; //usada para armazenar os números recém tirados do arquivo
  PilhaDinamica pilha_dinamica; //usada para armazenar os números convertidos e impressos ao contrário
  int *vetor; //armazena os números do arquivo de entrada
  int conv; //armazena o número já convertido de decimal para binário
  int i = 0; //usado no while

  FILE *entrada = fopen(argv[0], "rt"); //abertura do aquivo para leitura modo texto

  if(entrada == NULL){
    printf("Erro ao abrir o arquivo"); //verificação de abertura do arquivo
  }

  FILE *saida = fopen(argv[1], "wt"); //abertura do aquivo para leitura modo texto

  if(saida == NULL){
    printf("Erro ao abrir o arquivo"); //verificação de abertura do arquivo
  }

  if(argc != 3){
    printf("Erro nos argumentos!\n");
    return 0;
  }

  vetor = malloc(sizeof(int)); //alocando memória para o vetor
  int n;

  char c = fgetc(entrada); //pega o caracter que define se a manipulação será com pilha estática ou dinâmica
  printf("%c\n", c);
  //MANIPULAÇÃO COM PILHA ESTÁTICA
  if(c == 'e'){
    criar(&pilha_estatica); //criação

    for(int  i = 0; !feof(entrada); i++){ //faz com que pegue todos os números, independente da quantidade
      fscanf(entrada, "%d", &n); //lê
      printf("N: %d\n", n);
      inserir(&pilha_estatica, n); //insere na pilha
      imprimir(&pilha_estatica);
    }

    //for para conseguir remover os elementos da pilha, converter e armazenar em
    //outra para imprimir ao contrário
    for(int i = pilha_estatica.topo; i > 0; i--){
      int ret = remover(&pilha_estatica);
      imprimir(&pilha_estatica);
      int a = 0;
      int vetor2[a];
      //converte de decimal para binário
      while(ret >= 0){
        if(ret < 2){
          a++;
          vetor2[a - 1] = ret % 2;
          printf("Vetor 2 = %d\n", vetor2[a - 1]);
          ret = 0;
          ret --;
        }

        else if(ret % 2 == 0){
          a++;
          vetor2[a - 1] = ret % 2;
          printf("Vetor 2 = %d\n", vetor2[a - 1]);
          ret = ret / 2;
        }

        else{
          a++;
          vetor2[a - 1] = ret % 2;
          printf("Vetor 2 = %d\n", vetor2[a - 1]);
          ret = (ret - 1) / 2;
        }
      }

      // printf("Pilha estatica: {");
      // for(int i = 0; i <= p -> topo-1; i++){
      //   printf("%i ", p -> vetor[i]);
      // }
      // printf("}");

      for (int j = (a - 1); j >= 0; j--) {    // imprime a conversão no arquivo
          fprintf(saida, "%i", vetor2[j]);
      }

      fputs ("\n", saida);                        // quebra de linha
    }

    imprimir(&pilha_estatica); //imprime o resultado no arquivo de saída
  }

  //MANIPULAÇÃO COM PILHA DINÂMICA
  else if(c == 'd'){
    inicia(&pilha_dinamica); //criação



    while(!feof(entrada)){ //faz com que pegue todos os números, independente da quantidade
        fscanf(entrada, "%d", &n); //lê
        insere(&pilha_dinamica, n); //insere na pilha dinâmica
    }

    imprime(&pilha_dinamica); //imprime o resultado no arquivo de saída

    for(int i = tamanhoP(&pilha_dinamica); i > 0; i--){
      n = pilha_dinamica.topo -> x;
      int a = 0;
      int vetor2[a];

      while(n >= 0){
        if(n < 2){
          a++;
          vetor2[a - 1] = n % 2;
          printf("Vetor 2 = %d\n", vetor2[a - 1]);
          n = 0;
          n --;
        }

        else if(n % 2 == 0){
          a++;
          vetor2[a - 1] = n % 2;
          printf("Vetor 2 = %d\n", vetor2[a - 1]);
          n = n / 2;
        }

        else{
          a++;
          vetor2[a - 1] = n % 2;
          printf("Vetor 2 = %d\n", vetor2[a - 1]);
          n = (n - 1) / 2;
        }
      }

      for (int j = (a - 1); j >= 0; j--) {    // imprime a conversão no arquivo
          fprintf(saida, "%i", vetor2[j]);
      }
      fputs ("\n", saida);
    }

    imprime(&pilha_dinamica);
  }

  //arquivo não tendo a opção de manipulaçao estática ou dinâmica
  else{
    printf("Arquivo invalido!\n");
  }

  destroi(&pilha_dinamica); //destrói a pilha dinâmica
  free(vetor); //libera a memória de vetor
  fclose(entrada); //fecha o arquivo
  fclose(saida);

  return 0; //retorno da função main
}
