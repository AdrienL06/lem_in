/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** routes
*/

#include <stddef.h>
#include "algorithm.h"

/**
* @brief Adds a node to the current path, following the least costly
*  unvisited node.
* @param hill Anthill structure containing the graph and start/end nodes.
* @param pop_node The current node being popped off the stack.
* @param current_path Pointer to the current path being built.
* @param stack Pointer to the stack of nodes to visit.
*/
static void add_node_in_path(anthill_t *hill, node_t *pop_node,
    ll_void_t **current_path, ll_stack_t **stack)
{
    node_t *least_cost_node = NULL;

    for (ll_void_t *ln = pop_node->links; ln; ln = ln->next) {
        if (((node_t *) (ln->data))->isVisited == false &&
            ((node_t *) (ln->data))->isInPath == false &&
            (!hill->ignore_direct_path || (hill->ignore_direct_path &&
            llv_len(*current_path) != 1) ||
            (hill->ignore_direct_path && ln->data != hill->start))) {
            ((node_t *) (ln->data))->isVisited = true;
            least_cost_node == NULL || ((node_t *) (ln->data))->h_cost <
                least_cost_node->h_cost ? least_cost_node = ln->data : 0;
        }
    }
    if (least_cost_node) {
        stack_push(stack, least_cost_node);
        if (least_cost_node != hill->start)
            least_cost_node->isInPath = true;
        llv_add(current_path, least_cost_node);
    }
}

/**
* @brief Finds a new shortest path in the anthill graph using the A* algorithm.
* @param hill Anthill structure containing the graph and start/end nodes.
* @return Pointer to the new shortest path found, or NULL if no new path was
*  found.
*/
static ll_void_t *find_new_shortest_path(anthill_t *hill)
{
    node_t *current_node = hill->end;
    node_t *pop_node;
    ll_stack_t *stack = NULL;
    ll_void_t *current_path = NULL;

    stack_push(&stack, current_node);
    llv_add(&current_path, current_node);
    while (stack) {
        pop_node = stack_pop(&stack);
        pop_node->isVisited = true;
        if (pop_node == hill->start) {
            llv_free(stack);
            return current_path;
        }
        add_node_in_path(hill, pop_node, &current_path, &stack);
    }
    llv_free(current_path);
    return NULL;
}

/**
* @brief Frees the memory allocated for all the routes in a linked list.
* @param all_routes Pointer to the head of the linked list of routes.
*/
void free_all_routes(ll_void_t *all_routes)
{
    for (ll_void_t *curr_route = all_routes; curr_route;
        curr_route = curr_route->next)
        llv_free(curr_route->data);
    llv_free(all_routes);
}

/**
* @brief Determines whether a given path is valid, which means it starts
*  at the start node and ends at the end node of the given anthill.
* @param hill The anthill structure containing the graph and start/end nodes.
* @param path Pointer to the path to be checked.
* @return True if the path is valid, false otherwise.
*/
bool is_path_valid(anthill_t *hill, ll_void_t *path)
{
    ll_void_t *curr = path;

    if (((node_t *)(path->data)) != hill->start)
        return false;
    for (; curr->next; curr = curr->next);
    if (((node_t *)(curr->data)) != hill->end)
        return false;
    return true;
}

/**
* @brief Finds all valid routes between the start and end nodes in the graph.
* @param hill Anthill structure containing the graph and start/end nodes.
* @return A linked list of valid paths, represented as linked lists of nodes,
*  or NULL if no valid paths were found.
*/
ll_stack_t *find_all_routes(anthill_t *hill)
{
    ll_void_t *all_routes = NULL;

    compute_heuristic_cost(hill->end, hill->start, 0);
    for (ll_void_t *current_path = NULL;;) {
        graph_reset_visit_status(hill->all_rooms);
        current_path = find_new_shortest_path(hill);
        if (current_path == NULL)
            break;
        if (llv_len(current_path) == 2)
            hill->ignore_direct_path = true;
        if (is_path_valid(hill, current_path))
            llv_add(&all_routes, current_path);
        else
            llv_free(current_path);
    }
    return all_routes;
}
