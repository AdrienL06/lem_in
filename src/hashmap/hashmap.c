/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** HASHMAP
*/

#include <stdlib.h>
#include "hashmap.h"
#include "mini_lib.h"

/**
* @brief Calculates the hash value for a given string key.
* @param str The string key to calculate the hash value for.
* @param len_hash_table The length of the hash table.
* @return The calculated hash value for the given string key.
*/
unsigned int hash_str(char const *str, unsigned int len_hash_table)
{
    unsigned int hashval;

    for (hashval = 0; *str != '\0'; str++)
        hashval = *str + 31 * hashval;
    return hashval % len_hash_table;
}

/**
* @brief Inserts a new node into the specified bucket.
* @param head The head of the bucket.
* @param key The key to insert.
* @return Returns 0 on success or 1 if the key already exists.
*/
static int bucket_insert(bucket_t **head, char *key)
{
    bucket_t *new_node = malloc(sizeof(bucket_t));
    bucket_t *curr = *head;

    new_node->key = my_strdup(key);
    new_node->next = NULL;
    new_node->node = NULL;
    if (*head == NULL) {
        if (compare_nodes(new_node, *head))
            return 1;
        *head = new_node;
        return 0;
    }
    for (; curr->next; curr = curr->next) {
        if (compare_nodes(new_node, curr->next))
            return 1;
    }
    curr->next = new_node;
    return 0;
}

/**
* @brief Inserts a new key-value pair into the specified hash table.
* @param hashmap The hashmap to insert into.
* @param key The key to insert.
* @return Returns 0 on success, -1 if the key already exists.
*/
int hashmap_insert(hashmap_t *hashmap, char *key)
{
    bucket_t *new_node;
    unsigned int key_hash = hash_str(key, hashmap->capacity);

    if (hashmap->array[key_hash] == NULL) {
        new_node = malloc(sizeof(bucket_t));
        new_node->node = NULL;
        new_node->key = my_strdup(key);
        new_node->next = NULL;
        hashmap->array[key_hash] = new_node;
    } else {
        if (my_strcmp(hashmap->array[key_hash]->key, key) == 0)
            return -1;
        if (bucket_insert(&hashmap->array[key_hash], key))
            return -1;
    }
    return 0;
}

/**
* @brief Initializes a new hashmap with the specified capacity.
* @param capacity The capacity of the hashmap.
* @return Returns a pointer to the newly created hashmap.
*/
hashmap_t *hashmap_init(size_t capacity)
{
    hashmap_t *new_hashmap = malloc(sizeof(hashmap_t));

    new_hashmap->capacity = capacity;
    new_hashmap->array = malloc(sizeof(bucket_t *) * capacity);
    for (size_t i = 0; i < capacity; i++)
        new_hashmap->array[i] = NULL;
    return new_hashmap;
}

/**
* @brief Frees the memory associated with the specified hashmap.
* @param hashmap The hashmap to free.
*/
void hashmap_free(hashmap_t *hashmap)
{
    bucket_t *to_free = NULL;

    if (!hashmap)
        return;
    for (unsigned int i = 0; i < hashmap->capacity; i++) {
        if (!hashmap->array[i])
            continue;
        for (bucket_t *curr = hashmap->array[i]; curr;) {
            to_free = curr;
            free(curr->key);
            curr->node ? free(curr->node->name) : 0;
            curr->node ? llv_free(curr->node->links) : 0;
            free(curr->node);
            curr = curr->next;
            free(to_free);
        }
    }
    free(hashmap->array);
    free(hashmap);
}
