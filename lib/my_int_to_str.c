/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"

static int size_to_malloc(int nb)
{
    int count = 0;
    while (nb > 0) {
        nb /= 10;
        count += 1;
    }
    return count;
}

char *my_int_to_str(int nb)
{
    int size = size_to_malloc(nb);
    char *str = malloc(sizeof(char) * (size + 1));
    int i = 0;

    if (nb == 0) {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
    while (nb > 0) {
        str[i++] = nb % 10 + '0';
        nb /= 10;
    }
    str[i] = '\0';
    my_revstr(str);
    return (str);
}
