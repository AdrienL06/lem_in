/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** parsing
*/

#include <stdio.h>
#include "mini_lib.h"
#include "graph.h"
#include "lem_in.h"

/**
* @brief Parses the number of ants in the file contents and updates the
*  anthill struct accordingly.
* @param hill Pointer to the anthill struct.
* @param file_contents Double pointer to an array of strings representing
*  the contents of the input file.
* @param ind Pointer to the current index in the file_contents array.
* @return 0 on success, 84 otherwise.
*/
static int parse_ants_nbr_info(anthill_t *hill, char **file_contents, int *ind)
{
    char **split;
    int nbr;
    char endptr = '\0';

    while (file_contents[*ind] && file_contents[*ind][0] == '\0')
        (*ind)++;
    if (!file_contents[*ind])
        return 84;
    split = my_str_to_word_array(file_contents[*ind], " \t");
    (*ind)++;
    if (my_arrlen(split) != 1)
        return free_arr2d(split, FREE_ALL, 84);
    nbr = my_atoi(split[0], &endptr);
    if (endptr != '\0' || nbr < 0)
        return free_arr2d(split, FREE_ALL, 84);
    hill->ants_nbr = nbr;
    return free_arr2d(split, FREE_ALL, 0);
}

/**
* @brief Parses the contents of the input file and updates the anthill
*  struct accordingly.
* @param hill Pointer to the anthill struct.
* @param file_contents The contents of the input file, split by lines.
* @return 0 on success, 84 otherwise.
*/
int parse_file(anthill_t *hill, char **file_contents)
{
    int ind = 0;
    node_t *previous_room = NULL;

    if (parse_ants_nbr_info(hill, file_contents, &ind) == 84)
        return 84;
    if (parse_rooms(hill, file_contents, &ind, &previous_room) == 84)
        return 84;
    if (!hill->hasStart || !hill->hasEnd)
        return 84;
    if (parse_tunnels(hill, file_contents, ind) == 84)
        return 84;
    return 0;
}
