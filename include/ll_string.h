/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-lemin-enzo.maltese
** File description:
** ll_string
*/

#ifndef LL_STRING_H_
    #define LL_STRING_H_

    #include <stdbool.h>

    typedef struct ll_string_s {
        char *data;
        struct ll_string_s *next;
        struct ll_string_s *prev;
    } ll_string_t;

    void lls_free(ll_string_t *head, bool free_str);
    int lls_len(ll_string_t *head);
    void lls_add(ll_string_t **head, char *data, bool dup_data);
#endif /* !LL_STRING_H_ */
