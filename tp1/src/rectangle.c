#include <stdlib.h>
#include <stdio.h>
#include "colimacon.h"

int main(void) {

  int *array;

  
  printf("Affichage d'un tableau rectangulaire impair/pair\n");
  if(colimacon(&array, 3, 6)){
    printArray(array, 3, 6);
    free(array);
  }
  else {
    printf("Echec\n");
  }
  
  printf("Affichage d'un tableau rectangulaire pair/impair\n");
  if(colimacon(&array, 8, 5)){
    printArray(array, 8, 5);
    free(array);
  }
  else {
    printf("Echec\n");
  }

  return 0;
}
