/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** graph
*/

#include <stdlib.h>
#include "mini_lib.h"
#include "lem_in.h"

/**
* @brief Creates a new node with the specified parameters and adds it to the
*  specified hashmap.
* @param name The name of the node.
* @param coords The coordinates of the node.
* @param room_type The room type of the node.
* @param hashmap The hashmap to add the node to.
* @return Returns a pointer to the newly created node.
*/
node_t *create_node(char *name, int *coords, enum room_type room_type,
hashmap_t *hashmap)
{
    node_t *new_node = malloc(sizeof(node_t));

    new_node->name = my_strdup(name);
    new_node->x = coords[0];
    new_node->y = coords[1];
    new_node->type = room_type;
    new_node->links = NULL;
    new_node->isPrinted = false;
    new_node->next_print = NULL;
    new_node->isVisited = false;
    new_node->isInPath = false;
    new_node->h_cost = 0;
    new_node->isEmpty = true;
    hashmap_set(hashmap, new_node);
    return new_node;
}

/**
* @brief Creates a tunnel between the two specified nodes.
* @param node1 The first node to link.
* @param node2 The second node to link.
*/
void create_tunnel(node_t *node1, node_t *node2)
{
    llv_add(&node1->links, node2);
    llv_add(&node2->links, node1);
}

/**
* @brief Resets the visit status of all nodes in the given graph to false.
* @param graph_map Pointer to the graph map containing the nodes.
*/
void graph_reset_visit_status(hashmap_t *graph_map)
{
    for (size_t i = 0; i < graph_map->capacity; i++)
        for (bucket_t *curr = graph_map->array[i]; curr; curr = curr->next)
            curr->node->isVisited = false;
}

/**
* @brief Recursively computes the heuristic cost of each node in the graph
*  from the current node to the end node.
* @param end Pointer to the end node.
* @param current Pointer to the current node.
* @param current_cost The cost from the start node to the current node.
*/
void compute_heuristic_cost(node_t *end, node_t *current,
    int current_cost)
{
    if (!current->isVisited) {
        current->h_cost = current_cost;
        current->isVisited = true;
        for (ll_void_t *curr = current->links; curr != NULL; curr = curr->next)
            compute_heuristic_cost(end, curr->data, current_cost + 1);
    }
}
