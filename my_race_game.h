#define parent_node(i) ((i-1)/2)
#define left_child_node(i) (2*i+1)
#define right_child_node(i) (2*i+2)
#define MAX_INFO 1000.00

//no do heap
typedef struct node{
  float info;
  int index;
  struct node* brother1;
  struct node* brother2;
} node;

//fila de prioridade implementada com heap
typedef struct priority_queue{
  node **heap;
  int next;
} priority_queue;

//0. Basic Functions
//imprime o vetor heap que representa a fila de prioridade
void print_heap(priority_queue* priority_queue){
  int size = (priority_queue->next);
  int i;
  for(i=0; i<size; i++){
    printf("%.2f ", priority_queue->heap[i]->info);
  }
  printf("\n");
  return;
}

//cria uma nova fila de prioridade
priority_queue* new_priority_queue(int heap_max){
  priority_queue* new = malloc(sizeof(priority_queue));
  new->heap = malloc(heap_max * sizeof(node*));
  new->next = 0;
  return new;
}

//cria novo no
node* new_node(float val, int index){
  node* new = malloc(sizeof(node));
  new->info = val;
  new->index = index;
  return new;
}

void desallocate_queue(priority_queue** queue){
  int i = ((*queue)->next)-1;
  if (i>=0){
    for (;i>=0;i--)
      free((*queue)->heap[i]);
  }
  free((*queue)->heap);
  free(*queue);
  return;
}

//1.Insertion
//troca dois elementos da fila
void switch_nodes(priority_queue** priority_queue, int first, int second){
  ((*priority_queue)->heap)[second]->index = first;
  ((*priority_queue)->heap)[first]->index = second;
  node* aux = ((*priority_queue)->heap)[first];
  ((*priority_queue)->heap)[first] = ((*priority_queue)->heap)[second];
  ((*priority_queue)->heap)[second] = aux;
  return;
}

//ajusta o heap percorrendo de baixo pra cima a partir de uma folha
int bubble_up(priority_queue** priority_queue, int i){
  while (i>0){
    if ((*priority_queue)->heap[i]->info > (*priority_queue)->heap[parent_node(i)]->info){
      switch_nodes(priority_queue, i, parent_node(i));
      i = parent_node(i);
    }
    else{
      break;
    }
  }
  return i;
}

//insere um elemento na fila (retorna a posicao do novo no)
int insert_node(priority_queue** priority_queue, float val){
  int i = ((*priority_queue)->next);
  (*priority_queue)->heap[i] = new_node(val, i);
  int position = bubble_up(priority_queue, i);
  ((*priority_queue)->next)++;
  return position;
}

//2.Remove MAX
//ajusta o heap percorrendo de cima pra baixo a partir da nova raiz
void bubble_down(priority_queue** priority_queue){
   int i=0;
   int bigger_child;
   while(left_child_node(i) < ((*priority_queue)->next)){
     //por que sempre veficar com o next? pense que estamos verificando que a altura nao e ilegal
      bigger_child = left_child_node(i);
      if (right_child_node(i) < ((*priority_queue)->next) && ((*priority_queue)->heap)[right_child_node(i)]->info > ((*priority_queue)->heap)[left_child_node(i)]->info)
        bigger_child = right_child_node(i);
      if (((*priority_queue)->heap)[i]->info < ((*priority_queue)->heap)[bigger_child]->info){
        switch_nodes(priority_queue, i, bigger_child);
        i = bigger_child;
      }
      else
        break;
   }
   return;
}


//remove o elemento maximo, trocando a utima folha com a raiz e aplicando o bubble down
node* remove_max(priority_queue** priority_queue){
  node* max = ((*priority_queue)->heap)[0];
  switch_nodes(priority_queue, ((*priority_queue)->next-1), 0);
  (*priority_queue)->next--;
  bubble_down(priority_queue);
  return max;
}

//3. Operacoes especificas do lab7
void link_cars(priority_queue** acc_queue, priority_queue** con_queue, priority_queue** vel_queue, int last_acc, int last_con, int last_vel){
  (*acc_queue)->heap[last_acc]->brother1 = (*con_queue)->heap[last_con];
  (*acc_queue)->heap[last_acc]->brother2 = (*vel_queue)->heap[last_vel];

  (*con_queue)->heap[last_con]->brother1 = (*acc_queue)->heap[last_acc];
  (*con_queue)->heap[last_con]->brother2 = (*vel_queue)->heap[last_vel];

  (*vel_queue)->heap[last_vel]->brother1 = (*acc_queue)->heap[last_acc];
  (*vel_queue)->heap[last_vel]->brother2 = (*con_queue)->heap[last_con];
  return;
}
