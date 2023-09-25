/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-lemin-enzo.maltese
** File description:
** HASHMAP
*/

#ifndef HASHMAP_H
    #define HASHMAP_H

    #include <sys/types.h>
    #include "graph.h"

    typedef struct bucket_s {
        char *key;
        node_t *node;
        struct bucket_s *next;
    } bucket_t;

    typedef struct hashmap_s {
        bucket_t **array;
        unsigned long capacity;
    } hashmap_t;

    hashmap_t *hashmap_init(size_t capacity);
    void hashmap_free(hashmap_t *hashmap);
    unsigned int hash_str(char const *str, unsigned int len_hash_table);
    int hashmap_insert(hashmap_t *hashmap, char *key);
    int compare_nodes(bucket_t *new_node, bucket_t *other_node);
    void hashmap_set(hashmap_t *hashmap, node_t *node);
    node_t *hashmap_get(hashmap_t *hashmap, char *key);
#endif //HASHMAP_H
