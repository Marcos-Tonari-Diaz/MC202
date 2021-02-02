#include <stdio.h>
#include <stdlib.h>
#include "my_race_game.h"

int main(){
  int iterations, maximum_cars, num_add, num_rem, which_queue;
  int last_acc, last_con, last_vel;
  float acc = 0.0, con = 0.0, vel= 0.0;
  node* removed;
  scanf("%d %d\n", &iterations, &maximum_cars);
  priority_queue* acc_queue = new_priority_queue(maximum_cars);
  priority_queue* con_queue = new_priority_queue(maximum_cars);
  priority_queue* vel_queue = new_priority_queue(maximum_cars);
  for (; iterations>0; iterations--){
    scanf("%d %d", &num_add, &num_rem);
    //Adicionar carro
    for (; num_add>0; num_add--){
      scanf("%f %f %f", &acc, &con, &vel);
      last_acc = insert_node(&acc_queue, acc);
      last_con = insert_node(&con_queue, con);
      last_vel = insert_node(&vel_queue, vel);
      link_cars(&acc_queue, &con_queue, &vel_queue, last_acc, last_con, last_vel);
    }
    //Remover da fila
    for(; num_rem>0; num_rem--){
      scanf("%d", &which_queue);
      //aceleracao
      if (which_queue == 0){
        printf("%.2f ", acc_queue->heap[0]->info);
        removed = remove_max(&acc_queue);
        //remover de con_queue
        printf("%.2f ", removed->brother1->info);
        removed->brother1->info = MAX_INFO;
        bubble_up(&con_queue, removed->brother1->index);
        remove_max(&con_queue);
        //remover de vel_queue
        printf("%.2f\n", removed->brother2->info);
        removed->brother2->info = MAX_INFO;
        bubble_up(&vel_queue, removed->brother2->index);
        remove_max(&vel_queue);

        free(removed->brother1);
        free(removed->brother2);
        free(removed);
      }
      //controle
      else if (which_queue == 1){
        removed = remove_max(&con_queue);
        //remover de acc_queue
        printf("%.2f ", removed->brother1->info);
        removed->brother1->info = MAX_INFO;
        bubble_up(&acc_queue, removed->brother1->index);
        remove_max(&acc_queue);
        //printa de con_queue
        printf("%.2f ", removed->info);
        //remover de vel_queue
        printf("%.2f\n", removed->brother2->info);
        removed->brother2->info = MAX_INFO;
        bubble_up(&vel_queue, removed->brother2->index);
        remove_max(&vel_queue);

        free(removed->brother1);
        free(removed->brother2);
        free(removed);
      }
      //velocidade
      else if (which_queue == 2){
        removed = remove_max(&vel_queue);
        //remover de acc_queue
        printf("%.2f ", removed->brother1->info);
        removed->brother1->info = MAX_INFO;
        bubble_up(&acc_queue, removed->brother1->index);
        remove_max(&acc_queue);
        //remover de con_queue
        printf("%.2f ", removed->brother2->info);
        removed->brother2->info = MAX_INFO;
        bubble_up(&con_queue, removed->brother2->index);
        remove_max(&con_queue);
        //printa de vel_queue
        printf("%.2f\n", removed->info);

        free(removed->brother1);
        free(removed->brother2);
        free(removed);
      }
    }
  }
  desallocate_queue(&acc_queue);
  desallocate_queue(&con_queue);
  desallocate_queue(&vel_queue);
  return 0;
}
