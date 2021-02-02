//MC202 LAB8 - MACOS GABRIEL BARBOZA DURE DIAZ - RA: 221525

#include <stdio.h>
#include <stdlib.h>

typedef struct bst{
  int info;
  struct bst* left, *right;
} bst;

//1.Operacoes comuns em arvores binarias de busca
//retorna novo no com valor val
bst* new_node(int val){
  bst* new = malloc(sizeof(bst));
  new->info = val;
  new->left = NULL;
  new->right = NULL;
  return new;
}

//insere um no na arvore (recursiva)
void insert_node(bst** tree, bst* new){
  if (*tree == NULL){
    *tree = new;
    return;
  }
  else{
    if(new->info < (*tree)->info)
      insert_node(&(*tree)->left, new);
    else if(new->info > (*tree)->info)
      insert_node(&(*tree)->right, new);
    else{
      printf("Duplicate!");
      return;
    }
  }
}

void desallocate_tree(bst** tree){
  if (*tree != NULL){
    desallocate_tree(&((*tree)->left));
    desallocate_tree(&((*tree)->right));
    free(*tree);
  }
  return;
}

//2.Impressao dos percursos
void pre_ordem(bst* tree){
  if (tree != NULL){
    printf("%d ", tree->info);
    pre_ordem(tree->left);
    pre_ordem(tree->right);
  }
}

void pos_ordem(bst* tree){
  if (tree != NULL){
    pos_ordem(tree->left);
    pos_ordem(tree->right);
    printf("%d ", tree->info);
  }
}

void in_ordem(bst* tree){
  if (tree != NULL){
    in_ordem(tree->left);
    printf("%d ", tree->info);
    in_ordem(tree->right);
  }
}

//3.Funcoes relacionadas ao diametro
//retorna o maximo de 3 inteiros
int max_3(int a, int b, int c){
  if (a>=b && a>=c)
    return a;
  if (b>=a && b>=c)
    return b;
  if (c>=a && c>=a)
    return c;
  else{
    return -1;
  }
}
//retorna a profundidade maxima de uma arvore
int max_depth(bst*bst){
  if (bst==NULL)
    return 0;
  else{
    int max_left = max_depth(bst->left);
    int max_right = max_depth(bst->right);
    if (max_left > max_right)
      return max_left+1;
    else
      return max_right+1;
  }
}
//retorna o diametro de uma arvore
int diameter(bst*bst){
  if(bst==NULL)
    return 0;
  int left_diameter = diameter(bst->left);
  int right_diameter = diameter(bst->right);
  int root_diameter = max_depth(bst->left) + max_depth(bst->right) + 1;
  return max_3(left_diameter, right_diameter, root_diameter);
}



int main(){
  int n = 1, iterations = 0, new_val = 0;
  char ordem[] = "nothing";
  while(n!= 0 && ordem[0]!= '0'){
    scanf("%d %s", &n, ordem);
    if (n!=0 && ordem[0]!= '0'){
      bst* tree = NULL;
      iterations = n;
      for (;iterations>0; iterations--){
        scanf("%d", &new_val);
        insert_node(&tree, new_node(new_val));
      }
      //calcular e imprimir diametro
      printf("Diametro da arvore binaria: %d", diameter(tree));
      //imprime o percurso
      printf("\n");
      if (ordem[0] == 'i'){
        in_ordem(tree);
      }
      else if (ordem[0] == 'p'){
        if(ordem[1] == 'r'){
          pre_ordem(tree);
        }
        else{
          pos_ordem(tree);
        }
      }
      printf("\n");
      desallocate_tree(&tree);
    }
    //problemas na funcao desallocate_tree
  }
  return 0;
}
