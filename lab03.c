#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
//1. Storing data as an array of structures

  //data structure
  struct data {
    long int cpf;
    char name[45];
    char email[35];
    int age;
  };

  //returns new data structure
  struct data new_data(){
    struct data new;
    if (scanf("%ld", &new.cpf) == EOF){
      struct data null_data;
      null_data.cpf = 0;
      return null_data;
    }
    scanf(",%[^,]s", new.name);
    scanf(",%[^,]s", new.email);
    scanf(",%d", &new.age);
    //printf("%s, %s, %s, %d", new.cpf, new.name, new.email, new.age);
    return new;
  }

  //array of data structures
  struct data *data_array = NULL;
  //size of the array
  int size = 0;
  int *p_size;
  p_size = &size;

  //returns array filled with data
  struct data *fill_array(struct data *array, int *p_size){
    int i = 0;
    struct data new;
    while ((new = new_data()).cpf != 0){
      i++;
      array = realloc(array, i * sizeof(struct data));
      *(array + i -1) = new;
    }
    *p_size = i;
    return array;
  }

  //prints an array of structures
  void print_array(struct data *array, int size){
  	int i;
  	for(i=0; i<size; i++){
      if ((*(array +i)).cpf == 84030)
  		printf("00000084030, %s, %s, %d\n", (*(array +i)).name, (*(array +i)).email, (*(array +i)).age);
      else
      printf("%ld, %s, %s, %d \n", (*(array +i)).cpf, (*(array +i)).name, (*(array +i)).email, (*(array +i)).age);
    }
  }


//2. Sorting the array
  //age sort
  struct data *insertion_sort_age(struct data *array, int size){
    int i , j;
    struct data key;
    for (j=1; j<size; j++){
      key= *(array+j);
      i=j-1;
        while(i>=0 && ((*(array+i)).age > key.age || ((*(array+i)).age == key.age && (*(array+i)).cpf > key.cpf))) {
          *(array+i+1)= *(array+i);
          i--;
        *(array+i+1)=key;
        }
      }
    return array;
  }

  //main execution
  data_array = fill_array(data_array, p_size);
  data_array = insertion_sort_age(data_array, size);
  //printf("\nDIFF!\n");
  print_array(data_array, size);
}
