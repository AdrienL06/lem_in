/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-lemin-enzo.maltese
** File description:
** graph
*/

#ifndef GRAPH_H_
    #define GRAPH_H_

    #include <stdbool.h>
    #include "ll_void.h"
    #include "enums.h"

    typedef struct hashmap_s hashmap_t;

    typedef struct node_s {
        char *name;
        int x, y;
        enum room_type type;
        ll_void_t *links;
        bool isPrinted;
        bool isEmpty;
        bool isVisited;
        bool isInPath;
        int h_cost;
        struct node_s *next_print;
    } node_t;

    node_t *create_node(char *name, int *coords, enum room_type room_type,
    hashmap_t *hashmap);
    void create_tunnel(node_t *node1, node_t *node2);
    void graph_reset_visit_status(hashmap_t *graph_map);
    void compute_heuristic_cost(node_t *end, node_t *current,
        int current_cost);
#endif /* !GRAPH_H_ */
