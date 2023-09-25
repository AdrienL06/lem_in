/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-lemin-enzo.maltese
** File description:
** stack header
*/

#ifndef STACK_H
    #define STACK_H

    #include "ll_void.h"
    #include "graph.h"

    typedef ll_void_t ll_stack_t;
    void stack_push(ll_stack_t **stack, node_t *node);
    node_t *stack_pop(ll_stack_t **stack);
#endif //STACK_H
