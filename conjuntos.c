#include <stdio.h>
#include <stdlib.h>

//Representacao de um conjunto
typedef struct node{
  int info;
  struct node* next;
} Node;

//Printa um conjunto
Node *print_set(Node *list){
  if (list == NULL)
    return NULL;
  else if ((*list).next == NULL){
      printf("%d", (*list).info);
      return NULL;
  }
  printf("%d,", (*list).info);
  print_set((*list).next);
  return NULL;
}

//Retorna uma lista vazia
Node *new_empty_list(){
  return NULL;
}

//Retorna um novo no de valor val
Node *new_node(int val){
  Node * new = malloc(sizeof(Node));
  if (new == NULL)
    exit(1);
  (*new).info = val;
  (*new).next = NULL;
  return new;
}

//Retorna lista com elemento inserido em ordem crescente (recursiva)
Node *insert_r(Node *list, Node *node, Node *aux){
  //lista vazia
  if (aux == NULL){
    return node;
  }
  if (list == NULL){
    (*node).next = NULL;
    return node;
  }
  else if ((*node).info < (*list).info){
    (*node).next = list;
    return node;
  }
  else if ((*node).info == (*list).info){
    return list;
  }
  else{
    (*list).next = insert_r((*list).next, node, aux);
    return list;
  }
}

//Retorna o numero de nos da lista
int count_nodes(Node *list){
  int i=0;
  while(list != NULL){
    list = (*list).next;
    i++;
  }
  return i;
}

//Imprime se elemento pertence a algum no da lista
Node *search(Node *list, int val){
  if (list == NULL){
    printf("NAO\n");
    return list;
  }
  else if ((*list).info == val){
    printf("SIM\n");
    return list;
  }
  else
    return search((*list).next, val);
}

//Retorna no de valor val
Node *r_search(Node *list, int val){
  if (list == NULL){
    return list;
  }
  else if ((*list).info == val){
    return list;
  }
  else
    return r_search((*list).next, val);
}

//Retorna uma lista com o no de valor especificado removido
Node *remove_node(Node *list, int val){
  if (list == NULL)
    return NULL;
  else if ((*list).info == val){
    //free(list);
    return (*list).next;
  }
  else{
    (*list).next = remove_node((*list).next, val);
    return list;
  }
}

//Retorna uma copia da lista (recursiva)
Node *copy(Node *list){
  if (list == NULL){
    return list;
  }
  else{
    Node* node = new_node((*list).info);
    (*node).next = copy((*list).next);
    return node;
  }
}

//Retorna primeiro elemento repetido da lista (COM PROBELMAS!)
Node *find_duplicate(Node *list){
  Node *mover = (*list).next;
  if (list == NULL)
    return list;
  while(mover != NULL){
    if ((*mover).info == (*list).info)
      return mover;
    mover = (*mover).next;
  }
  find_duplicate((*list).next);
  return list;
}

//Retorna a concatenacao das listas (WORKING!)
Node *concatenate(Node *first, Node *second){
  if (first == NULL && second == NULL)
    return NULL;
  //insere conteudo da lista second
  else if (first == NULL && second != NULL){
    Node *node = new_node((*second).info);
    (*node).next = concatenate(first, (*second).next);
    return node;
  }
  //insere conteudo da lista first
  else if (first != NULL){
    Node *node = new_node((*first).info);
    (*node).next = concatenate((*first).next, second);
    return node;
  }
  return NULL;
}

//Retorna a uniao dos conjuntos
Node *union1(Node *first, Node *second, Node *first_c, Node *result){
  if (first_c == NULL)
    return copy(second);
  if (first == NULL)
    return NULL;
  Node *aux = second;
  while (aux != NULL){
    if ((*first).info == (*aux).info){
      aux = (*aux).next;
      return re
    }
    else{
      result = insert_r(first_c, new_node((*aux).info), first_c);
      aux = (*aux).next;
      return result;
    }
  }
  return union1((*first).next, second, first_c, result);
}

//Retorna a intersecao dos conjuntos
Node *intersect(Node *first, Node *second, Node *intersection){
  if (first == NULL){
    return intersection;
  }
  Node *aux = second;
  while (aux != NULL){
    if ((*first).info == (*aux).info){
      intersection = insert_r(intersection, new_node((*first).info), intersection);
      aux = (*aux).next;
    }
    else{
      aux = (*aux).next;
    }
  }
  return intersect((*first).next, second, intersection);
}

//Retorna a subtracao dos conjuntos
Node *subtract(Node *list, Node *intersection, Node* result){
  if (list == NULL)
    return result;
  Node *aux = intersection;
  while(aux != NULL){
    if((*list).info == (*aux).info){
      result = remove_node(result, (*aux).info);
      aux = NULL;
    }
    else
      aux = (*aux).next;
  }
  return subtract((*list).next, intersection, result);
}

//Desaloca memoria ocupada pelos nos recursivamente
Node *desalocate(Node *list){
  if (list != NULL){
    desalocate((*list).next);
    free(list);
  }
  return NULL;
}

int main(){
  int val = 0, set = 0;
  char in = 0;

  //Inicia os conjuntos
  Node *c1 = new_empty_list();
  Node *c2 = new_empty_list();

  //Ponteiros auxiliares
  Node *insert;
  Node *intersection;

  //Controle de entradas
  while(1){
    scanf("%c", &in);
    //printf("%c ", in);
    if (in == 'i'){
      scanf("%d", &val);
      scanf("%d\n", &set);
      //printf("%d ", val);
      //printf("%d\n", set);
      if (set == 1){
        insert = insert_r(c1, new_node(val), c1);
        if (insert!= NULL)
          c1 = insert;
      }
      else{
        insert = insert_r(c2, new_node(val), c2);
        if (insert!= NULL)
          c2 = insert;
      }
    }
    else if (in == 'p'){
      scanf("%d", &val);
      scanf("%d\n", &set);
      //printf("%d ", val);
      //printf("%d\n", set);

      if (set == 1){
        search(c1, val);
      }
      else {
        search(c2, val);
      }
    }
    else if (in == 'r'){
      scanf("%d", &val);
      scanf("%d\n", &set);
      //printf("%d ", val);
      //printf("%d\n", set);
      if (set == 1){
        c1 = remove_node(c1, val);
      }
      else{
        c2 = remove_node(c2, val);
      }
    }
    else if (in == 'u'){
      scanf("\n");
      c1 = union1(c1, c2, c1, c1);
    }
    else if (in == 'x'){
      scanf("\n");
      intersection = new_empty_list();
      c1 = intersect(c1, c2, intersection);
    }
    else if (in == 'b'){
      scanf("\n");
      intersection = new_empty_list();
      intersection = intersect(c1, c2, intersection);
      c1 = subtract(c1, intersection, c1);
    }
    else if (in == 's'){
      printf("{");
      print_set(c1);
      printf("}\n");
      printf("{");
      print_set(c2);
      printf("}\n");
      break;
    }
    printf("{");
    print_set(c1);
    printf("}\n");
    printf("{");
    print_set(c2);
    printf("}\n");
  }
desalocate(c1);
desalocate(c2);
return 0;
}
