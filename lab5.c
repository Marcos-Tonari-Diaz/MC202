#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Conjunto de funcoes para manipular listas circulares duplamente ligadas

//No da lista circular duplamente ligada
typedef struct Node{
  char name[25];
  struct Node *next;
  struct Node *previous;
} Node;


//Cria novo no (retorna ponteiro para o novo no)
Node *new_node(char name[]){
  Node *new = malloc(sizeof(Node));
  strcpy((*new).name, name);
  (*new).next = new;
  (*new).previous = new;
  return new;
}

//Insere novo no antes no no apotado por list (retorna o comeco da nova lista)
Node *insert_node(Node *list, Node *new){
  Node*aux = list;
  (*new).previous = (*list).previous;
  (*list).previous = new;
  while((*aux).next != list){
    aux = (*aux).next;
  }
  (*aux).next = new;
  (*new).next = list;
  return new;
}

//Imprime a lista
void *print_list(Node *list){
  Node *aux = list;
  do {
    printf("%s ", (*aux).name);
    aux = (*aux).next;
  } while(aux != list);
}

//Troca a posicao (troca somente o conteudo dos nos)
Node *switch_positions(Node *list, char name1[], char name2[]){
  Node *aux = list;
  do {
    if (!strcmp((*aux).name, name1)){
        strcpy((*aux).name, name2);
        aux = (*aux).next;
    }
    else if (!strcmp((*aux).name, name2)){
      strcpy((*aux).name, name1);
      aux = (*aux).next;
    }
    else{
      aux = (*aux).next;
    }
  } while (aux != list);
  return list;
}

//Remove o primeiro no da lista
Node *remove_first(Node *list){
  (*(*list).next).previous = (*list).previous;
  (*(*list).previous).next = (*list).next;
  Node *aux = list;
  free(list);
  return (*aux).next;
}

//Desaloca memoria dos nos da lista
void *free_list(Node *list){
  Node *aux = list;
  do {
    free(aux);
    aux = (*aux).next;
  } while(aux != list);
}

//Anda n nos (direction 1 HOR, 0 ANTIHOR)
Node *walk(Node *list, int n, int direction){
  int i;
  Node *aux = list;
  for(i=0; i< n; i++)
    if (direction)
      aux = (*aux).next;
    else
      aux = (*aux).previous;
  return aux;
}

//



//Execucao primaria
int main(){
  Node *list;
  char kylo[25] = "kylo";
  char rey[25] = "rey";
  char luke[25] = "luke";
  char marie[25] = "marie";
  list = new_node(kylo);
  list = insert_node(list, new_node(rey));
  list = insert_node(list, new_node(luke));
  list = insert_node(list, new_node(marie));
  //list = switch_positions(list, marie, rey);
  //list = remove_first(list);
  //list = walk(list, 2, 1);
  print_list(list);
  printf("\n");
  free_list(list);
  return 0;
}
