#ifndef HASH_H
#define HASH_H

#include "listechaine.h"

/* Types used to define which type the hash table is working with */
#define HASH_A 1
#define HASH_CHAR 2

/* Return values */
#define HASH_UNKNOWN_TYPE -1
#define HASH_ELEMENT_NOT_FOUND -2
#define HASH_SUCCESS 1

#define cast_type(to_ptr, from_ptr, type) (to_ptr = (type *) from_ptr);

#define to_indice(key, size_hash) (key % size_hash);

struct hash_element {
  unsigned int key;
  void *data;
  struct list_head head;
};


struct hash_table {

  unsigned int size;
  struct hash_element **table;

};


struct A {

  unsigned int id;

};


/** INIT_HASH
 * This function will initialize the given hash table 
 */
void INIT_HASH (struct hash_table *hash);


/** insert
 * This function will add the <element> in the hash table
 * the <type> is the type of the element to insert and 
 * can be either "HASH_A" or "HASH_CHAR"
 * Return value : HASH_UNKNOWN_TYPE, the hash_key of the given element in the hash table
 */
int insert_hash (void *element, unsigned char type, struct hash_table *hash);


/** remove 
 * This function will search for the <key> and remove it from the hash table
 * the <type> is the type of the element to remove and 
 * can be either "HASH_A" or "HASH_CHAR"
 * Return value : HASH_UNKNOWN_TYPE, HASH_ELEMENT_NOT_FOUND, HASH_SUCCESS
 */
int remove_hash (unsigned int key, struct hash_table *hash);


/** find
 * This function will search for the <key> and put into <element> the result
 * the <type> is the type of the element to find and
 * can be either "HASH_A or "HASH_CHAR"
 * Return value : HASH_UNKNOWN_TYPE, HASH_ELEMENT_NOT_FOUND, HASH_SUCCESS
 * In case of HASH_UNKNOWN_TYPE or HASH_ELEMENT_NOT_FOUND
 */
int find_hash (void **element, unsigned int key, struct hash_table *hash);

#endif
