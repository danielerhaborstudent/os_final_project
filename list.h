// list/list.h
// 
// Interface definition for linked list.
//
// <Daniel>

#include <stdbool.h>


/* Defines the node structure. Each node contains its key and value, and points to the
 * next node in the list. The last element in the list should have NULL as its
 * next pointer. */
struct node {
    char* key;
    char* value;
	struct node *next;
};
typedef struct node node_t;

/* Defines the list structure, which simply points to the first node in the
 * list. */
struct list {
	node_t *head;
};
typedef struct list list_t;

/* Functions for allocating and freeing lists. By using only these functions,
 * the user should be able to allocate and free all the memory required for
 * this linked list library. */
list_t *list_alloc();
void list_free(list_t *l);

/* Prints the list in some format. */
void list_print(list_t *l, char* buffer);



/* Methods for adding to the list. */
void list_add_to_front(list_t *l, char* key, char* value);


/* Checks to see if the given element exists in the list. */
bool list_is_in(list_t *l, char* key);


void list_put(list_t *l, char* key, char* value);
    
    
/* Returns the value at particularly key. */
char* list_get_value_of_key(list_t *l, char* key);
