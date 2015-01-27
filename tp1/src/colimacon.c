#include <stdlib.h>
#include <stdio.h>
#include "colimacon.h"


int allocArray(int **array, unsigned int rows, unsigned int columns) {

  if(rows < 1 || columns < 1) {
    return 0; //Incorrect size
  }

  *array = (int *) malloc(rows * columns * sizeof(int));

  if(array == NULL) {
    return 0; //Allocation error
  }

  return 1; //Success
}


int colimacon(int **array, unsigned int rows, unsigned int columns) {

  int i, j;
  int row_min = 0;
  int row_max = rows-1;
  int column_min = 0;
  int column_max = columns-1;
  unsigned int value = INITIAL_VALUE;
  unsigned int value_end = rows * columns;

  if(rows < 1 || columns < 1) {
    return 0; //Incorrect size
  }
  
  //Memory allocation
  if(allocArray(array, rows, columns) == 0) {
    return 0;
  }

  i = row_min;
  j = column_min;

  while(value <= value_end) {
    //We first do the top
    for(j=column_min; j <= column_max; j++) {
      (*array)[row_min * columns + j] = value;
      value++;
    }
    //Then the right
    for(i=row_min+1; i <= row_max; i++) {
      (*array)[i * columns + column_max] = value;
      value++;
    }
    //Then the bottom
    for(j=column_max-1; j >= column_min; j--) {
      (*array)[row_max * columns + j] = value;
      value++;
    }
    //Finally we do the left
    for(i=row_max-1; i > row_min; i--) {
      (*array)[i*columns + column_min] = value;
      value++;
    }

    //for the next turn we need to update the row_min, row_max, column_min and column_max indices
    row_min++;
    row_max--;
    column_min++;
    column_max--;
  }
  return 1;
}


void printArray(int *array, unsigned int rows, unsigned int columns) {
  unsigned int i = 0;
  unsigned int j = 0;
  
  for(i = 0; i < rows; i++) {
    for(j = 0; j < columns; j++) {
      printf("%d\t", array[i*columns+j]);
    }
    printf("\n");
  }
}
