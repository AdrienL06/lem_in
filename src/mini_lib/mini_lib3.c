/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** mini_lib2
*/

#include <stdlib.h>
#include "mini_lib.h"

/**
* @brief Concatenates three strings with a delimiter between left and
*  right strings.
* @param left The left string.
* @param delim The delimiter string.
* @param right The right string.
* @return A newly allocated string which is the concatenation of the three
*  input strings with the delimiter. It should be freed by the caller when no
*  longer needed.
*/
char *my_strcat_delim(char *left, char *delim, char *right)
{
    char *result = NULL;
    int left_len = my_strlen(left);
    int delim_len = my_strlen(delim);
    int right_len = my_strlen(right);
    int index = 0;

    result = malloc(sizeof(char) * (left_len + delim_len + right_len + 1));
    for (; index < left_len; index++, left++)
        result[index] = *left;
    for (; index < left_len + delim_len; index++, delim++)
        result[index] = *delim;
    for (; index < left_len + delim_len + right_len; index++, right++)
        result[index] = *right;
    result[left_len + delim_len + right_len] = '\0';
    return result;
}

/**
* @brief Convert a linked list of void pointers into a dynamic array of
*  void pointers.
* @param list Pointer to the head of the linked list.
* @param inverse A boolean indicating whether the elements in the array
*  should be in the same order as in the linked list or in reverse order.
* @return A dynamic array of void pointers.
*/
void **llv_to_array(ll_void_t *list, bool inverse)
{
    int list_len = llv_len(list);
    void **array = malloc(sizeof(void *) * (list_len + 1));

    if (inverse)
        for (; list->next; list = list->next);
    for (int i = 0; i < list_len; i++) {
        array[i] = list->data;
        if (inverse)
            list = list->prev;
        else
            list = list->next;
    }
    array[list_len] = NULL;
    return array;
}
