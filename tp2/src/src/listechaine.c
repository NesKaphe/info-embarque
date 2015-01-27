#include "listechaine.h"
#include <stdlib.h>
#include <stdio.h>


void INIT_LIST_HEAD (struct list_head *head) {
  
  head->prev = head;
  head->next = head;
}


void list_add (struct list_head *node, struct list_head *head) {
  
  node->prev = head;
  node->next = head->next;
  head->next->prev = node;
  head->next = node;
}


void list_del (struct list_head *node) {

  node->prev->next = node->next;
  node->next->prev = node->prev;
}
