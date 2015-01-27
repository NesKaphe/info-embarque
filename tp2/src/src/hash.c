#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Hash function not shown in header file */
unsigned int hash_char (char *text) {

  unsigned int key = 0;
  unsigned int i = 0;
  char c = text[0];

  while (c != '\0') {
    key += (unsigned int) c;
    c = text[++i];
  }
  return key;
}

unsigned int hash_A (struct A *a) {

  return a->id;

}

struct hash_element *allocate_hash_element() {
  struct hash_element *elem = NULL;

  elem = (struct hash_element *) malloc(sizeof(struct hash_element));
  memset(elem, 0, sizeof(struct hash_element));

  return elem;
}


struct hash_element *find_element(unsigned int key, struct hash_table *hash) {
  // First we need to find the indice of the key in the hash table
  unsigned int indice = key % hash->size;
  struct hash_element *elem = hash->table[indice];
  
  //We can now use the list_for_each_entry to iterate over the list to search for the key
  if(elem->key == key) {
    return elem;
  }

  list_for_each_entry(elem, elem->head, head) {
    if(elem->key == key) {
      return elem;
    }
  }
  
  return NULL;
}


void INIT_HASH (struct hash_table *hash) {

  unsigned int i;

  for(i = 0; i < hash->size; i++) {
    hash->table[i] = NULL; 
  }

}


int insert_hash (void *element, unsigned char type, struct hash_table *hash) {

  struct hash_element *elem = NULL;

  if( type != HASH_A && type != HASH_CHAR ) {
    return HASH_UNKNOWN_TYPE;
  }

  //We first need to create a new hash_element
  elem = allocate_hash_element();

  //Then we need to hash the given element to get a key 
  if( type == HASH_A) {
    elem->key = hash_A((struct A *) element);
  }
  else {
    elem->key = hash_char((char *) element);
    printf("CREATE : cle %d\n",elem->key);
  }

  // We store the data in the element
  elem->data = element;

  //Finally we can store into the hash_table
  if(hash->table[elem->key % hash->size] == NULL) {
    hash->table[elem->key % hash->size] = elem;
    INIT_LIST_HEAD(&(hash->table[elem->key % hash->size]->head));
  }
  else{
    list_add(&(elem->head), &(hash->table[elem->key % hash->size]->head));
  }
  return elem->key;
}

int find_hash (void **element, unsigned int key, struct hash_table *hash) {

  struct hash_element *elem = find_element(key, hash);
  
  if (elem == NULL) {
    return HASH_ELEMENT_NOT_FOUND;
  }

  *element = elem->data;
  return HASH_SUCCESS;
}


int remove_hash (unsigned int key, struct hash_table *hash) {
  //First we search for the element
  struct hash_element *elem = find_element(key, hash);

  if (elem == NULL) {
    return HASH_ELEMENT_NOT_FOUND;
  }

  list_del(&elem->head);
  return HASH_SUCCESS;
}
