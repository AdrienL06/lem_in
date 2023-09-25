/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** ll_string
*/

#include <stdlib.h>
#include <stdbool.h>
#include "ll_string.h"
#include "mini_lib.h"

/**
* @brief Frees the memory of a linked list of strings, optionally freeing
*  the string data as well.
* @param head the head of the linked list
* @param free_str if true, also free the string data for each node
*/
void lls_free(ll_string_t *head, bool free_str)
{
    ll_string_t *to_free = NULL;

    for (ll_string_t *curr = head; curr;) {
        to_free = curr;
        curr = curr->next;
        if (free_str)
            free(to_free->data);
        free(to_free);
    }
}

/**
* @brief Adds a new node with the given string data to the head of a linked
*  list of strings.
* @param head a pointer to the head of the linked list
* @param data the string data for the new node
* @param dup_data if true, duplicate the string data with `my_strdup()`,
*  otherwise use the original pointer
*/
void lls_add(ll_string_t **head, char *data, bool dup_data)
{
    ll_string_t *new = malloc(sizeof(ll_string_t));
    if (dup_data)
        new->data = my_strdup(data);
    else
        new->data = data;
    new->next = *head;
    new->prev = NULL;
    if (*head != NULL)
        (*head)->prev = new;
    *head = new;
}

/**
* @brief Computes the length of a linked list of strings.
* @param head the head of the linked list
* @return the length of the linked list
*/
int lls_len(ll_string_t *head)
{
    int result = 0;

    for (ll_string_t *curr = head; curr; curr = curr->next)
        result++;
    return result;
}
