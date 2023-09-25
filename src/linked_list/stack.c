/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** Stack wrapper ll_void
*/

#include <stdlib.h>
#include "graph.h"
#include "stack.h"

/**
* @brief Pushes a node onto the top of a linked list stack.
* @param stack Pointer to a pointer to the head of the stack.
* @param node Pointer to the node to be pushed onto the stack.
*/
inline void stack_push(ll_stack_t **stack, node_t *node)
{
    llv_add(stack, node);
}

/**
* @brief Pops the top node off a linked list stack.
* @param stack Pointer to a pointer to the head of the stack.
* @return Pointer to the node that was popped off the stack.
*/
node_t *stack_pop(ll_stack_t **stack)
{
    node_t *pop_node = (*stack)->data;
    ll_void_t *to_free = *stack;

    *stack = (*stack)->next;
    free(to_free);
    return pop_node;
}
