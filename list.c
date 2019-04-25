// list/list.c
// 
// Implementation for linked list.
//
// <Daniel>

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list_t *list_alloc() { 
    list_t *list = malloc(sizeof(list_t));
    list->head = NULL;
    return list; 
}

void list_free(list_t *l) {
    node_t *traverser;
    for (traverser = l->head; traverser != NULL; ){
        node_t *node_to_free = traverser;
        traverser = traverser->next;
        free(node_to_free);
    }
    free(l);
}

void list_print(list_t *l, char* buffer) {
    node_t *traverser;
    printf("Now in print_list function:");
    for (traverser = l->head; traverser != NULL; traverser = traverser->next){
          printf("%d ", traverser->value);
    }
}


void list_add_to_front(list_t *l, char* key, char* value) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->key = malloc(strlen(key));
    new_node->value = malloec(strlen(value));
    strcpy(new_node->key, key);
    strcpy(new_node->value, value)
    new_node->next = l->head;
    l->head = new_node; 
}

void list_put(list_t *l, char* key, char* value) {
    if ( !list_is_in(l, key) ){
        list_add_to_front(l, key, value);
    }
    else{
        node_t *traverser;
        for (traverser = l->head; traverser != NULL; traverser = traverser->next){
            if (strcmp(key,traverser->key) == 0){
                traverser->value
                break;
            }
        }
    }

}





bool list_is_in(list_t *l, char* key) { 
    bool is_val_in_list = false;
    node_t *traverser;
    for (traverser = l->head; traverser != NULL; traverser = traverser->next){
        if (strcmp(key,traverser->key) == 0){
            is_val_in_list = true;
            break;
        }
    }
    return is_val_in_list; 
}

char* list_get_value_of_key(list_t *l, char* key) {

//     if ( !list_is_in(l, key) ) return value;
    node_t *traverser;
    for (traverser = l->head; traverser != NULL; traverser = traverser->next){
        if (strcmp(key,traverser->key) == 0){
            return traverser->value;
        }
    }
    char* value = malloc(128);
    sprintf(value, "%s not found!", key);
    return value;
}