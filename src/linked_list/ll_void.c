/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** ll_void
*/

#include <stdlib.h>
#include "ll_void.h"

/**
* @brief Add a new element to the beginning of a linked list of void pointers.
* @param head Pointer to the head of the linked list.
* @param data Pointer to the data to be added to the linked list.
*/
void llv_add(ll_void_t **head, void *data)
{
    ll_void_t *new = malloc(sizeof(ll_void_t));
    new->data = data;
    new->next = *head;
    new->prev = NULL;
    if (*head != NULL) {
        new->len = (*head)->len + 1;
        (*head)->prev = new;
    } else
        new->len = 1;
    *head = new;
}

/**
* @brief Free the memory of a linked list of void pointers.
* @param head Pointer to the head of the linked list.
*/
void llv_free(ll_void_t *head)
{
    ll_void_t *to_free = NULL;

    for (ll_void_t *curr = head; curr;) {
        to_free = curr;
        curr = curr->next;
        free(to_free);
    }
}

/**
* @brief Computes the length of a linked list of void pointers.
* @param head the head of the linked list
* @return the length of the linked list
*/
int llv_len(ll_void_t *head)
{
    if (head == NULL)
        return 0;
    return head->len;
}
