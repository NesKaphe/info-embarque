#include <stdlib.h>
#include <stdio.h>
#include "colimacon.h"

int main(int argc, char** argv) {

  int *array;
  int rows, columns;

  if(argc < 3) {
    perror("Error : Usage main <sizeX> <sizeY>");
    return -1;
  }

  rows = atoi(argv[1]);
  columns = atoi(argv[2]);

  if(colimacon(&array, (unsigned int) rows, (unsigned int) columns)){
    printArray(array, (unsigned int) rows, (unsigned int) columns);
    free(array);
  }
  else {
    printf("Echec\n");
  }
  
  return 0;
}
