/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-lemin-enzo.maltese
** File description:
** anthill
*/

#ifndef ANTHILL_H_
    #define ANTHILL_H_

    #include <stdbool.h>
    #include "ll_void.h"
    #include "ll_string.h"
    #include "hashmap.h"

    typedef struct anthill_s {
        int ants_nbr;
        bool hasStart;
        bool hasEnd;
        bool ignore_direct_path;
        hashmap_t *all_rooms;
        ll_string_t *all_tunnels;
        node_t *start;
        node_t *end;
        node_t *first_room_display;
    } anthill_t;

#endif /* !ANTHILL_H_ */
