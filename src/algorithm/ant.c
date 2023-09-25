/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** ant
*/

#include <unistd.h>
#include <stdlib.h>
#include "ant.h"
#include "mini_lib.h"

/**
* @brief Merge an array of linked list stacks into a single array.
* @param array The array of linked list stacks.
* @return ant_t** The new array containing all the ants.
*/
ant_t **merge_array(ll_stack_t **array)
{
    ll_void_t *new_queue = NULL;
    ant_t **new_ant_array = NULL;
    ll_void_t *curr_ant = NULL;

    for (int i = 0; array[i]; i++)
        while (array[i])
            llv_add(&new_queue, stack_pop(&array[i]));
    free(array);
    new_ant_array = malloc(sizeof(ant_t *) * (llv_len(new_queue) + 1));
    curr_ant = new_queue;
    for (int i = 0; i < llv_len(new_queue); i++, curr_ant = curr_ant->next)
        new_ant_array[i] = curr_ant->data;
    new_ant_array[llv_len(new_queue)] = NULL;
    llv_free(new_queue);
    return new_ant_array;
}

/**
* @brief Create a new ant with the given number and path.
* @param ant_nbr The number of the ant.
* @param path The linked list representing the ant's path.
* @return ant* The newly created ant.
*/
ant_t *ant_create(int ant_nbr, ll_void_t *path)
{
    ant_t *new_ant = malloc(ant_nbr * sizeof(ant_t));

    new_ant->nbr = ant_nbr;
    new_ant->current_path = path;
    return new_ant;
}

/**
* @brief Move the ant to the next node on its path if possible.
* @param ant The ant to move.
* @param nb_ant_at_end The number of ants that have reached the end.
* @param as_print Whether to print the movement of the ant or not.
*/
void ant_move(ant_t *ant, int *nb_ant_at_end, int *as_print)
{
    if (ant->current_path->next != NULL &&
        ((node_t *)(ant->current_path->next->data))->isEmpty) {
        *as_print ? write(1, " P", 2) : write(1, "P", 1);
        my_put_nbr(ant->nbr);
        write(1, "-", 1);
        write(1, ((node_t *) (ant->current_path->next->data))->name,
            my_strlen(((node_t *) (ant->current_path->next->data))->name));
        ((node_t *) (ant->current_path->data))->isEmpty = true;
        ant->current_path = ant->current_path->next;
        if (ant->current_path->next)
            ((node_t *) (ant->current_path->data))->isEmpty = false;
        if (ant->current_path->next == NULL)
            (*nb_ant_at_end)++;
        *as_print = 1;
    }
}
