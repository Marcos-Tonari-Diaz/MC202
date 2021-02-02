//LAB06 - MARCOS GABRIEL BARBOZA DURE DIAZ 221525

//Pilhas e Filas foram implementadas por listas ligadas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int code;
  char* cpfname;
  struct node* next;
} node;

typedef struct queue_index {
  node* start ;
  node* end ;
} queue_index;

//-Operacoes comuns em listas ligadas

//Cria uma nova lista vazia
node* new_empty_list(){
  return NULL;
}

//Cria novo aluno (no)
node* new_node(int codigo, char* cpfname){
  node* new = malloc(sizeof(node));
  new->code = codigo;
  new->cpfname = cpfname;
  new->next = NULL;
  return new;
}

//verifica se a lista e vazia
int isEmpty(node* stack){
  if (stack == NULL)
    return 1;
  else
    return 0;
}

void desallocate(node* stack){
  if (stack!=NULL){
    desallocate(stack->next);
    free(stack->cpfname);
    free(stack);
    return;
  }
  else
    return;
}

//-Operacoes em Pilhas

//Insercao
node* push(node* stack, node*new){
  new->next = stack;
  return new;
}

//Remocao
node* pop(node** p_stack){
  if ((*p_stack) == NULL)
    return NULL;
  else{
    node *aux = (*p_stack);
    (*p_stack) = (*p_stack)->next;
    return aux;
  }
}

//Imprime uma lista (util para pilhas invertidas)
void print_list(node* list){
    while(list!=NULL){
      printf("%d,%s\n", list->code, list->cpfname);
      list = list->next;
    }
    return;
}

//Imprime a os codigos da pilha em ordem reversa
void print_stack(node* stack){
  int print_array[5];
  int i;
  for (i=0; i<5; i++){
    *(print_array+i) = 0;
  }
  i=4;
  while(stack!=NULL){
    *(print_array+i) = stack -> code;
    i--;
    stack = stack -> next;
  }
  for (i=0; i<5; i++){
    if (*(print_array+i) != 0)
      printf("%d,", *(print_array+i));
  }
}

//-Operacoes em filas

//Insercao (no fim)
node* enqueue(node* queue, node*new, queue_index* queue_index){
  if (queue == NULL){
    queue_index->start = new;
    queue_index->end = new;
    return new;
  }
  else{
    queue_index->end->next = new;
    queue_index->end = new;
    return queue;
  }
}

//Remocao (no inicio)
node* dequeue(node** p_queue, queue_index* queue_index){
  if (*p_queue == NULL){
    return NULL;
  }
  else{
    node* aux = (*p_queue);
    queue_index->start = (*p_queue)->next;
    (*p_queue) = (*p_queue)->next;
    return aux;
  }
}

//Imprime a fila
void print_queue(node* queue){
  while(queue != NULL){
    printf("%d,", queue->code);
    queue  = queue->next;
  }
  return;
}

//input de dados (retorna string)
char* input_to_string(int size){
  char *string = malloc((size+1) * sizeof(char));
  int i;
  char aux;
  for (i=0; i<(size+1); i++){
    if ((aux=getchar())!='\n'){
      *(string+i) = aux;
    }
    else{
      *(string+i) = '\0';
      return string;
    }
  }
  return string;
}


//Execucao primaria
int main(){
  //inicializar a fila
  queue_index queue_i;
  queue_index* queue_index = &queue_i;
  node* queue = new_empty_list();
  node** p_queue = &queue;

  //inicializar as pilhas
  node* stack1 = new_empty_list();
  node* stack2 = new_empty_list();
  node* stack3 = new_empty_list();
  node* stack4 = new_empty_list();
  node* stack5 = new_empty_list();
  node* stack6 = new_empty_list();

  node** p_stack1 = &stack1;
  node** p_stack2 = &stack2;
  node** p_stack3 = &stack3;
  node** p_stack4 = &stack4;
  node** p_stack5 = &stack5;
  node** p_stack6 = &stack6;


  //inicializar vetor de pilhas
  node*** column = malloc(6*sizeof(node**));
  *column = p_stack1;
  *(column+1) = p_stack2;
  *(column+2) = p_stack3;
  *(column+3) = p_stack4;
  *(column+4) = p_stack5;
  *(column+5) = p_stack6;

  //inicializar stack reverso
  node* reverse_stack = new_empty_list();

  //Controle
  int times = 0;
  int codigo = 1;
  char aux;
  int i;
  while((aux=getchar())!= EOF){
      if (aux == 'Q'){
        if(getchar()=='I'){
          scanf("%d", &times);
          getchar();
          getchar();
          for(;times>0;times--){
            queue = enqueue(queue, new_node(codigo , input_to_string(51)), queue_index);
            codigo++;
          }
        }
        else{
          scanf("%d", &times);
          for(;times>0;times--){
           //dequeue e push
           if (queue->code < 6)
            stack1 = push(stack1, dequeue(p_queue, queue_index));
           else if (queue->code  < 11)
            stack2 = push(stack2, dequeue(p_queue, queue_index));
           else if (queue->code  < 16)
            stack3 = push(stack3, dequeue(p_queue, queue_index));
           else if (queue->code  < 21)
            stack4 = push(stack4, dequeue(p_queue, queue_index));
           else if (queue->code  < 26)
            stack5 = push(stack5, dequeue(p_queue, queue_index));
           else
            stack6 = push(stack6, dequeue(p_queue, queue_index));
          }
        }
      }
      else if (aux == 'P'){
        //printa
        printf("[Q]");print_queue(queue);printf("\n");
        printf("[S1]");print_stack(stack1);printf("\n");
        printf("[S2]");print_stack(stack2);printf("\n");
        printf("[S3]");print_stack(stack3);printf("\n");
        printf("[S4]");print_stack(stack4);printf("\n");
        printf("[S5]");print_stack(stack5);printf("\n");
        printf("[S6]");print_stack(stack6);printf("\n");
      }
      //stack remove has problems. replay debug.in as is to figure out
      else if (aux == 'S'){
        //printf("column %d\n", (*(*(column+3)))->code);
        getchar();
        //pop stack
        //reverse
        scanf("%d", &times);
        i=5;
        for (;times>0;times--){
          while(*(*(column+i))== NULL){
            i--;
          }
          reverse_stack = push(reverse_stack, pop(*(column+i)));
        }
      }
      else if (aux == 'D'){
        print_list(reverse_stack);
        desallocate(reverse_stack);
        free(column);
      }
  }
  return 0;
}
