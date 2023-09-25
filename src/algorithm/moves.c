/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** Ant Moves functions
*/

#include <unistd.h>
#include <stdlib.h>
#include "ll_void.h"
#include "anthill.h"
#include "ant.h"

/**
* @brief Move the current linked list head to the start of the list.
* @param head The linked list head.
*/
static void llv_goto_start(ll_void_t **head)
{
    for (; (*head)->prev; *head = (*head)->prev);
}

/**
* @brief Get the list of moves for each ant.
* @param hill The anthill structure.
* @param curr_routes The current list of routes for ants.
* @return ll_stack_t** The list of moves for each ant.
*/
ll_stack_t **get_ant_moves(anthill_t *hill, ll_void_t *curr_routes)
{
    int nb_of_routes = llv_len(curr_routes);
    ll_stack_t **ants_mv = malloc(sizeof(ll_stack_t *) * (nb_of_routes + 1));

    for (int i = 0; i < nb_of_routes + 1; ants_mv[i] = NULL, i++);
    llv_add(&ants_mv[0], ant_create(1, curr_routes->data));
    for (int ant_nbr = 2, route_i = 0; ant_nbr <= hill->ants_nbr; ant_nbr++) {
        llv_add(&ants_mv[route_i], ant_create(ant_nbr, curr_routes->data));
        if (route_i + 1 < nb_of_routes &&
            llv_len(curr_routes->data) + llv_len(ants_mv[route_i]) >
            llv_len(curr_routes->next->data) + llv_len(ants_mv[route_i + 1])) {
            route_i++;
            curr_routes = curr_routes->next;
            continue;
        } if (route_i + 1 >= nb_of_routes - 1) {
            route_i = 0;
            llv_goto_start(&curr_routes);
        }
    }
    return ants_mv;
}

/**
* @brief Print the moves for all ants.
* @param hill The anthill structure.
* @param all_routes The list of all possible routes.
* @param ant_queue The list of ants to move.
*/
void print_move(anthill_t *hill, ll_void_t **all_routes, ant_t **ant_queue)
{
    int nb_ant_at_end = 0;

    while (nb_ant_at_end != hill->ants_nbr) {
        for (int i = 0, as_print = 0; ant_queue[i]; i++)
            ant_move(ant_queue[i], &nb_ant_at_end, &as_print);
        write(1, "\n", 1);
    }
    for (int i = 0; ant_queue[i]; i++)
        free(ant_queue[i]);
    free(ant_queue);
    free(all_routes);
}
