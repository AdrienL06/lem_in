/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-lemin-enzo.maltese
** File description:
** algo
*/

#ifndef ALGORITHM_H
    #define ALGORITHM_H
    #include "lem_in.h"
    #include "stack.h"
    #include "anthill.h"
    #include "ant.h"

    //routes
    ll_stack_t *find_all_routes(anthill_t *hill);
    void free_all_routes(ll_void_t *all_routes);

    //moves
    ll_void_t **get_ant_moves(anthill_t *hill, ll_void_t *curr_routes);
    void print_move(anthill_t *hill, ll_void_t **all_routes,
        ant_t **ant_queue);
#endif //ALGORITHM_H
