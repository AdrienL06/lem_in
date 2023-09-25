/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** mini_lib
*/

#include <stdlib.h>
#include "mini_lib.h"

/**
* @brief Computes the length of a given string.
* @param str The string to compute the length of.
* @return The length of the string.
*/
int my_strlen(char *str)
{
    int result = 0;

    for (int i = 0; str[i]; i++)
        result++;
    return result;
}

/**
* @brief Allocates a new string, copies the contents of a given string
*  to it, and returns a pointer to the new string.
* @param str The string to duplicate.
* @return A pointer to the new string.
*/
char *my_strdup(char *str)
{
    char *result = malloc(sizeof(char) * (my_strlen(str) + 1));
    int index = 0;

    for (; str[index]; index++)
        result[index] = str[index];
    result[index] = '\0';
    return result;
}

/**
* @brief Compares the first n characters of two strings.
* @param s1 The first string to compare.
* @param s2 The second string to compare.
* @param n The maximum number of characters to compare.
* @return An integer less than, equal to, or greater than zero if s1 is found,
*  respectively, to be less than, to match, or be greater than s2.
*/
int my_strncmp(const char *s1, const char *s2, int n)
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0' && i < n - 1) {
        if (s1[i] != s2[i])
            break;
        i++;
    }
    return s1[i] - s2[i];
}

/**
* @brief Converts a string to an integer.
* @param str The string to convert.
* @param endptr A pointer to a character that will be set to the first
*  character not converted if the entire string is not converted.
* @return The integer value of the string, or 0 if the string is not a
*  valid integer.
*/
int my_atoi(char *str, char *endptr)
{
    int result = 0;
    int i = 0;
    int negative_coeff = *str == '-' ? -1 : 1;

    if (my_strncmp(str, "-2147483648", 12) == 0) {
        *endptr = str[my_strlen(str)];
        return -2147483648;
    }
    *str == '-' ? str++ : 0;
    for (; str[i] != '\0' && str[i] != '\n'; i++) {
        if (str[i] < '0' || str[i] > '9')
            break;
        result = result * 10 + (str[i] - '0');
        if (result < 0)
            break;
    }
    *endptr = (char)((*str == '\0') ? '-' : str[i]);
    return result * negative_coeff;
}

/**
* @brief Checks if a character is present in a given string.
* @param c The character to search for.
* @param str The string to search in.
* @return 1 if the character is present in the string, 0 otherwise.
*/
inline int is_char_in_str(char c, const char *str)
{
    for (int i = 0; str[i]; i++)
        if (c == str[i])
            return 1;
    return 0;
}
