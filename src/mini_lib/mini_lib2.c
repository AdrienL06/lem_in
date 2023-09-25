/*
** EPITECH PROJECT, 2023
** lem_in
** File description:
** mini_lib2
*/

#include <stdlib.h>
#include <unistd.h>
#include "mini_lib.h"

/**
* @brief Computes the length of a null-terminated array of strings.
* @param arr The array of strings to compute the length of.
* @return The number of strings in the array, excluding the null-terminating
*  string.
*/
int my_arrlen(char **arr)
{
    int result = 0;

    for (int i = 0; arr[i]; i++)
        result++;
    return result;
}

/**
* @brief Frees the memory allocated for a 2D array of strings, with an option
*  to free the array itself.
* @param arr The array to free.
* @param flag Determines whether to free the entire array or just the strings.
* @param return_value The value to return after freeing the memory.
* @return The specified return value.
*/
int free_arr2d(char **arr, int flag, int return_value)
{
    if (!arr)
        return return_value;
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    if (flag == FREE_ALL)
        free(arr);
    return return_value;
}

/**
 * @brief Compares two strings. This function compares the two null-terminated
 *  strings `s1` and `s2`.
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @return An integer less than, equal to, or greater than zero if `s1` is
 *  found, respectively, to be less than, to match, or be greater than `s2`.
 */
int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i])
            break;
        i++;
    }
    return s1[i] - s2[i];
}

/**
 * @brief Prints an integer to the standard output.
 *  This function prints the given integer to the standard output. If the
 *  integer is negative, a '-' sign is printed before the number. The function
 *  returns 0 on success.
 * @param nb The integer to print.
 * @return 0.
 */
int my_put_nbr(int nb)
{
    char c;

    if (nb == -2147483648)
        return (int)write(1, "-2147483648", 11);
    if (nb < 0) {
        nb *= -1;
        write(1, "-", 1);
    }
    if (nb >= 10)
        my_put_nbr(nb / 10);
    c = (char)('0' + nb % 10);
    write(1, &c, 1);
    return 0;
}
