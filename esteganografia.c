#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// working!
int dec_to_bin(int dec){
  int i = 0;
  int sum = 0;
  while (dec>0){
    sum+=(dec%2) * pow(10, i);
    i++;
    dec = dec/2;
  }
  return sum;
}

// working!
int bin_to_dec(int bin){
  int i = 0;
  int sum = 0;
  while(bin>=10){
    sum+=(bin%10) * pow(2, i);
    i++;
    bin = bin/10;
  }
  return ((bin * pow(2, i)) + sum);
}

// working!
int get_last_two(int i, int matrix[]){
  int last_two = 0;
  int bin = dec_to_bin(matrix[i]);
  int a = bin%10;
  bin -= a;
  int b = bin%100;
  last_two = a + b;
  return last_two;
}

int main(){
char p[10];
int  m, n, max;
scanf("%s", p);
scanf("%d", &m);
scanf("%d", &n);
scanf("%d", &max);
int img_size = n*m;
int *matrix = malloc(img_size * sizeof(int));
int i=0;
// working!
for (i=0; i<img_size; i++){
    scanf("%d", &matrix[i]);
  }
// 1 char array
int bin_final = 0;
int dec_final = 0;
for (i=0; i<img_size; i=i+4){
    bin_final=
    pow(10, 6)*get_last_two(i, matrix)
  + pow(10, 4)*get_last_two(i+1, matrix)
  + pow(10, 2)*get_last_two(i+2, matrix)
  + pow(10, 0)*get_last_two(i+3, matrix);
    dec_final = bin_to_dec(bin_final);
    if (dec_final == 0){
      break;
    }
    printf("%c", dec_final);
}
}
