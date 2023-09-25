/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-lemin-enzo.maltese
** File description:
** mini_lib
*/

#ifndef MINI_LIB_H_
    #define MINI_LIB_H_

    #include "ll_void.h"

    enum {FREE_ALL, FREE_PARTIAL};

    int my_strlen(char *str);
    char *my_strdup(char *str);
    int my_strncmp(const char *s1, const char *s2, int n);
    int my_atoi(char *str, char *endptr);
    int is_char_in_str(char c, const char *str);
    char **my_str_to_word_array(char *str, const char *delim);
    int my_arrlen(char **arr);
    int free_arr2d(char **arr, int flag, int return_value);
    int my_strcmp(char const *s1, char const *s2);
    int my_put_nbr(int nb);
    char *my_strcat_delim(char *left, char *delim, char *right);
    void **llv_to_array(ll_void_t *list, bool inverse);
#endif /* !MINI_LIB_H_ */
