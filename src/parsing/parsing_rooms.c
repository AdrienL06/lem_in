/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** rooms_parsing
*/

#include <stdlib.h>
#include "lem_in.h"
#include "mini_lib.h"

/**
* @brief Sets the previous room and updates the anthill fields accordingly.
* @param hill Pointer to the anthill struct.
* @param room_type Pointer to the integer representing the type of the
*  current room.
* @param splitted_data Pointer to the array of strings containing the data
*  of the current room.
* @return 0 on success, 84 otherwise.
*/
static int finish_read_room_info(anthill_t *hill, int *room_type,
char **splitted_data)
{
    if (*room_type == START) {
        if (hill->hasStart)
            return free_arr2d(splitted_data, FREE_ALL, 84);
        hill->hasStart = true;
        *room_type = OTHER;
    }
    if (*room_type == END) {
        if (hill->hasEnd)
            return free_arr2d(splitted_data, FREE_ALL, 84);
        hill->hasEnd = true;
        *room_type = OTHER;
    }
    return free_arr2d(splitted_data, FREE_ALL, 0);
}

/**
* @brief Sets the previous room and updates the anthill fields accordingly
* @param hill Pointer to the anthill struct
* @param new_room Pointer to the newly created node for the room
* @param previous_room Pointer to the pointer of the previous room node
*/
static void set_previous_room(anthill_t *hill, node_t *new_room,
node_t **previous_room)
{
    new_room->type == START ? hill->start = new_room : 0;
    new_room->type == END ? hill->end = new_room : 0;
    if (*previous_room == NULL)
        hill->first_room_display = new_room;
    else
        (*previous_room)->next_print = new_room;
    *previous_room = new_room;
}

/**
* @brief Parses a string of data representing a room, creates a node for it,
*  and adds it to the anthill.
* @param hill The anthill to add the new room to.
* @param data The string of data representing the room.
* @param room_type The type of the room being added.
* @param previous_room A pointer to the previous room in the list.
* @return 0 on success, 84 otherwise.
*/
static int read_room_info(anthill_t *hill, char *data, int *room_type,
node_t **previous_room)
{
    char **splitted_data = my_str_to_word_array(data, " \t");
    char endptr;
    int x, y;
    node_t *new_room;

    if (my_arrlen(splitted_data) != 3)
        return free_arr2d(splitted_data, FREE_ALL, 84);
    x = my_atoi(splitted_data[1], &endptr);
    if (endptr != '\0')
        return free_arr2d(splitted_data, FREE_ALL, 84);
    y = my_atoi(splitted_data[2], &endptr);
    if (endptr != '\0')
        return free_arr2d(splitted_data, FREE_ALL, 84);
    if (hashmap_insert(hill->all_rooms, splitted_data[0]) == -1)
        return free_arr2d(splitted_data, FREE_ALL, 84);
    new_room = create_node(splitted_data[0], (int[2]){x, y}, *room_type,
    hill->all_rooms);
    set_previous_room(hill, new_room, previous_room);
    return finish_read_room_info(hill, room_type, splitted_data);
}

/**
* @brief Calculates the number of rooms in the given file contents.
* @param file_contents The contents of the file to calculate
*  the number of rooms from.
* @return The number of rooms in the file.
*/
static int get_rooms_nbr(char **file_contents)
{
    int result = 0;
    int return_value;
    int room_type = OTHER;

    for (int i = 1; file_contents && file_contents[i]; i++) {
        return_value = treat_special_cases(file_contents[i], &room_type);
        if (return_value == CONTINUE)
            continue;
        if (return_value == BREAK)
            break;
        result++;
    }
    room_type = OTHER;
    return result;
}

/**
* @brief Parses the rooms from the given file contents and adds them
*  to the given anthill.
* @param hill The anthill to add the rooms to.
* @param file_contents The contents of the file to parse.
* @param ind A pointer to the starting index to parse the file contents from.
* @param previous_room A pointer to the previous room in the linked
*  list, used to add tunnels.
* @return 0 on success, 84 otherwise.
*/
int parse_rooms(anthill_t *hill, char **file_contents, int *ind,
node_t **previous_room)
{
    int return_value;
    int room_type = OTHER;

    hill->all_rooms = hashmap_init(get_rooms_nbr(file_contents));
    for (; file_contents && file_contents[*ind]; (*ind)++) {
        return_value = treat_special_cases(file_contents[*ind], &room_type);
        if (return_value == CONTINUE)
            continue;
        if (return_value == BREAK)
            break;
        if ((room_type == START && hill->start)
        || (room_type == END && hill->end))
            break;
        if (read_room_info(hill, file_contents[*ind], &room_type, previous_room)
        == 84)
            return 84;
    }
    return 0;
}
