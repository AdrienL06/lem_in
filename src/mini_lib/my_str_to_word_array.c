/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** my_str_to_word_array
*/

#include <stdlib.h>
#include "mini_lib.h"

/**
* @brief Removes consecutive delimiter characters in a string, starting from
*  the given index.
* @param str The string to remove delimiters from.
* @param i Pointer to the index to start removing from. The value of i is
*  updated to the index of the last delimiter character removed.
* @param delim The string of delimiter characters to remove.
*/
static void remove_delimiter(char *str, int *i, const char *delim)
{
    while (is_char_in_str(str[*i + 1], delim))
        (*i)++;
}

/**
* @brief Copies a substring of a given length from a string to a dynamically
*  allocated array of characters.
* @param result Pointer to the array to store the copied substring.
* @param ind Pointer to the index to store the copied substring in the array.
*  The value of ind is updated to the next available index in the array.
* @param size The length of the substring to copy.
* @param string The string to copy the substring from.
*/
static void copy_str(char **result, int *ind, int size, char *string)
{
    result[*ind] = malloc(sizeof(char) * (size + 1));
    result[*ind][size] = '\0';
    for (int i = 0; i < size; i++)
        result[*ind][i] = string[i];
    (*ind)++;
}

/**
* @brief Counts the number of non-empty words in a string, delimited by the
*  characters in a given string.
* @param str The string to count words in.
* @param delim The string of delimiter characters.
* @return The number of non-empty words in the string.
*/
static int get_words_nbr(char *str, const char *delim)
{
    int result = 0;

    for (; is_char_in_str(*str, delim); str++);
    for (int i = 0; str[i]; i++) {
        if ((str[i + 1] == '\0' || is_char_in_str(str[i + 1], delim))
        && !is_char_in_str(str[i], delim)) {
            remove_delimiter(str, &i, delim);
            result++;
        }
    }
    return result;
}

/**
* @brief Splits a string into an array of non-empty words, delimited by the
*  characters in a given string.
* @param str The string to split into words.
* @param delim The string of delimiter characters.
* @return A dynamically allocated array of dynamically allocated strings,
*  each containing a non-empty word from the input string.
*/
char **my_str_to_word_array(char *str, const char *delim)
{
    int words_nbr = get_words_nbr(str, delim);
    char **result = malloc(sizeof(char*) * (words_nbr + 1));

    result[words_nbr] = NULL;
    for (; is_char_in_str(*str, delim); str++);
    for (int i = 0, y = 1, x = 0; str[i]; i++, y++) {
        if ((str[i + 1] == '\0' || is_char_in_str(str[i + 1], delim))
        && !is_char_in_str(str[i], delim)) {
            copy_str(result, &x, y, &str[i - y + 1]);
            remove_delimiter(str, &i, delim);
            y = 0;
        }
    }
    return result;
}
