/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** tunnels_parse
*/

#include <unistd.h>
#include <stdbool.h>
#include "lem_in.h"
#include "mini_lib.h"

/**
* @brief Check if each element in the string array 'split' can be
*  into the hash table 'rooms'.
* @param rooms The hash table to check.
* @param split The string array to check.
* @return 0 if all elements can be inserted into the hash table, 1 otherwise.
*/
int check_valid_room(hashmap_t *rooms, char **split)
{
    for (int i = 0; split[i]; i++)
        if (!hashmap_get(rooms, split[i]))
            return 1;
    return 0;
}

/**
* @brief Parses the tunnels from the given file contents and adds
*  them to the given anthill.
* @param hill The anthill to add the tunnels to.
* @param file_contents The contents of the file to parse.
* @param ind The starting index to parse the file contents from.
* @return 0 on success, 84 otherwise.
*/
int parse_tunnels(anthill_t *hill, char **file_contents,
int ind)
{
    char **split = NULL;

    for (; file_contents && file_contents[ind]; ind++) {
        if (!file_contents[ind][0])
            continue;
        split = my_str_to_word_array(file_contents[ind], "- \t");
        if (my_arrlen(split) != 2)
            return free_arr2d(split, FREE_ALL, 84);
        if (check_valid_room(hill->all_rooms, split))
            return free_arr2d(split, FREE_ALL, 84);
        create_tunnel(hashmap_get(hill->all_rooms, split[0]),
        hashmap_get(hill->all_rooms, split[1]));
        lls_add(&hill->all_tunnels,
            my_strcat_delim(split[0], "-", split[1]), false);
        free_arr2d(split, FREE_ALL, 0);
    }
    return 0;
}
