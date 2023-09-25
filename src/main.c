/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** main
*/

#include <stdlib.h>
#include <unistd.h>
#include "mini_lib.h"
#include "graph.h"
#include "lem_in.h"
#include "stack.h"
#include "algorithm.h"

/**
* @brief Frees the memory allocated for the anthill structure and its contents.
* @param file_contents The 2D array of file contents.
* @param hill The anthill structure to free.
* @param return_value The return value to be returned by the function.
* @return Returns the given return value.
*/
static int free_memory(char **file_contents, anthill_t *hill, int return_value)
{
    free_arr2d(file_contents, FREE_ALL, 0);
    if (hill) {
        hashmap_free(hill->all_rooms);
        lls_free(hill->all_tunnels, true);
        free(hill);
    }
    return return_value;
}

/**
* @brief Initializes a new anthill structure and sets its fields to default
*  values.
* @return Returns a pointer to the newly created anthill structure.
*/
static anthill_t *init_anthill(void)
{
    anthill_t *anthill = malloc(sizeof(anthill_t));

    anthill->ants_nbr = -1;
    anthill->hasStart = false;
    anthill->hasEnd = false;
    anthill->all_rooms = NULL;
    anthill->all_tunnels = NULL;
    anthill->start = NULL;
    anthill->end = NULL;
    anthill->first_room_display = NULL;
    anthill->ignore_direct_path = false;
    return anthill;
}

/**
* @brief This function is the init main function of the entire parsing of the
*  file given.
* @param file_contents The 2D array of file contents to init.
* @param hill The anthill structure to init.
* @return Returns 0 on success, 84 otherwise.
*/
static int init_parsing(anthill_t **hill, char ***file_contents)
{
    int return_value = 0;

    (*file_contents) = load_file();
    if (!(*file_contents))
        return 84;
    (*hill) = init_anthill();
    delete_comments((*file_contents));
    return_value = parse_file((*hill),(*file_contents));
    display_hill_info((*hill));
    write(1, "#moves\n", 7);
    return return_value;
}

/**
 * @author  Enzo Maltese
 * @author  Virgile Legros
 * @author  Adrien Lachambre
 * @date    2023
 */
int main(int argc, UNUSED char **argv)
{
    char **file_contents = NULL;
    anthill_t *hill = NULL;

    if (argc != 1)
        return 84;
    init_parsing(&hill, &file_contents);
    if (!hill || !hill->hasStart || !hill->hasEnd)
        return free_memory(file_contents, hill, 0);
    ll_void_t *all_routes = find_all_routes(hill);
    if (all_routes != NULL) {
        ll_stack_t **ants_mv = get_ant_moves(hill, all_routes);
        print_move(hill, (ll_void_t **) llv_to_array(all_routes, true),
            merge_array(ants_mv));
    }
    free_all_routes(all_routes);
    return free_memory(file_contents, hill, 0);
}
