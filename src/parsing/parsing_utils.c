/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** parsing_utils
*/

#include <stdlib.h>
#include "lem_in.h"
#include "mini_lib.h"

/**
* @brief Treats the special cases that can be encountered in a room's line
* @param line The string representing the line to be checked
* @param room_type Pointer to an integer representing the type of the
*  current room
* @return An integer representing the action to take next:
*  - NONE if no special case is encountered
*  - CONTINUE if the line should be skipped
*  - BREAK if the end of the rooms section is reached
*/
int treat_special_cases(char *line, int *room_type)
{
    if (!line[0])
        return CONTINUE;
    if (is_char_in_str('-', line))
        return BREAK;
    if (!my_strcmp("##start", line) && *room_type == OTHER) {
        *room_type = START;
        return CONTINUE;
    }
    if (!my_strcmp("##end", line) && *room_type == OTHER) {
        *room_type = END;
        return CONTINUE;
    }
    return NONE;
}

/**
* @brief Deletes the comments from the given string array.
* @param str The string array to delete the comments from.
*/
void delete_comments(char **str)
{
    char **cut = NULL;

    for (int i = 0; str[i]; i++) {
        cut = my_str_to_word_array(str[i], " \t");
        if (my_arrlen(cut) == 1 && cut[0] && (!my_strcmp("##start", cut[0])
        || (!my_strcmp("##end", cut[0])))) {
            free(str[i]);
            str[i] = my_strdup(cut[0]);
            free_arr2d(cut, FREE_ALL, 0);
            continue;
        } if (str[i][0] == '\0') {
            free_arr2d(&str[i], FREE_PARTIAL, 0);
            str[i] = NULL;
            free_arr2d(cut, FREE_ALL, 0);
            break;
        }
        for (int c = 0; str[i][c]; c++)
            str[i][c] == '#' ? str[i][c] = '\0' : 0;
        free_arr2d(cut, FREE_ALL, 0);
    }
}
