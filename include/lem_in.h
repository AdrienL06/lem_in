/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-lemin-enzo.maltese
** File description:
** lem_in
*/

#ifndef LEM_IN_H_
    #define LEM_IN_H_

    #include "anthill.h"

    #define UNUSED __attribute__((unused))

    /* parsing */
    char **load_file(void);
    int parse_file(anthill_t *anthill, char **file_contents);
    int treat_special_cases(char *line, int *room_type);
    void delete_comments(char **str);
    int parse_rooms(anthill_t *hill, char **file_contents, int *ind,
    node_t **previous_room);
    int parse_tunnels(anthill_t *hill, char **file_contents, int ind);
    void display_hill_info(anthill_t *hill);

#endif /* !LEM_IN_H_ */
