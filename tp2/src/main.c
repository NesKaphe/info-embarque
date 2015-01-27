#include "listechaine.h"
#include "hash.h"
#include <stdio.h>

// To test the lists
struct integer_list {
  int integer;
  struct list_head head;
};

int main(void) {

  //Definitions to test the lists
  struct integer_list e1,e2,e3,e4;
  struct integer_list *cur; //to iterate over the list


  //Definitions to test the hash table
  struct hash_element *tab[16];
  struct hash_table hash= {16, tab};

  struct A a1,a2,a3;
  a1.id = 22;
  a2.id = 34;
  a3.id = 40;
  char *c1 = "Alain";
  char *c2 = "Albert";

  unsigned int k[5] = {0};

  void *search_elem = NULL;

  INIT_HASH(&hash);
  k[0] = insert_hash((void *)c1, HASH_CHAR, &hash);
  k[1] = insert_hash((void *)c2, HASH_CHAR, &hash);
  k[2] = insert_hash((void *)&a1, HASH_A, &hash);
  k[3] = insert_hash((void *)&a2, HASH_A, &hash);
  k[4] = insert_hash((void *)&a3, HASH_A, &hash);


  //HASH_TEST
  printf("Test de la table de hash\n");
  printf("Recherche de clé : %d (char) =>", k[1]);
  if(find_hash(&search_elem, k[1], &hash) == HASH_SUCCESS) {
    printf("%s\n", (char *)search_elem);
  }
  printf("Recherche de clé : %d (struct A) =>", k[3]);
  if(find_hash(&search_elem, k[3], &hash) == HASH_SUCCESS) {
    printf(" id = %d\n", ((struct A*)search_elem)->id);
  }

  printf("suppression de clé : %d", k[0]);
  if(remove_hash(k[0], &hash) == HASH_SUCCESS) {
    printf(" Element trouvé et supprimé \n");
  }

  // LIST TEST
  printf("Test des listes\n");
  e1.integer = 5;
  e2.integer = 6;
  e3.integer = 8;
  e4.integer = 9;

  //We'll do the list like this : e1->e2->e3->e4
  INIT_LIST_HEAD (&(e1.head));
  list_add(&(e2.head), &(e1.head));
  list_add(&(e3.head), &(e2.head));
  list_add(&(e4.head), &(e3.head));

  //We'll print the list on screen with list_for_each_entry
  cur = &e1;
  printf("%d",cur->integer);
  list_for_each_entry(cur, e1.head, head) {
    printf(" - %d", cur->integer);
  }
  printf("\n");


  
  return 0;
}

//Temps total pour faire la partie 1 => 1h30
