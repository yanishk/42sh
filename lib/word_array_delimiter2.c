/*
** EPITECH PROJECT, 2022
** my_str_to_word_array.c
** File description:
** pool day08
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

int is_delimiter(char c, char *delim)
{
    for (int i = 0; delim[i] != '\0'; i++) {
        if (c == delim[i])
            return (0);
    }
    return (1);
}

int cut_str(char const *str, char *delim)
{
    int nb_of_spaces = 0; int check1 = 2; int check2 = 2;
    for (int i = 0; str[i] != '\0'; i++) {
        check1 = is_delimiter(str[i], delim);
            if (i > 0)
            check2 = is_delimiter(str[i - 1], delim);
        if (check1 == 0 && check2 == 1)
            nb_of_spaces += 1;
    }
    int last_space = 0;
    check2 = 2;
    for (int i = 0; str[i] != '\0'; i++) {
        check1 = is_delimiter(str[i], delim);
        if (i > 0)
            check2 = is_delimiter(str[i - 1], delim);
        if (check1 == 0 && check2 == 1)
            last_space += 1;
        if (last_space == nb_of_spaces)
            return (i);
    }
    return (0);
}

int check_character(char const *str, char *delim, int cut_here)
{
    int count_w = 0;
    int check2 = 2;

    for (int i = 0; str[i] != '\0'; i++) {
        int check1 = is_delimiter(str[i], delim);
        if (i > 0)
            check2 = is_delimiter(str[i - 1], delim);
        if (check1 == 0 && check2 == 1
        && i != 0 && i < cut_here) {
            count_w += 1;
        }
    }
    return (count_w);
}
