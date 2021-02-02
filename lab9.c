#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//1.Funcoes e declaracoes para a fila de strings auxiliar
//declaracao da fila de strings
typedef struct string_queue{
  char** array;
  int start, end, data_size, current_size;
} string_queue;

//nova fila
string_queue* new_queue(int data_size){
  string_queue *new = malloc(sizeof(string_queue));
  new->array = malloc(data_size* sizeof(char*));
  new->start = 0;
  new->end = 0;
  new->data_size = data_size;
  new->current_size = 0;
  return new;
}

//adiciona item a fila
void enqueue(string_queue**queue, char* string){
  (*queue)->array[(*queue)->end] = malloc(15*sizeof(char));
  strcpy((*queue)->array[(*queue)->end], string);
  (*queue)->end = ((*queue)->end+1) % (*queue)->data_size;
  (*queue)->current_size ++;
  return;
}

//remove e retorna item da fila
char* dequeue(string_queue**queue){
  char* removed = (*queue)->array[(*queue)->start];
  (*queue)->start = ((*queue)->start +1) % (*queue)->data_size;
  (*queue)->current_size --;
  return removed;
}

//imprime os elementos da fila e a esvazia
void empty_queue(string_queue**queue){
  int i;
  int current_size = (*queue)->current_size;
  for (i=0; i < current_size; i++)
    // printf("string %d %s\n", i, dequeue(queue));
  free((*queue)->array);
  free(*queue);
  return;
}

//procurar na fila
int search_queue(string_queue**queue, char* string){
  int i;
  for (i=0; i<(*queue)->current_size; i++){
    if (!strcmp(string, (*queue)->array[i]))
      return 1;
  }
  return 0;
}

//funcao booleana que verifica se uma palavra e reservada
int is_reserved(char* word, char** reserved_array){
    int i;
    for (i=0; i<32; i++){
      if (!strcmp(word, reserved_array[i]))
        return 1;
    }
    return 0;
}


//2.Funcoes e declaracoes para a arvore AVL

//2.0.Utilidades

int max2(int a, int b){
  if (a>b)
    return a;
  else if (a<b)
    return b;
  else
    return a;
}

//2.1.Operacoes em arvores AVL
typedef struct avl{
  char* word;
  int height;
  struct avl* left, *right;
} avl;

//retorna a altura do no na arvore
int height(avl*tree){
  if(tree == NULL)
    return 0;
  return tree->height;
}

//retorna novo no com valor val
avl* new_node(char* str){
  avl* new = malloc(sizeof(avl));
  new->height = 1;
  new->word = str;
  new->left = NULL;
  new->right = NULL;
  return new;
}

//desaloca a memoria ocupada pela arvore
void desallocate_tree(avl** tree){
  if (*tree != NULL){
    desallocate_tree(&((*tree)->left));
    desallocate_tree(&((*tree)->right));
    free((*tree)->word);
    free(*tree);
  }
  return;
}

//imprime o percurso em profundidade pre-ordem
void pre_ordem(avl* tree){
  if (tree != NULL){
    printf("%s ", tree->word);
    pre_ordem(tree->left);
    pre_ordem(tree->right);
  }
}

//retorna o fator de balanceaento de um no
int balancing_factor(avl*tree){
  if (tree == NULL)
    return 0;
  return height(tree->right) - height(tree->left);
}

//rotacao a direita
void rotate_right(avl**tree){
  if ((*tree)->left!=NULL){
    avl* aux2 = (*tree)->left->right;
    avl* aux = (*tree)->left;
    (*tree)->left->right = (*tree);
    (*tree)->left = aux2;
    (*tree) = aux;
    //atualiza alturas
    (*tree)->right->height = 1 + max2(height((*tree)->right->left), height((*tree)->right->right));
    (*tree)->height = 1 + max2(height((*tree)->left), height((*tree)->right));
  }
  return;
}

//rotacao a esquerda
void rotate_left(avl**tree){
  if ((*tree)->right!=NULL){
    avl* aux2 = (*tree)->right->left;
    avl* aux = (*tree)->right;
    (*tree)->right->left = (*tree);
    (*tree)->right = aux2;
    (*tree) = aux;
    //atualiza alturas
    (*tree)->left->height = 1 + max2(height((*tree)->left->left), height((*tree)->left->right));
    (*tree)->height = 1 + max2(height((*tree)->left), height((*tree)->right));
  }
  return;
}

//rebalanceamento de um no utilizando rotacoes
void rebalance_node(avl**tree){
  if ((*tree) == NULL)
    return;
  //caso 1
  if (height((*tree)->left) > height((*tree)->right)){
    //caso 1.1
    if (height(((*tree)->left)->left) > height(((*tree)->left)->right)){
      rotate_right(tree);
    }
    //caso 1.2
    if (height(((*tree)->left)->left) < height(((*tree)->left)->right)){
      rotate_left(&(*tree)->left);
      rotate_right(tree);
    }
  }
  //caso 2
  if (height((*tree)->left) < height((*tree)->right)){
    //caso 2.1
    if (height(((*tree)->right)->left) < height(((*tree)->right)->right)){
      rotate_left(tree);
    }
    //caso 2.2
    if (height(((*tree)->right)->left) > height(((*tree)->right)->right)){
      rotate_right(&(*tree)->right);
      rotate_left(tree);
    }
  }
  return;
}

//rebalanceamento da arvore (no a no)
void rebalance_tree(avl**tree){
  if (tree != NULL && (balancing_factor(*tree)<-1 || balancing_factor(*tree)>1)){
    rebalance_node(tree);
    rebalance_tree(&(*tree)->left);
    rebalance_tree(&(*tree)->right);
  }
  (*tree)->height = 1 + max2(height((*tree)->left), height((*tree)->right));
  return;
}


//insere um no na arvore (recursiva)
void insert_node(avl** tree, avl* new){
  if (*tree == NULL){
    *tree = new;
    return;
  }
  if(strcmp(new->word, (*tree)->word)<0){
    insert_node(&(*tree)->left, new);
  }
  else if(strcmp(new->word, (*tree)->word)>0){
    insert_node(&(*tree)->right, new);
  }
  else{
    printf("Duplicate!");
    return;
  }
  (*tree)->height = 1 + max2(height((*tree)->left), height((*tree)->right));
  rebalance_tree(tree);
}


//2.3.Impressao em zig-zag
//Pilha auxiliar

//declaracao da pilha
typedef struct stack{
  avl** array;
  int top, max_size;
} stack;

//cria nova pilha
stack* new_stack (int size){
  stack* new = malloc(sizeof(stack));
  new->array = malloc(size * sizeof(avl*));
  new->top = 0;
  new->max_size = size;
  return new;
}

//insere novo elemento na pilha
void insert_stack (stack**stack, avl* tree){
  if (tree == NULL)
    return;
  else if ((*stack)->top < (*stack)-> max_size){
    (*stack)->array[(*stack)->top] = tree;
    (*stack)->top++;
    return;
  }
  else{
    printf("stack full!\n");
    return;
  }
}

//remove elemento da pilha
avl* remove_stack (stack**stack){
  if (((*stack)->top)>0){
    (*stack)->top--;
    return (*stack)->array[(*stack)->top];
  }
  else{
    (*stack)->top = -1;
    return new_node("invalid!!!");
  }
}

//esvazia o stack
void empty_stack(stack**stack){
  while((*stack)->top > 0){
    remove_stack(stack);
  }
  return;
}
//desaloca a pilha
void desallocate_stack(stack**stack){
  free((*stack)->array);
  free(*stack);
  return;
}

//esvazia uma pilha
void print_stack(stack**stack){
  int i;
  printf("stack: ");
  for (i=0; i<= (*stack)->top-1; i++){
    printf("%s - ", (*stack)->array[i]->word);
  }
  printf("\n");
  return;
}

//copia a pilha 1 na pilha 2
void copy_stack(stack**stack1, stack**stack2){
  empty_stack(stack2);
  int i, f;
  f = (*stack1)->top;
  for(i=0; i<f ;i++)
    (*stack2)->array[i] = (*stack1)->array[i];
  (*stack2)->top = (*stack1)->top;
  return;
}

//percurso em largura (utilizando uma pilha) (AGORA FOI!)
void zig_zag_traversal(avl*tree){
  int dir = 0;
  avl*current = tree;
  stack* p_stack = new_stack(100);
  stack* s_stack = new_stack(100);
  insert_stack(&p_stack, tree);
  while(p_stack->top >0){
    printf("[ ");
    while(p_stack->top >0){
      current = remove_stack(&p_stack);
      printf("%s ", current->word);
      if(dir){
        insert_stack(&s_stack, current->left);
        insert_stack(&s_stack, current->right);
      }
      else{
        insert_stack(&s_stack, current->right);
        insert_stack(&s_stack, current->left);
      }
    }
    printf("]\n");
    dir++;
    dir = dir %2;
    copy_stack(&s_stack, &p_stack);
    empty_stack(&s_stack);
  }
  desallocate_stack(&p_stack);
  desallocate_stack(&s_stack);
  return;
}



int main(){
  int i;
  avl* tree = NULL;
  char delimiters[] = " ,;(){}.#<>-*=:'\"+[}|";
  char *line;
  char *token;
  char dummy = '0';
  //criando um aray de strings das palavras reservadas
  char input[100];
  char **reserved_array = malloc(32 * sizeof(char*));
  char reserved_list[] = "auto,double,int,struct,break,else,long,switch,case,enum,register,typedef,char,extern,return,union,continue,for,signed,void,do,if,static,while,default,goto,sizeof,volatile,const,float,short,unsigned";
  reserved_array[0] = strtok(reserved_list, ",");
  for(i=1; i<32; i++){
    reserved_array[i] = strtok(NULL, ",");
  }
  string_queue* reserved_queue = new_queue(32);

  //1.Verificao das palavras reservadase armazenamento em um array

  //verifica se o primeiro token da string capturada e palavra reservada
  while (scanf("%s", input)!=EOF){
    token = &dummy;
    line = strtok(input, delimiters);
    if (line!=NULL && is_reserved(line, reserved_array)){
      // printf("RESERVED: %s\n", line);
      //verifica se a plavra reservada ja foi selecionada
      if (!search_queue(&reserved_queue, line))
        enqueue(&reserved_queue, line);
    }
    //verifica os outros tokens dentro da string anterior
    while (token != NULL){
      token = strtok(NULL, delimiters);
      if (token!=NULL && is_reserved(token, reserved_array)){
        // printf("RESERVED_TOK: %s\n", token);
        if (!search_queue(&reserved_queue, token))
          enqueue(&reserved_queue, token);
      }
    }
  }

  //insercao na arvore
  while(reserved_queue->current_size > 0){
    insert_node(&tree, new_node(dequeue(&reserved_queue)));
  }
   // rebalance_tree(&tree);
  // pre_ordem(tree);
  printf("O percurso da árvore é:\n");
  zig_zag_traversal(tree);
  desallocate_tree(&tree);
  free(reserved_queue->array);
  free(reserved_queue);
  free(reserved_array);
  return 0;
}
