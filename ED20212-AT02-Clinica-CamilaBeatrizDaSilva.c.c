#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//estrutura de um único cliente
typedef struct{
  int code;
  char nome[50];
  char sexo;
  float peso;
  float altura;
}Paciente;

typedef struct NoLista *Ponteiro; //ponteiro para o NoLista

//estrtura do NoLista
typedef struct NoLista{
  Paciente pessoa;
  Ponteiro proximo;
  Ponteiro anterior;
}NoLista;

//estrtura da lista
typedef struct {
  Ponteiro primeiro;
  int tamanho;
}Lista;

//--------------------------------------------------------
//FUNÇÕES PARA MANIPULAÇÃO DE LISTAS DUPLAMENTE ENCADEADAS
//função de incialização da lista
void IniciaLista(Lista *lista){
  lista -> primeiro = NULL;
  lista -> tamanho = 0;
}

//função de preenchimento da lista
int EstaVazia(Lista *lista){
  return (lista -> tamanho == 0);
}

//função de inserção na lista
void Inserir(Lista *lista, Paciente x){
  Ponteiro aux = (Ponteiro) malloc(sizeof(NoLista));

  aux -> pessoa = x; //pessoa recebe a estrutura de um único cliente

  if(EstaVazia(lista)){ //verificação de lista vazia para inserção ma primeira posição
    aux -> proximo = NULL;
    aux -> anterior = NULL;
    lista -> primeiro = aux;
  }
  //-------------------------------------------------------------
  //procura o posição ideal na lista do menor para o maior código
  else if(x.code < lista -> primeiro -> pessoa.code){
    aux -> anterior = NULL;
    lista -> primeiro -> anterior = aux;
    aux -> proximo = lista -> primeiro;
    lista -> primeiro = aux;
  }

  else{
    Ponteiro percorre = malloc(sizeof(NoLista));

    for(percorre = lista -> primeiro; percorre -> proximo != NULL && x.code > percorre -> proximo -> pessoa.code; percorre = percorre -> proximo);

    aux -> pessoa = x;
    aux -> proximo = percorre -> proximo;
    aux -> anterior = percorre;

    percorre -> proximo=aux;
  }
  //--------------------------------------------------------------
  lista -> tamanho++; //incrementa o tamanho

  free(aux); //desaloca o ponteiro auxiliar
}

//função de impressão da lista no arquivo de entrada
void ImprimeLista(Lista *lista){
  Ponteiro  ptr;

  for(ptr = lista -> primeiro; ptr != NULL; ptr = ptr -> proximo){
    printf("{");
    printf("%i, %s, %c, %.2f, %.2f", ptr -> pessoa.code, ptr -> pessoa.nome, ptr -> pessoa.sexo, ptr -> pessoa.peso, ptr -> pessoa.altura);
    printf("}\n");
  }
}

//fução de destrução da lista
void DestruirLista(Lista *lista) {
  Ponteiro aux;
  while((lista -> primeiro) != NULL) {
    aux = lista -> primeiro;
    lista -> primeiro = lista -> primeiro -> proximo;
    lista -> tamanho--;
    free(aux);
  }

  printf("LISTA DESTRUIDA!\n");
}
//---------------------------------------------------------------
//main
int main(){
  Paciente p;
  Ponteiro ptr;
  Ponteiro pointer;
  Ponteiro aux;
  Lista lista_dupla;
  int op;
  int x;
  char c;

  //abertura do arquivo de entrada como append
  FILE *entrada = fopen(argv[0], "a+");

  //verficação do arquivo
  if(entrada == NULL){
    printf("Erro ao abrir o arquivo de entrada!");
    exit(1);
  }

  FILE *saida = fopen(argv[1], "wt");

  //verficação do arquivo
  if(saida == NULL){
    printf("Erro ao abrir o arquivo de saida!");
    exit(1);
  }

  if(argc != 3){
    printf("Erro nos argumentos!");
    return 0;
  }

  IniciaLista(&lista_dupla); //inicialização da lista

  printf("Deseja adicionar cadastros de pacientes (s/n)?\n");
  scanf("%c", &c);

  if(c == 's'){
    //pega todos os dados os pacientes: código, nome, sexo, peso, altura
    do{
      printf("\nDigite o codigo do paciente: \n");
      scanf("%i", &p.code);
      printf("CODIGO: %i\n", p.code);
      setbuf(stdin, NULL);

      fflush(stdin);
      printf("\nDigite o nome do paciente: \n");
      fgets(p.nome, sizeof(p.nome), stdin);
      p.nome[strcspn(p.nome, "\n")] = '\0';
      printf("NOME: %s\n", p.nome);
      setbuf(stdin, NULL);

      for(;;){
        printf("\nDigite o sexo do paciente: \n");
        scanf("%c", &p.sexo);
        setbuf(stdin, NULL);
        if(p.sexo == 'f' || p.sexo == 'm'){
          break;
        }
      }

      printf("\nDigite o peso do paciente: \n");
      scanf("%f", &p.peso);
      setbuf(stdin, NULL);

      printf("\nDigite a altura do paciente: \n");
      scanf("%f", &p.altura);
      setbuf(stdin, NULL);

      Inserir(&lista_dupla, p); //insere na lista

      printf("\nDeseja adicionar mais pacientes (s/n)?\n");
    } while(getchar() == 's');
  }

  ImprimeLista(&lista_dupla); //imprime a lista no arquivo de entrada

  printf("\nEscolha:\n1 - Imprimir crescente;\n2 - Imprimir decrescente;\n3 - Consultar;\n");
  scanf("%i", &op);

  fprintf(entrada, "%i\n", op);

  //menu de opções: imprimir crescente, decrescente e consultar um paciente
  switch(op){
    case 1: //imprime crescente
      for(pointer = lista_dupla.primeiro; pointer != NULL; pointer = pointer -> proximo){
        fprintf(saida, "{");
        fprintf(saida, "%i, %s, %c, %.2f, %.2f", pointer -> pessoa.code, pointer -> pessoa.nome, pointer -> pessoa.sexo, pointer -> pessoa.peso, pointer -> pessoa.altura);
        fprintf(saida, "}\n");
      }

      break;

    case 2: //imprime decrescente
      for(ptr = lista_dupla.primeiro; ptr -> proximo != NULL; ptr = ptr -> proximo);

      aux = ptr;
      do {
        fprintf(saida, "{");
        fprintf(saida, "%i, %s, %c, %.2f, %.2f", aux -> pessoa.code, aux -> pessoa.nome, aux -> pessoa.sexo, aux -> pessoa.peso, aux -> pessoa.altura);
        fprintf(saida, "}\n");
        aux = aux -> anterior;
      } while(aux != NULL);

      break;

    case 3: //consulta do paciente
      printf("Qual cadastro deseja encontrar?\n");
      scanf("%i", &x);

      fprintf(entrada, "%i\n", x);

      if(EstaVazia(&lista_dupla)){
        printf("O cadastro do paciente nao foi encontrado\n");
      }

      for(ptr = lista_dupla.primeiro; ptr -> proximo != NULL && x > ptr -> pessoa.code; ptr = ptr -> proximo);

      if(ptr == NULL || ptr -> pessoa.code > x) {
        printf("O cadastro do paciente nao foi encontrado\n");
      }

      else{
        printf("O cadastro do paciente foi encontrado\n");
        fprintf(saida, "{");
        fprintf(saida, "%i, %s, %c, %.2f, %.2f", ptr -> pessoa.code, ptr -> pessoa.nome, ptr -> pessoa.sexo, ptr -> pessoa.peso, ptr -> pessoa.altura);
        fprintf(saida, "}\n");
      }

      break;

    default: //opção inválida
      printf("Opcao Invalida!\n");
      exit(1);
  }

  DestruirLista(&lista_dupla); //destrução da lista
  fclose(entrada); //arquivo de entrada fechado
  fclose(saida);

  return 0;
}
