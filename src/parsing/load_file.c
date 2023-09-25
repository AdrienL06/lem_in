/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** load_file
*/

#include <stdio.h>
#include <stdlib.h>
#include "ll_string.h"
#include "lem_in.h"

/**
* @brief Convert a linked list of strings to a 2D array.
*  This function iterates over a linked list of strings and copies each string.
*  into a specific index of a 2D array.
* @param head Pointer to the first node of the linked list.
* @param array Pointer to the 2D array to store the strings.
* @param index Index of the last row of the 2D array to start copying into.
*/
static void convert_ll_to_arr2d(ll_string_t *head, char **array, int index)
{
    for (ll_string_t *curr = head; curr; curr = curr->next) {
        array[index - 1] = curr->data;
        index--;
    }
}

/**
* @brief Load a file from standard input and return its contents as an array of
*  strings. The function reads each line from standard input and adds it to a
*  linked list. The contents of the linked list are then converted into an
*  array of strings and returned.
* @return An array of strings containing the contents of the file read from
*  standard input, or NULL if there was an error or the file was empty.
*/
char **load_file(void)
{
    char **result = NULL;
    int malloc_size;
    ll_string_t *contents = NULL;
    char *lineptr = NULL;
    size_t n = 0;

    for (ssize_t rbytes = 0; (rbytes = getline(&lineptr, &n, stdin)) != EOF;) {
        if (lineptr[rbytes - 1] == '\n')
            lineptr[rbytes - 1] = '\0';
        lls_add(&contents, lineptr, true);
    }
    free(lineptr);
    malloc_size = lls_len(contents);
    if (malloc_size == 0)
        return NULL;
    result = malloc(sizeof(char*) * (malloc_size + 1));
    result[malloc_size] = NULL;
    convert_ll_to_arr2d(contents, result, malloc_size);
    lls_free(contents, false);
    return result;
}
