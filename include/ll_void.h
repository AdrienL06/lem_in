/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-lemin-enzo.maltese
** File description:
** ll_void
*/

#ifndef LL_VOID_H_
    #define LL_VOID_H_

    #include <stdbool.h>

    typedef struct ll_void_s {
        void *data;
        struct ll_void_s *next;
        struct ll_void_s *prev;
        int len;
    } ll_void_t;

    void llv_add(ll_void_t **head, void *data);
    void llv_free(ll_void_t *head);
    int llv_len(ll_void_t *head);
#endif /* !LL_VOID_H_ */
