/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-lemin-enzo.maltese
** File description:
** Ant functions
*/

#ifndef ANT_H
    #define ANT_H

    #include "ll_void.h"
    #include "stack.h"

    typedef struct ant_s {
        int nbr;
        ll_void_t *current_path;
    } ant_t;

    ant_t *ant_create(int ant_nbr, ll_void_t *path);
    void ant_move(ant_t *ant, int *nb_ant_at_end, int *as_print);
    ant_t **merge_array(ll_stack_t **array);
#endif //ANT_H
