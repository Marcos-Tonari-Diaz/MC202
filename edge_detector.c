#include <math.h>   /*Biblioteca com a funcao de raiz quadrada*/
#include <stdio.h>  /*Biblioteca para input e output*/
#include <stdlib.h>

#define WIDTH 128
#define HEIGHT 96



int combine(int ** x_matrix, int ** y_matrix, double ** f_matrix){
  for (int i = 0; i< HEIGHT ; i++){
    for (int j = 0; j< WIDTH ; j++){
      f_matrix[i][j] = sqrt(pow(x_matrix[i][j], 2) + pow(y_matrix[i][j], 2));
    }
  }

  return 0;
}

int sobel(int ** matrix, int ** d_matrix, int filter[][3]){
  for (int i = 0; i< (HEIGHT) ; i++){
      for (int j = 0; j< (WIDTH) ; j++){
        *(*(d_matrix + i) + j) =
         *(*(matrix + i + 1 -1) + j + 1 -1)*filter[0][0]
        + *(*(matrix + i + 1 -1) + j + 1)*filter[0][1]
        + *(*(matrix + i + 1 -1) + j + 1 +1)*filter[0][2]
        + *(*(matrix + i + 1) + j + 1 -1)*filter[1][0]
        + *(*(matrix + i + 1) + j + 1)*filter[1][1]
        + *(*(matrix + i + 1) + j + 1 +1)*filter[1][2]
        + *(*(matrix + i + 1 +1) + j + 1 -1)*filter[2][0]
        + *(*(matrix + i + 1 +1) + j + 1)*filter[2][1]
        + *(*(matrix + i + 1 +1) + j + 1 +1)*filter[2][2];
      }
  }
  return 0;
}

int padding(int **pad_matrix, int **matrix){
  for (int i = 0; i< (HEIGHT+2) ; i++){
      for (int j = 0; j< (WIDTH+2) ; j++){
        *(*(pad_matrix + i) + j) = 0;
      }
  }
  for (int i = 0; i< (HEIGHT) ; i++){
      for (int j = 0; j< (WIDTH) ; j++){
        *(*(pad_matrix + i + 1) + j + 1) = *(*(matrix+i)+j);
      }
  }
  return 0;
}


int input(int **matrix){
  for (int i = 0; i< HEIGHT ; i++){
    for (int j = 0; j< WIDTH ; j++){
      scanf("%d", (*(matrix + i)+j));
    }
  }
  return 0;
}

int main() {
  //create matrix
  int **matrix = malloc(HEIGHT * sizeof(int *));
  for (int i = 0; i< HEIGHT ; i++){
    *(matrix + i) = malloc(WIDTH * sizeof(int));
  }
  //assign inputs
  input(matrix);

  //padding
    // create new WIDHT+2, HEIGHT+2 matrix
  int **pad_matrix = malloc((HEIGHT+2) * sizeof(int *));
  for (int i = 0; i< (HEIGHT+2) ; i++){
    *(pad_matrix + i) = malloc((WIDTH+2) * sizeof(int));
  }
  padding(pad_matrix, matrix);

  //convolution on X
  int **x_matrix = malloc((HEIGHT) * sizeof(int *));
  for (int i = 0; i< (HEIGHT) ; i++){
    *(x_matrix + i) = malloc((WIDTH) * sizeof(int));
  }
  int filter_x[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
  sobel(pad_matrix, x_matrix, filter_x);

  //convolution on Y
  int **y_matrix = malloc((HEIGHT) * sizeof(int *));
  for (int i = 0; i< (HEIGHT) ; i++){
    *(y_matrix + i) = malloc((WIDTH) * sizeof(int));
  }
  int filter_y[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
  sobel(pad_matrix, y_matrix, filter_y);

  //combine convolutions
  double **f_matrix = malloc((HEIGHT) * sizeof(double *));
  for (int i = 0; i< (HEIGHT) ; i++){
    *(f_matrix + i) = malloc((WIDTH) * sizeof(double));
  }
  combine(x_matrix, y_matrix, f_matrix);

  //prints final image
  for (int i = 0; i< HEIGHT ; i++){
    for (int j = 0; j< WIDTH ; j++){
      int x = *(*(f_matrix + i)+j);
      if (x<10)
        printf("    %d", x);
      else if (x<100 && x>=10)
        printf("   %d", x);
      else if (x<1000 && x>=100)
        printf("  %d", x);
      else
        printf(" %d", x);
    }
    printf("\n");
  }

  //desallocation
   // matrix
  for (int i = 0; i< HEIGHT ; i++)
    free(*(matrix+i));
  free(matrix);
   // x_matrix
  for (int i = 0; i< HEIGHT ; i++)
   free(*(x_matrix+i));
  free(x_matrix);
   // y_matrix
  for (int i = 0; i< HEIGHT ; i++)
   free(*(y_matrix+i));
  free(y_matrix);
   // f_matrix
  for (int i = 0; i< HEIGHT ; i++)
   free(*(f_matrix+i));
  free(f_matrix);
  // pad_matrix
 for (int i = 0; i< HEIGHT + 2 ; i++)
   free(*(pad_matrix+i));
 free(pad_matrix);


  return 0;
  }
