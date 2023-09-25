/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** hashmap1
*/

#include <stdlib.h>
#include "mini_lib.h"
#include "hashmap.h"

/**
* @brief Compare two nodes based on their keys. If the keys are equal, the
*  new node is freed.
* @param new_node Pointer to the new node to compare.
* @param other_node Pointer to the other node to compare.
* @return 1 if the keys are equal, 0 otherwise.
*/
int compare_nodes(bucket_t *new_node, bucket_t *other_node)
{
    if (my_strcmp(new_node->key, other_node->key) == 0) {
        free(new_node->key);
        free(new_node);
        return 1;
    }
    return 0;
}

/**
* @brief Set a node in the hashmap. It calculates the hash value of
*  the node's name and sets the node in the corresponding bucket of the
*  hashmap's array.
* @param hashmap Pointer to the hashmap.
* @param node Pointer to the node to set.
*/
void hashmap_set(hashmap_t *hashmap, node_t *node)
{
    unsigned int key_hash = hash_str(node->name, hashmap->capacity);
    bucket_t *curr = hashmap->array[key_hash];

    for (; curr->next; curr = curr->next);
    curr->node = node;
}

/**
* @brief Gets a node from the hashmap based on its key. Searches for the
*  node in the linked list associated with the bucket corresponding to the
*  hash value of the key.
* @param hashmap Pointer to the hashmap
* @param key Key of the node to get
* @return Pointer to the node if found, NULL otherwise
*/
node_t *hashmap_get(hashmap_t *hashmap, char *key)
{
    unsigned int key_hash = hash_str(key, hashmap->capacity);
    bucket_t *curr = hashmap->array[key_hash];

    for (; curr; curr = curr->next)
        if (my_strcmp(key, curr->node->name) == 0)
            break;
    if (!curr)
        return NULL;
    return curr->node;
}
