#include <stdlib.h>
#include <stdio.h>
#include "colimacon.h"

int main(void) {

  int *array;

  
  printf("Affichage d'un tableau rectangulaire impair\n");
  if(colimacon(&array, 9, 9)){
    printArray(array, 9, 9);
    free(array);
  }
  else {
    printf("Echec\n");
  }
  
  printf("Affichage d'un tableau rectangulaire pair\n");
  if(colimacon(&array, 10, 10)){
    printArray(array, 10, 10);
    free(array);
  }
  else {
    printf("Echec\n");
  }

  return 0;
}
