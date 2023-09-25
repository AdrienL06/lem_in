/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** DISPLAY
*/

#include <unistd.h>
#include "lem_in.h"
#include "mini_lib.h"

/**
* @brief Displays the number of ants in the given anthill.
* @param hill The anthill to display the number of ants for.
*/
static void display_antnbr(anthill_t *hill)
{
    write(1, "#number_of_ants\n", 16);
    if (hill->ants_nbr != -1) {
        my_put_nbr(hill->ants_nbr);
        write(1, "\n", 1);
    }
}

/**
* @brief Displays the rooms in the given anthill.
* @param hill The anthill to display the rooms for.
*/
static void display_rooms(anthill_t *hill)
{
    write(1, "#rooms\n", 7);
    for (node_t *curr_room = hill->first_room_display; curr_room;
    curr_room = curr_room->next_print) {
        if (curr_room->type == START)
            write(1, "##start\n", 8);
        if (curr_room->type == END)
            write(1, "##end\n", 6);
        write(1, curr_room->name, my_strlen(curr_room->name));
        write(1, " ", 1);
        my_put_nbr(curr_room->x);
        write(1, " ", 1);
        my_put_nbr(curr_room->y);
        write(1, "\n", 1);
    }
}

/**
* @brief Displays the tunnels in the given anthill.
* @param hill The anthill to display the tunnels for.
*/
static void display_tunnels(anthill_t *hill)
{
    ll_string_t *curr_tunnel = hill->all_tunnels;

    write(1, "#tunnels\n", 9);
    if (!curr_tunnel)
        return;
    for (; curr_tunnel->next; curr_tunnel = curr_tunnel->next);
    for (; curr_tunnel; curr_tunnel = curr_tunnel->prev) {
        write(1, curr_tunnel->data, my_strlen(curr_tunnel->data));
        write(1, "\n", 1);
    }
}

/**
* @brief Displays all the information about the given anthill.
* @param hill The anthill to display information about.
*/
void display_hill_info(anthill_t *hill)
{
    display_antnbr(hill);
    display_rooms(hill);
    display_tunnels(hill);
}
